#include <math.h>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <eigen3/Eigen/Dense>
#include <string>

#include "autonomous_msg/EnvironmentDetected.h"
#include "autonomous_msg/LanePointData.h"
#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/PointWithArclength.h"
#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "autonomous_msg/SpeedLimit.h"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include "autonomous_msg/VehicleOutputs.h"
#include "std_msgs/Float64.h"

using namespace std;

// bool no_lane_flag = false;
// bool parking_flag = false;
// double no_lane_elapsed_time;

class AutonomousDriving
{
public:
  ros::Publisher m_marker_pub;

  visualization_msgs::Marker marker;

protected:
  ros::NodeHandle m_rosNodeHandler;

  ros::Subscriber m_rosSubVehicleState;
  ros::Subscriber m_rosSubDrivingInput;
  ros::Subscriber m_rosSubLimitSpeed;
  ros::Subscriber m_rosSubEnvironmentMode;
  ros::Subscriber m_rosSubROILanePoints;
  ros::Publisher m_rosPubVehicleInput;
  ros::Publisher m_rosPubDrivingWay;
  ros::Publisher m_rosPubPolyLanes;
  ros::Publisher m_rosPubPolyLanesDetected;

  std::string m_vehicle_namespace_param;
  double m_lookAhead_param = 0.0;
  double m_dWheelBase = 1.402 + 1.646;
  bool m_use_manual_inputs = false;
  double m_curr_curvature = 0;
  double prev_polyfit[2][4];
  double prev_midpolyfit[4];
  double prev_l_x_d = 0.;
  double prev_delta = 0.;

public:
  AutonomousDriving()
  {
    // m_marker_pub = m_rosNodeHandler.advertise<visualization_msgs::Marker>("my_lane_marker_pub", 10);
    memset(prev_polyfit, 0, sizeof(double) * 8);
    memset(prev_midpolyfit, 0, sizeof(double) * 4);

    m_rosPubDrivingWay =
        m_rosNodeHandler.advertise<autonomous_msg::PolyfitLaneData>(
            "driving_way", 10);

    m_rosPubVehicleInput =
        m_rosNodeHandler.advertise<autonomous_msg::VehicleInput>(
            "vehicle_input", 10);

    m_rosPubPolyLanes =
        m_rosNodeHandler.advertise<autonomous_msg::PolyfitLaneDataArray>(
            "polyfit_lanes", 10);

    m_rosPubPolyLanesDetected =
        m_rosNodeHandler.advertise<autonomous_msg::PolyfitLaneDataArray>(
            "polyfit_lanes_detected", 10);

    m_rosSubVehicleState = m_rosNodeHandler.subscribe(
        "vehicle_output", 10, &AutonomousDriving::vehicleStateCallback, this);

    m_rosSubLimitSpeed = m_rosNodeHandler.subscribe(
        "/limit_speed", 10, &AutonomousDriving::limitSpeedCallback, this);

    m_rosSubDrivingInput = m_rosNodeHandler.subscribe(
        "/driving_input", 10, &AutonomousDriving::drivingInputCallback, this);

    m_rosSubEnvironmentMode = m_rosNodeHandler.subscribe(
        "/environment_detected", 10, &AutonomousDriving::environmentModeCallback, this);

    m_rosSubROILanePoints = m_rosNodeHandler.subscribe(
        "ROI_lane_points", 10, &AutonomousDriving::ROILanePointsCallback, this);

    m_rosNodeHandler.param("autonomous_driving/ns", m_vehicle_namespace_param,
                           std::string(""));
    m_rosNodeHandler.param("autonomous_driving/lookAhead", m_lookAhead_param,
                           5.0);
    m_rosNodeHandler.param("autonomous_driving/use_manual_inputs", m_use_manual_inputs,
                           false);
  }

  ~AutonomousDriving() {}

protected:
  autonomous_msg::LanePointData m_ROILanePoints;
  autonomous_msg::LanePointDataArray m_ROILanes;
  autonomous_msg::PolyfitLaneDataArray m_polyLanes;
  autonomous_msg::PolyfitLaneDataArray m_polyLanesDetected;
  autonomous_msg::VehicleInput m_drivingInput;
  autonomous_msg::PolyfitLaneData m_midPolyLane;
  autonomous_msg::VehicleOutput m_vehicleState;
  autonomous_msg::SpeedLimit m_speedLimit;

