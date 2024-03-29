#pragma once
#include <vector>
#include <list>
#include <stack>

// The class represents a directed graph using adjacency list representation
class Graph
{
    // Vth of vertices
    int v_;

    // Pointer to an array containing adjacency list
    std::vector<std::list<int>> adj_;

    void topological(int v, bool visited[], std::stack<int>& stack);

public:
    /* Constructor */
    Graph(int v);

    /* Methods */

    // Add w to v's list
    void AddEdge(int v, int w);

    // Print BFS traversal from a given source
    void BFS(int src);

    void TopologicalSort();
};