#include "Graph.h"
#include <iostream>
#include <queue>
#include <limits>
Graph::Graph(int V) : V(V) {
    adj.resize(V);
}
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); // undirected
}

void Graph::dijkstra(int src) {
    vector<int> dist(V, numeric_limits<int>::max());
    dist[src] = 0;

    typedef pair<int, int> pii;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(make_pair(0, src));

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
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "\nDijkstra from source " << src << ":\n";
    for (int i = 0; i < V; ++i)
        cout << "Node " << i << " - Distance: " << dist[i] << "\n";
}

void Graph::primMST() {
    vector<int> key(V, numeric_limits<int>::max());
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    key[0] = 0;

    typedef pair<int, int> pii;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    cout << "\nPrim's MST:\n";
    for (int i = 1; i < V; ++i)
        cout << "Edge: " << parent[i] << " - " << i << " | Weight: " << key[i] << "\n";
}
