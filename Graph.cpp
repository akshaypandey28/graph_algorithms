#include "Graph.h"
#include <iostream>
#include <queue>
#include<climits>
#include<unordered_set>
#define pp pair<int,int>
Graph::Graph(int V) : V(V) {
    adj.resize(V);
}
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); // undirected
}

void Graph::dijkstra(int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    unordered_set<int> vis;
    priority_queue<pp, vector<pp>, greater<pp>> pq;
    pq.push({0, src}); // {distance, node}

    while (!pq.empty()) {
        int u = pq.top().second; //node
        int d = pq.top().first; //distance
        if(vis.find(u) != vis.end()) {  // Skip if already visited
            pq.pop();
            continue; 
        }
        pq.pop();
        vis.insert(u);

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nDijkstra from source " << src << ":\n";
    for (int i = 0; i < V; ++i)
        cout << "Node " << i << " - Distance: " << dist[i] << "\n";
}

void Graph::primMST(int src) {
    priority_queue<pp, vector<pp>, greater<pp>> pq;
    vector<int> key(V, INT_MAX);
    unordered_set<int> vis;
    vector<int> parent(V, -1);
    key[src] = 0;
    int total_count=0; //keeps track of no. of vertices have been added to the MST
    int result=0; //it gives the total weight of the MST
    pq.push(make_pair(0, src)); //weight and node
    
    while (total_count < V and !pq.empty()) {
        pp curr=pq.top();
        pq.pop();
        int u= curr.second; //current node
        if(vis.find(u)!= vis.end()) continue; // Skip if already visited
        vis.insert(u);

        if (parent[u] != -1) result+=key[u]; //add edge weight only if it is real edge

        total_count++;
        
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (vis.find(v)==vis.end() and w < key[v]) {
                key[v] = w;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "\nPrim's MST:\n";
    for (int i = 0; i < V; ++i)
        cout << "Edge: " << parent[i] << " to " << i << " | Weight: " << key[i] << "\n";

    cout << "Total weight of MST: " << result << "\n";
}
