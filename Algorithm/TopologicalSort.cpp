/**
 * Reference: https://www.geeksforgeeks.org/topological-sorting/
*/


#include <list>
#include <stack>
#include <iostream>
#include "Graph.h"

void Graph::topological(int v, bool visited[], std::stack<int>& stack)
{
    // Visit current node
    visited[v] = true;

    // Recursive all adjacencies of this vertex
    // unless this adjacency has been visited
    for (int u : adj_[v])
    {
        // `*` downcast from _List_node_base to _List_node to get to value
        if (!visited[u])
        {
            topological(u, visited, stack);
        }
    }
    // Push vertex to stack after visit all adjacencies
    stack.push(v);
}

void Graph::TopologicalSort()
{
    std::stack<int> stack;

    // Initialize visited list (fill with false value)
    bool* visited = new bool[this->v_] {false};

    // Start topological by calling helper function
    for (size_t i{ 0 }; i < this->v_; ++i)
        if (visited[i] == false)
            topological(i, visited, stack);

    // Print result
    while (stack.empty() == false)
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }

    delete[] visited;
}

void TestTopologicalSort()
{
    Graph graph(6);
    graph.AddEdge(5, 2);
    graph.AddEdge(5, 0);
    graph.AddEdge(4, 0);
    graph.AddEdge(4, 1);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 1);

    std::cout << "Start Topological Sort: " << std::endl;

    graph.TopologicalSort();
}