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
    /// This function calculates the shortest distances from the start vertex
    std::vector<int> shortestPath(int nStart, int nFinal);
    /// Pair list to store the graph
    std::list< std::pair<int, int> > *adj;

private:
    /// Number of nodes in the graph
    int nn;
};


#endif //DIJKSTRA_H
