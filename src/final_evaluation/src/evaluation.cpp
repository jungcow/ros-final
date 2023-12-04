/**
 * @file evaluation.cpp
 * @author Eunsan Jo (eunsan.mountain@gmail.com)
 * @brief
 * @version 0.1
 * @date 2018-11-28
 *
 * @copyright Copyright (c) 2018
 *
 */
#include "KusvLane.hpp"
#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/VehicleOutput.h"
#include "jsk_rviz_plugins/OverlayText.h"
#include "autonomous_msg/VehicleOutputs.h"
#include "autonomous_msg/PointWithArclength.h"
#include "autonomous_msg/SpeedLimit.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"
#include <math.h>
#include <ros/ros.h>
#include <string>
#include <tf/tf.h>

#define PI 3.1415926579
#define CHAR_ZERO '0'
#define LOOPRATE (50.0)

class SpeedLimitInfo {
public:
  double curr_limit = 0.0;
  double next_limit = 0.0;
  double section_boundary = 0.0;

public:
  SpeedLimitInfo() {}
  SpeedLimitInfo(double curr_limit, double next_limit, double section_boundary) {
    this->curr_limit = curr_limit;
    this->next_limit = next_limit;
    this->section_boundary = section_boundary;
  }
  ~SpeedLimitInfo() {}
};

class Evaluation {
protected:
  ros::NodeHandle m_rosNodeHandler;

  ros::Publisher m_rosPubLimitSpeed;
  ros::Publisher m_rosPubMasterVehicleInitPoint;
  ros::Publisher m_rosPubMasterTargetSpeed;
  ros::Publisher m_rosPubLidar;

  ros::Subscriber m_rosSubVehicle_Output;
  ros::Subscriber m_rosSubRefPointArray;
  ros::Subscriber m_rosSubMasterVehicle_Output;
  ros::Subscriber m_rosSubMasterVehicleCollision;
  ros::Publisher m_rosPubPlotLimitSpeed;
  ros::Publisher m_rosPubTextLimitSpeed;
  ros::Publisher m_rosPubEvaluationResult;
  
  std::string m_ref_path_param;
  std::string m_laneId_param;
  int m_numTargetVehicle_param;

  double prev_sec;

  double m_limitSpeed_ms;
  std::vector<SpeedLimitInfo> m_limitSpeedSigns;

  double m_targetSpeed_master_ms;
  geometry_msgs::Point m_masterInitPoint;
  std::vector<SpeedLimitInfo> m_targetSpeedMasterSigns;


  double m_start_time = 0.0;
  double m_prev_evaluationTime = 0.0;
  double m_dt_evaluation_sec = 0.0;
  double m_drivingTime = 0.0;
  double m_drivingDistance = 0.0;
  double m_timeLimit_param = 0.0;
  double m_lidarROI_param = 0.0;

  // double m_parkingRegion_x_param = 0.0;
  // double m_parkingRegion_y_param = 0.0;

  double parkingSlot0_center_x_param = 0.0;
  double parkingSlot0_center_y_param = 0.0;
  double parkingSlot1_center_x_param = 0.0;
  double parkingSlot1_center_y_param = 0.0;
  double parkingSlot2_center_x_param = 0.0;
  double parkingSlot2_center_y_param = 0.0;

  // if csv is changed then have to change goal point: 
  double m_goalX = 864.865464;
  double m_goalY = 73.053000;
  double m_prevX = 0.0;
  double m_prevY = 0.0;
  double m_timeGap = 1.0;
  double m_minDistance = 10.0;
  int m_section_idx = 0;

  bool m_masterVehicleCollision = false;

