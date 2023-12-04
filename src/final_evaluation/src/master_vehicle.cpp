/**
 * @file master_vehicle.cpp
 * @author Eunsan Jo (eunsan.mountain@gmail.com)
 * @brief
 * @version 0.1
 * @date 2018-11-28
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "master_vehicle.h"
#include "KusvLane.hpp"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include <cmath>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>

#define PI 3.14159265358979323846 /* pi */

MasterVehicle::MasterVehicle() {
  m_rosPubVehicle_output =
      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
          "vehicle_output", 10);
  m_rosPubMasterVehicle_output =
      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
          "/master_vehicle_output", 10);
  m_rosPubIsCollide = m_rosNodeHandler.advertise<std_msgs::Bool>("/master_vehicle_collision", 10);

  m_rosSubEgoVehicle_output = m_rosNodeHandler.subscribe(
      "/ego/vehicle_output", 10, &MasterVehicle::egoVehicleOutputCallback, this);  
  
  m_vehicle_namespace = ros::this_node::getNamespace();
  m_vehicle_namespace.erase(m_vehicle_namespace.begin()); // Remove "/" in namespace front

  m_rosNodeHandler.param("master_vehicle/init_x", init_x, 0.0);
  m_rosNodeHandler.param("master_vehicle/init_y", init_y, 0.0);
  m_rosNodeHandler.param("master_vehicle/init_yaw", init_yaw, 0.0);
  m_rosNodeHandler.param("master_vehicle/init_speed", init_speed, 0.0);

  m_rosNodeHandler.param("master_vehicle/decelerate_x", m_decelerate_x, 0.0);
  m_rosNodeHandler.param("master_vehicle/decelerate_y", m_decelerate_y, 0.0);
  m_rosNodeHandler.param("master_vehicle/decelerate_speed", m_decelerate_speed, 0.0);

  m_rosNodeHandler.param("master_vehicle/refPath", m_ref_path_param,
                         std::string(""));
  m_rosNodeHandler.param("master_vehicle/laneId", m_laneId_param,
                         std::string("1"));

  m_dDt = 0.0;
  m_dPrevTime = ros::Time::now().toSec();
}

MasterVehicle::~MasterVehicle() {}

void MasterVehicle::initMasterVehicle() {

  m_targetSpeed = init_speed;
  //가장 가까운 점을 찾는다
  double min_distance_sq = std::numeric_limits<double>::max();
  int min_index = 0;
  for (int i = 0; i < m_refLane.point.size(); i++) {
    double dx = init_x - m_refLane.point[i].x;
    double dy = init_y - m_refLane.point[i].y;
    double distance_sq = dx * dx + dy * dy;

    if (distance_sq < min_distance_sq) {
      min_distance_sq = distance_sq;
      min_index = i;
    }
  }
  //그 다음의 인덱스 점의 yaw angle을 구한다.

  int next_index = (min_index + 1) % m_refLane.point.size();
  double init_yaw = atan2(m_refLane.point[next_index].y - init_y,
                          m_refLane.point[next_index].x - init_x);

  this->setInitialState(init_x, init_y, init_yaw, 0);
  isMasterCreated = true;

  // Initialize variable
  m_prev_vehicleOutput.velocity = 0.0;
}

void MasterVehicle::checkEgoVehicleStarted(){
  // Use ego vehicle velocity for check vehicle departure
  if (m_prev_vehicleOutput.velocity != m_egoVehicleState.velocity){
    isEgoStarted = true;
  }
  m_prev_vehicleOutput = m_egoVehicleState;
}


void MasterVehicle::setInitialState(double x, double y, double yaw,
                                    double speed_mps) {
  m_dX = x;
  m_dY = y;
  m_dYaw = yaw;
  m_dVehicleVel_ms = speed_mps;
}

