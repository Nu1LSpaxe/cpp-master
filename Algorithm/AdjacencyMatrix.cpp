#include <vector>
#include <iostream>

std::vector<std::vector<int>> adj;

void addEdge(int x, int y)
{
    adj[x][y] = 1;
    adj[y][x] = 1;
}

void bfs(int start)
{
    // Create a vector to record visited,
    // so that a vertex is not visited more than once
    // Initializing the vector to false
    std::vector<bool> visited(adj.size(), false);
    std::vector<int> queue;
    queue.push_back(start);

    int visit;
    while (!queue.empty())
    {
        visit = queue[0];

        std::cout << visit << " ";
        // std::vector.erase()
        // erases the specified elements from the container.
        queue.erase(queue.begin());

        // For every adjacent vertex to the current vertex
        for (size_t i{ 0 }; i < adj[visit].size(); ++i)
        {
            if (adj[visit][i] == 1 && (!visited[i]))
            {
                // Push the adjacent node to the queue
                queue.push_back(i);
                visited[i] = true;
            }
        }
    }
}

void TestAdjacencyMatrix()
{
    int v{ 5 };

    // adjacency matrix
    adj = std::vector<std::vector<int>>(v, std::vector<int>(v, 0));
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);

    bfs(0);
}