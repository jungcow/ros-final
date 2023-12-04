#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <ros/ros.h>
#include <string>

struct point {
    double x = 0.0;
    double y = 0.0;
};

class SaveParkingCsv {
  ////////////////////////////////////////////////////////////////////////////////
  // 0. Constructor & destructure
    protected:
        ros::NodeHandle m_rosNodeHandler;
        std::string m_path_csv = "src/final_project/final_simulator/csv";

        double m_dLength = 4.6;
        double m_laneWidth = 4.0;
        double m_resolution = 0.1;
        

    public:
        SaveParkingCsv() {}

        ~SaveParkingCsv() {}

    public:

        void CreateParkingLot(const int lane_num, const double dist, const double yaw_deg) {

            int left_num = lane_num/2 - 1;      // center lane's left line number
            int right_num = left_num + 1;       // center lane's right line number
            int last_num = right_num + 1;

            std::string left_num_string = std::to_string(left_num);
            std::string right_num_string = std::to_string(right_num);
            std::string last_num_string = std::to_string(last_num);

            std::string left_csv_path = m_path_csv + "/KusvLane_" + left_num_string + ".csv";
            std::string right_csv_path = m_path_csv + "/KusvLane_" + right_num_string + ".csv";
            std::string last_csv_path = m_path_csv + "/KusvLane_" + last_num_string + ".csv";

            std::vector<double> left_last_point = GetLastPointFromCsv(left_csv_path);
            std::vector<double> right_last_point = GetLastPointFromCsv(right_csv_path);

            // ROS_INFO("last (%f,%f), (%f,%f)",left_last_point.at(0), left_last_point.at(1), right_last_point.at(0), right_last_point.at(1));

            std::vector<double> norm_left = GetNormalVector(left_csv_path);
 
            double center_x = (left_last_point.at(0)+right_last_point.at(0))/2.0;
            double center_y = (left_last_point.at(1)+right_last_point.at(1))/2.0;

            double left_vec_x = left_last_point.at(0) - center_x;
            double left_vec_y = left_last_point.at(1) - center_y;
        
            double right_vec_x = right_last_point.at(0) - center_x;
            double right_vec_y = right_last_point.at(1) - center_y;

            double parking_center_x = center_x + dist*norm_left.at(0);
            double parking_center_y = center_y + dist*norm_left.at(1);

            double parking_left_x = parking_center_x + 5.5*left_vec_x;
            double parking_left_y = parking_center_y + 5.5*left_vec_y;

            double parking_right_x = parking_center_x + 5.5*right_vec_x;
            double parking_right_y = parking_center_y + 5.5*right_vec_y;

            double norm_vec_rad = atan2(norm_left.at(1),norm_left.at(0));
            double yaw_rad = yaw_deg * M_PI/180.0;

            double target_rad = norm_vec_rad + yaw_rad;

            std::vector<point> ref_parking_points = FillReferenceParkingLot();
            // ROS_INFO("size %d",parking_points.size());

            std::vector<point> center_parking_lot = TransformRefParkingLot(ref_parking_points, parking_center_x, parking_center_y, target_rad);
            std::vector<point> left_parking_lot = TransformRefParkingLot(ref_parking_points, parking_left_x, parking_left_y, target_rad);
            std::vector<point> right_parking_lot = TransformRefParkingLot(ref_parking_points, parking_right_x, parking_right_y, target_rad);
            
            PutParkingLot(center_parking_lot, right_csv_path);
            PutParkingLot(left_parking_lot, left_csv_path);
            PutParkingLot(right_parking_lot, last_csv_path);

            ROS_INFO_STREAM("**Save csv data**");
        }

        void PutParkingLot(std::vector<point> parking_lot, const std::string csv_path) {
            std::fstream outputFile(csv_path, std::ios::app);
            if (outputFile.is_open()) {
                for (int i = 0; i < parking_lot.size(); i++) {
                    outputFile << "\n" << parking_lot[i].x << "," << parking_lot[i].y;
                }

                outputFile.close();
            }
        }

