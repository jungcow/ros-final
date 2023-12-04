#include <math.h>
#include <ros/ros.h>
#include <string>
#include <eigen3/Eigen/Dense>
#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutputs.h"
#include "autonomous_msg/VehicleOutput.h"
#include "autonomous_msg/LanePointData.h"
#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/EnvironmentDetected.h"
#include "autonomous_msg/PointWithArclength.h"
#include "autonomous_msg/SpeedLimit.h"
#include "std_msgs/Float64.h"
#include <map>
#include <set>

using namespace std;

class AutonomousDriving
{
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
  bool m_use_manual_inputs = true;

public:
  AutonomousDriving()
  {

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
                           true);
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

  void printLaneInfo(void)
  {
    // ROS_INFO("detected polyLane: %s, %ld", m_polyLanesDetected.frame_id, m_polyLanesDetected.polyfitLanes.size());
    // ROS_INFO("ROILane lane Info: %s, %s, %ld", m_ROILanes.frame_id.c_str(), m_ROILanes.id.c_str(), m_ROILanes.lane.size());
  }

  double coord_distance(int x1, int y1, int x2, int y2)
  {
    return sqrt(pow(2., (x1 - x2)) + pow(2., (y1 - y2)));
  }

  std::vector<int> get_index_inrange(const Eigen::VectorXd &arr, double start, double end)
  {
    std::vector<int> idx;
    for (int i = 0; i < arr.size(); i++)
    {
      if (arr[i] >= start && arr[i] < end)
      {
        idx.push_back(i);
      }
    }
    return idx;
  }

  std::pair<std::vector<double>, std::vector<size_t>> peak_intensity(autonomous_msg::LanePointData::_point_type &points, int bin_size)
  {
    Eigen::VectorXd X(500);
    Eigen::VectorXd Y(500);

    for (size_t i = 0; i < points.size(); i++)
    {
      double x = points[i].x;
      double y = points[i].y;

      X(i) = x;
      Y(i) = y;
    }

    double min_y = std::ceil(Y.minCoeff());
    double max_y = std::ceil(Y.maxCoeff());

    ROS_INFO("min_y, max_y: (%lf, %lf)", min_y, max_y);

    std::vector<double> y_val, ymean;
    std::vector<size_t> count_arr;

    for (int i = 0; i < bin_size; i++)
    {
      y_val.push_back(min_y + (max_y - min_y) * i / (bin_size - 1));
      ROS_INFO("Y bin: %lf", y_val.back());
    }

    for (size_t i = 0; i < y_val.size() - 1; i++)
    {
      std::vector<int> index = get_index_inrange(Y, y_val[i], y_val[i + 1]);

      size_t count = index.size();
      count_arr.push_back(count);
      ymean.push_back((y_val[i] + y_val[i + 1]) / 2);
    }
    return {ymean, count_arr};
  }

  void polyfitLane()
  {

    // ROS_INFO("m_ROILanePoints: %s, %s, %ld", m_ROILanePoints.frame_id, m_ROILanePoints.id, m_ROILanePoints.point.size());
    // ROS_INFO("m_ROILane: %s, %s, %ld", m_ROILanes.frame_id, m_ROILanes.id, m_ROILanes.lane.size());
    m_polyLanes.frame_id = m_vehicle_namespace_param + "/body";
    m_polyLanes.polyfitLanes.clear();

    m_polyLanesDetected.frame_id = m_vehicle_namespace_param + "/body";
    m_polyLanesDetected.polyfitLanes.clear();

    // if (!m_ROILanePoints.point.empty())
    // {
    //   for (int i = 0; i < m_ROILanePoints.point.size(); i++)
    //   {
    //     ROS_INFO("point info: %lf, %lf, %lf", m_ROILanePoints.point[i].x, m_ROILanePoints.point[i].y, m_ROILanePoints.point[i].arclength);
    //   }
    // }

    m_ROILanes.frame_id = m_vehicle_namespace_param + "/body";
    m_ROILanes.lane.clear();

    // TODO
    // Perceive lane info (make m_polyLanes)

    if (m_ROILanePoints.point.size())
      peak_intensity(m_ROILanePoints.point, 10);

    // guassian_blur();
    // detectLine(m_ROILanePoints);
    // separateLine(m_ROILanePoints);

    for (auto i_lane = 0; i_lane < m_ROILanes.lane.size(); i_lane++)
    {
      // Eigen의 매트릭스를 차선의 포인트 갯수에 맞게 생성한다.
      int down_size = (m_ROILanes.lane[i_lane].point.size());
      Eigen::MatrixXd X_Matrix(down_size, 4);
      Eigen::VectorXd y_Vector(down_size);
      Eigen::VectorXd a_Vector(4);

      // Eigen의 매트릭스에 포인트를 넣어준다.
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

      m_polyLanes.polyfitLanes.push_back(polyLane);
    }

    m_rosPubPolyLanes.publish(m_polyLanes);

    m_rosPubPolyLanesDetected.publish(m_polyLanesDetected);
  }

  void controlVehicleSpeed()
  {
    // TODO
    // Change this function to make the vehicle follow target speed (input of the function(parameters) can be modified)
    // if(m_use_manual_inputs == false){
    //   double targetSpeed_ms = 10.0;

    //   if (targetSpeed_ms > m_vehicleState.velocity)
    //   {
    //     m_drivingInput.accel = 1.0;
    //     m_drivingInput.brake = 0.0;
    //   }
    //   else
    //   {
    //     m_drivingInput.accel = 0.0;
    //     m_drivingInput.brake = 1.0;
    //   }
    // }
    double targetSpeed_ms = 10.0;

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
      }
      if (laneBound.id == "1") // right lane
      {
        // TODO
        a0[1] = laneBound.a0;
        a1[1] = laneBound.a1;
        a2[1] = laneBound.a2;
        a3[1] = laneBound.a3;
      }
    }

    m_midPolyLane.a0 = (a0[0] + a0[1]) / 2.;
    m_midPolyLane.a1 = (a1[0] + a1[1]) / 2.;
    m_midPolyLane.a2 = (a2[0] + a2[1]) / 2.;
    m_midPolyLane.a3 = (a3[0] + a3[1]) / 2.;

    ROS_INFO("(a0, a1, a2, a3) : (%lf, %lf, %lf, %lf)", a0, a1, a2, a3);
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
    double l_x_d = m_lookAhead_param - a2 * 2;
    double g_x = l_x_d;
    double g_y = (a3 * l_x_d * l_x_d * l_x_d) + (a2 * l_x_d * l_x_d) + (a1 * l_x_d) + (a0);
    double l_d = sqrt(g_x * g_x + g_y * g_y);
    double e_l_d = g_y;
    double L = 1.402 + 1.646;
    double delta = atan2((2 * L * e_l_d), (l_d * l_d));
    ROS_INFO("steering angle: %lf\n", delta);
    m_drivingInput.steering = delta;

    //   if (!m_use_manual_inputs)
    //   {
    //     m_drivingInput.steering = 0.0;
    //   }
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
  ros::Rate loop_rate(1);
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
