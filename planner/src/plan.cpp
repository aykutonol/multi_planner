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
    int nn = 10;    // number of nodes
    int ne = 2;     // number of edges
    int c = 10;     // cost value
    Dijkstra dijkstra(nn);

    dijkstra.addEdge(0, 1, c);
    dijkstra.addEdge(1, 2, c);

    std::list<std::pair<int, int>>::iterator i;
    for( i = dijkstra.adj[1].begin(); i != dijkstra.adj[1].end(); i++ )
    {
        std::cout << (*i).first << " - " << (*i).second << "\n";
    }

    return 0;
}