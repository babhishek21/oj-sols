/**
 * Problem: ACODE (SPOJ)
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


int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  string s;
  int preprev, prev, curr;

  cin >> s;

  while(s != "0") {
    preprev = 1; prev = 1; curr = 0;

    for(int i=1; i<s.size(); i++) {
      curr = (s[i] != '0') ? prev : 0;
      curr += ((s[i-1] != '0') && ((s[i-1] - '0')*10 + (s[i]- '0') < 27)) ? preprev : 0;

      preprev = prev;
      prev = curr;
    }

    cout << curr << endl;

    cin >> s;
  }

  return 0;
}