#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int weight;
};

class CityPathFinder {
private:
    vector<string> cityNames;
    map<string, int> cityIndex;
    vector<vector<Edge>> adj;

public:
    void addCity(const string& name) {
        if (cityIndex.find(name) == cityIndex.end()) {
            cityIndex[name] = cityNames.size();
            cityNames.push_back(name);
            adj.push_back({});
        }
    }

    void addRoute(const string& from, const string& to, int distance) {
        addCity(from);
        addCity(to);
        int u = cityIndex[from];
        int v = cityIndex[to];
        adj[u].push_back({v, distance});
        adj[v].push_back({u, distance});
    }

    void findShortestPath(const string& startCity, const string& endCity) {
        if (cityIndex.find(startCity) == cityIndex.end() || cityIndex.find(endCity) == cityIndex.end()) {
            cout << "❌ One or both cities do not exist in the network." << endl;
            return;
        }

        int src = cityIndex[startCity];
        int dest = cityIndex[endCity];
        int n = cityNames.size();

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "❌ No path available between " << startCity << " and " << endCity << "." << endl;
            return;
        }

        // Reconstruct path
        vector<int> path;
        for (int at = dest; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "\n==========================================" << endl;
        cout << "       CITY PATH FINDER ROUTE RESULT      " << endl;
        cout << "==========================================" << endl;
        cout << "📍 Origin      : " << startCity << endl;
        cout << "🏁 Destination : " << endCity << endl;
        cout << "📏 Total Distance: " << dist[dest] << " km" << endl;
        cout << "🛣️ Route       : ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << cityNames[path[i]];
            if (i < path.size() - 1) cout << " ➔ ";
        }
        cout << "\n==========================================" << endl;
    }
};

int main() {
    CityPathFinder finder;

    finder.addRoute("Mumbai", "Nashik", 165);
    finder.addRoute("Mumbai", "Pune", 150);
    finder.addRoute("Nashik", "Pune", 210);
    finder.addRoute("Nashik", "Nagpur", 620);
    finder.addRoute("Pune", "Bangalore", 840);
    finder.addRoute("Nagpur", "Bangalore", 1090);

    finder.findShortestPath("Mumbai", "Bangalore");
    finder.findShortestPath("Nashik", "Bangalore");

    return 0;
}
