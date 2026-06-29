/**
 * Problem: KQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved using Offline Queries + BIT (Fenwick Tree) + Coordinate Compression.
 * - Store both the input and the queries together.
 * - Sort them in descending order of values on which the operation applies.
 *  - For updates, the value is the param `k`
 * - Now replay the input and queries as they come. This will insert elements > k into the BIT before the corresponding query is encountered.
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

/*
Fenwick Tree (BIT) - 1-indexed.
pow2f == bit_floor(n)

To make Frequency BIT:
  add(val, 1) for each element → an order-statistic tree.
  kth smallest element = max_prefix(k-1)   (compressed to 0..n-1)
*/
template <typename T> struct BIT {
  int n; vector<T> tree; int pow2f;
  BIT(int n) : n(n), tree(n + 1), pow2f(n ? (1u << (31 - __builtin_clz(n))) : 0) {}

  void add(int i, T v) { for (; i <= n; i += i & -i) tree[i] += v; }
  T sum(int i) { T s = 0; for (; i > 0; i -= i & -i) s += tree[i]; return s; }
  T sum(int l, int r) { return sum(r) - sum(l - 1); }

  int max_prefix(T c) {
    T v{}; int at = 0;
    for (int len = pow2f; len; len >>= 1)
      if (at + len <= n && v + tree[at + len] <= c)
        v += tree[at + len], at += len;
    return at;
  }
};

constexpr int MAXN = 30002;
constexpr int MAXQ = 200002;

int n, q;
BIT<int> ft(MAXN);

struct OP {
  int typ, // type = 0 for input, 1 for queries
    idx, l, r, val;

  OP(int idx, int val): typ(0), idx(idx), val(val) {}   // input
  OP(int idx, int l, int r, int k): typ(1), idx(idx), l(l), r(r), val(k) {}   // query

  bool operator> (const OP& other) const {
    return tie(val, typ) > tie(other.val, other.typ); // reverse sort by k value first, and then queries before input
  }

  // for debugging
  // friend ostream& operator<< (ostream& out, const OP& op) {
  //   if(op.typ)
  //     out << "QUERY " << tie(op.l, op.r, op.val) << " [" << op.idx << "]";
  //   else
  //     out << "INPUT " << tie(op.idx, op.val);
  //   return out;
  // }
};

vector<OP> ops;

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int l, r, k, ans[MAXQ];

  cin >> n;
  ops.reserve(n);

  for(int i=1; i<=n; i++) {
    cin >> k;
    ops.eb(i, k);
  }

  cin >> q;
  ops.reserve(n+q);

  for(int i=0; i<q; i++) {
    cin >> l >> r >> k;
    ops.eb(i, l, r, k);
  }

  whole(sort, ops, greater<OP>()); // reverse sort ops
  // debug(ops);

  for(auto &op: ops) {
    // debug(op);

    if(op.typ)
      ans[op.idx] = ft.sum(op.l, op.r); // since all elements tracked by ft are currently > k, query [l..r] is just sum(l, r)
    else
      ft.add(op.idx, 1);    // track frequency by index
  }

  for(int i=0; i<q; i++)
    cout << ans[i] << "\n";

  return 0;
}
