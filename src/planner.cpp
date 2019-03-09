#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include "dijkstra.h"
//
//bool plan(planner::PlanSingleAgent &req,
//          nav_msgs::Path &res)

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

    /// Initialize dijkstra object for the grid
    int n  = 11;        // size of the grid
    int nn = n*n;       // number of nodes
    int c  = 10;        // cost value
    Dijkstra dijkstra(nn);
    /// Build the graph
    int count = 0;
    for( int i=0; i<n; i++ )
    {
        for( int j=0; j<n-1; j++ )
        {
            // add an edge between columns on the same row
            dijkstra.addEdge(i*n+j, i*n+j+1,   c);
            // add and edge between rows on the same column
            dijkstra.addEdge(j*n+i, (j+1)*n+i, c);
            std::cout << "\nEdge " << count << ": " << i*n+j << " <-> " << i*n+j+1;
            std::cout << "\nEdge " << count+1 << ": " << j*n+i << " <-> " << (j+1)*n+i;
            count = count+2;
        }
    }
    /// Print the shortest path
    std::cout << "\n\n\nShortest path:\n";
    std::vector<int> path =  dijkstra.shortestPath(120, 0);
    dijkstra.printPath(path, 0);
    std::cout <<"\n";



    return 0;
}