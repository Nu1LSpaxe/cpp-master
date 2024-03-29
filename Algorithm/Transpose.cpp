#include <vector>
#include <iostream>

// Add an edge form vertex src to vertex dest
void addEdge(std::vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
}

// Print adjacency list of a graph
void displayGraph(std::vector<int> adj[], int v)
{
    for (size_t i{ 0 }; i < v; ++i)
    {
        std::cout << i << "-->";
        for (size_t j{ 0 }; j < adj[i].size(); ++j)
            std::cout << adj[i][j] << " ";

        std::cout << std::endl;
    }
}

// Get transpose of a graph 
void transposeGraph(std::vector<int> adj[], std::vector<int> transpose[], int v)
{
    // Traverse the adjacency list of given graph,
    // for each edge (u,v) add an edge (v,u)
    // in the transpose graph's adjacency list
    for (size_t i{ 0 }; i < v; ++i)
        for (size_t j{ 0 }; j < adj[i].size(); ++j)
            addEdge(transpose, adj[i][j], i);
}

void TestTranspose()
{
    // Construct a graph
    const int v{ 5 };
    std::vector<int> adj[v];
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 0, 3);
    addEdge(adj, 2, 0);
    addEdge(adj, 3, 2);
    addEdge(adj, 4, 1);
    addEdge(adj, 4, 3);

    // Finding transpose of graph represented by adjacency list adj[]
    std::vector<int> transpose[v];
    transposeGraph(adj, transpose, v);

    // Displaying adjacency list of transpose graph i.e. b
    displayGraph(transpose, v);
}