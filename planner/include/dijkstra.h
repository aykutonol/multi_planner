#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

#ifndef DIJKSTRA_H
#define DIJKSTRA_H


class Dijkstra {
public:
    /// Constructor
    Dijkstra(int nn_in);
    /// This function adds an edge between nodes n1 and n2 with a cost of c
    void addEdge(int n1, int n2, int c);
    /// This function returns the shortest path from nStart to nFinal
    std::vector<int> shortestPath(int nStart, int nFinal);
    /// This function prints the resulting path
    void printPath(std::vector<int> path, int j);

private:
    /// Number of nodes in the graph
    int nn;
    /// Pair list to store the graph
    std::list< std::pair<int, int> > *adj;
};

#endif //DIJKSTRA_H