  std::string m_iceMode = "Asphalt";
  double m_iceParam = 6200.0;

public:
  /**
   * @brief Temporary functions for debugging pure pursuit
   *
   * @param VehicleInput accel and brake
   */
  void drivingInputCallback(const autonomous_msg::VehicleInput::ConstPtr &msg)
  {
    if (m_use_manual_inputs)
    {
      m_drivingInput.accel = msg->accel;
      m_drivingInput.brake = msg->brake;
      m_drivingInput.steering = msg->steering;
    }
  }

  void vehicleStateCallback(
      const autonomous_msg::VehicleOutput::ConstPtr &msg)
  {
    m_vehicleState = *msg;
  }

  void limitSpeedCallback(const autonomous_msg::SpeedLimit::ConstPtr &msg)
  {
    m_speedLimit = *msg;
  }

  void environmentModeCallback(const autonomous_msg::EnvironmentDetected::ConstPtr &msg)
  {
    m_iceMode = msg->ice_mode;
    m_iceParam = msg->ice_param;
  }

  void ROILanePointsCallback(const autonomous_msg::LanePointData::ConstPtr &msg)
  {
    m_ROILanePoints = *msg;
  }

  Eigen::VectorXd pointsetToLane(autonomous_msg::LanePointData::_point_type &points)
  {
    int down_size = points.size();
    Eigen::MatrixXd X_Matrix(down_size, 4);
    Eigen::VectorXd y_Vector(down_size);
    Eigen::VectorXd a_Vector(4);

    for (int i_point = 0; i_point < down_size; i_point++)
    {
      double x = points[i_point].x;
      double y = points[i_point].y;

      X_Matrix(i_point, 0) = 1;
      X_Matrix(i_point, 1) = x;
      X_Matrix(i_point, 2) = x * x;
      X_Matrix(i_point, 3) = x * x * x;
      y_Vector(i_point) = y;
    }

    a_Vector =
        ((X_Matrix.transpose() * X_Matrix).inverse() * X_Matrix.transpose()) *
        y_Vector;

    return a_Vector;
  }

  double magnitudeSaturateValue(double src, double saturate_num)
  {
    if (abs(src) > saturate_num)
    {
      if (src > 0)
        src = saturate_num;
      else
        src = -saturate_num;
    }
    return src;
  }

  autonomous_msg::LanePointDataArray::_lane_type
  separateAndPushLane(autonomous_msg::LanePointData::_point_type &points)
  {
    int size = points.size();
    autonomous_msg::LanePointData left;
    autonomous_msg::LanePointData right;
    autonomous_msg::LanePointData mid;

    autonomous_msg::LanePointDataArray::_lane_type laneset;
    const double epsilon = 0.25;

    ROS_INFO("Current Curvature: %lf", m_curr_curvature);

    double abs_curvature = m_curr_curvature > 0 ? m_curr_curvature : -1 * m_curr_curvature;

    double x_range_limit = 19;

    // abs_curvature = magnitudeSaturateValue(abs_curvature)

    if (abs_curvature > 0.025)
      abs_curvature = 0.025; // saturated

    x_range_limit = x_range_limit - abs_curvature * 500;

    if (abs_curvature < 0.001)
    {
      x_range_limit = 19;
    }

    ROS_INFO("Current X View Limit: %lf", x_range_limit);

    for (auto &point : points)
    {
      double x = point.x;
      double y = point.y;

      if (x > x_range_limit || x < -5)
        continue;
      if (y > epsilon && y < 4 - epsilon)
        left.point.push_back(point);
      else if (y < -epsilon && y > -4 + epsilon)
        right.point.push_back(point);
    }
    left.id = "0";
    right.id = "1";
    laneset.push_back(left);
    laneset.push_back(right);
    return laneset;
  }

