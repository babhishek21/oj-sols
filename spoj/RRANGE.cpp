/**
 * Problem: RRANGE (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const long long MOD = 10000LL;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

vector<pair<int, int>> upd;

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, u, q, i, j;

  cin >> n >> u >> q;

  while(u--) {
    cin >> i >> j;
    upd.eb(i, j);
  }

  while(q--) {
    cin >> i >> j;

    long long sum = 0;

    for(auto&& tup: upd) {
      if(i > tup.second || j < tup.first)
        continue;

      long long st = max(1, i - tup.first + 1), num = max(1, min(j, tup.second) - max(i, tup.first) + 1);

      sum = (sum + ((num * (num + 2*st - 1))/2LL)) % MOD;
    }

    cout << sum << endl;
  }

  return 0;
}
