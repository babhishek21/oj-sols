/**
 * Problem: Floyd-Warshall Algortihm (All Pairs Shortest Path: No negative cyles)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

///////////////////////////////////////////////
// Floyd-Warshall implementation starts here //
///////////////////////////////////////////////

// Edge class - optional
class Edge {
public:
  int src, dest;
  long long cost;

  Edge(int u, int v, long long c): src(u), dest(v), cost(c) {}
};
vector<Edge> E; // store edges - optional

int n, m, u, v; // n = vertices; m = edges; u, v, c = src, dest, cost
long long c;

// Graphs
unordered_map<int, vector<pair<int, long long>>> G; // Graph - Adjacency List <src, <dest, cost>>

vector<vector<long long>> dist; // all-pairs distance matrix

void FloydWarshall() {
  // init dist
  dist.clear();
  dist.resize(n, vector<long long>(n, INFLL));

  for(auto&& edge: E) {
    dist[edge.src][edge.dest] = edge.cost;
    dist[edge.dest][edge.src] = edge.cost;
  }

  for(int i=0; i<n; i++)
    dist[i][i] = 0;

  // dp procedure
  for(int k=0; k<n; k++)
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> n >> m;

  for(int i=0; i<m; i++) {
    cin >> u >> v >> c;

    // G[u].eb(v, c);
    // G[v].eb(u, c);
    E.eb(u-1, v-1, c);
  }

  FloydWarshall();

  cout << (dist[0][n-1] >= INFLL ? "INF" : to_string(dist[0][n-1])) << endl;

  return 0;
}
