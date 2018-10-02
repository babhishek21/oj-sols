/**
 * Problem: 11504 - Dominos (UVa)
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

void dfs(const vector<vector<int>> &dominos, vector<bool> &visited, vector<int> &topo, int u) {
  visited[u] = true;

  for(int i=0; i<dominos[u].size(); i++) {
    int v = dominos[u][i];
    if(!visited[v])
      dfs(dominos, visited, topo, v);
  }

  topo.pb(u);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int t, n, m, x, y;

  cin >> t;

  while(t--) {
    cin >> n >> m;

    vector<vector<int>> dominos(n+1);
    vector<int> topo;
    vector<bool> visited(n+1, false);

    while(m--) {
      cin >> x >> y;
      dominos[x].pb(y);
    }

    for(int u=1; u<=n; u++)
      if(!visited[u])
        dfs(dominos, visited, topo, u);

    reverse(topo.begin(), topo.end());

    int ans = 0;
    visited.assign(n+1, false);

    for(int i=0; i<n; i++) {
      int u = topo[i];
      if(!visited[u]) {
        dfs(dominos, visited, topo, u);
        ans++;
      }
    }

    cout << ans << endl;

  }

  return 0;
}
