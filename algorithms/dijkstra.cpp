#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>
#include <ranges>
#include <iterator>

class UnweightedGraph
{
    std::unordered_map<int, std::unordered_map<int, int>> adjMatrix;

public:
    void addEdge(int source, int destination, int weight)
    {
        adjMatrix[source][destination] = weight;
        adjMatrix[destination][source] = weight;
    }
    std::unordered_set<int> getNodes() const
    {
        std::unordered_set<int> Nodes;
        for (const auto &element : adjMatrix)
            Nodes.insert(element.first);
        return Nodes;
    }
    void print()
    {
        for (const auto &[snode, adj] : adjMatrix)
            for (const auto &[dnode, weight] : adj)
            {
                std::cout << "(" << snode << "," << dnode << ")=" << weight << " ";
                std::cout << "(" << dnode << "," << snode << ")=" << weight << " ";
            }
    }
    friend void dijkstra(UnweightedGraph &, int);
};
void dijkstra(UnweightedGraph &g, int start)
{
    auto Nodes = g.getNodes();
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, int> distanceFromStart;

    // Initialise
    for (const auto &node : Nodes)
    {
        visited[node] = false;
        distanceFromStart[node] = INT_MAX; // proxy for infinity
    }

    // get ready for start
    distanceFromStart[start] = 0;
    auto v = start;

    int pass = 0;
    bool done{false};

    // main loop
    while (!done)
    {
        pass++;
        visited[v] = true;
        auto nodesFromV = g.adjMatrix[v];
        auto distanceToVFromStart = distanceFromStart[v];
        for (const auto [k, weight] : nodesFromV)
        {
            if (!visited[k])
            {
                auto distanceThroughK = distanceToVFromStart + weight;
                if (distanceThroughK < distanceFromStart[k])
                    distanceFromStart[k] = distanceThroughK;
            }
        }
        std::cout << "state after pass:" << pass << "(node=" << v << ") ";
        for (const auto &[k, v] : distanceFromStart)
        {
            std::cout << k << "=" << v << " ";
        }
        std::cout << std::endl;

        // prepare for next loop
        // find univisted node shortest from start
        int shortestDistance = INT_MAX;
        int index = -1;
        for (const auto &[node, hasVisited] : visited)
        {
            if (!hasVisited)
            {
                auto dist = distanceFromStart[node];
                if (dist < shortestDistance)
                {
                    index = node;
                    shortestDistance = dist;
                }
            }
        }
        done = (index == -1);
        v = index;
    }
}

// testing
int main()
{
    UnweightedGraph g;
    g.addEdge(0, 1, 3);
    g.addEdge(0, 3, 7);
    g.addEdge(0, 4, 8);
    g.addEdge(1, 3, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 3);
    // g.print();
    dijkstra(g, 0);
    return 0;
}