        std::vector<double> GetLastPointFromCsv(const std::string csv_path) {
            std::vector<double> last_point;

            std::ifstream input(csv_path);
            if(!input.is_open()) {
                ROS_ERROR_STREAM("can not open lane");
                return last_point;
            }

            std::vector<std::string> last_point_string;
            while(input) {

                std::string token;

                getline(input, token, ',');
                if(token == std::string("")) {
                    break;
                }
                last_point_string.clear();
                last_point_string.push_back(token);
                getline(input, token, '\n');
                last_point_string.push_back(token);
            }

            double tmp;
            tmp = std::stod(last_point_string.at(0));
            last_point.push_back(tmp);
            tmp = std::stod(last_point_string.at(1));
            last_point.push_back(tmp);

            return last_point;
        }

        std::vector<double> GetNormalVector(const std::string csv_path) {
            std::vector<double> norm;

            std::ifstream input(csv_path);
            if(!input.is_open()) {
                ROS_ERROR_STREAM("can not open lane");
                return norm;
            }

            std::vector<std::string> last_point_string;
            double x = 0.0;
            double y = 0.0;
            double prev_x = 0.0;
            double prev_y = 0.0;

            int iter = 0;
            while(input) {

                std::string token;

                getline(input, token, ',');
                if(token == std::string("")) {
                    break;
                }
                if(last_point_string.size() > 1 && iter > 1) {
                    prev_x = std::stod(last_point_string.at(0));
                    prev_y = std::stod(last_point_string.at(1));
                }
                else {
                    iter++;
                }
                last_point_string.clear();
                last_point_string.push_back(token);
                getline(input, token, '\n');
                last_point_string.push_back(token);
            }

            x = std::stod(last_point_string.at(0));
            y = std::stod(last_point_string.at(1));

            double v_x = x-prev_x;
            double v_y = y-prev_y;

            norm.push_back(v_x);
            norm.push_back(v_y);
        
            return norm;
        }

        std::vector<point> FillReferenceParkingLot() {
            std::vector<point> filled_points;

            double parking_lot_w = 2*m_dLength;
            double parking_lot_h = 1.5*m_laneWidth;

            int num_w = parking_lot_w/m_resolution;
            int num_h = parking_lot_h/m_resolution;

            for(int i=0; i<num_w; i++) {
                point upper;
                upper.x = 4.6 - i*m_resolution;
                upper.y = 3.0;

                filled_points.push_back(upper);
            }
            for(int i=0; i<num_h; i++) {
                point left;
                left.x = -4.6;
                left.y = 3.0 - i*m_resolution;

                filled_points.push_back(left);
            }
            for(int i=0; i<num_w; i++) {
                point lower;
                lower.x = -4.6 + i*m_resolution;
                lower.y = -3.0;
                
                filled_points.push_back(lower);
            }
            for(int i=0; i<num_h; i++) {
                point right;
                right.x = 4.6;
                right.y = -3.0 + i*m_resolution;

                filled_points.push_back(right);
            }

            return filled_points;
        }

        std::vector<point> TransformRefParkingLot(std::vector<point>& ref_points, const double x, const double y, const double target_rad) {
            std::vector<point> transformed_parking_points;

            std::vector<point> four_points;
            int id=0;

            for(int i=0; i<ref_points.size(); i++) {
                point t_point;
                t_point.x = ref_points.at(i).x*cos(-target_rad) - ref_points.at(i).y*sin(-target_rad);
                t_point.y = ref_points.at(i).x*sin(-target_rad) + ref_points.at(i).y*cos(-target_rad);

                t_point.x += x;
                t_point.y += y;

                if(i == 0 || i == 93 || i == 153 || i == 245) {
                    ROS_INFO("parking lot point[%d] : %f,%f",t_point.x,t_point.y);
                }

                transformed_parking_points.push_back(t_point);
            }

            return transformed_parking_points;
        }
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "parking_lot_maker");

  SaveParkingCsv SaveParkingCsv;

  SaveParkingCsv.CreateParkingLot(4, 100.0, 30.0);

  return 0;
}
