#include "dijkstra.h"

Dijkstra::Dijkstra(int nn_in)
{
    this->nn = nn_in;
    adj = new std::list<std::pair<int, int>>[nn_in];
}

void Dijkstra::addEdge(int n1, int n2, int c)
{
    adj[n1].push_back(std::make_pair(n2, c));
    adj[n2].push_back(std::make_pair(n1, c));
}

void Dijkstra::shortestPath(int n0)
{

}