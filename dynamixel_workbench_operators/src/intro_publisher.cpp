#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string.h>
#include <sstream>

std::string mypose;
std_msgs::String mymsg;
int flag =0;
 void poseCallback(const std_msgs::String::ConstPtr& msg)
  {
     mypose = msg->data.c_str();
     if(0 == (mypose.compare("intro")  ))
     {
     	flag=1;
     }
     if(0 == (mypose.compare("intro_movement")  ))
     {
     	flag=2;
     }
     if(0 == (mypose.compare("talking_hand_1")  ))
     {
     	flag=3;
     }
  }
  
  
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "intro_publisher");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/pose_name", 1000);
  ros::Subscriber sub = n.subscribe("intro_pose", 1000, poseCallback);

    while ( ros::ok()) {
    	if (1==flag )
    
    {  mymsg.data="left_hand_intro_final";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(9).sleep();
     	 mymsg.data="head_left_intro";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(3).sleep();
     	 mymsg.data="all_finger_open";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(2).sleep();
     	  mymsg.data="all_finger_close";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(2).sleep();
     	 mymsg.data="left_hand_home";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="right_hand_intro_final";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(9).sleep();
     	 mymsg.data="head_right_intro";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(3).sleep();
     	  mymsg.data="all_finger_open_r";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2).sleep();
     	  mymsg.data="all_finger_close_r";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2).sleep();
     	 mymsg.data="right_hand_home";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="head_home";
     	 chatter_pub.publish(mymsg);
     	 flag=0;
     }
     else if (2==flag)
     {
     	mymsg.data="fold_both_elbow";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(4).sleep();
     	 mymsg.data="move_forward";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(3).sleep();
     	 mymsg.data="rotate_both_outward";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(2).sleep();
     	  mymsg.data="all_finger_open";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(2).sleep();
     	 mymsg.data="all_finger_open_r";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2).sleep();
     	 mymsg.data="all_finger_close";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2).sleep();
     	 mymsg.data="all_finger_close_r";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2).sleep();
     	  mymsg.data="lift_both_outwards";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(4).sleep();
     	  mymsg.data="left_hand_home";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="right_hand_home";
     	 chatter_pub.publish(mymsg);
    
     	//code for intro_movement
     	flag=0;
     }
     else if (3==flag)
     {
     	mymsg.data="talking_hand_1_0";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(3).sleep();
     	 mymsg.data="talking_hand_1_1";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(3).sleep();
     	 mymsg.data="talking_hand_1_2";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(2.5).sleep();
     	  mymsg.data="talking_hand_1_3";
     	 chatter_pub.publish(mymsg);
     	 ros::Duration(2.5).sleep();
     	 mymsg.data="talking_hand_1_4";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2.5).sleep();
     	 mymsg.data="talking_hand_1_5";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2.5).sleep();
     	 mymsg.data="talking_hand_1_6";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2.5).sleep();
     	  mymsg.data="talking_hand_1_7";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(2.5).sleep();
     	  mymsg.data="left_hand_home";
     	 chatter_pub.publish(mymsg);
     	  ros::Duration(5).sleep();
     	 mymsg.data="right_hand_home";
     	 chatter_pub.publish(mymsg);
    
     	//code for intro_movement
     	flag=0;
     }
        ros::spinOnce(); //normally, can simply do: ros::spin();  

    }


  return 0;
}
