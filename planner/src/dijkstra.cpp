#include "dijkstra.h"

/// Constructor: initializes the graph given the number of nodes
Dijkstra::Dijkstra(int nn_in)
{
    this->nn = nn_in;
    adj = new std::list< std::pair<int, int> >[nn_in];
}

/// addEdge: adds and edge between the nodes n1 and n2 with cost c
void Dijkstra::addEdge(int n1, int n2, int c)
{
    adj[n1].push_back(std::make_pair(n2, c));
    adj[n2].push_back(std::make_pair(n1, c));
}

/// printPath: prints the resulting path
void Dijkstra::printPath(std::vector<int> path, int j)
{
    if (path[j] == - 1)
        return;
    printPath(path, path[j]);
    printf("%d ", j);
}

/// shortestPath: returns the shortest path found by Dijkstra
std::vector<int> Dijkstra::shortestPath(int nStart, int nFinal)
{
    /// Set of nodes being processed
    std::set< std::pair<int, int> > setn;
    /// Distance vector, initialize with infinity
    std::vector<int> dist(this->nn, INF);
    /// Shortest path
    std::vector<int> path(this->nn, -1);
    /// Insert the start node to the set and set its distance to zero
    setn.insert(std::make_pair(0, nStart));
    dist[nStart] = 0;
    /// Find all shortest paths
    while( !setn.empty() )
    {
        /**
         * Extract the first node from the set since it is the minimum
         * distance node
         */
        std::pair<int, int> tmp = *(setn.begin());
        setn.erase(setn.begin());
        /**
         * Store the node label in the second element of the pair and
         * the distance in the first element so that the pairs can be
         * sorted with respect to the distance
         */
         int n1 = tmp.second;
         /// Iterate over adjacent nodes
         std::list< std::pair<int, int> >::iterator i;
         for( i = adj[n1].begin(); i != adj[n1].end(); i++ )
         {
             /// get node label and cost
             int n2 = (*i).first;
             int cost = (*i).second;
             /// Check if there is a shorter path to n2 through v1
             if( dist[n2] > dist[n1] + cost )
             {
                 /**
                  * If the distance is not infinity, then include
                  * the node in the set. Otherwise, remove it.
                  */
                 if( dist[n2] != INF )
                 {
                     setn.erase(setn.find(std::make_pair(dist[n2], n2)));
                 }
                 /// Update the distance of n2 and insert to the set
                 dist[n2] = dist[n1] + cost;
                 setn.insert(std::make_pair(dist[n2], n2));
                 /// Update the path
                 path[n2] = n1;
             }
         }
         /// Stop the algorithm if the final node is reached
         if( n1 == nFinal )
         {
             break;
         }
    }
    return path;
}