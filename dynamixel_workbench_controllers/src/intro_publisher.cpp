#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string.h>
#include <sstream>

std::string mypose;
std_msgs::String mymsg;

 void poseCallback(const std_msgs::String::ConstPtr& msg)
  {
     mypose = msg->data.c_str();
     if(0 == (strcmp(mypose,"intro")  )
     {  mymsg.data="left_hand_intro_final";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(5).sleep();
     	 mymsg.data="head_left_intro";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(5).sleep();
     	 mymsg.data="left_hand_home";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="right_hand_intro_final";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="head_right_intro";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="right_hand_home";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="head_home";
     	 chatter_pub.publish(mymsg);
     }
  }
  
  
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "intro_publisher");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/pose_name", 1000);
  ros::Subscriber sub = n.subscribe("intro_pose", 1000, poseCallback);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    ros::spinOnce();
  }


  return 0;
}
