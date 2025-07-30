#include "Graph.h"
#include <iostream>
#include <queue>
#include <limits>
Graph::Graph(int V) : V(V) {
    adj.resize(V);
}
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w)); // undirected
}

void Graph::dijkstra(int src) {
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    dist[src] = 0;

    typedef std::pair<int, int> pii;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push(std::make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    cout << "\nDijkstra from source " << src << ":\n";
    for (int i = 0; i < V; ++i)
        std::cout << "Node " << i << " - Distance: " << dist[i] << "\n";
}

void Graph::primMST() {
    std::vector<int> key(V, std::numeric_limits<int>::max());
    std::vector<bool> inMST(V, false);
    std::vector<int> parent(V, -1);
    key[0] = 0;

    typedef std::pair<int, int> pii;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push(std::make_pair(0, 0));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    std::cout << "\nPrim's MST:\n";
    for (int i = 1; i < V; ++i)
        cout << "Edge: " << parent[i] << " - " << i << " | Weight: " << key[i] << "\n";
}
