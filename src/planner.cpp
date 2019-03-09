#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Path.h>

#include "multi_planner/PlanPath.h"
#include "dijkstra.h"

geometry_msgs::Pose2D startPose;

void feedbackCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    ROS_INFO("Agent feedback received");
    startPose.x = msg->pose.position.x;
    startPose.y = msg->pose.position.y;
}

bool planPath( multi_planner::PlanPathRequest  &req,
               multi_planner::PlanPathResponse &resp )
{
    /// Parse request
    int col = req.goal_pose.x;
    int row = req.goal_pose.y;

    ROS_INFO("Agent node: %d", col*11+row);

//    /// Initialize dijkstra object for the grid
//    int n  = 11;        // size of the grid
//    int nn = n*n;       // number of nodes
//    int c  = 10;        // cost value
//    Dijkstra dijkstra(nn);
//    /// Build the graph
//    int count = 0;
//    for( int i=0; i<n; i++ )
//    {
//        for( int j=0; j<n-1; j++ )
//        {
//            // add an edge between columns on the same row
//            dijkstra.addEdge(i*n+j, i*n+j+1,   c);
//            // add and edge between rows on the same column
//            dijkstra.addEdge(j*n+i, (j+1)*n+i, c);
//            std::cout << "\nEdge " << count << ": " << i*n+j << " <-> " << i*n+j+1;
//            std::cout << "\nEdge " << count+1 << ": " << j*n+i << " <-> " << (j+1)*n+i;
//            count = count+2;
//        }
//    }
//    /// Print the shortest path
//    std::cout << "\n\n\nShortest path:\n";
//    std::vector<int> path =  dijkstra.shortestPath(120, 0);
//    dijkstra.printPath(path, 0);
//    std::cout <<"\n";
//    resp.
//    resp.start
    resp.success = true;
}

int main(int argc, char **argv)
{
    /// Initialize ros
    ros::init(argc, argv, "planner");
    /// Create node handle
    ros::NodeHandle nh;
    /// Create service
    ros::ServiceServer service = nh.advertiseService("plan_path", planPath);
    ROS_INFO("Ready to plan.");
    /// Create subscriber
    ros::Subscriber sub = nh.subscribe("agent_feedback", 5, feedbackCallback);

    ros::spin();

    return 0;
}