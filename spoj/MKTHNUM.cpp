/**
 * Problem: MKTHNUM (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved by making a merge-sort tree and then binary searching over possible candidates to satisfy the requirements of a query.
 * You can apply the exact same approach, using sqrt decomposed blocks instead of segtree.
 *
 * Can also be solved directly using Wavelet Tree or Chairman Tree, or even Tries.
 *
 * Another alternative is to use Mo's algorithm by maintaining a frequency BIT over the sliding window. Since a BIT over the
 * entire value range [-1e9, 1e9] would be too big and sparse, we need to coordinate compress first. Also, looking for the kth
 * rank can be done via binary lifting (i.e. find smallest index such that the prefix sum till then >= k)
 *
 * Related: KQUERY, DQUERY, INVCNT, ADALIST
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

constexpr int INF = 0x3f3f3f3f;

#define pb push_back
#define eb emplace_back
#define mp make_pair

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(std::begin(var), std::end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 100004;

int n, arr[MAXN];
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

// query over range [l, r] for count of elements <= limit
int queryLTE(int node, int start, int end, int l, int r, int limit) { // 1-based indexing
  if(end < l or start > r)
    return 0;

  if(l <= start and end <= r)
    return distance(segtree[node].begin(), whole(upper_bound, segtree[node], limit));

  int mid = start + (end - start) / 2;

  int leftCnt = queryLTE(2*node, start, mid, l, r, limit);
  int rightCnt = queryLTE(2*node+1, mid+1, end, l, r, limit);

  return leftCnt + rightCnt;
}

// find kth ranked element in array index range [l, r]
int kth(int lo, int hi, int l, int r, int k) {  // 1-indexed
  int mid;

  while(lo < hi) {
    mid = lo + (hi-lo)/2;

    if(queryLTE(1, 1, n, l, r, mid) >= k)
      hi = mid;
    else
      lo = mid+1;
  }

  return lo;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int q, l, r, k, lo, hi;

  cin >> n >> q;

  lo = INF, hi = -INF;
  for(int i=0; i<n; i++) {
    cin >> arr[i];
    lo = min(lo, arr[i]);
    hi = max(hi, arr[i]);
  }

  build(arr, 1, 1, n);

  while(q--) {
    cin >> l >> r >> k;

    cout << kth(lo, hi, l, r, k) << "\n";
  }

  return 0;
}
