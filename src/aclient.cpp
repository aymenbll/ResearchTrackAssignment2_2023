#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2023/PlanningAction.h>
#include <my_robot_control/Pos_vel.h>
#include <geometry_msgs/Point.h>
#include <nav_msgs/Odometry.h>
#include <iostream>

using namespace std;

ros::Publisher pub_pos_vel;

double fbX = 0.0;
double fbY=0.0;
string state;
double od_px;
double od_py;
double od_vx;
double od_vz;


// Callback function for action feedback
void CallBack1(const assignment_2_2023::PlanningActionFeedback::ConstPtr& feed)
{
    // Extracting feedback information
  fbX = feed->feedback.actual_pose.position.x;
  fbY = feed->feedback.actual_pose.position.y;
  state = feed->feedback.stat;
    // Displaying feedback information
  ROS_INFO("the robot bosition is (%d, %d) and state is: %s ",fbX, fbY, state);
}

// Callback function for the /odom topic
void CallBack2(const nav_msgs::Odometry::ConstPtr& od)
{
  
    // Extracting information from the /odom message
  od_px = od->pose.pose.position.x;
  od_py = od->pose.pose.position.y;
  od_vx = od->twist.twist.linear.x;
  od_vz = od->twist.twist.linear.z;
  
  // Creating a custom message and publishing it
  my_robot_control::Pos_vel custom;
  custom.pos_x=od_px;
  custom.pos_y=od_py;
  custom.vel_x=od_vx;
  custom.vel_z=od_vz;
  pub_pos_vel.publish(custom);
  

  
  
}






int main(int argc, char **argv){

	ros::init(argc, argv, "aclient");
	ros::NodeHandle nh;
	
	  // Creating an action client
	actionlib::SimpleActionClient<assignment_2_2023::PlanningAction>ac("reaching_goal", true);
	
	  // Waiting for the action server to start
	ROS_INFO("Waiting for action server to start.");
	  ac.waitForServer();

	ROS_INFO("Action server started, sending goal.");
	  assignment_2_2023::PlanningGoal target;
	  
	  // Setting up subscribers and publisher
	ros::Subscriber sub_fb = nh.subscribe("reaching_goal/feedback",10,CallBack1);
	ros::Subscriber sub_pos_vel = nh.subscribe("odom",10,CallBack2);
	pub_pos_vel = nh.advertise<my_robot_control::Pos_vel>("custom_pos_vel",10);  
	
	  // Main loop to interact with the action server
	int choice, x, y;
	
	while(ros::ok()){
	
		    // User interaction
		cout << "Enter your choice \n1- for setting target \n2- for cancel the process \n3- for getting the coordinates and the state of the robot): ";
    		cin >> choice;
    		
    		if (choice == 1){
    		
      	      	   // Setting a new target
		      cout << "Enter the target (x,y).\n";
		      cout << "Enter the value of x: \n";
		      cin >> x;
		      cout << "Enter the value of y: \n";
		      cin >> y;
		      ac.waitForServer(); 

		      target.target_pose.pose.position.x = x;
		      target.target_pose.pose.position.y = y;

		      ac.sendGoal(target);
		      
        	 } else if (choice == 2) {
        	 
		     // Canceling the operation
		      cout << "You cancelled the Operation.\n";
		      ac.cancelGoal();
		      break;
		 } else if(choice == 3) {
		 
      		  // Displaying current position and state
		      ROS_INFO("the position of X is : [%f\n]",fbX );
		      ROS_INFO("the position of Y is : [%f]\n",fbY );
		      ROS_INFO("the status : ");
		     cout<<state<<std::endl;
		      
		 } else{
		      cout<<"you choosed wrong answer";
		 }


		    ros::spinOnce();
		    
	}
	
	
	return 0;

	
}
	  



