#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

int main(int argc, char **argv)
{
    /// Initialize ros
    ros::init(argc, argv, "agent");
    /// Create node handle
    ros::NodeHandle nh("~");
    /// Parse input arguments
    double startX, startY, startT;
    std::string serialID;
    nh.getParam("/startX", startX);
    nh.getParam("/startY", startY);
    nh.getParam("/startT", startT);
    ROS_INFO("start: %f, %f, %f", startX, startY, startT);
    /// Build the feedback message
    geometry_msgs::PoseStamped agent_pose_msg;
    agent_pose_msg.header.frame_id = serialID;
    agent_pose_msg.pose.position.x = startX;
    agent_pose_msg.pose.position.y = startY;
    /// Create Publisher
    ros::Publisher agent_feedback_pub = nh.advertise<geometry_msgs::PoseStamped>("agent_feedback",5);
    /// Publish the agent pose
    ros::Rate loop_rate(10);
    while( ros::ok() )
    {
        agent_feedback_pub.publish(agent_pose_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}