#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // {distance, node}

class DijkstraGraph {
private:
    int V;
    vector<vector<pii>> adj;

public:
    DijkstraGraph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    void dijkstra(int src) {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<int> dist(V, INT_MAX);

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "==========================================" << endl;
        cout << "   DIJKSTRA SHORTEST DISTANCE FROM NODE " << src << endl;
        cout << "==========================================" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Node " << src << " -> Node " << i << " : ";
            if (dist[i] == INT_MAX) cout << "INF" << endl;
            else cout << dist[i] << " units" << endl;
        }
    }
};

int main() {
    DijkstraGraph g(5);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);

    g.dijkstra(0);

    return 0;
}