  autonomous_msg::VehicleOutputs m_masterVehicleOutputs;

public:
  Evaluation() {

    m_rosPubLimitSpeed =
        m_rosNodeHandler.advertise<autonomous_msg::SpeedLimit>("/limit_speed", 10);

    m_rosPubLidar =
        m_rosNodeHandler.advertise<autonomous_msg::VehicleOutputs>("/lidar", 10);

    m_rosSubVehicle_Output = m_rosNodeHandler.subscribe(
        "/ego/vehicle_output", 10, &Evaluation::vehicleOutputCallback, this);

    m_rosSubMasterVehicleCollision = m_rosNodeHandler.subscribe(
        "/master_vehicle_collision", 10, &Evaluation::masterVehicleCollisionCallback, this);
  
    m_rosSubMasterVehicle_Output = m_rosNodeHandler.subscribe(
        "/master_vehicle_output", 10, &Evaluation::masterVehicleOutputCallback, this);


    m_rosPubPlotLimitSpeed = 
        m_rosNodeHandler.advertise<std_msgs::Float32>("/plot_limit_speed",10);
    m_rosPubTextLimitSpeed = 
        m_rosNodeHandler.advertise<jsk_rviz_plugins::OverlayText>("/text_limit_speed",10);
    m_rosPubEvaluationResult = 
        m_rosNodeHandler.advertise<jsk_rviz_plugins::OverlayText>("/text_evaluation_result",10);

    m_rosNodeHandler.param("evaluation/refPath", m_ref_path_param,
                           std::string(""));
    m_rosNodeHandler.param("evaluation/laneId", m_laneId_param,
                           std::string(""));
    m_rosNodeHandler.param("evaluation/numTargetVehicle", m_numTargetVehicle_param, 0);
    m_rosNodeHandler.param("evaluation/timeLimit", m_timeLimit_param, 0.0);
    m_rosNodeHandler.param("evaluation/lidarROI", m_lidarROI_param, 0.0);

    // m_rosNodeHandler.param("evaluation/parkingRegion_x", m_parkingRegion_x_param, 0.0);
    // m_rosNodeHandler.param("evaluation/parkingRegion_y", m_parkingRegion_y_param, 0.0);

    m_rosNodeHandler.param("evaluation/parkingSlot0_center_x", parkingSlot0_center_x_param, 0.0);
    m_rosNodeHandler.param("evaluation/parkingSlot0_center_y", parkingSlot0_center_y_param, 0.0);
    m_rosNodeHandler.param("evaluation/parkingSlot1_center_x", parkingSlot1_center_x_param, 0.0);
    m_rosNodeHandler.param("evaluation/parkingSlot1_center_y", parkingSlot1_center_y_param, 0.0);
    m_rosNodeHandler.param("evaluation/parkingSlot2_center_x", parkingSlot2_center_x_param, 0.0);
    m_rosNodeHandler.param("evaluation/parkingSlot2_center_y", parkingSlot2_center_y_param, 0.0);
    
    if (m_ref_path_param == std::string("")) {
      ROS_ERROR_STREAM("Empty path!!");
    }

    m_limitSpeed_ms = 0.0;

    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(50, 20, 100.0));
    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(20, 30, 200.0));
    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(30, 80, 300.0));
    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(80, 45, 400.0));
    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(45, 80, 500.0));
    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(80, 50, 800.0));
    m_targetSpeedMasterSigns.push_back(SpeedLimitInfo(50, 50, 2000.0));

    m_prev_evaluationTime = ros::Time::now().toSec();
  }

  ~Evaluation() {}

public:
  void evaluation() {
    double curr_evaluationTime = ros::Time::now().toSec();
    m_dt_evaluation_sec = curr_evaluationTime - m_prev_evaluationTime;
    m_prev_evaluationTime = curr_evaluationTime;

    this->checkAndSendLimitSpeedSign(); // ego_vehicle의 속도 제한 설정

    if (isSimulatorOn == true && isFinish == false) {
      // if (isMasterCreated == true) { 
      // 마스터(앞차량)이 생성되면 마스터의 위치와 속도를 lidar 데이터로 출력한다.
      m_rosPubLidar.publish(
            m_masterVehicleOutputs); 
      this->calcOverSpeedPenalty();
      this->checkFailure();
      this->calcOffsetError();
      this->checkParking();
      // }

    } else if (isSimulatorOn == false) {
      m_start_time = ros::Time::now().toSec();
    }

    // this->measureDrivingTime();
    // this->printEvaluationValue();
    this->publishEvaluationResult();
  }

protected:
  double m_LADSpacingError = 0.0;
  double m_currSpacingError = 0.0;

