#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>



std_msgs::Float64 velocity_left;
std_msgs::Float64 velocity_right;


 void velocity_callback(const sensor_msgs::JointState::ConstPtr& msg)
{
	velocity_left.data=msg->velocity[0];
	velocity_right.data=msg->velocity[1];

}



int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "velocity_publisher");

  ros::NodeHandle n;
  
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 10);
  ros::Publisher velocity_left_pub = n.advertise<std_msgs::Float64>("velocity_left", 1000);
  ros::Publisher velocity_right_pub = n.advertise<std_msgs::Float64>("velocity_right", 1000);
  ros::Subscriber sub = n.subscribe("/dynamixel_workbench/joint_states", 1000, velocity_callback);
  

  velocity_left.data=0.0;
  velocity_right.data=0.0;
  
  
  // initial position
  double x = 0.0; 
  double y = 0.0;
  double th = 0;
  // velocity
  double vx = 0.4;
  double vy = 0.0;
  double vth = 0.4;

  
  ros::Time current_time;
  ros::Time last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();
  
  tf::TransformBroadcaster broadcaster;
  const double degree = M_PI/180;
  // message declarations
  geometry_msgs::TransformStamped odom_trans;
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "chasis";
  
  
  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    //publishing left and right wheel velocities
    velocity_left_pub.publish(velocity_left);
    velocity_right_pub.publish(velocity_right);
    
    //calculating linear and angular velocities from wheel velocities
   vth = (double)(velocity_right.data-velocity_left.data)/0.430;//43 cm being the wheel separation
   vx = (velocity_left.data + velocity_right.data)/2;
   vy = 0;//since wheel dvive is not omnidirectional
   ROS_INFO("linear velocity %ld    angular velocity %ld ",vx,vth);
    current_time = ros::Time::now(); 

		double dt = (current_time - last_time).toSec();
		double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
		double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
		double delta_th = vth * dt;
   ROS_INFO("dt %ld delta x %ld    delta y %ld  delta z %ld ",dt,delta_x,delta_y,delta_th);
		x += delta_x;
		y += delta_y;
		th += delta_th;

		geometry_msgs::Quaternion odom_quat;	
		odom_quat = tf::createQuaternionMsgFromRollPitchYaw(0,0,th);

		// update transform
		odom_trans.header.stamp = current_time; 
		odom_trans.transform.translation.x = x; 
		odom_trans.transform.translation.y = y; 
		odom_trans.transform.translation.z = 0.0;
		odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(th);
		
		//filling the odometry
		nav_msgs::Odometry odom;
		odom.header.stamp = current_time;
		odom.header.frame_id = "odom";
		odom.child_frame_id = "chasis";

		// position
		odom.pose.pose.position.x = x;
		odom.pose.pose.position.y = y;
		odom.pose.pose.position.z = 0.0;
		odom.pose.pose.orientation = odom_quat;

		//velocity
		odom.twist.twist.linear.x = vx;
		odom.twist.twist.linear.y = vy;
		odom.twist.twist.linear.z = 0.0;
		odom.twist.twist.angular.x = 0.0;
		odom.twist.twist.angular.y = 0.0;
		odom.twist.twist.angular.z = vth;
		//covarience
		
		odom.covariance=[0.01  0.0  0.0  0.0  0.0  0.0,
 						0.0  0.01  0.0  0.0  0.0  0.0,
 						0.0   0.0 0.01  0.0  0.0  0.0,
 						0.0   0.0  0.0  0.1  0.0  0.0,
 						0.0   0.0  0.0  0.0  0.1  0.0,
 						0.0   0.0  0.0  0.0  0.0  0.1]

		last_time = current_time;

		// publishing the odometry and the new tf
		broadcaster.sendTransform(odom_trans);
		odom_pub.publish(odom);

    ros::spinOnce();
    loop_rate.sleep();
    
  }

  return 0;
}

