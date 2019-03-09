#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>

int main(int argc, char **argv)
{
    /// Initialize ros
    ros::init(argc, argv, "agent");
    /// Create node handle relative to namespace
    ros::NodeHandle nh("~");
    /// Parse input arguments
    double startX, startY, startT;
    nh.getParam("startX", startX);
    nh.getParam("startY", startY);
    nh.getParam("startT", startT);
    ROS_INFO("start: %f, %f, %f", startX, startY, startT);
    /// Build the feedback message
    geometry_msgs::Pose2D agent_pose_msg;
    agent_pose_msg.x = startX;
    agent_pose_msg.y = startY;
    agent_pose_msg.theta = startT;
    /// Create Publisher
    ros::Publisher agent_feedback_pub = nh.advertise<geometry_msgs::Pose2D>("agent_feedback",5);
//    /// Create service
//    ros::ServiceServer service = nh.advertiseService("update_goal", updateGoal);
//    ROS_INFO("Ready to set goal.");
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