  void polyfitLane()
  {
    m_polyLanes.frame_id = m_vehicle_namespace_param + "/body";
    m_polyLanes.polyfitLanes.clear();

    m_polyLanesDetected.frame_id = m_vehicle_namespace_param + "/body";
    m_polyLanesDetected.polyfitLanes.clear();

    m_ROILanes.frame_id = m_vehicle_namespace_param + "/body";
    m_ROILanes.lane.clear();

    // TODO
    // Perceive lane info (make m_polyLanes)
    if (m_vehicleState.velocity < 0.01)
      return;

    m_ROILanes.lane = separateAndPushLane(m_ROILanePoints.point);
    // m_ROILanes.lane[0].point = removeOutlier(m_ROILanes.lane[0].point);
    // m_ROILanes.lane[1].point = removeOutlier(m_ROILanes.lane[1].point);

    ROS_INFO("Left lane size: %ld", m_ROILanes.lane[0].point.size());
    ROS_INFO("Right lane size: %ld", m_ROILanes.lane[1].point.size());

    const int lane_efficient_num = 6; // least number of point for get coeff(a0, a1, a2, a3)
    bool no_lane_flag = false;

    if (m_ROILanes.lane[0].point.size() < lane_efficient_num &&
        m_ROILanes.lane[1].point.size() < lane_efficient_num)
      no_lane_flag = true;

    for (auto i_lane = 0; i_lane < m_ROILanes.lane.size(); i_lane++)
    {
      // Eigen의 매트릭스를 차선의 포인트 갯수에 맞게 생성한다.
      int down_size = (m_ROILanes.lane[i_lane].point.size());
      Eigen::MatrixXd X_Matrix(down_size, 4);
      Eigen::VectorXd y_Vector(down_size);
      Eigen::VectorXd a_Vector(4);

      // Eigen의 매트릭스에 포인트를 넣어준다.
      if (down_size < lane_efficient_num)
      {
        autonomous_msg::PolyfitLaneData polyLane;
        polyLane.frame_id = m_vehicle_namespace_param + "/body";
        polyLane.id = m_ROILanes.lane[i_lane].id;
        if (m_ROILanes.lane[i_lane].id == "0")
        {
          ROS_INFO("No Left lane: %s", m_ROILanes.lane[i_lane].id.c_str());
          polyLane.a0 = prev_polyfit[1][0] + 4;
          polyLane.a1 = prev_polyfit[1][1];
          polyLane.a2 = prev_polyfit[1][2];
          polyLane.a3 = prev_polyfit[1][3];
          // ROS_INFO("L -- (a0, a1, a2, a3) \n: (%lf, %lf, %lf, %lf)", polyLane.a0, polyLane.a1, polyLane.a2, polyLane.a3);
        }
        else if (m_ROILanes.lane[i_lane].id == "1")
        {
          ROS_INFO("No Right lane: %s", m_ROILanes.lane[i_lane].id.c_str());
          polyLane.a0 = prev_polyfit[0][0] - 4;
          polyLane.a1 = prev_polyfit[0][1];
          polyLane.a2 = prev_polyfit[0][2];
          polyLane.a3 = prev_polyfit[0][3];
          // ROS_INFO("R -- (a0, a1, a2, a3) \n: (%lf, %lf, %lf, %lf)", polyLane.a0, polyLane.a1, polyLane.a2, polyLane.a3);
        }

        if (abs(polyLane.a2) > 0.1)
        {
          ROS_INFO("Polyfit is insane!!! curvature is : %lf\n", polyLane.a2);
          if (m_ROILanes.lane[i_lane].id == "0")
          {
            ROS_INFO("LEFT is INSANE!!!!!!!!!!!!!!!!!!!!");
            // polyLane.a0 = prev_polyfit[1][0] + 4;
            // polyLane.a1 = prev_polyfit[1][1];
            // polyLane.a2 = prev_polyfit[1][2];
            // polyLane.a3 = prev_polyfit[1][3];
            polyLane.a0 = +2;
            polyLane.a1 = 0;
            polyLane.a2 = 0;
            polyLane.a3 = 0;
          }
          else if (m_ROILanes.lane[i_lane].id == "1")
          {
            ROS_INFO("RIGHT is INSANE!!!!!!!!!!!!!!!!!!!!");
            // polyLane.a0 = prev_polyfit[0][0] - 4;
            // polyLane.a1 = prev_polyfit[0][1];
            // polyLane.a2 = prev_polyfit[0][2];
            // polyLane.a3 = prev_polyfit[0][3];
            polyLane.a0 = -2;
            polyLane.a1 = 0;
            polyLane.a2 = 0;
            polyLane.a3 = 0;
          }
          for (auto &point : m_ROILanes.lane[i_lane].point)
          {
            ROS_INFO("Insane Lane's Points(%s): (%lf, %lf)", m_ROILanes.id.c_str(), point.x, point.y);
          }
        }

        m_polyLanes.polyfitLanes.push_back(polyLane);
        continue;
      }
      for (int i_point = 0; i_point < down_size; i_point++)
      {
        double x = m_ROILanes.lane[i_lane].point[i_point].x;
        double y = m_ROILanes.lane[i_lane].point[i_point].y;

        X_Matrix(i_point, 0) = 1;
        X_Matrix(i_point, 1) = x;
        X_Matrix(i_point, 2) = x * x;
        X_Matrix(i_point, 3) = x * x * x;
        y_Vector(i_point) = y;
      }

      a_Vector =
          ((X_Matrix.transpose() * X_Matrix).inverse() * X_Matrix.transpose()) *
          y_Vector;

      autonomous_msg::PolyfitLaneData polyLane;
      polyLane.frame_id = m_vehicle_namespace_param + "/body";
      polyLane.id = m_ROILanes.lane[i_lane].id;

      polyLane.a0 = a_Vector(0);
      polyLane.a1 = a_Vector(1);
      polyLane.a2 = a_Vector(2);
      polyLane.a3 = a_Vector(3);

      if (abs(polyLane.a2) > 0.1)
      {
        ROS_INFO("Polyfit is insane!!! curvature is : %lf\n", polyLane.a2);
        if (m_ROILanes.lane[i_lane].id == "0")
        {
          ROS_INFO("LEFT is INSANE!!!!!!!!!!!!!!!!!!!!");
          // polyLane.a0 = prev_polyfit[1][0] + 4;
          // polyLane.a1 = prev_polyfit[1][1];
          // polyLane.a2 = prev_polyfit[1][2];
          // polyLane.a3 = prev_polyfit[1][3];
          polyLane.a0 = +2;
          polyLane.a1 = 0;
          polyLane.a2 = 0;
          polyLane.a3 = 0;
        }
        else if (m_ROILanes.lane[i_lane].id == "1")
        {
          ROS_INFO("RIGHT is INSANE!!!!!!!!!!!!!!!!!!!!");
          // polyLane.a0 = prev_polyfit[0][0] - 4;
          // polyLane.a1 = prev_polyfit[0][1];
          // polyLane.a2 = prev_polyfit[0][2];
          // polyLane.a3 = prev_polyfit[0][3];
          polyLane.a0 = -2;
          polyLane.a1 = 0;
          polyLane.a2 = 0;
          polyLane.a3 = 0;
        }
        for (auto &point : m_ROILanes.lane[i_lane].point)
        {
          ROS_INFO("Insane Lane's Points(%s): (%lf, %lf)", m_ROILanes.id.c_str(), point.x, point.y);
        }
      }

      // ROS_INFO("1 -- (a0, a1, a2, a3) \n: (%lf, %lf, %lf, %lf)", polyLane.a0, polyLane.a1, polyLane.a2, polyLane.a3);
      m_polyLanes.polyfitLanes.push_back(polyLane);
    }
    if (no_lane_flag)
    {
      autonomous_msg::PolyfitLaneData polyLane;
      m_polyLanes.polyfitLanes.pop_back();
      m_polyLanes.polyfitLanes.pop_back();
      polyLane.a0 = 0;
      polyLane.a1 = 0;
      polyLane.a2 = 0;
      polyLane.a3 = 0;
      m_polyLanes.polyfitLanes.push_back(polyLane);
      m_polyLanes.polyfitLanes.push_back(polyLane);
    }
    m_rosPubPolyLanes.publish(m_polyLanes);
    m_rosPubPolyLanesDetected.publish(m_polyLanes);
  }

