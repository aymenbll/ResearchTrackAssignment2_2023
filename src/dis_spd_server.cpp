#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2023/PlanningAction.h>
#include <my_robot_control/Pos_vel.h>
#include <my_robot_control/Cor_ser.h>
#include <my_robot_control/Dis_spd.h>
#include <geometry_msgs/Point.h>
#include<nav_msgs/Odometry.h>
#include <cmath>
#include <iostream>
using namespace std;

// Global variables to store robot's position, velocity, target coordinates, and calculated distance and speed
float pos_x;
float pos_y;
float vel_x;
float target_x;
float target_y;
float dx;
float dy;
float d;
float spd=0.0;
int i;
float spdf;

// Callback function for receiving robot position and velocity
void CallBack1(const my_robot_control::Pos_vel::ConstPtr& custom)
{
  

  pos_x = custom->pos_x;
  pos_y = custom->pos_y;
  vel_x = custom->vel_x;


}

// Callback function for receiving the goal from the action client
void CallBack2(const assignment_2_2023::PlanningActionGoal::ConstPtr& goal1)
{
  
  target_x = goal1->goal.target_pose.pose.position.x;
  target_y = goal1->goal.target_pose.pose.position.y;
}

// Service callback function to provide distance from the target and average speed
bool CallBack3(my_robot_control::Dis_spd::Request&req, my_robot_control::Dis_spd::Response &res){

	  // Calculated distance and average speed over a period of time
	res.dis = d;
 	res.speed =spdf;
 	
 return true;
}


int main(int argc, char **argv)
{
	  // Initialize the ROS node
	  ros::init(argc, argv, "dis_speed_node");
	  ros::NodeHandle nh;
	    // Subscribe to robot's position and velocity topic
	  ros::Subscriber sub = nh.subscribe("/custom_pos_vel", 10, CallBack1);
	    // Subscribe to the goal topic from the action client
	  ros::Subscriber sub2= nh.subscribe("reaching_goal/goal", 10, CallBack2);
	    // Create a service server for providing distance from the target and average speed
	  ros::ServiceServer service= nh.advertiseService("/distance_avgspeed",CallBack3);
	   
	     // Main loop
	   while(ros::ok() ){
	  
	       // Accumulate speed over a period of time
	   for(i=0;i<10;i++){
	   spd=spd+vel_x;
	   ros::spinOnce();
	   
	   }
	       // Calculate average speed
	   spdf=spd/i;
	   i=0;
	   spd=0;
	   
	       // Calculate distance from the target using Euclidean distance formula
	   dx=target_x-pos_x;
	   dy=target_y-pos_y;
	   d=sqrt((dx*dx)+(dy*dy));
	 
	   }

	   ros::spinOnce();
	  
	  
	  return 0;
  }
