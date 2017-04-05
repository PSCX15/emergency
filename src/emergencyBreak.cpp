#include "ros/ros.h"
#include "emergency/servo_command.h"
#include "std_msgs/Bool.h"

ros::Publisher heartbeat; 

void sendHeartBeat(const ros::TimerEvent&){
	std_msgs::Bool msg;
	msg.data = true;
	heartbeat.publish(msg);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "emergencyNode");
  ros::NodeHandle n;
  
  heartbeat = n.advertise<std_msgs::Bool>("bondServo",100);
  ros::Publisher command_pub = n.advertise<emergency::servo_command>("servo_command", 1000);
	
	ros::Timer timer = n.createTimer(ros::Duration(1.0), sendHeartBeat);
  

	
	ros::spin();
	return 0;
}
