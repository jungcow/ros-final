/**
 * @file lane_detection_simulator.cpp
 * @author Kyungwoon So (bigcow1999@gmail.com)
 * @brief simulator for lane detection
 * @details
 * @version 0.1
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "KusvLane.hpp"
#include "autonomous_msg/LanePointData.h"
#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
#include <tf/transform_listener.h>
#include <eigen3/Eigen/Dense>
#include <math.h>
#include <random>
#include <ros/ros.h>
#include <string>
#include <cstdlib>

class LaneDetection {

public:
  LaneDetection() {
    m_rosPubCsvLanes =
        m_rosNodeHandler.advertise<autonomous_msg::LanePointDataArray>(
            "csv_lanes", 10);

    m_rosPubROILanes =
        m_rosNodeHandler.advertise<autonomous_msg::LanePointDataArray>(
            "ROI_lanes", 10);

    m_rosPubROILanePoints =
        m_rosNodeHandler.advertise<autonomous_msg::LanePointData>(
            "ROI_lane_points", 10);

    m_rosNodeHandler.param("lane_detection/ROIFront", m_ROIFront_param, 20.0);
    m_rosNodeHandler.param("lane_detection/ROIRear", m_ROIRear_param, 10.0);
    m_rosNodeHandler.param("lane_detection/ROILeft", m_ROILeft_param, 3.0);
    m_rosNodeHandler.param("lane_detection/ROIRight", m_ROIRight_param, 3.0);
    m_rosNodeHandler.param("lane_detection/ROICloseThreshold", m_ROI_close_threshold, 0.7);

    m_rosNodeHandler.param("lane_detection/ns", m_vehicle_namespace_param,
                           std::string(""));
    m_rosNodeHandler.param("lane_detection/path", m_path_param,
                           std::string(""));
    if (m_path_param == std::string("")) {
      ROS_ERROR_STREAM("Empty path!!");
    }
  }

  ~LaneDetection() {}

protected:
  ros::NodeHandle m_rosNodeHandler;
  ros::Publisher m_rosPubROILanePoints;
  ros::Publisher m_rosPubROILanes;
  ros::Publisher m_rosPubCsvLanes;
  ros::Publisher m_rosPubPolyLanes;
  ros::Publisher m_rosPubPolyLanesDetected;
  std::string m_vehicle_namespace_param;

  double m_ROIFront_param = 20.0;
  double m_ROIRear_param = 10.0;
  double m_ROILeft_param = 3.0;
  double m_ROIRight_param = 3.0;
  double m_ROI_close_threshold = 0.7;
  double m_noise_std = 0.08;

  tf::TransformListener m_rosTfListenr;

  std::string m_path_param;
  autonomous_msg::LanePointDataArray m_csvLanes;
  autonomous_msg::LanePointDataArray m_ROILanes;
  autonomous_msg::LanePointData m_ROILanePoints;
  autonomous_msg::PolyfitLaneDataArray m_polyLanes;
  autonomous_msg::PolyfitLaneDataArray m_polyLanesDetected;

  autonomous_msg::LanePointData m_rightLane;
  autonomous_msg::PolyfitLaneData m_rightPoly;

public:
  void loadLaneData() {
    SKusvLanes csvLaneImport;
    csvLaneImport.ImportKusvLaneCsvFile(m_path_param);
    m_csvLanes.frame_id = "world";
    m_csvLanes.lane.clear();

    std::cout << "i_lane size : " << csvLaneImport.m_vecKusvLanes.size();
    for (auto i_lane = 0; i_lane < csvLaneImport.m_vecKusvLanes.size();
         i_lane++) {
      autonomous_msg::LanePointData lane;
      lane.frame_id = "world";
      lane.id = std::to_string(csvLaneImport.m_vecKusvLanes[i_lane].m_nLaneID);
      
      autonomous_msg::PointWithArclength prevPoint;
      double arclength = 0.0;
      bool is_first = true;
      
      ROS_INFO("i_point size : %d", csvLaneImport.m_vecKusvLanes[i_lane].m_vecKusvLanePoint.size());

      for (auto i_point = 0;
           i_point <
           csvLaneImport.m_vecKusvLanes[i_lane].m_vecKusvLanePoint.size();
           i_point++) {
        autonomous_msg::PointWithArclength point;
        point.x = csvLaneImport.m_vecKusvLanes[i_lane]
                      .m_vecKusvLanePoint[i_point]
                      .m_dPtX_m;
        point.y = csvLaneImport.m_vecKusvLanes[i_lane]
                      .m_vecKusvLanePoint[i_point]
                      .m_dPtY_m;
        point.arclength = arclength;

        if (is_first) {
          is_first = false;
        }
        else {
          double dx = point.x - prevPoint.x;
          double dy = point.y - prevPoint.y;
          arclength += sqrt(dx * dx + dy * dy);
        }
        prevPoint = point;
        lane.point.push_back(point);
      }
      ROS_INFO("arclength : %.3f", arclength);
      m_csvLanes.lane.push_back(lane);
    }
  }
  void publishCsvLanesData() { m_rosPubCsvLanes.publish(m_csvLanes); }

  void extractROILanePoints() {

    m_ROILanePoints.point.clear();

    for (auto i_lane = 0; i_lane < m_csvLanes.lane.size(); i_lane++) {

      m_ROILanePoints.frame_id = m_vehicle_namespace_param + "/body";
      // m_ROILanePoints.id = m_csvLanes.lane[i_lane].id;

      int down_size = (m_csvLanes.lane[i_lane].point.size() + 3) / 4;

      for (int i_point = 0; i_point < down_size; i_point++) {

        geometry_msgs::PointStamped lanePoint_world;
        lanePoint_world.header.frame_id = "world";
        lanePoint_world.header.stamp = ros::Time(0);
        lanePoint_world.point.x = m_csvLanes.lane[i_lane].point[i_point * 4].x;
        lanePoint_world.point.y = m_csvLanes.lane[i_lane].point[i_point * 4].y;
        geometry_msgs::PointStamped lanePoint_body; 

        try {
          m_rosTfListenr.transformPoint(m_vehicle_namespace_param + "/body",
                                        lanePoint_world, lanePoint_body);

          double dist_to_vehicle = std::hypot(lanePoint_body.point.x, lanePoint_body.point.y);      

          if ((dist_to_vehicle > m_ROI_close_threshold) &&
              (lanePoint_body.point.x <= m_ROIFront_param) &&
              (lanePoint_body.point.x >= -1 * m_ROIRear_param) &&
              (lanePoint_body.point.y <= m_ROILeft_param) &&
              (lanePoint_body.point.y >= -1 * m_ROIRight_param)) {
            autonomous_msg::PointWithArclength point;
            point.x = lanePoint_body.point.x + GenerateGaussianNoise(0.0, m_noise_std);
            point.y = lanePoint_body.point.y + GenerateGaussianNoise(0.0, m_noise_std);
            m_ROILanePoints.point.push_back(point);
          }

        } catch (tf::TransformException &ex) {
          // ROS_ERROR(ex.what());
        }
      }
    }
    m_rosPubROILanePoints.publish(m_ROILanePoints);
  }

  double GenerateGaussianNoise(double mean, double std_dev) {
    // This function is for generating gaussian noise
    static std::random_device        rd;
    std::default_random_engine       gen(rd());
    std::normal_distribution<double> dist(mean, std_dev);

    return dist(gen);
  }
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "lane_detection");

  LaneDetection laneDetection;
  laneDetection.loadLaneData();

  double prev_csvLaneMarkTime = ros::Time::now().toSec();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(30);
  while (ros::ok()) {
    laneDetection.extractROILanePoints();
    if ((ros::Time::now().toSec() - prev_csvLaneMarkTime) > 1.0) {
      prev_csvLaneMarkTime = ros::Time::now().toSec();
      laneDetection.publishCsvLanesData();
    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