void MasterVehicle::loadLaneData() {

  SKusvLanes csvRefLaneImport;
  csvRefLaneImport.ImportKusvLaneCsvFile(m_ref_path_param);

  m_refLane.frame_id = "world";
  m_refLane.point.clear();
  m_refLane.id = m_laneId_param;

  for (auto i_lane = 0; i_lane < csvRefLaneImport.m_vecKusvLanes.size();
       i_lane++) {

    if (m_laneId_param ==
        std::to_string(csvRefLaneImport.m_vecKusvLanes[i_lane].m_nLaneID)) {

      for (auto i_point = 0;
           i_point <
           csvRefLaneImport.m_vecKusvLanes[i_lane].m_vecKusvLanePoint.size();
           i_point++) {
        autonomous_msg::PointWithArclength point;
        point.x = csvRefLaneImport.m_vecKusvLanes[i_lane]
                      .m_vecKusvLanePoint[i_point]
                      .m_dPtX_m;
        point.y = csvRefLaneImport.m_vecKusvLanes[i_lane]
                      .m_vecKusvLanePoint[i_point]
                      .m_dPtY_m;
        m_refLane.point.push_back(point);
      }
    }
  }
}

bool MasterVehicle::simVehicleModel() {
  // Calculate dt_ by dividing the previous time and the current time
  m_dDt = ros::Time::now().toSec() - m_dPrevTime;
  if (m_dDt <= 0.0) {
    return false;
  }
  m_dPrevTime = ros::Time::now().toSec();
  if (isMasterCreated == true) {
    m_dVehicleVel_ms = simVehicleMaximumAcceleration(m_targetSpeed);
    m_dFrontAngle_rps = calcSteeringAngle();

    this->simVehicleLateralModel();

    // broadcasting the vehicle's body coordinate system
    broadcasting_tf_vehicle();

    autonomous_msg::VehicleOutput output;
    output.x = m_dX;
    output.y = m_dY;
    output.yaw = m_dYaw;
    output.velocity = m_dVehicleVel_ms;
    output.id = m_vehicle_namespace;
    output.length = m_dLength;
    output.width = m_dWidth;

    m_rosPubVehicle_output.publish(output);
    m_rosPubMasterVehicle_output.publish(output);
    return true;
  } else {
    return false;
  }
}

double MasterVehicle::calcSteeringAngle() {
  //가장 가까운 점을 찾는다
  double min_distance_sq = std::numeric_limits<double>::max();
  int min_index = 0;
  for (int i = 0; i < m_refLane.point.size(); i++) {
    double dx = m_dX - m_refLane.point[i].x;
    double dy = m_dY - m_refLane.point[i].y;
    double distance_sq = dx * dx + dy * dy;

    if (distance_sq < min_distance_sq) {
      min_distance_sq = distance_sq;
      min_index = i;
    }
  }
  //그 다음의 +10 인덱스 점으로 이동하는 steering angle을 구한다.
  //만약 마지막점이면 처음으로 이동한다.
  int goalPoint_index = (min_index + 10) % m_refLane.point.size();
  double goalX = m_refLane.point[goalPoint_index].x - m_dX;
  double goalY = m_refLane.point[goalPoint_index].y - m_dY;
  double alpha = atan2(goalY, goalX) - m_dYaw;
  double lookAhead = pow(goalX * goalX + goalY * goalY, 0.5);

  return atan2(2 * m_dWheelBase * sin(alpha), lookAhead);
}

/**
 * @brief 차량의 한계 속도를 구한다.
 * @details
 * 차량의 최고 가속도는 제로백을 기반으로하고, 최고 감가속도는 -g/5.0를 기준으로
 * 한다, 이때 입력된 속도가 현재의 속도와 비교하여 가속도를 구한 뒤, 이 가속도가
 * 한계 가속도보다 크면 제한한다.
 *
 * @param speed_input : 원하는 속도
 * @return double  : 한계 속도
 */
