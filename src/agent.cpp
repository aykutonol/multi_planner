#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv)
{
    /// initialize ros
    ros::init(argc, argv, "agent_publisher");
    /// create node handle
    ros::NodeHandle nh;
    /// build the feedback message
    geometry_msgs::PoseStamped agent_pose_msg;
    agent_pose_msg.header.frame_id = "agent1";
    agent_pose_msg.pose.position.x = 3;
    agent_pose_msg.pose.position.y = 4;

    /// publisher
    ros::Publisher agent_feedback_pub = nh.advertise<geometry_msgs::PoseStamped>("agent_feedback",5);
    ros::Rate loop_rate(10);
    while( ros::ok() )
    {
        agent_feedback_pub.publish(agent_pose_msg);
        ROS_INFO("Publishing the agent pose");
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}