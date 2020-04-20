#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

void odom_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
	static int state = 0;
	// Set our initial shape type to be a cube
	uint32_t shape = visualization_msgs::Marker::CUBE;
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	visualization_msgs::Marker marker;
	// Set the frame ID and timestamp.  See the TF tutorials for information on these.
	marker.header.frame_id = "odom";
	marker.header.stamp = ros::Time::now();

	// Set the namespace and id for this marker.  This serves to create a unique ID
	// Any marker sent with the same namespace and id will overwrite the old one
	marker.ns = "basic_shapes";
	marker.id = 0;

	// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
	marker.type = shape;

	// Set the scale of the marker -- 1x1x1 here means 1m on a side
	marker.scale.x = 0.1;
	marker.scale.y = 0.1;
	marker.scale.z = 0.1;

	// Set the color -- be sure to set alpha to something non-zero!
	marker.color.r = 0.0f;
	marker.color.g = 0.0f;
	marker.color.b = 1.0f;
	marker.color.a = 1.0;

	if(!state)
	{
		// first cube 
		// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
		marker.action = visualization_msgs::Marker::ADD;

		// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
		marker.pose.position.x = 3;
		marker.pose.position.y = 1;
		marker.pose.position.z = 0;
		marker.pose.orientation.x = 0.0;
		marker.pose.orientation.y = 0.0;
		marker.pose.orientation.z = 0.0;
		marker.pose.orientation.w = 1.0;


		//    marker.lifetime = ros::Duration();
		ROS_INFO("first marker");

		marker_pub.publish(marker);

		if(msg->pose.pose.position.x <= 3.5 && msg->pose.pose.position.x >= 2.5 && msg->pose.pose.position.y <= 1.5 && msg->pose.pose.position.y >= 0.5)
		{
			ros::Duration(5).sleep();

			marker.action = visualization_msgs::Marker::DELETEALL;
			marker_pub.publish(marker);
			state = 1;
			ROS_INFO("Picked up");
		}
	}
	else
	{
		// second cube
		if(msg->pose.pose.position.x <= -1.5 && msg->pose.pose.position.x >= -2.5 && msg->pose.pose.position.y <= 1.5 && msg->pose.pose.position.y >= 0.5)
		{
			ros::Duration(5).sleep();

			marker.header.stamp = ros::Time::now();

			marker.action = visualization_msgs::Marker::ADD;

			marker.pose.position.x = -2;
			marker.pose.position.y = 1;
			marker.pose.position.z = 0;
			marker.pose.orientation.x = 0.0;
			marker.pose.orientation.y = 0.0;
			marker.pose.orientation.z = 0.0;
			marker.pose.orientation.w = 1.0;

			ROS_INFO("second marker");

			marker_pub.publish(marker);
		}
	}

}

int main( int argc, char** argv )
{
	ros::init(argc, argv, "basic_shapes");
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	ros::Subscriber odom_sub = n.subscribe("odom", 1000, odom_callback);

	ros::spin();
}