double MasterVehicle::simVehicleMaximumAcceleration(double speed_input) {
  double acceleration = (speed_input - m_dVehicleVel_ms) / m_dDt;
  double zero2hundred = 7.0;
  double max_acceleration = ((100.0) / 3.6) / zero2hundred;
  double min_acceleration = 5 * -9.81;
  if (acceleration > max_acceleration) {
    acceleration = max_acceleration;
  } else if (acceleration < min_acceleration) {
    acceleration = min_acceleration;
  }
  double limitedSpeed = m_dVehicleVel_ms + acceleration * m_dDt;
  limitedSpeed = (limitedSpeed < 0.0) ? 0.0 : limitedSpeed;
  return limitedSpeed;
}

void MasterVehicle::simVehicleLateralModel() {

  double dx = 0.0;
  double dy = 0.0;
  double dyaw = 0.0;
  double dyawrate = 0.0;

  if (m_dFrontAngle_rps > 30.0 * 3.141592 / 180.0) {
    m_dFrontAngle_rps = 30.0 * 3.141592 / 180.0;
  } else if (m_dFrontAngle_rps < -30.0 * 3.141592 / 180.0) {
    m_dFrontAngle_rps = -30.0 * 3.141592 / 180.0;
  }

  m_dSlipAngle = atan((m_dLr * tan(m_dFrontAngle_rps)) / (m_dLf + m_dLr));

  dx = m_dDt * m_dVehicleVel_ms * cos(m_dYaw + m_dSlipAngle);
  dy = m_dDt * m_dVehicleVel_ms * sin(m_dYaw + m_dSlipAngle);

  m_dYawRate = ((m_dVehicleVel_ms * cos(m_dSlipAngle)) / (m_dLf + m_dLr)) *
               (tan(m_dFrontAngle_rps));
  dyaw = m_dDt * m_dYawRate;

  m_dX += dx;
  m_dY += dy;
  m_dYaw += dyaw;
}

void MasterVehicle::broadcasting_tf_vehicle() {
  tf::Quaternion q;
  q.setRPY(0, 0, m_dYaw);
  q.normalize();
  geometry_msgs::Pose pose;

  pose.position.x = m_dX;
  pose.position.y = m_dY;
  pose.orientation.x = q.getX();
  pose.orientation.y = q.getY();
  pose.orientation.z = q.getZ();
  pose.orientation.w = q.getW();

  tf::Transform transform;

  transform.setOrigin(tf::Vector3(m_dX, m_dY, 0.0));
  transform.setRotation(q);

  // broadcasting the vehicle's body coordinate system
  // The parent coordinate is world, child coordinate is body.
  m_rosTfBroadcaster.sendTransform(tf::StampedTransform(
      transform, ros::Time::now(), "world", m_vehicle_namespace + "/body"));
}

void MasterVehicle::egoVehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg){
  m_egoVehicleState = *msg;
}

