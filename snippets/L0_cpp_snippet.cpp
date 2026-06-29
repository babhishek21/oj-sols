/**
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

constexpr int MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

#define pb push_back
#define eb emplace_back
#define mp make_pair

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl;
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr double PI = 3.14159265358979323846;
constexpr double EPS = 1e-9;
inline bool equality(double a, double b) { return abs(a-b) < EPS; }

/* Direction Arrays */
const int dx[] = {0, 1, 0, -1}; // four cardinal directions
const int dy[] = {1, 0, -1, 0};
const int di[] = {1, -1, 0, 0, 1, -1, 1, -1}; // vector directions
const int dj[] = {0, 0, 1, -1, 1, -1, -1, 1};
const int diK[] = {-2, -2, -1, 1, 2, 2, 1, -1}; // knight directions
const int djK[] = {-1, 1, 2, 2, 1, -1, -2, -2};

/* Number Theory Utils */
template <typename T> T fastPowMod(T p, T e, T M) { // (p^e)%M
  long long ret = 1;
  while(e > 0) {
    if(e&1) ret = (ret * p) % M;
    p = (p * p) % M;
    e >>= 1;
  }
  return (T)ret;
}
template <typename T> T modInverse(T a, T M) { return fastPowMod(a, M-2, M); }

template <typename T> T modAdd(T a, T b, T M = MOD) { a += b; return (a >= M) ? a - M : a; }
template <typename T> T modSub(T a, T b, T M = MOD) { a -= b; return (a < 0) ? a + M : a; }
template <typename T> T modMul(T a, T b, T M = MOD) { return ((long long)a * b) % M; }
template <typename T> T modMul(T a, T b, T c, T M = MOD) { return modMul(modMul(a, b, M), c, M); }

template <typename T> T gcd(T a, T b) { if(b == 0) return a; return gcd(b, a%b); }
template <typename T> T lcm(T a, T b) { a = abs(a); b = abs(b); return (a / gcd(a, b)) * b; }

/* Bit operations */
template <typename T> bool testBit(T n, int i) { return (n>>i)&1; }
template <typename T> void setBit(T &n, int i) { n |= (1<<i); }
template <typename T> void resetBit(T &n, int i) { n &= ~(1<<i); }
template <typename T> T lastSetBit(T n) { return n & (-n); }
template <typename T> unsigned int bitcount(T v) { unsigned int c; for(c = 0; v; c++) { v &= v-1; } return c; }

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  cout << "Hello world!" << endl;

  return 0;
}
