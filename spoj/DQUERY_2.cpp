/**
 * Problem: DQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved using BIT / Fenwick Tree.
 *
 * Option 1: BIT + Offline queries
 * - sort queries by ending boundary (i.e. by increasing R for query range [L..R])
 * - process the array by keeping track of the latest seen instance of a value in the BIT
 *   i.e. if you encounter an element at idx j, previously seen at idx i do: BIT.add(i, -1), BIT.add(j, 1)
 * - query(l, r) == BIT.sum(r) - BIT.sum(l-1)
 *   wherein BIT.sum(i) is count of all latest seen instances of unique elements until index i
 *
 *   Related: KQUERY
 *
 * Option 2: 2D BIT (to keep Online queries)
 * - needs coordinate compression to save on memory
 * - store (i, P[i]) for every arr[i], where P[i] is the previously seen index for value of arr[i]
 * - then we need to query for i in [L..R] on dimension 1 and P[i] in [-1..(L-1)] on dimension 2.
 *
 *  Related: KQUERY, GIVEAWAY
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
// #define debug(x) cerr << #x << " : " << x << endl
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 30004;

/*
Fenwick Tree (BIT) - 1-indexed.

To make Frequency BIT:
  add(val, 1) for each element → an order-statistic tree.
*/
template <typename T> struct BIT {
  using OP = function<T(T, T)>;

  int n; vector<T> tree;
  OP op = plus<T>{}, inverse_op = minus<T>{};

  BIT(int n) : n(n), tree(n + 1) {}
  BIT(int n, OP op_fn, OP inv_op_fn): n(n), tree(n + 1), op(move(op_fn)), inverse_op(move(inv_op_fn)) {}

  void add(int i, T v) { add(i, v, op); }
  void add(int i, T v, OP op) { for (; i <= n; i += i & -i) tree[i] = op(tree[i], v); }

  T sum(int i) { return sum(i, op); }
  T sum(int i, OP op) { T s = 0; for (; i > 0; i -= i & -i) s = op(s, tree[i]); return s; }

  T sum(int l, int r) { return sum(l, r, op, inverse_op); }
  T sum(int l, int r, OP op, OP inverse_op) { return inverse_op(sum(r, op), sum(l - 1, op)); }
};

namespace offline_1D_BIT {
  unordered_map<int, int> last_seen_index;
  BIT<int> ft(MAXN);

  struct OP {
    int typ, // type = 0 for input, 1 for queries
      idx, l, r, val;

    OP(int idx, int val): typ(0), idx(idx), r(idx), val(val) {}   // input
    OP(int idx, int l, int r): typ(1), idx(idx), l(l), r(r) {}   // query

    bool operator< (const OP& other) const {
      return tie(r, typ) < tie(other.r, other.typ); // sort by range end boundary first, and then queries before input
    }
  };

  void solve() {
    int n, q, l, r, x;
    vector<OP> ops;
    vector<int> ans;

    cin >> n;
    ops.reserve(n);

    for(int i=0; i<n; i++) {
      cin >> x;
      ops.eb(i+1, x);
    }

    cin >> q;
    ops.reserve(n+q);

    for(int i=0; i<q; i++) {
      cin >> l >> r;
      ops.eb(i, l, r);
    }

    whole(sort, ops);

    ans.assign(q, 0);

    for(auto &op: ops) {
      if(op.typ)
        ans[op.idx] = ft.sum(op.l, op.r);
      else {
        if(last_seen_index.count(op.val))
          ft.add(last_seen_index[op.val], -1);

        ft.add(op.idx, 1);
        last_seen_index[op.val] = op.idx;
      }
    }

    for(auto &a: ans)
      cout << a << "\n";
  }
}

namespace online_2D_BIT {

  constexpr int BIT_OFFSET = 2;

  /*
  Each Node in the Fenwick Tree stores two things:
  - coordinate compressed list of all P[i] values that a Node (representing a prefix range) will ever see
  - the second layer Fenwick Tree that is the actual frequency BIT over the coordinate compressed P[i]
  */
  struct Node {
    vector<int> coords, bit;

    void enumerate(int val) { // val must already be in coords
      auto it = whole(lower_bound, coords, val);
      int idx = distance(coords.begin(), it) + 1;

      for(; idx < bit.size(); idx += idx & -idx)
        bit[idx]++;
    }

    int query_lt(int limit) {  // query number of elements < limit
      auto it = whole(lower_bound, coords, limit);   // first index >= limit
      int idx = distance(coords.begin(), it);  // idx+1 is the first index in BIT for element >= limit

      int cnt = 0;

      for(; idx > 0; idx -= idx & -idx)
        cnt += bit[idx];

      return cnt;
    }
  };

  int n, arr[MAXN];
  Node ft[MAXN];

  void introduce_val(int i, int val) {
    for(; i<= n; i += i & -i)
      ft[i].coords.push_back(val);
  }

  void register_val(int i, int val) {
    for(; i<= n; i += i & -i)
      ft[i].enumerate(val);
  }

  // query prefix range [1, i] to get count of elements with value < lim;
  int query_bit_prefix(int i, int lim) {
    int res = 0;

    for(; i > 0; i -= i & -i)
      res += ft[i].query_lt(lim + BIT_OFFSET);

    return res;
  }

  void preprocess_bit() {
    // first pass - gather last seen for every element and introduce it to relevant Nodes
    unordered_map<int, int> last_seen;

    for(int i=0; i<n; i++) {
      introduce_val(i+1, (last_seen.count(arr[i]) ? last_seen[arr[i]] : -1) + BIT_OFFSET);
      last_seen[arr[i]] = i;
    }

    // second pass - normalize and compress coordinates in each Node
    for(int i=1; i<=n; i++) {
      auto &node = ft[i];

      whole(sort, node.coords);
      node.coords.erase(whole(unique, node.coords), node.coords.end());

      node.bit.assign(node.coords.size()+1, 0);
    }
  }

  void insert_into_bit() {
    // third pass - actually insert each element's last seen 
    unordered_map<int, int> last_seen;

    for(int i=0; i<n; i++) {
      register_val(i+1, (last_seen.count(arr[i]) ? last_seen[arr[i]] : -1) + BIT_OFFSET);
      last_seen[arr[i]] = i;
    }
  }

  /*
  query index range [l, r] to get count of elements with value < lim
  l and r are 1-based indices.
  */
  int query_bit_range(int l, int r, int lim) {
    return query_bit_prefix(r, lim) - query_bit_prefix(l-1, lim);
  }

  void solve() {
    int q, l, r;

    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    preprocess_bit();
    insert_into_bit();

    cin >> q;

    while(q--) {
      cin >> l >> r;

      cout << query_bit_range(l, r, l-1) << "\n"; // l and r are 1-based indices, hence we need to count elements <= l-2 in range arr[l-1..r-1]
    }
  }
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  // offline_1D_BIT::solve();
  online_2D_BIT::solve();

  return 0;
}