void MasterVehicle::calcMasterVehicleSpeed(){
  // check pass decelerate zone
  double dxd = m_dX - m_decelerate_x;
  double dyd = m_dY - m_decelerate_y;

  double dist = sqrt(pow(dxd,2)+pow(dyd,2));
  if (dist < 5.0){
    isMasterDeclerateZonePassed = true;
  }

  // Calculate distance btw ego vehicle

  double dx = m_egoVehicleState.x - m_dX;
  double dy = m_egoVehicleState.y - m_dY;

  double distance = sqrt(dx * dx + dy * dy); 

  // if ego is ahead slow the target vehicle
 
  geometry_msgs::PointStamped ego_point, target_point;

  ego_point.header.frame_id = "world";
  ego_point.point.x = m_egoVehicleState.x;
  ego_point.point.y = m_egoVehicleState.y;
  ego_point.point.z = 0.0;
  // ROS_ERROR_STREAM(m_vehicle_namespace);
  try {
    m_rosTfListener.transformPoint(m_vehicle_namespace+"/body", ego_point,target_point);
  } catch (tf::TransformException &ex) {
    // ROS_ERROR("%s", ex.what());
    ROS_INFO("%s", ex.what());
  }
  
  // Start target vehicle when ego_vehicle approaches (70m)
  if (distance < 70){
    m_targetSpeed = init_speed;
  }
  else{
    m_targetSpeed = 0.0;

  }
  // Stop target vehicle when ego is close and ahead
  if(target_point.point.x > 4.6 && target_point.point.x < 25 && fabs(target_point.point.y) < 4.0 ){
    m_targetSpeed = 0.0;
  }
  
  if(isMasterDeclerateZonePassed){
    m_targetSpeed = m_decelerate_speed;
  } 
  // // Decelerate if ego vehicle approach closely (10m)
  // if (distance < 20 && m_decelerate_speed != 0){
  //   m_targetSpeed = m_decelerate_speed;
  // }

  // ROS_ERROR_STREAM(m_targetSpeed);

  return;
}
void MasterVehicle::checkCollision(){
  
  std_msgs::Bool isCollision;
  isCollision.data = false;
  if (isEgoStarted == true){

    // 1. check collision  tf /ego/body to /front/{id}/body
    for(uint8_t i = 0 ; i<2 ; i++){
      tf::StampedTransform transform;
      if(i == 0){
        try{
          m_rosTfListener.lookupTransform( "ego/body",  m_vehicle_namespace+"/body",
                                    ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
          ROS_ERROR("%s",ex.what());
          ros::Duration(1.0).sleep();
        }
      }
      else if(i == 1){
        try{
          m_rosTfListener.lookupTransform(  m_vehicle_namespace+"/body", "ego/body",
                                    ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
          ROS_ERROR("%s",ex.what());
          ros::Duration(1.0).sleep();
        }
      }
      
      // 4 corner points of vehicle bbox
      tf::Vector3 target_frontRight (m_dLength/2, m_dWidth/2, 0.0);
      tf::Vector3 target_frontLeft (m_dLength/2, -m_dWidth/2, 0.0);
      tf::Vector3 target_backRight  (-m_dLength/2, m_dWidth/2, 0.0);
      tf::Vector3 target_backLeft  (-m_dLength/2, -m_dWidth/2, 0.0);

      // 4 corner points of transformed vehicle bbox
      tf::Vector3 target_frontRight_t = transform * target_frontRight;
      tf::Vector3 target_frontLeft_t = transform * target_frontLeft;
      tf::Vector3 target_backRight_t = transform * target_backRight;
      tf::Vector3 target_backLeft_t = transform * target_backLeft;

      // Check collision
      if(target_frontRight_t[1] > -m_dWidth/2 && target_frontRight_t[1] < m_dWidth/2 && target_frontRight_t[0] > -m_dLength/2 && target_frontRight_t[0] < m_dLength/2){
        isCollision.data = true;
        break;
      }
      if(target_frontLeft_t[1] > -m_dWidth/2 && target_frontLeft_t[1] < m_dWidth/2 && target_frontLeft_t[0] > -m_dLength/2 && target_frontLeft_t[0] < m_dLength/2){
        isCollision.data = true;
        break;
      }
      if(target_backRight_t[1] > -m_dWidth/2 && target_backRight_t[1] < m_dWidth/2 && target_backRight_t[0] > -m_dLength/2 && target_backRight_t[0] < m_dLength/2){
        isCollision.data = true;
        break;
      }
      if(target_backLeft_t[1] > -m_dWidth/2 && target_backLeft_t[1] < m_dWidth/2 && target_backLeft_t[0] > -m_dLength/2 && target_backLeft_t[0] < m_dLength/2){
        isCollision.data = true;
        break;
      }
    }
  }
  else{
    isCollision.data = false;
  }

  // Calculate if points are inside ego's bbox

  // Publish collision information
  if(isCollision.data){
    // ROS_WARN("Collide!!!!");
    m_rosPubIsCollide.publish(isCollision);
  }
}


int main(int argc, char **argv) {

  ros::init(argc, argv, "master_vehicle");
  MasterVehicle vehicle;
  vehicle.loadLaneData();
  vehicle.initMasterVehicle();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok()) {
    vehicle.checkEgoVehicleStarted();
    vehicle.calcMasterVehicleSpeed();
    vehicle.simVehicleModel();
    vehicle.checkCollision();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
