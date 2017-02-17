/**
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFL = 0x3f3f3f3f3f3f3f3fLL;

#define pb push_back
#define eb emplace_back
#define mp make_pair

static const double PI = 3.14159265358979323846;
static const double EPS = 1e-9;
inline bool equality(double a, double b) { return fabs(a-b) < EPS; }

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) \{ return (func)(begin(var), end(var), ##__VA_ARGS__); \})(x)

/* Direction Arrays */
const int dx[] = {0, 1, 0, -1}; // four cardinal directions
const int dy[] = {1, 0, -1, 0};
const int di[] = {1, -1, 0, 0, 1, -1, 1, -1}; // vector directions
const int dj[] = {0, 0, 1, -1, 1, -1, -1, 1};
const int diK[] = {-2, -2, -1, 1, 2, 2, 1, -1}; // knight directions
const int djK[] = {-1, 1, 2, 2, 1, -1, -2, -2};

/* Number Theory Utils */
template <class T> inline T fastPowMod(T p, T e, T M) { // (p^e)%M
  long long ret = 1;
  while(e > 0) {
    if(e&1) ret = (ret * p) % M;
    p = (p * p) % M;
    e >>= 1;
  }
  return (T)ret;
}
template <class T> inline T modInverse(T a, T M) { return fastPowMod(a,M-2,M); }
template <class T> inline T gcd(T a, T b) { if(b == 0) return a; return gcd(b,a%b); }
template <class T> inline T lcm(T a, T b) { a = abs(a); b = abs(b); return (a/gcd(a,b))*b; }

/* Bit operations */
template <class T> inline bool testBit(T n, int i) { return (n>>i)&1; }
template <class T> inline void setBit(T &n, int i) { n |= (1<<i); }
template <class T> inline void resetBit(T &n, int i) { n &= ~(1<<i); }
template <class T> inline T lastSetBit(T n) { return n & (-n); }
template <class T> inline unsigned int bitcount(T v) { unsigned int c; for(c = 0; v; c++) { v &= v-1; } return c; }


int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O


  return 0;
}

