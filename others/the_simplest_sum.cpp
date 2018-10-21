/**
 * Problem: The Simplest Sum (HackerRank)
 * https://www.hackerrank.com/contests/hackerrank-hiring-contest/challenges/the-simplest-sum
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

long long S(long long a, long long b, int k) {
  long long ss = 0;
  long long idx = 1, val = 1, pval = 1, pw = 1;
  long long c = 1;    // for pattern 2

  while(idx <= a) {
    pw *= (long long)k;
    pval = val;
    // val = (val + (k * (idx%MOD)) + 1)%MOD;   // pattern 1
    val = ((k * val)%MOD + ++c)%MOD;         // pattern 2
    idx += pw;
  }

  ss = (ss + (((idx - a)%MOD) * pval)%MOD)%MOD;

  // debug(idx)
  // debug(ss)

  while(idx <= b) {
    pw *= (long long)k;
    pval = val;
    // val = (val + (k * (idx%MOD)) + 1)%MOD;   // pattern 1
    val = ((k * val)%MOD + ++c)%MOD;         // pattern 2
    idx += pw;

    ss = (ss + ((pw%MOD) * pval)%MOD)%MOD;
  }

  // debug(idx)
  // debug(ss)

  ss = (ss - ((idx - b - 1)%MOD * pval)%MOD + MOD)%MOD;

  return ss;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int q, k;
  long long a, b;

  cin >> q;

  while(q--) {
    cin >> k >> a >> b;

    cout << S(a, b, k) << endl;
  }

  return 0;
}
