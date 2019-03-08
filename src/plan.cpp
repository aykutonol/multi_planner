#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include "dijkstra.h"

bool plan(planner::PlanSingleAgent &req,
          nav_msgs::Path &res)

int main(int argc, char **argv)
{
    /// Initialize ros
    ros::init(argc, argv, "planner");
    /// Create node handle
    ros::NodeHandle nh;
    /// Parse start and goal
    geometry_msgs::PoseStamped start, goal;
    start.pose.position.x = 0;
    start.pose.position.y = 0;
    goal.pose.position.x = 2;
    goal.pose.position.y = 1;




    return 0;
}