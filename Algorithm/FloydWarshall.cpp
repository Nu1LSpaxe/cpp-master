/**
 * Reference: https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
 */

#include <iostream>

#define VERTEXNUM 4
 // Stand for vertices not connect to each other
#define INF 99999

void printFloyd(int dist[][VERTEXNUM])
{
    std::cout << "Shortest distances between every pair of vertices" << std::endl;

    for (size_t i{ 0 }; i < VERTEXNUM; ++i)
    {
        for (size_t j{ 0 }; j < VERTEXNUM; ++j)
        {
            if (dist[i][j] == INF)
                std::cout << "INF ";
            else
                std::cout << dist[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

bool isShorter(int dist[][VERTEXNUM], int i, int j, int k)
{
    return (
        dist[i][j] > (dist[i][k] + dist[k][j]) &&
        dist[i][k] != INF &&
        dist[k][j] != INF);
}

void floydWarshall(int dist[][VERTEXNUM])
{
    // Before pick vertex number k as an intermediate vertex, we already have considered vertices {0, 1, 2, .. k-1} as intermediate vertices.
    for (size_t k{ 0 }; k < VERTEXNUM; ++k)
        for (size_t i{ 0 }; i < VERTEXNUM; ++i)
            for (size_t j{ 0 }; j < VERTEXNUM; ++j)
                if (isShorter(dist, i, j, k))
                    dist[i][j] = dist[i][k] + dist[k][j];
}

void TestFloydWarshall()
{
    int graph[VERTEXNUM][VERTEXNUM] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0} };

    floydWarshall(graph);
    printFloyd(graph);
}