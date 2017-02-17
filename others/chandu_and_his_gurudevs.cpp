/**
 * Problem: Chandu and his Gurudevs (Hackerearth - Amazon Developer Hiring Challenge)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

#define MAXN 200005
int parent[MAXN];
long long sz[MAXN];
pair<long long, pair<int, int>> edges[MAXN];

// DSU by set size, not rank
int findSet(int x) {
  if(parent[x] != x)
    parent[x] = findSet(parent[x]);
  return parent[x];
}

int main() {
  int t, n, a, b;
  long long c, ans;

  scanf("%d", &t);

  while(t--) {
    scanf("%d", &n);

    // setup union find by set size
    for(int i=0; i<n; i++) {
      parent[i] = i;
      sz[i] = 1;
    }

    // take input
    for(int i=0; i<n-1; i++) {
      scanf("%d%d%lld", &a, &b, &c);
      edges[i] = make_pair(c, make_pair(--a, --b));
    }

    sort(edges, edges + n-1);
    ans = 0;

    // process edges by Kruskal's MST
    for(int i=0; i<n-1; i++) {
      a = findSet(edges[i].second.first);
      b = findSet(edges[i].second.second);

      if(a != b) {
        ans += (edges[i].first * sz[a] * sz[b]) % MOD;
        ans %= MOD;

        // union
        parent[a] = b;
        sz[b] += sz[a];
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}
