#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2023/PlanningAction.h>
#include <assignment_2_2023/PlanningAction.h>
#include <my_robot_control/Pos_vel.h>
#include <my_robot_control/Cor_ser.h>
#include <geometry_msgs/Point.h>
#include<nav_msgs/Odometry.h>
#include <iostream>

// Global variables to store the target coordinates
float target_x;
float target_y;

// Callback function for receiving the goal from the action client
void CallBack2(const assignment_2_2023::PlanningActionGoal::ConstPtr& goal)
{
  
	    // Extracting the target coordinates from the received goal
	  target_x = goal->goal.target_pose.pose.position.x;
	  target_y = goal->goal.target_pose.pose.position.y;
}

// Service callback function to provide the last target coordinates
bool CallBack1(my_robot_control::Cor_ser::Request&req, my_robot_control::Cor_ser::Response &res){

	    // Filling the response with the last target coordinates
	res.goal_x = target_x;
 	res.goal_y = target_y;
 	
 return true;
}


int main(int argc, char **argv)
{
	    // Initialize the ROS node
	  ros::init(argc, argv, "target_server");
	  ros::NodeHandle nh;

	    // Create a service server for providing the last target coordinates
	   ros::ServiceServer target_ser = nh.advertiseService("/Last_Target",CallBack1);
	   
	    // Create a subscriber to receive goals from the action client
	   ros::Subscriber sub = nh.subscribe("reaching_goal/goal", 10, CallBack2);

	    // Spin to keep the node alive and process callbacks
	  ros::spin();
  
  
  return 0;
  }
