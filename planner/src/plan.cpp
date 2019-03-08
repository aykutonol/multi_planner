#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

#include "dijkstra.h"

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
    /// Build the graph
    int nn = 10;     // number of nodes
    int ne = 10;     // number of edges
    int c = 10;      // cost value
    Dijkstra dijkstra(nn);

    for( int i=0; i<nn-1; i++ )
    {
        dijkstra.addEdge(i, i+1, c);
    }
    dijkstra.addEdge(5, 2, 1);

    std::vector<int> path =  dijkstra.shortestPath(5, 2);
    dijkstra.printPath(path, 2);

    return 0;
}