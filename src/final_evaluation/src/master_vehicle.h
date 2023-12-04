/**
 * @file master_vehicle.h
 * @author Eunsan Jo (eunsan.mountain@gmail.com)
 * @brief
 * @version 0.1
 * @date 2018-11-28
 *
 * @copyright Copyright (c) 2018
 *
 */
#ifndef MASTER_VEHILCE_H
#define MASTER_VEHILCE_H

#include "autonomous_msg/LanePointData.h"
#include "autonomous_msg/VehicleInput.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include "visualization_msgs/Marker.h"
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include "autonomous_msg/VehicleOutput.h"

#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/tf.h>
#include <tf/transform_datatypes.h>


#define PI 3.14159265358979323846 /* pi */

class MasterVehicle {
protected:
  ros::NodeHandle m_rosNodeHandler;

  ros::Publisher m_rosPubVehicle_output;
  ros::Publisher m_rosPubIsCollide;
  ros::Publisher m_rosPubMasterVehicle_output;

  ros::Subscriber m_rosInitPoint;
  ros::Subscriber m_rosTargetSpeed;
  ros::Subscriber m_rosSubEgoVehicle_output;
  
  tf::TransformBroadcaster m_rosTfBroadcaster;
  tf::TransformListener m_rosTfListener;

  // ros::Publisher m_rosPubVehicleMarker;

  std::string m_vehicle_namespace;

  double m_dAccelInput = 0.0;
  double m_dBrakeInput = 0.0;
  double m_dFrontAngle_rps = 0.0;

  double m_dDt = 0.0;
  double m_dPrevTime;

  double m_dX = 0.0;
  double m_dY = 0.0;
  double m_dYaw = 0.0;
  double m_dYawRate = 0.0;
  double m_dSlipAngle = 0.0;
  double m_dVehicleVel_ms = 0;

  double m_dWheelBase = 1.402 + 1.646; // m
  double m_dLf = 1.402;                // m
  double m_dLr = 1.646;                // m
  double m_dWidth = 2.3;               // m
  double m_dLength = 4.6;              // m
  
  autonomous_msg::LanePointData m_refLane;
  std::string m_laneId_param;
  std::string m_ref_path_param;

  double m_targetSpeed = 0.0;
  bool isMasterCreated = false;
  bool isMasterDeclerateZonePassed = false;
  
  bool isEgoStarted = false;
  autonomous_msg::VehicleOutput m_prev_vehicleOutput;
  
  double init_x, init_y, init_yaw, init_speed = 0.0;
  double m_decelerate_x, m_decelerate_y, m_decelerate_speed = 0.0;

  // Ego vehicle informantion
  autonomous_msg::VehicleOutput m_egoVehicleState;

public:
  MasterVehicle();
  ~MasterVehicle();
  void setInitialState(double x = 0.0, double y = 0.0, double yaw = 0.0,
                       double speed_mps = 0.0);
  void checkEgoVehicleStarted();
  bool simVehicleModel();
  void simVehicleLateralModel();
  double simVehicleMaximumAcceleration(double speed_input);
  void loadLaneData();
  double calcSteeringAngle();
  void initPointCallback(const geometry_msgs::Point::ConstPtr &msg);
  void egoVehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg);

  void initMasterVehicle();
  void calcMasterVehicleSpeed();
  void checkCollision();

private:
  void broadcasting_tf_vehicle();
};

#endif
