#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

#include "dijkstra.h"

void printPath(std::vector<int> parent, int j)
{
    // Base Case : If j is source
    if (parent[j] == - 1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}

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
    int nn = 5;     // number of nodes
    int ne = 2;     // number of edges
    int c = 10;     // cost value
    Dijkstra dijkstra(nn);

    dijkstra.addEdge(0, 1, c);
    dijkstra.addEdge(1, 2, c);
    dijkstra.addEdge(2, 3, c);
    dijkstra.addEdge(3, 4, c);

    std::vector<int> path =  dijkstra.shortestPath(1, 4);
    printPath(path, 4);

    return 0;
}