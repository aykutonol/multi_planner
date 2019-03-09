#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>

#include <multi_planner/UpdateGoal.h>
#include "multi_planner/PlanPath.h"

/// Create path planner service
multi_planner::PlanPath planSrv;
/// Flag for requesting plan per /update_goal
bool goalSet = false;
/// Namespace
std::string ns;
/// Set the goal for the planner upon /update_goal
bool updateGoal( multi_planner::UpdateGoalRequest  &req,
                 multi_planner::UpdateGoalResponse &res )
{
    planSrv.request.goal_pose.x = req.goal_pose.x;
    planSrv.request.goal_pose.y = req.goal_pose.y;
    planSrv.request.serial_id = ns;
    goalSet = true;

    res.success = true;

    return true;
}

int main(int argc, char **argv)
{
    /// Initialize ros
    ros::init(argc, argv, "agent");
    /// Create node handle relative to namespace
    ros::NodeHandle nh("~");
    ns = ros::this_node::getNamespace();
    ROS_INFO("namespace: %s", ns.c_str());
    /// Parse input arguments
    double startX, startY, startT;
    nh.getParam("startX", startX);
    nh.getParam("startY", startY);
    nh.getParam("startT", startT);
    ROS_INFO("Start pose: %f, %f, %f", startX, startY, startT);
    /// Build the feedback message
    geometry_msgs::Pose2D agent_pose_msg;
    agent_pose_msg.x = startX;
    agent_pose_msg.y = startY;
    agent_pose_msg.theta = startT;
    /// Create Publishers
    ros::Publisher agent_feedback_pub = nh.advertise<geometry_msgs::Pose2D>("agent_feedback", 1000);
    ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("path", 1000);
    /// Create Client
    ros::ServiceClient client = nh.serviceClient<multi_planner::PlanPath>("/get_plan", false);
    if( client )
    {
        ROS_INFO("Found the plan service.");
    }
    /// Create service
    ros::ServiceServer service = nh.advertiseService("update_goal", updateGoal);
    ROS_INFO("Ready to set goal.");
    /// Loop
    ros::Rate loop_rate(10);
    while( ros::ok() )
    {
        /// Publish the agent pose
        agent_feedback_pub.publish(agent_pose_msg);
        /// If the /update_goal service is called, call the planner
        if( goalSet )
        {
            ROS_INFO("Plan service called.");
            client.call(planSrv);
            if(  planSrv.response.success ) {
                ROS_INFO("Planning for %s was successful", planSrv.request.serial_id.c_str()); }
            else {
                ROS_INFO("Planning for %s failed", planSrv.request.serial_id.c_str()); }
            goalSet = false;
        }
        /// Publish the path
        path_pub.publish(planSrv.response.path);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}