public:
  double calcDistance(double front_x, double front_y, double back_x,
                      double back_y) {
    //거리를 구한다.
    //앞차량의 포인트 인덱스를 구한다.
    double min_distance_sq = std::numeric_limits<double>::max();
    int frontIndex = 0;
    for (int i = 0; i < m_refLane.point.size(); i++) {
      double dx = front_x - m_refLane.point[i].x;
      double dy = front_y - m_refLane.point[i].y;
      double distance_sq = dx * dx + dy * dy;

      if (distance_sq < min_distance_sq) {
        min_distance_sq = distance_sq;
        frontIndex = i;
      }
    }
    //뒷 차량의 인덱스를 구한다.
    min_distance_sq = std::numeric_limits<double>::max();
    int backIndex = 0;
    for (int i = 0; i < m_refLane.point.size(); i++) {
      double dx = back_x - m_refLane.point[i].x;
      double dy = back_y - m_refLane.point[i].y;
      double distance_sq = dx * dx + dy * dy;

      if (distance_sq < min_distance_sq) {
        min_distance_sq = distance_sq;
        backIndex = i;
      }
    }

    //인덱스 사이의 거리를 적분한다.
    if (frontIndex < backIndex) {
      frontIndex += m_refLane.point.size();
    }
    double distance = 0.0;
    for (int i = backIndex + 1; i < frontIndex; i++) {
      int back_i = (i - 1) % m_refLane.point.size();
      int front_i = i % m_refLane.point.size();
      double dx = m_refLane.point[front_i].x - m_refLane.point[back_i].x;
      double dy = m_refLane.point[front_i].y - m_refLane.point[back_i].y;
      double ds = pow(dx * dx + dy * dy, 0.5);
      distance += ds;
    }
    return distance;
  }

protected:
  double m_overSpeedPenalty = 0.0;

public:
  void calcOverSpeedPenalty() {
    double gain = 2.0;

    if (m_limitSpeed_ms > 0.1) {
      if (m_vehicleState.velocity > m_limitSpeed_ms) {
        m_overSpeedPenalty += gain * m_dt_evaluation_sec; // Over Speed Penalty = 2* Over Speed Time
      }
    }
    // ROS_WARN("current speed : %.3f", m_vehicleState.velocity);
    // ROS_WARN("limit speed : %.3f", m_limitSpeed_ms);
    // ROS_ERROR("m_overSpeedPenalty : %.3f", m_overSpeedPenalty);
  }

protected:
  double m_maxOffsetError = 0.0;
  double m_currOffsetError = 0.0;
  double m_LADOffsetError = 0.0;

