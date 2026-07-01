/**
 * Problem: DQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved online using Merge Sort Tree & Wavelet Tree.
 *
 * Option 1: Merge Sort Tree
 * - Similar to sqrt decomposition + binary search solution
 * - In this case, instead of flat decomposed blocks, we have a segment tree-like hierarchy, traversing which we apply
 *  binary search on relevant nodes
 * - Obviously, need to keep the subarray sorted within each node
 *
 *   Related: KQUERY
 *
 * Option 2: Wavelet Tree
 * - Wavelet Tree already gives kth order statistic search and limits search as well
 * - Apply the same logic as Merge Sort Tree / sqrt decomposition, on previous occurence index P[]
 *
 *  Related: KQUERY, INVCNT
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(std::begin(var), std::end(var), ##__VA_ARGS__); })(x)
// #define debug(x) cerr << #x << " : " << x << endl
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 30004;

int n, arr[MAXN],
  p[MAXN]; // index with previous occurrence of arr[i]

namespace merge_sort_tree {
  vector<int> segtree[4 * MAXN];

  void build(int* array, int node, int start, int end) {  // 1-based indexing
    if(start == end) {
      segtree[node].pb(array[start-1]);
      return;
    }

    int mid = start + (end - start) / 2;

    build(array, 2*node, start, mid);
    build(array, 2*node+1, mid+1, end);

    // merge
    segtree[node].resize(segtree[2*node].size() + segtree[2*node+1].size());
    merge(segtree[2*node].begin(), segtree[2*node].end(),
      segtree[2*node+1].begin(), segtree[2*node+1].end(),
      segtree[node].begin());
  }

  // query over range [l, r] for count of elements < limit
  int queryLT(int node, int start, int end, int l, int r, int limit) { // 1-based indexing
    if(end < l or start > r)
      return 0;

    if(l <= start and end <= r)
      return distance(segtree[node].begin(), whole(lower_bound, segtree[node], limit));

    int mid = start + (end - start) / 2;

    int leftCnt = queryLT(2*node, start, mid, l, r, limit);
    int rightCnt = queryLT(2*node+1, mid+1, end, l, r, limit);

    return leftCnt + rightCnt;
  }
}

namespace wavelet_tree {
  // Lets you run order statistic queries on a value range [u, v]

  struct Node {
    int lo, hi, // the lowest and highest value elements represented by this node
      left_node, right_node;  // indices of subtree nodes
    vector<int> kos; // prefix count of elements going to the left child. 1-based indexing
  };

  Node tree[2*MAXN];
  int nodes_cnt = 0;

  // build wavelet tree from array iterator range [from, to) for elements' value range [lo, hi]
  int build(int* from, int *to, int lo, int hi) {
    if(from >= to) return 0;

    int curr = ++nodes_cnt;
    auto &node = tree[curr];

    // init curr node
    node.lo = lo;
    node.hi = hi;

    if(lo == hi) {  // leaf node
      node.left_node = node.right_node = -1;
      return curr;
    }

    // build the kos prefix array
    node.kos.reserve(to - from + 1);
    node.kos.pb(0);

    int mid = lo + (hi - lo) / 2;
    for(auto it = from; it != to; it++)
      node.kos.pb(node.kos.back() + (*it <= mid));

    // partition elements into <= mid and > mid
    auto pivot = stable_partition(from, to, [=](const int &x) {
      return x <= mid;
    });

    // build subtrees
    node.left_node = build(from, pivot, lo, mid);
    node.right_node = build(pivot, to, mid+1, hi);

    return curr;
  }

  // query curr subtree for count of elements in index range [l, r] which are < k
  int query_LTk(int curr, int l, int r, int k) {
    if(l > r || !curr)
      return 0;

    auto& node = tree[curr];

    // if lowest item of node >= k, none of this node's items are useful
    if(node.lo >= k)
      return 0;

    // if highest item of node < k, this entire node's items are useful
    if(node.hi < k)
      return r - l + 1;

    int lkos = node.kos[l-1];
    int rkos = node.kos[r];

    // recurse subtrees
    int left_cnt = query_LTk(node.left_node, lkos+1, rkos, k);
    int right_cnt = query_LTk(node.right_node, l-lkos, r-rkos, k);

    return left_cnt + right_cnt;
  }
}

void preprocess() {
  unordered_map<int, int> last_seen;

  for(int i=0; i<n; i++) {
    p[i] = (last_seen.count(arr[i]) ? last_seen[arr[i]] : -1);
    last_seen[arr[i]] = i;
  }

  // merge_sort_tree::build(p, 1, 1, n);
  wavelet_tree::build(p, p+n, -1, n-1);
}

int query_range(int l, int r) { // 1-indexed range [l, r]
  // return merge_sort_tree::queryLT(1, 1, n, l, r, l-1);
  return wavelet_tree::query_LTk(1, l, r, l-1);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int q, l, r;

  cin >> n;

  for(int i=0; i<n; i++)
    cin >> arr[i];

  preprocess();

  cin >> q;

  while(q--) {
    cin >> l >> r;

    cout << query_range(l, r) << "\n";
  }

  return 0;
}
