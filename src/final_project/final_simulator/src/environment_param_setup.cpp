#include "environment_param_setup.h"
#include "autonomous_msg/EnvironmentParam.h"
#include "autonomous_msg/EnvironmentMode.h"
#include "autonomous_msg/EnvironmentDetected.h"
#include "autonomous_msg/EnvironmentModeArea.h"
#include "autonomous_msg/VehicleOutput.h"
#include "autonomous_msg/PointWithArclength.h"
#include <tf/transform_listener.h>
#include "geometry_msgs/PointStamped.h"
#include <ros/ros.h>
#include <vector>
#include <math.h>


EnvironmentSetup::EnvironmentSetup(){
   m_rosPubEnvironmentParam_output =
         m_rosNodeHandler.advertise<autonomous_msg::EnvironmentParam>(
            "environment_param", 10);

   m_rosPubEnvironmentModeArea =
         m_rosNodeHandler.advertise<autonomous_msg::EnvironmentModeArea>(
            "/environment_area", 10);

   m_rosPubEnvironmentMode =
         m_rosNodeHandler.advertise<autonomous_msg::EnvironmentMode>(
            "/environment_mode", 10);
   
   m_rosPubEnvironmentDetected =
         m_rosNodeHandler.advertise<autonomous_msg::EnvironmentDetected>(
            "/environment_detected", 10);

   m_rosSubVehicle_Output = m_rosNodeHandler.subscribe(
        "/ego/vehicle_output", 10, &EnvironmentSetup::vehicleOutputCallback, this);

   m_rosNodeHandler.param("initFyfMax", this->initFyfMax, 6200.0);
   m_rosNodeHandler.param("initFyrMax", this->initFyrMax, 6200.0);
   m_rosNodeHandler.param("lane_detection/ROIFront", m_ROIFront_param, 20.0);
   m_rosNodeHandler.param("lane_detection/ROIRear", m_ROIRear_param, 10.0);
   m_rosNodeHandler.param("lane_detection/ROILeft", m_ROILeft_param, 3.0);
   m_rosNodeHandler.param("lane_detection/ROIRight", m_ROIRight_param, 3.0);
   m_rosNodeHandler.param("vehicle/ns", m_vehicle_namespace_param,
                           std::string(""));


   // If use ice csv files, use below
   // 1. map : ice
   // m_iceParam.push_back(IceParam(90.202971,150.650000, 20.0, 2000.0, 2000.0));
   // m_iceParam.push_back(IceParam(320.0,40.0, 50.0, 2000.0, 2000.0));
   // m_iceParam.push_back(IceParam(400.0,200.0, 40.0, 2000.0, 2000.0));

   // 2. map : easy
   m_iceParam.push_back(IceParam(99.0,33.0, 20.0, 2000.0, 2000.0));
   m_iceParam.push_back(IceParam(116.0,180.0, 30.0, 2000.0, 2000.0));
   m_iceParam.push_back(IceParam(290.0,100.0, 30.0, 2000.0, 2000.0));
   m_iceParam.push_back(IceParam(401.0,70.0, 5.0, 2000.0, 2000.0));

   // 3. map : hard
   // m_iceParam.push_back(IceParam(99.0,33.0, 20.0, 2000.0, 2000.0));
   // m_iceParam.push_back(IceParam(116.0,180.0, 30.0, 2000.0, 2000.0));
   // m_iceParam.push_back(IceParam(304.0,26.0, 30.0, 2000.0, 2000.0));
   // m_iceParam.push_back(IceParam(361.0,405.0, 5.0, 2000.0, 2000.0));

    // 8. emergency
// m_iceParam.push_back(IceParam(66.0,19.0, 25.0, 2000.0, 2000.0));
// m_iceParam.push_back(IceParam(227.0,2.0, 20.0, 2000.0, 2000.0));
// m_iceParam.push_back(IceParam(111.0,108.0, 6.0, 2000.0, 2000.0));
}

EnvironmentSetup::~EnvironmentSetup(){}

void EnvironmentSetup::vehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg){
   m_vehicleState = *msg;
   isSimulatorOn = true;
}

void EnvironmentSetup::masterVehicleCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
   m_masterVehicleState = *msg;
   isMasterDataExist = true;
}

void EnvironmentSetup::checkIce() {
   for (auto i = 0; i < m_iceParam.size(); i++) {
      double dx = m_vehicleState.x - m_iceParam[i].x;
      double dy = m_vehicleState.y - m_iceParam[i].y;
      double distance_sq = dx * dx + dy * dy;

      if (distance_sq <= m_iceParam[i].radius*m_iceParam[i].radius) {
         this->m_dFyf_max = m_iceParam[i].fyf_max;
         this->m_dFyr_max = m_iceParam[i].fyr_max;
         this->m_ice_mode = "Ice";
         break;
      }
      else{
         this->m_dFyf_max = this->initFyfMax;
         this->m_dFyr_max = this->initFyrMax;
         this->m_ice_mode = "Asphalt";
      }
   }
}

void EnvironmentSetup::environmentAreaPublish(){
   std::vector<double> ice_x;  std::vector<double> ice_y;  std::vector<double> ice_radius;
   for (auto i = 0; i < m_iceParam.size(); i++) {
      ice_x.push_back(m_iceParam[i].x);
      ice_y.push_back(m_iceParam[i].y);
      ice_radius.push_back(m_iceParam[i].radius);
   }

   autonomous_msg::EnvironmentModeArea env_mode_xy;
   env_mode_xy.ice_x = ice_x;   env_mode_xy.ice_y = ice_y;   env_mode_xy.ice_radius =  ice_radius;

   m_rosPubEnvironmentModeArea.publish(env_mode_xy);
}

void EnvironmentSetup::environmentParamPublish(){
   if(isSimulatorOn==true){ 
      this->checkIce();
      this->environmentAreaPublish();     

      autonomous_msg::EnvironmentParam env_param_msg;
      env_param_msg.fyr_max = this->m_dFyr_max;
      env_param_msg.fyf_max = this->m_dFyf_max;
      m_rosPubEnvironmentParam_output.publish(env_param_msg);

      autonomous_msg::EnvironmentMode env_mode_msg;
      env_mode_msg.ice_mode = this->m_ice_mode;
      m_rosPubEnvironmentMode.publish(env_mode_msg);

      autonomous_msg::EnvironmentDetected env_giving_msg;
      env_giving_msg.ice_mode = this->m_ice_mode;
      env_giving_msg.ice_param = this->m_dFyf_max;
      m_rosPubEnvironmentDetected.publish(env_giving_msg);

   }
}

int main(int argc, char **argv) {

   ros::init(argc, argv, "environment_adjustment");
   EnvironmentSetup env_param;

   ros::Rate loop_rate(100);
   while (ros::ok()) {
      env_param.environmentParamPublish();
      ros::spinOnce();
      loop_rate.sleep();
   }

   return 0;
}