  void controlVehicleSpeed()
  {
    // TODO
    // Change this function to make the vehicle follow target speed (input of the function(parameters) can be modified)
    double targetSpeed_ms;
    ROS_INFO("Curr Speed Limit: %lf, Mode: %s", m_speedLimit.curr_limit, m_iceMode.c_str());

    double current_limit = m_speedLimit.curr_limit * 0.95;
    double next_limit = m_speedLimit.next_limit * 0.95;
    double remain_distance = m_speedLimit.dist_left;

    if (current_limit < 0.01)
      return;

    // target speed Initialize
    targetSpeed_ms = current_limit;
    if (remain_distance < 10 && next_limit < current_limit)
      targetSpeed_ms = next_limit;

    double abs_curvature = m_curr_curvature > 0 ? m_curr_curvature : -1 * m_curr_curvature;

    if (m_use_manual_inputs == false)
    {
      if (abs(m_curr_curvature) < 0.007) // straight line
      {
      }
      else if (m_iceMode == "Ice") // road mode is ice
      {
        if (abs_curvature < 0.007)
          targetSpeed_ms = targetSpeed_ms > 15 ? 15 : targetSpeed_ms;
        else
          targetSpeed_ms = targetSpeed_ms > 8 ? 8 : targetSpeed_ms;
      }
      else if (abs(m_curr_curvature) < 0.025 && m_iceMode != "Ice") // gentle curvature
        targetSpeed_ms = targetSpeed_ms > 17. ? 17 : targetSpeed_ms;
      else // curve
      {
        if (abs_curvature > 0.07)
          abs_curvature = 0.07; // max curvature

        if (targetSpeed_ms > 20)
          targetSpeed_ms = 20;

        double low_speed_mode = targetSpeed_ms - (450 * abs_curvature);
        if (low_speed_mode < 9)
          low_speed_mode = 9;
        targetSpeed_ms = low_speed_mode > targetSpeed_ms ? targetSpeed_ms : low_speed_mode;
      }

      ROS_INFO("Current Target Speed: %lf", targetSpeed_ms);

      if (targetSpeed_ms > m_vehicleState.velocity)
      {
        m_drivingInput.accel = 1.0;
        m_drivingInput.brake = 0.0;
      }
      else
      {
        m_drivingInput.accel = 0.0;
        m_drivingInput.brake = 1.0;
      }
    }
  }

