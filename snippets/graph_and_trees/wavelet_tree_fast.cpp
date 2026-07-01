/**
 * Wavelet Tree (flat-storage, index-based) — competitive programming formulation
 * Ref: https://users.dcc.uchile.cl/~jperez/papers/ioiconf16.pdf
 * Ref: http://rachitiitr.blogspot.com/2017/06/wavelet-trees-wavelet-trees-editorial.html
 *
 * Memory: O(n log σ) ints  (σ = alphabet size = hi-lo+1)
 * Build:  O(n log σ)
 * Queries (kth, range-count, range-sum): O(log σ)
 *
 * Nodes live in a flat array; subtrees are tracked by index (no pointers).
 * Each node stores a prefix count of elements routed left (kos[]) and a prefix
 * sum of element values (prfs[]). 1-indexed array positions (inclusive [l, r]);
 * inclusive value range [lo, hi].
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

namespace wavelet_tree {

  struct Node {
    int lo, hi;             // value range [lo, hi] represented by this node
    int left_node, right_node;  // indices of subtree nodes (0 = none)
    vector<int> kos;        // kos[i] = count of elements <= mid among first i elements
    vector<long long> prfs; // prfs[i] = prefix sum of first i elements
  };

  vector<Node> tree;
  int nodes_cnt = 0;

  // build wavelet tree from array iterator range [from, to) for value range [lo, hi].
  // When build_sums is false, prfs[] is not populated (saves memory + time); the
  // sum-dependent ops (rangeSum, sumLTEk) will then return wrong answers.
  int build(int *from, int *to, int lo, int hi, bool build_sums = true) {
    if(from >= to) return 0;

    /*
      The tree is a binary tree over the value range [lo, hi]; node count is bounded
      by 2*σ - 1 (full binary tree with σ = hi-lo+1 leaves), reached when every value
      in the range is present. Pre-reserve so recursive calls never reallocate and
      dangle references. (tree is 1-indexed; slot 0 unused.)
    */
    if(tree.empty()) tree.resize(2 * (hi - lo + 1));

    int curr = ++nodes_cnt;
    auto &node = tree[curr];

    node.lo = lo;
    node.hi = hi;
    node.left_node = node.right_node = 0;

    if(lo == hi) {  // leaf node: no kos needed, no children.
      if(build_sums) {
        node.prfs.reserve(to - from + 1);
        node.prfs.push_back(0);
        for(auto it = from; it != to; ++it)
          node.prfs.push_back(node.prfs.back() + (*it));
      }
      return curr;
    }

    int mid = lo + (hi - lo) / 2;

    node.kos.reserve(to - from + 1);
    node.kos.push_back(0);
    if(build_sums) {
      node.prfs.reserve(to - from + 1);
      node.prfs.push_back(0);
    }
    for(auto it = from; it != to; ++it) {
      node.kos.push_back(node.kos.back() + (*it <= mid));
      if(build_sums)
        node.prfs.push_back(node.prfs.back() + (*it));
    }

    auto pivot = stable_partition(from, to, [=](const int &x) { return x <= mid; });

    tree[curr].left_node  = build(from, pivot, lo, mid, build_sums);
    tree[curr].right_node = build(pivot, to, mid + 1, hi, build_sums);

    return curr;
  }

  // k-th smallest element in index range [l, r] (1-indexed, inclusive). k is 1-indexed.
  int kth(int curr, int l, int r, int k) {
    if(!curr) return 0;
    auto &node = tree[curr];

    if(node.lo == node.hi) return node.lo;  // lo == hi == kth element

    int cnt_left = node.kos[r] - node.kos[l - 1];
    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    if(k <= cnt_left)
      return kth(node.left_node, lkos + 1, rkos, k);
    else
      return kth(node.right_node, l - lkos, r - rkos, k - cnt_left);
  }

  // count of elements in index range [l, r] with value in [u, v] (inclusive).
  int range(int curr, int l, int r, int u, int v) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(node.hi < u || v < node.lo) return 0;
    if(u <= node.lo && node.hi <= v) return r - l + 1;

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return range(node.left_node, lkos + 1, rkos, u, v)
         + range(node.right_node, l - lkos, r - rkos, u, v);
  }

  // count of elements in index range [l, r] with value <= k.
  int LTEk(int curr, int l, int r, int k) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(k < node.lo) return 0;
    if(k >= node.hi) return r - l + 1;

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return LTEk(node.left_node, lkos + 1, rkos, k)
         + LTEk(node.right_node, l - lkos, r - rkos, k);
  }

  // count of elements in index range [l, r] with value < k.
  int LTk(int curr, int l, int r, int k) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(k <= node.lo) return 0;
    if(k > node.hi) return r - l + 1;

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return LTk(node.left_node, lkos + 1, rkos, k)
         + LTk(node.right_node, l - lkos, r - rkos, k);
  }

  // count of elements in index range [l, r] with value > k (strict).
  int GTk(int curr, int l, int r, int k) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(node.hi <= k) return 0;
    if(k < node.lo) return r - l + 1;

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return GTk(node.left_node, lkos + 1, rkos, k)
         + GTk(node.right_node, l - lkos, r - rkos, k);
  }

  // count of elements in index range [l, r] with value >= k.
  int GTEk(int curr, int l, int r, int k) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(node.hi < k) return 0;
    if(k <= node.lo) return r - l + 1;

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return GTEk(node.left_node, lkos + 1, rkos, k)
         + GTEk(node.right_node, l - lkos, r - rkos, k);
  }

  // count of elements in index range [l, r] with value == k.
  int EQk(int curr, int l, int r, int k) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(k < node.lo || k > node.hi) return 0;
    if(node.lo == node.hi) return r - l + 1;  // lo == hi == k

    int mid = node.lo + (node.hi - node.lo) / 2;
    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    if(k <= mid)
      return EQk(node.left_node, lkos + 1, rkos, k);
    else
      return EQk(node.right_node, l - lkos, r - rkos, k);
  }

  // sum of elements in index range [l, r] with value in [u, v] (inclusive).
  // NOTE: requires build(..., build_sums = true). Returns 0 if prfs[] was not built.
  long long rangeSum(int curr, int l, int r, int u, int v) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(node.hi < u || v < node.lo) return 0;
    if(u <= node.lo && node.hi <= v) {
      if(node.prfs.empty()) return 0;  // sums not built
      return node.prfs[r] - node.prfs[l - 1];
    }

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return rangeSum(node.left_node, lkos + 1, rkos, u, v)
         + rangeSum(node.right_node, l - lkos, r - rkos, u, v);
  }

  // sum of elements in index range [l, r] with value <= k.
  // NOTE: requires build(..., build_sums = true). Returns 0 if prfs[] was not built.
  long long sumLTEk(int curr, int l, int r, int k) {
    if(l > r || !curr) return 0;
    auto &node = tree[curr];

    if(k < node.lo) return 0;
    if(k >= node.hi) {
      if(node.prfs.empty()) return 0;  // sums not built
      return node.prfs[r] - node.prfs[l - 1];
    }

    int lkos = node.kos[l - 1];
    int rkos = node.kos[r];

    return sumLTEk(node.left_node, lkos + 1, rkos, k)
         + sumLTEk(node.right_node, l - lkos, r - rkos, k);
  }

}  // namespace wavelet_tree

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int arr[] = {1, 2, 3, 3, 5, 4, 2};
  int n = 7;

  int root = wavelet_tree::build(arr, arr + n, 1, 5);

  auto chk = [&](const string& name, long long got, long long exp) {
    cerr << (got == exp ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
         << " " << name << ": got=" << got << " exp=" << exp << "\n";
  };

  // arr = [1,2,3,3,5,4,2]; 1-indexed positions 1..7
  // k-th smallest in [l, r], k is 1-indexed.
  chk("kth([5,7],1)", wavelet_tree::kth(root, 5, 7, 1), 2);   // [5,4,2] -> 2
  chk("kth([5,7],2)", wavelet_tree::kth(root, 5, 7, 2), 4);   // [5,4,2] -> 4
  chk("kth([1,7],2)", wavelet_tree::kth(root, 1, 7, 2), 2);   // all -> 2
  chk("kth([1,4],3)", wavelet_tree::kth(root, 1, 4, 3), 3);    // [1,2,3,3] -> 3

  // count <= k in [l, r]
  chk("LTEk([2,6],4)", wavelet_tree::LTEk(root, 2, 6, 4), 4);  // [2,3,3,5,4] <=4 -> 4
  chk("LTEk([1,7],3)", wavelet_tree::LTEk(root, 1, 7, 3), 5);  // all <=3 -> 5

  // count == k
  chk("EQk([1,7],3)", wavelet_tree::EQk(root, 1, 7, 3), 2);  // two 3s
  chk("EQk([2,4],2)", wavelet_tree::EQk(root, 2, 4, 2), 1);  // [2,3,3] -> one 2

  // count < k
  chk("LTk([1,7],3)", wavelet_tree::LTk(root, 1, 7, 3), 3);    // <3 -> {1,2,2} = 3
  chk("LTk([1,7],1)", wavelet_tree::LTk(root, 1, 7, 1), 0);    // <1 -> 0

  // count > k (strict)
  chk("GTk([1,7],3)", wavelet_tree::GTk(root, 1, 7, 3), 2);    // >3 -> {5,4} = 2
  chk("GTk([1,7],5)", wavelet_tree::GTk(root, 1, 7, 5), 0);     // >5 -> 0

  // count >= k
  chk("GTEk([1,7],3)", wavelet_tree::GTEk(root, 1, 7, 3), 4);   // >=3 -> {3,3,5,4} = 4
  chk("GTEk([1,7],6)", wavelet_tree::GTEk(root, 1, 7, 6), 0);   // >=6 -> 0

  // range count [u, v]
  chk("range([1,7],2,4)", wavelet_tree::range(root, 1, 7, 2, 4), 5);  // {2,3,3,4,2} = 5

  // range sum [u, v]
  chk("rangeSum([1,7],2,4)", wavelet_tree::rangeSum(root, 1, 7, 2, 4), 14);  // 2+3+3+4+2 = 14
  chk("sumLTEk([1,7],3)", wavelet_tree::sumLTEk(root, 1, 7, 3), 11);          // 1+2+3+3+2 = 11

  // --- second build with build_sums = false: count ops must still work,
  //     sum ops degrade to 0 (no crash). Uses a fresh copy since build()
  //     stable-partitions (destroys) its input. ---
  int arr2[] = {1, 2, 3, 3, 5, 4, 2};
  wavelet_tree::nodes_cnt = 0;
  wavelet_tree::tree.clear();
  int root_ns = wavelet_tree::build(arr2, arr2 + n, 1, 5, /*build_sums=*/false);

  chk("kth_ns([5,7],1)", wavelet_tree::kth(root_ns, 5, 7, 1), 2);
  chk("LTEk_ns([2,6],4)", wavelet_tree::LTEk(root_ns, 2, 6, 4), 4);
  chk("EQk_ns([1,7],3)", wavelet_tree::EQk(root_ns, 1, 7, 3), 2);
  chk("range_ns([1,7],2,4)", wavelet_tree::range(root_ns, 1, 7, 2, 4), 5);
  // sum ops return 0 (prfs not built), not the true values.
  chk("rangeSum_ns([1,7],2,4)", wavelet_tree::rangeSum(root_ns, 1, 7, 2, 4), 0);
  chk("sumLTEk_ns([1,7],3)", wavelet_tree::sumLTEk(root_ns, 1, 7, 3), 0);

  cerr << "\nAll queries use 1-indexed positions, 1-indexed k for kth().\n";
  return 0;
}
