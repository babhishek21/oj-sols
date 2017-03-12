/**
 * Problem: Dijkstra's Algortihm (Single Source Shortest Path: +ve weights only)
 * Solves Codeforces 20-C (http://codeforces.com/contest/20/problem/C)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define INF 0x3f3f3f3f
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

/////////////////////////////////////////
// Dijkstra implementation starts here //
/////////////////////////////////////////

// Edge class - optional
// class Edge {
// public:
//   int src, dest, cost;

//   Edge(int u, int v, int c): src(u), dest(v), cost(c) {}
// };
// vector<Edge> E; // store edges - optional

int n, m, u, v; // n = vertices; m = edges; u, v, c = src, dest, cost
long long c;

// Graphs
unordered_map<int, vector<pair<int, long long>>> G; // Graph - Adjacency List <src, <dest, cost>>
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> PQ; // min heap <cost/dist till dest, dest>

unordered_map<int, long long> dist; // <dist till dest from src>
unordered_set<int> visited; // visited nodes
unordered_map<int, int> pred; // predecesssor array - optional

// Dijkstra's SSSP
long long Dijkstra(int src, int dest) {
  // init distances
  dist.clear();

  // init visited
  visited.clear();

  // init pred
  pred.clear(); // optional
  pred[src] = src; // optional

  // start from src
  dist[src] = 0;
  PQ.emplace(dist[src], src);

  // start priority bfs
  while(!PQ.empty()) {
    u = PQ.top().second;
    PQ.pop();

    if(visited.count(u) > 0)
      continue;

    for(auto&& tup: G[u]) {
      v = tup.first;
      c = tup.second;

      if(visited.count(v) <= 0 && (dist.count(v) <= 0 || dist[v] > dist[u] + c)) {
        dist[v] = dist[u] + c;
        pred[v] = u; // optional

        PQ.emplace(dist[v], v);
      }
    }

    visited.insert(u);
  }

  return (dist.count(dest) > 0 ? dist[dest] : -1);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> n >> m;

  for(int i=0; i<m; i++) {
    cin >> u >> v >> c;

    G[u].eb(v, c);
    G[v].eb(u, c);
  }

  if(Dijkstra(1, n) < 0)
    cout << -1 << endl;
  else {
    stack<int> st;
    while(pred[n] != n) {
      st.push(n);
      n = pred[n];
    }

    cout << 1 << " ";
    while(!st.empty()) {
      cout << st.top() << " ";
      st.pop();
    }
    cout << endl;
  }

  return 0;
}
