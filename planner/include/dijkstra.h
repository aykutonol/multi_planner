#include <bits/stdc++.h>

#ifndef DIJKSTRA_H
#define DIJKSTRA_H


class Dijkstra {
public:
    /// Constructor
    Dijkstra(int nn_in);
    /// This function adds an edge between nodes n1 and n2 with a cost of c
    void addEdge(int n1, int n2, int c);
    /// This function calculates the shortest distances from the start vertex
    void shortestPath(int start_vertex);
    /// Pair list to store the graph
    std::list<std::pair<int, int>> *adj;

private:
    /// Infinity value
    double inf = 1e20;
    /// Number of nodes in the graph
    int nn;
};


#endif //DIJKSTRA_H
