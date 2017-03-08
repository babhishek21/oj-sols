/**
 * Problem: Maximizing Mission Points (101Hack46 - HackerRank)
 * 2D Segtree + DP
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define INF 0x3f3f3f3f
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define all(c) (c).begin(), (c).end()

typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

struct town {
  int x, y, h, p;

  bool operator < (const town &other) const {
    return h < other.h;
  }
};

struct segtree { // max segtree
  vector<long long> data; // actual data store. starting from index 1
  int tsz; // actual size of tree = 2*tsz. tsz is position of bottom level of tree

  // init
  segtree() {
    data.clear();
    tsz = 0;
  }

  segtree(int n) {
    tsz = 1;
    while(tsz <= n)
      tsz <<= 1;     // get required tree size

    data.assign(tsz << 1, 0);  // we need about ~4n size
  }

  void put(int pos, long long what) { // pos is 0-based
    for(pos += tsz; pos > 0; pos >>= 1)
      data[pos] = max(data[pos], what);
  }

  long long query(int l, int r) {
    long long ans = 0;

    for(l += tsz, r += tsz; l < r; l >>= 1, r >>= 1) {
      if(l&1)
        ans = max(ans, data[l++]);

      if(r&1)
        ans = max(ans, data[--r]);
    }

    return ans;
  }
};

struct segtree2D {
  vvi who;
  vector<segtree> data;
  int tsz;

  segtree2D(const vii &ps) {
    int X = 0;
    for(auto&& p: ps)
      X = max(X, p.first);

    tsz = 1;
    while(tsz <= X)
      tsz <<= 1;

    data.resize(tsz << 1);
    who.resize(tsz << 1);

    for(int i=0; i < ps.size(); i++)
      who[ps[i].first + tsz].pb(ps[i].second);

    // set bottom level
    for(int i = tsz; i < (tsz << 1); i++)
      data[i] = segtree(who[i].size());

    // build upper levels
    for(int i = tsz - 1; i > 0; i--) {
      who[i].resize(who[i << 1].size() + who[(i << 1) + 1].size());
      merge(who[i << 1].begin(), who[i << 1].end(), who[(i << 1) + 1].begin(), who[(i << 1) + 1].end(), who[i].begin());
      data[i] = segtree(who[i].size());
    }
  }

  long long query(int v, int d, int u) {
    int rd = distance(who[v].begin(), lower_bound(all(who[v]), d));
    int ru = distance(who[v].begin(), lower_bound(all(who[v]), u));

    return data[v].query(rd, ru);
  }

  long long query2D(int l, int r, int d, int u) {
    r = min(r, tsz);
    long long ans = 0;

    for(l += tsz, r += tsz; l < r; l >>= 1, r >>= 1) {
      if(l&1)
        ans = max(ans, query(l++, d, u));

      if(r&1)
        ans = max(ans, query(--r, d, u));
    }

    return ans;
  }

  void put(int v, int pos, long long what) {
    int curr = distance(who[v].begin(), lower_bound(all(who[v]), pos));

    assert(curr != who[v].size() && who[v][curr] == pos); // optional

    data[v].put(curr, what);
  }

  void put2D(int x, int y, long long what) {
    for(x += tsz; x > 0; x >>= 1)
      put(x, y, what);
  }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, mx, my;
  cin >> n >> mx >> my;

  vector<town> town(n);
  for(int i=0; i<n; i++)
    cin >> town[i].x >> town[i].y >> town[i].h >> town[i].p;

  sort(all(town));

  vii coord(n);
  for(int i=0; i<n; i++)
    coord[i] = mp(town[i].x, town[i].y);

  segtree2D tree(coord);
  vector<long long> dp(n);

  for(int i=0; i<n; i++) {
    int cx = town[i].x, cy = town[i].y;

    int lx = max(0, cx - mx), ly = max(0, cy - my);
    int rx = cx + mx, ry = cy + my;

    dp[i] = tree.query2D(lx, rx+1, ly, ry+1) + town[i].p;
    tree.put2D(cx, cy, dp[i]);
  }

  cout << max(0LL, *max_element(all(dp))) << endl;

  return 0;
}
