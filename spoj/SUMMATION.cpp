/**
 * Problem: SUMMATION (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

constexpr int MOD = 100000007;

#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

/* Number Theory Utils */
template <typename T> T fastPowMod(T p, T e, T M = MOD) { // (p^e)%M
  long long ret = 1LL;
  long long base = (p % M + M) % M; // Handle negative p and prevent overflow
  while(e > 0) {
    if(e&1) ret = (ret * base) % M;
    base = (base * base) % M;       // Safe from 32-bit overflow
    e >>= 1;
  }
  return (T)ret;
}
template <typename T> T modInverse(T a, T M = MOD) { a = (a % M + M) % M; return fastPowMod(a, M-2, M); }

template <typename T> T modAdd(T a, T b, T M = MOD) { a += b; return (a >= M) ? a - M : a; }  // Condition: 0 <= a, b < M
template <typename T> T modSub(T a, T b, T M = MOD) { a -= b; return (a < 0) ? a + M : a; }   // Condition: 0 <= a, b < M
template <typename T> T modMul(T a, T b, T M = MOD) { return ((long long)a * b) % M; }
template <typename T> T modMul(T a, T b, T c, T M = MOD) { return modMul(modMul(a, b, M), c, M); }

int main() {
  int t, n;
  int summ, x;

  cin >> t;

  for(int cc=1; cc<=t; cc++) {
    cin >> n;

    summ = 0LL;
    for(int i=0; i<n; i++) {
      cin >> x;
      summ = modAdd(summ, x % MOD);
    }

    // debug(summ);
    // debug(fastPowMod(2, n-1));

    summ = modMul(fastPowMod(2, n-1), summ);

    cout << "Case " << cc << ": " << summ << "\n";
  }

  return 0;
}
