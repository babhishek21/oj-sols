/**
 * Problem: KQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved using Wavelet Tree / Merge-sort tree
 *
 * Related: KQUERYO, INVCNT
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define pb push_back
#define eb emplace_back

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 30004;
constexpr int SIGMA = 1e9 + 3;

// Wavelet tree (1-idx based)
struct wavelet_tree {
  int lo, hi;                            // elements are in the range [lo, hi]
  wavelet_tree *left = 0, *right = 0;    // left[] represents all elements <= mid, right[] represents the rest
  vector<int> kos;                       // count of elements <= mid, of the elements seen till then

  // elements are in range [u, v]
  // array indices are in range [from, to)
  wavelet_tree(int *from, int *to, int u, int v) {
    lo = u, hi = v;

    if(from >= to) return;

    int mid = lo + (hi-lo)/2;

    kos.reserve(to-from+1);
    kos.pb(0);

    for(auto it=from; it != to; ++it) {
      kos.pb(kos.back() + (*it <= mid));
    }

    auto pivot = stable_partition(from, to, [=](const int &x) { return x <= mid; });

    if(lo == hi) return;

    left = new wavelet_tree(from, pivot, lo, mid);
    right = new wavelet_tree(pivot, to, mid+1, hi);
  }

  // count of elements in index range [l, r] which are > k
  int Gk(int l, int r, int k) {
    if(l > r or hi <= k) return 0;
    if(k < lo) return r-l+1;

    int lkos = kos[l-1];
    int rkos = kos[r];

    return left->Gk(lkos+1, rkos, k) + right->Gk(l-lkos, r-rkos, k);
  }

  ~wavelet_tree() {
    delete left;
    delete right;
  }
};

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int n, q, l, r, k, arr[MAXN];

  cin >> n;

  for(int i=0; i<n; i++)
      cin >> arr[i];

  wavelet_tree ww(arr, arr+n, 1, SIGMA);

  cin >> q;

  while(q--) {
    cin >> l >> r >> k;
    cout << ww.Gk(l, r, k) << "\n";
  }

  return 0;
}
