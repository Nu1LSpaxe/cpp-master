#include "Graph.h"
#include <iostream>

Graph::Graph(int v)
{
    this->v_ = v;
    // std::vector.resize()
    // resizes the container to contain count elements
    adj_.resize(v);
}

void Graph::AddEdge(int v, int w)
{
    adj_[v].push_back(w);
}

void Graph::BFS(int start)
{
    // Mark all the vertices as not visited
    std::vector<bool> visited;
    visited.resize(v_, false);

    // Create a queue for BFS
    std::list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[start] = true;
    queue.push_back(start);

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        start = queue.front();
        std::cout << start << " ";
        queue.pop_front();  // no data is returned

        // Get all adjacent vertices of the dequeued vertex src.
        // If an adjancent has not been visited,
        // then mark it visited and enqueue it.
        for (auto adjacent : adj_[start])
        {
            if (!visited[adjacent])
            {
                visited[adjacent] = true;
                queue.push_back(adjacent);
            }
        }
    }
}

void TestGraph()
{
    Graph graph(4);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 0);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 3);

    std::cout << "Following is Breadth First Traversal (starting from vertex 2)"
        << std::endl;
    graph.BFS(2);
}