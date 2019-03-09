#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>

#include <multi_planner/UpdateGoal.h>
#include "multi_planner/PlanPath.h"

multi_planner::PlanPath planSrv;
bool goalSet = false;
std::string ns;
bool updateGoal( multi_planner::UpdateGoalRequest  &req,
                 multi_planner::UpdateGoalResponse &res )
{
    planSrv.request.goal_pose.x = req.goal_pose.x;
    planSrv.request.goal_pose.y = req.goal_pose.y;
    planSrv.request.serial_id = ns;
    ROS_INFO("updateGoal namespace: %s", ns.c_str());
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
    /// Create Publisher
    ros::Publisher agent_feedback_pub = nh.advertise<geometry_msgs::Pose2D>("agent_feedback", 1000);
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
        if( goalSet )
        {
            client.call(planSrv);
            ROS_INFO("Plan service called.");
            goalSet = false;
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}