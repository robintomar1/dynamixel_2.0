#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char **argv)
{

ros::init(argc, argv, "trigger_catcher");
ros::NodeHandle n;
ros::Publisher pub = n.advertise<std_msgs::String>("/pose_name", 1000);
ros::Publisher intro_pub = n.advertise<std_msgs::String>("/intro_pose", 1000);

ros::Rate loop_rate(1);
while (ros::ok())
{ 
	ifstream inputFile("/home/robin/Desktop/test.txt");
	string line;
	while (getline(inputFile, line)) 
		{
			istringstream ss(line);
			string heart;
			ss >> heart;
			std_msgs::String msg;
			msg.data = ss.str();
			if (msg.data == "attention" || msg.data =="thinking" || msg.data =="weather" || msg.data =="thankyou" || msg.data =="group_greeting" || msg.data =="hello" || msg.data =="move_neck")
				{pub.publish(msg);
				break;}
			if(msg.data == "intro" || msg.data == "intro_movement")
			{intro_pub.publish(msg);
				break;}	
		}
	ros::spinOnce();
	loop_rate.sleep();
}

return 0;

}
