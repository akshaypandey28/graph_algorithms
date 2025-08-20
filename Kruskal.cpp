#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Edge {
    int src, dest, wt;
};

bool cmp(Edge e1, Edge e2) {
    return e1.wt < e2.wt;
}

int find(vector<int> &parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent, parent[x]);
}

void Union(vector<int> &parent, vector<int> &rank, int a, int b) {
    a = find(parent, a);
    b = find(parent, b);
    if (a == b) return;
    if (rank[a] >= rank[b]) {
        rank[a]++;
        parent[b] = a;
    } else {
        rank[b]++;
        parent[a] = b;
    }
}



void Graph::kruskalMST() {
    vector<Edge> edges;
    // Extract edges (only one direction for undirected)
    for (int u = 0; u < V; ++u) {
        for (auto &p : adj[u]) {
            int v = p.first, w = p.second;
            if (u < v) edges.push_back({u, v, w});
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(V), rank(V, 1);
    for (int i = 0; i < V; ++i) parent[i] = i;

    int edgeCount = 0;
    ll ans = 0; //this gives the weight of the MST
    int i=0; //for iterating through edges
    vector<Edge> mst;
    while(edgeCount < V-1 and i < edges.size()) { // V-1 -> O(Vlog*V)
        Edge curr = edges[i]; // because input is sorted so we will get min wt edge
        int srcPar = find(parent, curr.src); //log*V
        int destpar = find(parent, curr.dest); //log*V
        if(srcPar != destpar) {
            // include edge as this will not make cycle
            Union(parent, rank, srcPar, destpar);
            ans += curr.wt;
            edgeCount++;
            mst.push_back(curr); // add to MST
        }

        i++; // doesnt matter i picked the last edge or not, we still need to go to next edge
    }

    cout << "Total weight of MST: " << ans << endl;
    cout << "Edges in the MST:\n";
    for (const Edge &e : mst)
        cout << e.src << " to " << e.dest << " | Weight: " << e.wt << endl;
}
