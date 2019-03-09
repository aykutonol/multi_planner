#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv)
{
    /// initialize ros
    ros::init(argc, argv, "agent_publisher");
    /// create node handle
    ros::NodeHandle nh;
//    /// build the feedback message
//    geometry_msgs::PoseStamped agent_pose_msg;
//    agent_pose_msg.header.frame_id = "agent1";
//    agent_pose_msg.pose.position.x = 0;
//    agent_pose_msg.pose.position.y = 0;
//    tf::Quaternion q;
//    q.setRPY(0,0,0);
////    q.setRPY(0,0,theta);
//    /// Transform
//    tf::Transform transform;
//    transform.setOrigin(tf::Vector3(0,0,0));
//    transform.setRotation(q);
//
//
//    tf::TransformBroadcaster broadcaster;
//
//    ros::Rate loop_rate(10);
//
//    while( ros::ok() )
//    {
//        broadcaster.sendTransform(tf::StampedTransform(
//                        transform, ros::Time::now(), "world", "agent_feedback"));
//        ros::spinOnce();
//        loop_rate.sleep();
//    }



//    /// publisher
//    ros::Publisher agent_feedback_pub = nh.advertise<geometry_msgs::PoseStamped>("agent_feedback",5);
//    ros::Rate loop_rate(10);
//    while( ros::ok() )
//    {
//        agent_feedback_pub.publish(agent_pose_msg);
//        ROS_INFO("Publishing the agent pose");
//        ros::spinOnce();
//        loop_rate.sleep();
//    }

    return 0;
}