public:
  void calcOffsetError() {
    double min1_distance_sq = std::numeric_limits<double>::max();
    double min2_distance_sq = std::numeric_limits<double>::max();
    autonomous_msg::PointWithArclength min1_point;
    autonomous_msg::PointWithArclength min2_point;
    for (auto i = 0; i < m_refLane.point.size(); i++) {
      double dx = m_vehicleState.x - m_refLane.point[i].x;
      double dy = m_vehicleState.y - m_refLane.point[i].y;
      double distance_sq = dx * dx + dy * dy;

      if (distance_sq < min1_distance_sq) {
        min2_distance_sq = min1_distance_sq;
        min2_point = min1_point;

        min1_distance_sq = distance_sq;
        min1_point = m_refLane.point[i];
      } else if (distance_sq < min2_distance_sq) {
        min2_distance_sq = distance_sq;
        min2_point = m_refLane.point[i];
      }
    }

    double a = (min2_point.y - min1_point.y) / (min2_point.x - min1_point.x);
    double b = -1.0;
    double c = -1.0 * a * min2_point.x + min2_point.y;


    m_currOffsetError = (a * m_vehicleState.x + b * m_vehicleState.y + c) /
                        (pow(a * a + b * b, 0.5));
    if (m_currOffsetError < 0.0) {
      m_currOffsetError *= -1.0;
    }
    if (m_currOffsetError > m_maxOffsetError) {
      m_maxOffsetError = m_currOffsetError;
      // ROS_INFO_STREAM("\n Max Offset Error: " << m_maxOffsetError);
    }
    m_LADOffsetError += m_dt_evaluation_sec * m_currOffsetError;
  }

  protected:
    bool m_VehicleMoveStart = false;
    bool m_ParkingStart = false;
    bool m_isParking = false;
    bool m_ParkingSuccess = false;
    double m_ParkingTime = 0;
    double m_bonusTime = 0;

  public:
  void checkParking(){

    // double dx = m_vehicleState.x - m_parkingRegion_x_param;
    // double dy = m_vehicleState.y - m_parkingRegion_y_param;
    // double distance_sq = dx * dx + dy * dy;

    // if (distance_sq <= 6.0 * 6.0 && m_ParkingState == false) {
    //   m_ParkingState = true;
    //   std::cout << "Parkig Mission Start!" << std::endl;
    // }
    if(m_vehicleState.velocity > 0 && m_VehicleMoveStart == false){
      m_VehicleMoveStart = true;
    }

    if(m_VehicleMoveStart == true){
      if(m_vehicleState.velocity == 0 && m_ParkingStart == false){
        m_ParkingTime = ros::Time::now().toSec();
        m_ParkingStart = true;
        std::cout << "Parkig Start!" << std::endl;
      }
      else if(m_ParkingStart == true && m_vehicleState.velocity != 0){
        m_ParkingStart = false;
        std::cout << "Parkig Reset!" << std::endl;
      }
      if(m_ParkingStart == true && ros::Time::now().toSec() - m_ParkingTime > 3.){
        m_isParking = true;

        double park_offset = 0;
        
        double distance1 = pow(m_vehicleState.x - parkingSlot0_center_x_param, 2) + pow(m_vehicleState.y - parkingSlot0_center_y_param, 2);
        double distance2 = pow(m_vehicleState.x - parkingSlot1_center_x_param, 2) + pow(m_vehicleState.y - parkingSlot1_center_y_param, 2);
        double distance3 = pow(m_vehicleState.x - parkingSlot2_center_x_param, 2) + pow(m_vehicleState.y - parkingSlot2_center_y_param, 2);

        if(distance1 > distance2){
          if(distance2 > distance3){
            park_offset = distance3;
          }
          else{
            park_offset = distance2;
          }
        }
        else{
          if(distance1 > distance3){
            park_offset = distance3;
          }
          else{
            park_offset = distance1;
          }
        }
        
        if(park_offset < 3){
          m_ParkingSuccess = true;
          m_bonusTime = m_timeLimit_param * 0.3;
        }
        else{
          m_ParkingSuccess = false;
        }

        std::cout << "Parkig Done! offset Distance: " << park_offset << std::endl;
      }

      if (isFinish == false && m_isParking == true) {
        m_drivingTime = ros::Time::now().toSec() - m_start_time;
        isFinish = true;
      }
    }
  }

  protected:
    bool m_isCollision = false;
    bool m_isLaneDeparture = false;
    bool m_isRetire = false;
    double m_laneDepartureThreshold = 1.15+6.0;
    // double m_timeLimit = 60.0;
  public:
  void checkFailure(){

    // 1. Lane Departure
    if (m_currOffsetError > m_laneDepartureThreshold){
      m_isLaneDeparture = true;
    }
    // // 2. Collision
    // if (m_masterVehicleCollision == true){
    //   m_isCollision = true;
    // }

    // 3. Time Limit
    if (m_drivingTime > m_timeLimit_param){
      m_isRetire = true;
    }
    // std::cout << "driving time: "<< m_drivingTime << ", timelimit: "<< m_timeLimit_param << ", diff time: " << m_timeLimit_param - m_drivingTime << std::endl;
  }

  void checkAndSendLimitSpeedSign() {
    
    double dx = m_vehicleState.x - m_prevX;
    double dy = m_vehicleState.y - m_prevY;
    double ds = sqrt(dx*dx + dy*dy);
    m_drivingDistance += ds;
    if (m_drivingDistance > m_targetSpeedMasterSigns.at(m_section_idx).section_boundary) {
      m_section_idx++;
    }
    m_limitSpeed_ms = m_targetSpeedMasterSigns.at(m_section_idx).curr_limit / 3.6;

    autonomous_msg::SpeedLimit speed_limit;
    speed_limit.curr_limit = m_targetSpeedMasterSigns.at(m_section_idx).curr_limit / 3.6;
    speed_limit.next_limit = m_targetSpeedMasterSigns.at(m_section_idx).next_limit / 3.6;
    speed_limit.dist_left = m_targetSpeedMasterSigns.at(m_section_idx).section_boundary - m_drivingDistance;
 
    std_msgs::Float32 plotLimitVel;
    plotLimitVel.data = m_limitSpeed_ms;
    m_rosPubLimitSpeed.publish(speed_limit);
    m_rosPubPlotLimitSpeed.publish(plotLimitVel);
    text_limit();  
    m_prevX = m_vehicleState.x;
    m_prevY = m_vehicleState.y;
  }

  void text_limit(){
    jsk_rviz_plugins::OverlayText modeText;
    double backGround_rgb[] = {0.0f,0.0f,0.0f,0.0f};
    double text_rgb[] = {0.9f,0.9f,0.9f,0.7f};
    //Bounding Box
    modeText.width = 128;
    modeText.height = 128;
    modeText.left = 128;
    modeText.top = 128;
    modeText.bg_color.r = backGround_rgb[0];
    modeText.bg_color.g = backGround_rgb[1];
    modeText.bg_color.b = backGround_rgb[2];
    modeText.bg_color.a = backGround_rgb[3];
    //Text
    modeText.line_width = 1;
    modeText.text_size = 9.0;
    modeText.fg_color.r = text_rgb[0];
    modeText.fg_color.r = text_rgb[1];
    modeText.fg_color.r = text_rgb[2];
    modeText.fg_color.r = text_rgb[3];

    modeText.text = " Limit Velocity : \n" + std::to_string(3.6*m_limitSpeed_ms);

    m_rosPubTextLimitSpeed.publish(modeText);
  }
  
