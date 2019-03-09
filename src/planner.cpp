#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Path.h>

#include "multi_planner/PlanPath.h"
#include "dijkstra.h"

/// Listen to the agent_feedback and get the start pose on the grid
int startCol, startRow;
void feedbackCallback(const geometry_msgs::Pose2D::ConstPtr& msg)
{
    ROS_INFO("Agent feedback received");
    startCol = msg->x;
    startRow = msg->y;
}
/// Plan a path given a goal pose using Dijkstra's algorithm
bool planPath( multi_planner::PlanPathRequest  &req,
               multi_planner::PlanPathResponse &resp )
{
    /// Parse request
    int goalCol = req.goal_pose.x;
    int goalRow = req.goal_pose.y;
    /// Initialize dijkstra object for the grid
    int n  = 11;        // size of the grid
    int nn = n*n;       // number of nodes
    int c  = 10;        // cost value
    Dijkstra dijkstra(nn);
    /// Start and goal nodes
    int nStart = startRow*n+startCol;
    int nGoal  = goalRow*n+goalCol;
    ROS_INFO("Agent start node: %d", nStart);
    ROS_INFO("Agent goal node: %d",  nGoal);
    /// Build the graph
    for( int i=0; i<n; i++ )
    {
        for( int j=0; j<n-1; j++ )
        {
            // add an edge between columns on the same row
            dijkstra.addEdge(i*n+j, i*n+j+1,   c);
            // add and edge between rows on the same column
            dijkstra.addEdge(j*n+i, (j+1)*n+i, c);
        }
    }
    /// Find the shortest path
    std::vector<int> pathNodes = dijkstra.shortestPath(nStart, nGoal);
    std::vector<int> pathVec;
    dijkstra.getPath(pathNodes, nGoal, pathVec);
    /// Response
    nav_msgs::Path path;
    geometry_msgs::PoseStamped pathPose;
//    path.header.frame_id = frame_id;
    ROS_INFO("Serial ID: %s", req.serial_id.c_str());
    // Add the start pose
    int frame_no = 0;
    pathPose.pose.position.x = startCol;
    pathPose.pose.position.y = startRow;
    path.poses.push_back(pathPose);
    path.header.frame_id = "map";
    // Add the remaining path to the goal
    for( auto const& value: pathVec )
    {
        int pathx = value % n;
        int pathy = (value-pathx)/n;
        pathPose.pose.position.x = pathx;
        pathPose.pose.position.y = pathy;
        pathPose.header.frame_id = "map";
        path.poses.push_back(pathPose);
    }
    resp.path = path;
    resp.success = true;

    return true;
}

int main(int argc, char **argv)
{
    /// Initialize ros
    ros::init(argc, argv, "planner");
    /// Create node handle
    ros::NodeHandle nh;
    /// Create service
    ros::ServiceServer service = nh.advertiseService("get_plan", planPath);
    ROS_INFO("Ready to plan.");
    /// Create subscriber
    ros::Subscriber sub = nh.subscribe("/agent_feedback", 1000, feedbackCallback);
    /// Loop
    ros::Rate loop_rate(10);
    while( ros::ok() )
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}