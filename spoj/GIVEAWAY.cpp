/**
 * Problem: GIVEAWAY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Can be solved with sqrt decomposition, segment trees and fenwick trees.
 *
 * To solve with either segment trees or fenwick trees, you need two layers:
 * 1. The outer layer is a segtree or BIT to split O(logN) layers to process for updates and range queries
 * 2. The inner layer (i.e. inside each node) has to be either a order-statistic tree (heavy on memory), or something that can
 *    a. keep the data sorted to allow for quick lookups or allow random access
 *    b. allow efficient insertion i.e. <= O(logN)
 *    c. allow efficient range queries i.e <= O(logn)
 *    Turns out, segtrees / BITs are perfect for that. So, just put another segtree or BIT inside each node.
 *
 * These are essentially 2D Segment Trees or 2D Fenwick Trees. Obviously, there are two immediate problems:
 * 1. Segtree is slower and potentially takes double the memory. If you use a Fenwick Tree and track frequencies with it,
 *    the range of elements is not really addressible in memory.
 *        ==> can be solved with localized coordinate compression
 * 2. Both updates and queries take O(N logN) time, so overall O(Q·N·logN) which is too slow.
 *        ==> can be reduced to O(Q logN logN) using dynamic inventory tracking.
 *            Simply look at all updates before-hand and include them alongside the tracked elements inside a node.
 *            -> Our tracking BIT stores frequencies of the elements being tracked. Initially mark the update values inactive (frequency = 0)
 *            -> As updates are replayed, the replaced values become inactive (frequency--) while the new updated values
 *               become active (frequency++).
 *            -> Queries are simple rank finding on the frequency BIT.
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

constexpr int MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

#define pb push_back
#define eb emplace_back

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
// #define debug(x) cerr << #x << " : " << x << endl
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 500005;
int arr[MAXN], n, q;

namespace sqrt_decomp {
  constexpr int BLOCK_LEN = 700;
  vector<vector<int>> blocks;

  void preprocess() {
    // put arr[1..700] in block 0, arr[701..1400] in block 1, and so on

    for(int i=0; i<blocks.size(); i++) {
      copy_n(arr + 1 + i*BLOCK_LEN, blocks[i].size(), blocks[i].begin());
      whole(sort, blocks[i]);
    }
  }

  void update(int idx, int val) {
    auto& block = blocks[(idx-1)/BLOCK_LEN];

    auto it = whole(find, block, arr[idx]); // in small blocks which fit in cache, linear search is very fast
    *it = val;
    whole(sort, block);

    arr[idx] = val;

    // debug("update", idx, val, blocks);
  }

  int query(int l, int r, int val) {
    // debug("query", l, r, val, blocks);

    int res = 0;

    for(int i=l; i<=r;) {
      if(i % BLOCK_LEN == 1 && i + BLOCK_LEN - 1 <= r) {
        auto& block = blocks[(i-1)/BLOCK_LEN];
        res += BLOCK_LEN - distance(block.begin(), whole(lower_bound, block, val));
        i += BLOCK_LEN;
      } else
        res += (arr[i++] >= val);
    }

    return res;
  }

  void solve() {
    blocks.assign(n/BLOCK_LEN + 1, vector<int>(BLOCK_LEN));
    blocks.back().resize(n%BLOCK_LEN);
    if(blocks.back().empty()) blocks.pop_back();

    preprocess();

    // debug(blocks);

    int op, a, b, c;

    cin >> q;

    while(q--) {
      cin >> op;

      if(op) { // update
        cin >> a >> b;
        update(a, b);
      } else { // query
        cin >> a >> b >> c;
        cout << query(a, b, c) << '\n';
      }
    }
  }
}

namespace fenwick_tree_2D {

  // This is collectively the first layer of 2D Fenwick tree flattented out.
  // Each combo of { node_block[i], freq_tracker[i] } is the second layer (i.e. a node of the outer Fenwick tree)

  vector<int> node_block[MAXN],      // node_block[i] == sorted list of all elements that will ever participate in this node (current + updates)
              freq_tracker[MAXN];    // freq_tracker[i] == frequency BIT (Fenwick tree) over the elements in node_block[i]

  void add_BIT(vector<int>& BIT, int idx, int delta) {
    // debug(BIT, idx, delta);

    for(; idx < BIT.size(); idx += (idx & -idx))
      BIT[idx] += delta;
  }

  int sum_prefix_BIT(vector<int>& BIT, int idx) {
    int sum = 0;
    for(; idx > 0; idx -= (idx & -idx))
      sum += BIT[idx];
    return sum;
  }

  void insert_into_nodes(int idx, int num) {
    for(; idx <= n; idx += (idx & -idx))
      node_block[idx].push_back(num);
  }

  void change_freq_in_nodes(int idx, int num, int freq_delta) {
    int where;
    for(; idx <= n; idx += (idx & -idx)) {
      where = distance(node_block[idx].begin(), whole(lower_bound, node_block[idx], num));
      add_BIT(freq_tracker[idx], where+1, freq_delta);
    }
  }

  void compress_nodes() { // coordinate compression
    for(int i=1; i<=n; i++) {
      whole(sort, node_block[i]);
      node_block[i].erase(whole(unique, node_block[i]), node_block[i].end());

      freq_tracker[i].assign(node_block[i].size()+1, 0);
    }
  }

  void build(vector<int>& update_indices_in_ops, int *idxs, int *vals) {
    // insert intial elements of arr[] into nodes of outer fenwick tree
    for(int i=1; i<=n; i++)
      insert_into_nodes(i, arr[i]);

    // debug(pretty_print_array(node_block+1, n));

    // insert the update elements as well
    for(auto i: update_indices_in_ops)
      insert_into_nodes(idxs[i], vals[i]);

    // debug(pretty_print_array(node_block+1, n));

    compress_nodes();

    // debug(pretty_print_array(node_block+1, n));
    // debug(pretty_print_array(freq_tracker+1, n));

    // set freq of initial elements of arr[] into nodes of outer fenwick tree
    for(int i=1; i<=n; i++)
      change_freq_in_nodes(i, arr[i], 1);
  }

  void update(int idx, int val) {
    change_freq_in_nodes(idx, arr[idx], -1);
    arr[idx] = val;
    change_freq_in_nodes(idx, arr[idx], 1);
  }

  int query(int idx, int val) { // count of elements in arr[1..idx] which are >= val
    int where, sum = 0;

    for(; idx; idx -= (idx & -idx)) {
      where = distance(node_block[idx].begin(), whole(lower_bound, node_block[idx], val));
      sum += sum_prefix_BIT(freq_tracker[idx], node_block[idx].size()) - sum_prefix_BIT(freq_tracker[idx], where);
    }

    return sum;
  }

  int query(int l, int r, int val) {
    return query(r, val) - query(l-1, val);
  }

  void solve() {
    int op[100000], a[100000], b[100000], c[100000];
    vector<int> upd_ids;

    cin >> q;

    // scan ops
    for(int i=0; i<q; i++) {
      cin >> op[i];

      if(op[i]) { // update
        cin >> a[i] >> b[i];
        upd_ids.pb(i);
      } else { // query
        cin >> a[i] >> b[i] >> c[i];
      }
    }

    // build inventory
    build(upd_ids, a, b);

    // debug(pretty_print_array(node_block+1, n));
    // debug(pretty_print_array(freq_tracker+1, n));

    // replay ops
    for(int i=0; i<q; i++) {
      if(op[i]) // update
        update(a[i], b[i]);
      else // query
        cout << query(a[i], b[i], c[i]) << '\n';
    }
  }
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  cin >> n;

  for(int i=1; i<=n; i++)
    cin >> arr[i];

  // debug(pretty_print_array(arr+1, n));

  // sqrt_decomp::solve();
  fenwick_tree_2D::solve();

  return 0;
}