protected:
  bool isMasterCreated = false;
  bool isMasterStarted = false;
public:
  void createMasterVehicle() {

    double distance = calcDistance(m_masterInitPoint.x, m_masterInitPoint.y,
                                   m_vehicleState.x, m_vehicleState.y);
    double spacing_Error =
        distance - (m_timeGap * m_vehicleState.velocity + m_minDistance);

    if (spacing_Error < 0.0) {
      spacing_Error *= -1.0;
    }

    if (spacing_Error < 100.0) {
      m_rosPubMasterVehicleInitPoint.publish(m_masterInitPoint);
    }
  }

  void masterVehicleCollisionCallback(const std_msgs::Bool::ConstPtr &msg){

    m_masterVehicleCollision = msg->data;

  }


protected:
  autonomous_msg::VehicleOutput m_vehicleState;
  autonomous_msg::VehicleOutput m_masterVehicleState;
  bool isSimulatorOn = false;

public:
  void
  vehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
    m_vehicleState = *msg;
    isSimulatorOn = true;
  }
  void
  masterVehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
    autonomous_msg::VehicleOutput masterVehicleOutput;
    masterVehicleOutput = *msg;
    std::string id = masterVehicleOutput.id;
    
    int i_id = id.back()- CHAR_ZERO - 1; // Get front vehicle ID

    double master_x = masterVehicleOutput.x;
    double master_y = masterVehicleOutput.y;
    double ego_x = m_vehicleState.x;
    double ego_y = m_vehicleState.y;
    double distance = sqrt(pow(master_x-ego_x, 2) + pow(master_y-ego_y, 2));

    // ROI내부의 차량만 lidar데이터 생성
    // 먼 거리의 target차량들은 정보 0으로 초기화
    if (distance > m_lidarROI_param){
      masterVehicleOutput.velocity = 0.0;
      masterVehicleOutput.x = 0.0;
      masterVehicleOutput.y = 0.0;
      masterVehicleOutput.yaw = 0.0;
      masterVehicleOutput.length = 0.0;
      masterVehicleOutput.width = 0.0;
    }

    if (m_masterVehicleOutputs.vehicleOuputs.size() == m_numTargetVehicle_param){
      m_masterVehicleOutputs.vehicleOuputs[i_id] = masterVehicleOutput;
    }
    else{
      m_masterVehicleOutputs.vehicleOuputs.push_back(masterVehicleOutput);
    }

    isMasterCreated = true; // After receive master vehicle's data, set true
  }

