#include "ros/ros.h"
#include "emergency/servo_command.h"
#include <bondcpp/bond.h>

#include "std_msgs/String.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "emergencyNode");
  ros::NodeHandle n;
  
  ros::Publisher bondTimonier = n.advertise<std_msgs::String>("bondTimonier",100);
  ros::Publisher command_pub = n.advertise<emergency::servo_command>("servo_command", 1000);
	
	std::string id = "99656856";
	
	bond::Bond* bondTimo = new bond::Bond("bondTimonier", id);
	
	while(true){
		std_msgs::String msg;
		msg.data = id.c_str();
		bondTimonier.publish(msg);
		bondTimo->start();
		if (!bondTimo->waitUntilFormed(ros::Duration(1.0))){
    	ROS_ERROR("timonier unconnected to emergencyBreak");
 		}
 		else{
 			ROS_INFO("timonier connected to emergencyBreak");
 			break;
 		}
		ros::Duration(1.0).sleep();
	}
// ... do things with B ...
	bondTimo->waitUntilBroken(ros::Duration(-1));
	printf("Timonier has broken the bond\n");
	return 0;
}
