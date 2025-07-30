#include "Graph.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter " << E << " edges in format: u v weight\n";
    cout<<"Nodes should be in range 0 to V-1\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }



    int choice;
    cout << "\nChoose algorithm:\n";
    cout << "Choose 1 for Dijkstra\n";
    cout << "Choose 2 for Prim's MST\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        int src;
        cout << "Enter source node for Dijkstra: ";
        cin >> src;
        g.dijkstra(src);
    } else if (choice == 2) {
        g.primMST();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
