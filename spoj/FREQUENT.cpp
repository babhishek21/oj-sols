/**
 * Problem: FREQUENT (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Static Range Mode Query - solved using Segment Trees.
 * Note that the array is already sorted (monotonous non-decreasing)
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

// Segtree Node
struct Node {
  int prefMode, prefCnt, suffMode, suffCnt, segMode, segCnt;
  bool isNull = false;

  static Node combine(const Node& L, const Node& R) {
    Node res{};

    // prefix
    res.prefMode = L.prefMode;
    res.prefCnt = L.prefCnt;

    if(L.prefMode == L.suffMode and L.suffMode == R.prefMode) // L's prefix mode is the entire L segment mode, and matches R's prefix mode
      res.prefCnt += R.prefCnt;

    // suffix
    res.suffMode = R.suffMode;
    res.suffCnt = R.suffCnt;

    if(R.suffMode == R.prefMode and R.prefMode == L.suffMode) // R's suffix mode is the entire R segment mode, and matches L's suffix mode
      res.suffCnt += L.suffCnt;

    // segment
    if(L.segCnt > R.segCnt) {
      res.segMode = L.segMode;
      res.segCnt = L.segCnt;
    } else {
      res.segMode = R.segMode;
      res.segCnt = R.segCnt;
    }

    if (L.suffMode == R.prefMode and L.suffCnt + R.prefCnt > res.segCnt) {
      res.segMode = L.suffMode;
      res.segCnt = L.suffCnt + R.prefCnt;
    }

    return res;
  }

  static Node null() {
    Node n{};
    n.isNull = true;
    return n;
  }
};

// Segtree
constexpr int MAXN = 100004;
Node tree[4 * MAXN];

void build(const int *arr, int nodeIdx, int l, int r) {
  // debug("build", nodeIdx, l, r);

  if(l == r) {
    tree[nodeIdx] = Node{arr[l], 1, arr[r], 1, arr[l], 1};
    return;
  }

  int mid = l + (r-l)/2;

  build(arr, 2*nodeIdx, l, mid);
  build(arr, 2*nodeIdx+1, mid+1, r);

  tree[nodeIdx] = Node::combine(tree[2*nodeIdx], tree[2*nodeIdx+1]);
}

Node query(int nodeIdx, int l, int r, int ql, int qr) {
  // debug("query", nodeIdx, l, r, ql, qr);

  if(ql > r or qr < l)
    return Node::null();

  if(ql <= l and r <= qr)
    return tree[nodeIdx]; // fully within range

  int mid = l + (r-l)/2;

  auto nodeL = query(2*nodeIdx, l, mid, ql, qr);
  auto nodeR = query(2*nodeIdx+1, mid+1, r, ql, qr);

  if(nodeL.isNull)
    return nodeR;

  if(nodeR.isNull)
    return nodeL;

  return Node::combine(nodeL, nodeR);
}


int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  cin.tie(nullptr); // for fast I/O; remember to flush cout before subsequent uses of cin for interactive use

  int arr[MAXN], n, q, l, r;

  while(cin >> n && n) {
    cin >> q;

    for(int i=1; i<=n; i++)
      cin >> arr[i];

    build(arr, 1, 1, n);

    while(q--) {
      cin >> l >> r;

      cout << query(1, 1, n, l, r).segCnt << "\n";
    }
  }

  return 0;
}