protected:
  bool isFinish = false;

public:
  void measureDrivingTime() {

    double dx = m_vehicleState.x - m_goalX;
    double dy = m_vehicleState.y - m_goalY;
    // ROS_WARN_STREAM("X:"<<m_goalX << "Y:"<<m_goalY);
    double distance_sq = dx * dx + dy * dy;

    if (distance_sq <= 6.0 * 6.0) {
      isFinish = true;
    }

    if (isFinish == false) {
      m_drivingTime = ros::Time::now().toSec() - m_start_time;
    }
  }

protected:
  autonomous_msg::LanePointData m_refLane;

public:
  void loadLaneData() {

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

  void publishEvaluationResult() {
    
    std::ostringstream evaluation_info_oss;

    evaluation_info_oss << "[Evaluation Result]\n"
        << "\n"
        << "1. limit Speed: " << m_limitSpeed_ms << " m/s"
        << "\n"
        << "Vehicle Speed: " << m_vehicleState.velocity << " m/s"
        << "\n"
        << "------------------------------------"
        << "\n"
        << "   Over Speed Penalty: " << m_overSpeedPenalty << " sec"
        << "\n"
        << "\n"
        << "===================================="
        << "\n"
        << "2. Lane Departure Threshold: " << m_laneDepartureThreshold << " m"
        << "\n"
        << "------------------------------------"
        << "\n"
        << "   Max Offset Error: " << m_maxOffsetError << " m"
        << "\n"
        << "\n"
        << "===================================="
        << "\n"
        << "3. Driving Time: " << m_drivingTime << " sec\n"
        << "   Time Limit: " << m_timeLimit_param << " sec"
        << "\n"
        << "\n"
        << "===================================="
        << "\n"
        << "4. Failure:"
        << "\n"
        << "   Time Limit: " << (m_isRetire ? "FAIL" : "SUCCESS") << "\n"
        << "   Lane Departure: " << (m_isLaneDeparture ? "FAIL" : "SUCCESS") << "\n"
        // << "   Collision: " << (m_isCollision ? "FAIL" : "SUCCESS") << "\n"
        << "   Parking: " << (!m_ParkingSuccess ? "FAIL" : "SUCCESS") << "\n"
        << "\n"
        << "------------- [Result] -------------"
        << "\n"
        << "Bonus Score:\t" << (m_bonusTime) << "\n"
        << "Total Score:\t" << (m_drivingTime + m_overSpeedPenalty - m_bonusTime) << "\n"
        << "Failure:\t" << ((m_isRetire + m_isLaneDeparture) ? "FAIL" : "SUCCESS");
        // << "Failure:\t" << ((m_isRetire + m_isLaneDeparture  + m_isCollision) ? "FAIL" : "SUCCESS");
    
    std::string evaluation_info = evaluation_info_oss.str();

    jsk_rviz_plugins::OverlayText evaluationText;
    double backGround_rgb[] = {0.0f,0.0f,0.0f,0.0f};
    double text_rgb[] = {0.9f,0.9f,0.9f,0.7f};
    //Bounding Box
    evaluationText.width = 128;
    evaluationText.height = 128;
    evaluationText.left = 128;
    evaluationText.top = 128;
    evaluationText.bg_color.r = backGround_rgb[0];
    evaluationText.bg_color.g = backGround_rgb[1];
    evaluationText.bg_color.b = backGround_rgb[2];
    evaluationText.bg_color.a = backGround_rgb[3];

    //Text
    evaluationText.line_width = 1;
    evaluationText.text_size = 9.0;
    evaluationText.fg_color.r = text_rgb[0];
    evaluationText.fg_color.r = text_rgb[1];
    evaluationText.fg_color.r = text_rgb[2];
    evaluationText.fg_color.r = text_rgb[3];

    evaluationText.text = evaluation_info;

    m_rosPubEvaluationResult.publish(evaluationText);
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "evaluation");
  Evaluation evaluation;
  evaluation.loadLaneData();

  ros::Rate loop_rate(LOOPRATE);
  while (ros::ok()) {
    evaluation.evaluation();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
