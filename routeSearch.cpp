#include <bits/stdc++.h>
using namespace std;

// Graph structure 
struct Graph {
    unordered_map<string, int> cityId;     // city name → numeric ID
    vector<string> cityName;               // numeric ID → city name
    vector<vector<int>> adj;               // adjacency list (flights)

    // trim spaces
    static string trim(const string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    // Make sure a city exists in our map
    int ensureCity(const string& name) {
        if (!cityId.count(name)) {
            int id = cityName.size();
            cityId[name] = id;
            cityName.push_back(name);
            adj.resize(cityName.size());
        }
        return cityId[name];
    }

    // Load flights from file (same format as flight.txt)
    void loadFlights(const string& fileName) {
        ifstream in(fileName);
        if (!in) {
            cerr << "Cannot open " << fileName << endl;
            exit(1);
        }
        string line;
        int from = -1;
        while (getline(in, line)) {
            line = trim(line);
            if (line.empty()) continue;
            if (line.rfind("From:", 0) == 0) {
                string city = trim(line.substr(5));
                from = ensureCity(city);
            } else if (line.rfind("To", 0) == 0 && from != -1) {
                string city = trim(line.substr(4));
                int to = ensureCity(city);
                adj[from].push_back(to);
            }
        }
    }

    // BFS (Breadth-First Search) to find shortest path
    pair<vector<int>, vector<int>> bfs(int start) const {
        int n = cityName.size();
        vector<int> parent(n, -1);
        vector<int> dist(n, INT_MAX);
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[v] == INT_MAX) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return {parent, dist};
    }

    // Rebuild the path from start to end
    static vector<int> reconstructPath(int start, int end, const vector<int>& parent) {
        vector<int> path;
        for (int v = end; v != -1; v = parent[v])
            path.push_back(v);
        if (path.back() != start) return {}; // unreachable
        reverse(path.begin(), path.end());
        return path;
    }

    // Print the path as "CityA to CityB to CityC"
    string formatPath(const vector<int>& path) const {
        string result;
        for (size_t i = 0; i < path.size(); i++) {
            result += cityName[path[i]];
            if (i + 1 < path.size()) result += " to ";
        }
        return result;
    }

    // Get city ID or show error
    int getId(const string& name) const {
        auto it = cityId.find(name);
        if (it == cityId.end()) throw runtime_error("Unknown city: " + name);
        return it->second;
    }
};

// ---------- Q1: Find shortest route with limited connections ----------
static void q1(const Graph& g, const string& cityA, const string& cityB, int limit) {
    int a = g.getId(cityA);
    int b = g.getId(cityB);

    // Run BFS from cityA
    auto [parent, dist] = g.bfs(a);

    // If cityB cannot be reached or exceeds limit
    if (dist[b] == INT_MAX || dist[b] > limit) {
        cout << "no such a route\n";
        return;
    }

    // Rebuild and print route
    auto path = Graph::reconstructPath(a, b, parent);
    cout << g.formatPath(path) << endl;
    cout << "total connection: " << dist[b] << endl;
}

// ---------- main() ----------
int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: ./routeSearch 1 <city_A> <city_B> <num_connection>\n";
        return 1;
    }

    Graph g;
    g.loadFlights("flight.txt"); // make sure flight.txt is in same folder

    string A = argv[2];
    string B = argv[3];
    int limit = stoi(argv[4]);

    q1(g, A, B, limit);
    return 0;
}
