/**
 * Problem: Saving The Universe Again (Gogole Code Jam Qualification Round 2018)
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

inline int calc(string pp) {
  int ans = 0, pdx = 1;

  for(auto&& ch: pp) {
    ans += (ch == 'S' ? pdx : 0);
    pdx *= (ch == 'C' ? 2 : 1);
  }

  return ans;
}

int solve(int d, string p) {
  int dd = calc(p), idx = p.size()-1, cnt = 0;

  // debug(cnt)
  // debug(dd)

  while(dd > d && idx > 0) {
    while(idx > 0 && !(p[idx] == 'S' && p[idx-1] == 'C'))
      idx--;
    if(idx > 0) {
      swap(p[idx], p[idx-1]);
      cnt++;
      idx = p.size()-1;
    }
    dd = calc(p);

    // debug(cnt)
    // debug(dd)
  }

  return (dd <= d ? cnt : -1);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int t, d, ans;
  string p;

  cin >> t;

  for(int i=1; i<=t; i++) {
    cin >> d >> p;

    cout << "Case #" << i << ": " << ((ans = solve(d, p)) > -1 ? to_string(ans) : "IMPOSSIBLE")  << endl;
  }

  return 0;
}
