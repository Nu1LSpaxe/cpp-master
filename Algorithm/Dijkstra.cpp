/**
 * Reference: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 */


 // Define number of vertices in the graph
#include <vector>
#include <iostream>
#define VERTEXNUM 9

void printDijkstra(std::vector<int>& dist)
{
    std::cout << "Vertex\t Distance from Source" << std::endl;
    for (size_t i{ 0 }; i < VERTEXNUM; ++i)
        std::cout << i << "\t " << dist[i] << std::endl;
}

// Find the vertex with minimum distance
// (from the set of vertices not yet included in shortest path tree)
int minDist(std::vector<int>& dist, std::vector<bool>& spt)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (size_t v{ 0 }; v < VERTEXNUM; ++v)
        if (spt[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

std::vector<int> dijkstra(int graph[VERTEXNUM][VERTEXNUM], int src)
{
    // Record the shortest distance from src to ith vertex; Initialize
    std::vector<int> dist(VERTEXNUM, INT_MAX);
    // true if ith vertex is included in shortest path tree; Initialize
    std::vector<bool> spt(VERTEXNUM, false);

    // Distance of source vertex is 0
    dist[src] = 0;

    // Find shortest path for all vertices (exclude src)
    for (size_t count{ 0 }; count < VERTEXNUM - 1; ++count)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDist(dist, spt);
        // Mark the picked vertex as processed
        spt[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (size_t v{ 0 }; v < VERTEXNUM; ++v)
            if (
                !spt[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
    }

    return dist;
}

void TestDijkstra()
{
    int graph[VERTEXNUM][VERTEXNUM] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    auto dist = dijkstra(graph, 0);
    printDijkstra(dist);
}