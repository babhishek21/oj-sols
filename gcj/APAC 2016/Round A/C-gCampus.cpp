/**
 * Problem: C. gCampus (APAC 2016 Round A)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define debug(x) cout << #x << " = " << x << endl;

class Edge {
public:
  int src, dest, cost;

  Edge(int u, int v, int c): src(u), dest(v), cost(c) {};
};

int t, n, m, u, v, c;

unordered_map<int, vector<pair<int, int>>> G; // <src, <dest, cost>>
vector<Edge> E; // <Edge>

priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q; // <dist till this src, src>

vector<long long> dist;
vector<bool> visited;
// vector<int> pred;

int dijkstra(int src, int dest) {
  dist.resize(n, numeric_limits<long long>::max());
  visited.resize(n, false);

  dist[src] = 0LL;
  Q.push(make_pair(dist[src], src));

  while(!Q.empty()) {
    u = Q.top().second;
    Q.pop();

    if(visited[u])
      continue;

    for(auto &tup: G[u]) {
      v = tup.first;
      long long w = tup.second;
      if(!visited[v] && (dist[v] > dist[u] + w)) {
        dist[v] = dist[u] + w;
        // pred[v] = u;

        Q.push(make_pair(dist[v], v));
      }
    }

    visited[u] = true;
  }

  // cleanup
  dist.clear();
  visited.clear();

  return dist[dest];
}

void solve() {
  cin >> n >> m;

  for(int i=0; i<m; i++) {
    cin >> u >> v >> c;
    E.emplace_back(u, v, c);
    G[u].push_back(make_pair(v, c));
    G[v].push_back(make_pair(u, c));
  }

  int i=0;
  for(auto it: E) {
    if(dijkstra(it.src, it.dest) < it.cost)
      cout << i << endl;
    i++;
  }

  // cleanup
  E.clear();
  G.clear();
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ":" << endl;
    solve();
  }

  return 0;
}
