/**
 * Problem: Roads in HackerLand (World Codesprint #4 - HackerRank)
 * Author: babhishek21
 * Lang: C++11
 * Description: Given N towns and M bi directional roads between them (each road
 * has cost of travel 2**C where all C are distinct) find the sum of minimum distances
 * between all pairs of towns and output in binary format.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int n, m;
vector<pair<int, pair<int, int>>> edges;
vector<int> parent;
unordered_map<int, vector<pair<int, int>>> mst;
vector<long long> ans;

int findSet(int x) {
  if(x != parent[x])
    parent[x] = findSet(parent[x]);
  return parent[x];
}

void makeMST() {
  parent.resize(n);
  iota(parent.begin(), parent.end(), 0);

  sort(edges.begin(), edges.end());

  for(auto &edge: edges) {
    int u = edge.second.first, v = edge.second.second, c = edge.first;

    if(findSet(u) != findSet(v)) {
      parent[findSet(u)] = findSet(v); // union

      mst[u].pb(mp(v, c));
      mst[v].pb(mp(u, c));
    }
  }

  parent.clear();
  edges.clear();
}

int dfs(int u, int par = -1) {
  int vertices_done = 1;

  for(auto &edge: mst[u]) {
    int v = edge.first, c = edge.second;

    if(v != par) {
      int sz = dfs(v, u);

      ans[c] += 1LL * sz * (n - sz);
      vertices_done += sz;
    }
  }

  return vertices_done;
}

void traverseMST() {
  ans.resize(2*m, 0LL);

  dfs(0);
}

int main() {
  int u, v, c;

  // input
  cin >> n >> m;

  for(int i=0; i<m; i++) {
    cin >> u >> v >> c;
    u--; v--;

    edges.pb(mp(c, mp(u, v)));
  }

  makeMST();
  traverseMST();

  // output
  for(int i=0; i<ans.size()-1; i++) {
    ans[i+1] += ans[i]/2;
    ans[i] %= 2;
  }

  int idx = ans.size()-1;
  while(idx >= 0 && ans[idx] == 0)
    idx--;

  for(int i = idx; i >= 0; i--)
    cout << ans[i];
  cout << (idx < 0 ? 0 : "") << endl;

  return 0;
}
