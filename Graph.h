#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void dijkstra(int src);
    void primMST(int src = 0); // Default source for Prim's MST
    void kruskalMST();
};
