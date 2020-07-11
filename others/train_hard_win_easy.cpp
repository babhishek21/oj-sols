/**
 * Problem: Train Hard, Win Easy (Codeforces Round #519 by Botan Investments)
 * http://codeforces.com/contest/1043/problem/E
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

vector<long long> x, y, arr;
vector<long long> xpref, ysuff;
vector<pair<long long, int>> diff;

unordered_map<int, vector<int>> gg;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); // for fast I/O

  int n, m, u, v;

  cin >> n >> m;

  x.reserve(n);
  y.reserve(n);
  arr.reserve(n);
  xpref.reserve(n);
  ysuff.reserve(n);
  diff.reserve(n);

  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
    diff.eb(x[i]-y[i], i);
  }

  for(int i=0; i<m; i++) {
    cin >> u >> v;

    u--; v--;
    gg[u].pb(v);
    gg[v].pb(u);
  }

  sort(diff.begin(), diff.end());

  // debug(pretty_print_array(x.data(), n))
  // debug(pretty_print_array(y.data(), n))
  // debug(diff)
  // debug(gg)

  xpref[0] = x[diff[0].second];
  ysuff[n-1] = y[diff[n-1].second];
  for(int i=1; i<n; i++) {
    xpref[i] = xpref[i-1] + x[diff[i].second];
    ysuff[n-1-i] = ysuff[n-i] + y[diff[n-1-i].second];
  }

  // debug(pretty_print_array(xpref.data(), n))
  // debug(pretty_print_array(ysuff.data(), n))

  long long ans;
  for(int i=0; i<n; i++) {
    u = diff[i].second;

    ans = (i<n-1 ? ysuff[i+1] + (n-1-i)*x[u] : 0) + (i>0 ? xpref[i-1] + i*y[u] : 0);

    for(auto v: gg[u]) {
      // debug(u)
      // debug(v)
      // debug(min(x[u] + y[v], x[v] + y[u]))
      ans -= min(x[u] + y[v], x[v] + y[u]);
    }

    arr[u] = ans;
  }

  for(int i=0; i<n; i++)
    cout << arr[i] << " ";
  cout << endl;

  return 0;
}