  /**
   * brief: Find the left lane and the right lane, then change to the actual
   * driving lane. input: m_polyLanes output: m_midPolyLane
   */
  void findDrivingWay()
  {
    // TODO

    m_midPolyLane.frame_id = m_vehicle_namespace_param + "/body";
    m_rosPubDrivingWay.publish(m_midPolyLane);

    double a0[2];
    double a1[2];
    double a2[2];
    double a3[2];
    for (auto laneBound : m_polyLanes.polyfitLanes)
    {
      if (laneBound.id == "0") // left lane
      {
        // TODO
        a0[0] = laneBound.a0;
        a1[0] = laneBound.a1;
        a2[0] = laneBound.a2;
        a3[0] = laneBound.a3;
        prev_polyfit[0][0] = laneBound.a0;
        prev_polyfit[0][1] = laneBound.a1;
        prev_polyfit[0][2] = laneBound.a2;
        prev_polyfit[0][3] = laneBound.a3;
      }
      else if (laneBound.id == "1") // right lane
      {
        // TODO
        a0[1] = laneBound.a0;
        a1[1] = laneBound.a1;
        a2[1] = laneBound.a2;
        a3[1] = laneBound.a3;
        prev_polyfit[1][0] = laneBound.a0;
        prev_polyfit[1][1] = laneBound.a1;
        prev_polyfit[1][2] = laneBound.a2;
        prev_polyfit[1][3] = laneBound.a3;
      }
    }

    m_midPolyLane.a0 = (a0[0] + a0[1]) / 2.;
    m_midPolyLane.a1 = (a1[0] + a1[1]) / 2.;
    m_midPolyLane.a2 = (a2[0] + a2[1]) / 2.;
    m_midPolyLane.a3 = (a3[0] + a3[1]) / 2.;

    ROS_INFO("(a0, a1, a2, a3) : (%lf, %lf, %lf, %lf)", m_midPolyLane.a0, m_midPolyLane.a1, m_midPolyLane.a2, m_midPolyLane.a3);
  }

  /**
   * brief: Find the steering angle for driving in the driving lane.
   * input: m_midPolyLane
   * output: m_drivingInput.steering
   */
  void calcSteeringAngle()
  {
    // TODO

    double a0 = m_midPolyLane.a0;
    double a1 = m_midPolyLane.a1;
    double a2 = m_midPolyLane.a2;
    double a3 = m_midPolyLane.a3;
    double l_x_d = m_lookAhead_param;
    double abs_a2 = a2 > 0 ? a2 : -1 * a2;
    if (abs_a2 > 0.02)
    {
      abs_a2 = 0.02; // saturate
    }
    double g_x = 10 - 300 * abs_a2;
    ROS_INFO("Current Lookahead Distance: %lf", g_x);
    double g_y = (a3 * l_x_d * l_x_d * l_x_d) + (a2 * l_x_d * l_x_d) + (a1 * l_x_d) + (a0);
    double l_d = sqrt(g_x * g_x + g_y * g_y);
    double e_l_d = g_y;
    double L = 1.402 + 1.646;

    double delta = atan2((2 * L * e_l_d), (l_d * l_d));
    prev_delta = delta;
    m_drivingInput.steering = delta;

    /**
     * set parameter for using somewhere
     */
    m_curr_curvature = abs(a2 * 2);
    prev_l_x_d = l_x_d;
    prev_delta = delta;
    ROS_INFO("steering angle: %lf\n", delta);
  }

  void publishVehicleInput()
  {
    m_rosPubVehicleInput.publish(m_drivingInput);
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "autonomous_driving");

  AutonomousDriving autonomousDriving;

  double prev_csvLaneMarkTime = ros::Time::now().toSec();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    autonomousDriving.polyfitLane();
    autonomousDriving.findDrivingWay();
    autonomousDriving.controlVehicleSpeed();
    autonomousDriving.calcSteeringAngle();
    autonomousDriving.publishVehicleInput();

    if ((ros::Time::now().toSec() - prev_csvLaneMarkTime) > 1.0)
    {
      prev_csvLaneMarkTime = ros::Time::now().toSec();
    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
