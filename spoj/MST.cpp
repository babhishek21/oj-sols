/**
 * Problem: MST (SPOJ)
 * Uses Prim's MST Algorithm. Priority Queue is guaranteed to have all
 * spannable vertices atleast once iff all edges are provided.
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

unordered_map<int, vector<pair<int, int>>> g;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
unordered_set<int> done;

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, m, u, v, w;
  long long mst = 0;

  cin >> n >> m;

  while(m--) {
    cin >> u >> v >> w;

    g[u].eb(v, w);
    g[v].eb(u, w);
  }

  // src is set to vertex 1
  // for(auto&& tup: g[1])
  //   pq.emplace(tup.second, tup.first);
  // done.insert(1);
  pq.emplace(0, 1);

  while(!pq.empty()) {
    auto toptup = pq.top();
    pq.pop();

    // debug(toptup)

    if(done.count(toptup.second) > 0)
      continue;

    done.insert(toptup.second);
    mst += (long long)toptup.first;

    for(auto&& tup: g[toptup.second])
      if(done.count(tup.first) <= 0)
        pq.emplace(tup.second, tup.first);
  }

  cout << mst << endl;

  return 0;
}
