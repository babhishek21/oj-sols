/**
 * Problem: KQUERYO (SPOJ)
 * This solution used Wavelet tree. Strict TLE, so use C-style fast I/O.
 * Author: babhishek21
 * Lang: C++14
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

int arr[30010];
static const int SIGMA = 1e9 + 10;

// Wavelet tree / Merge-sort tree (1-idx based)
struct wavelet_tree {
  int lo, hi;                    // elements are in the range [lo, hi]
  wavelet_tree *left = 0, *right = 0;    // left[] represents all elements <= mid, right[] represents the rest
  vector<int> kos;               // count of elements <= mid, of the elements seen till then

  // elements are in range [u, v]
  // array indices are in range [from, to)
  wavelet_tree(int *from, int *to, int u, int v) {
    lo = u, hi = v;

    if(from >= to) return;

    int mid = lo + (hi-lo)/2;

    kos.reserve(to-from+1);
    kos.eb(0);

    for(auto it=from; it != to; ++it)
      kos.eb(kos.back() + (*it <= mid));

    auto pivot = stable_partition(from, to, [&](int x) { return x <= mid; });

    if(lo == hi) return;

    left = new wavelet_tree(from, pivot, lo, mid);
    right = new wavelet_tree(pivot, to, mid+1, hi);
  }

  // count of elements in index range [l, r] which are > k
  int GEk(int l, int r, int k) {
    if(l > r or hi <= k) return 0;
    if(k < lo) return r-l+1;

    int lkos = kos[l-1];
    int rkos = kos[r];

    return left->GEk(lkos+1, rkos, k) + right->GEk(l-lkos, r-rkos, k);
  }

  ~wavelet_tree() {
    delete left;
    delete right;
  }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, q, ans, i, j, k;

  scanf("%d", &n);

  for(i=0; i<n; i++)
    scanf("%d", arr+i);

  wavelet_tree ww(arr, arr+n, 1, SIGMA);

  scanf("%d", &q);

  ans = 0;
  while(q--) {
    scanf("%d %d %d", &i, &j, &k);

    i = max(1, i xor ans);
    j = min(n, j xor ans);
    k = max(0, k xor ans);

    ans = ww.GEk(i, j, k);

    printf("%d\n", ans);
  }

  return 0;
}
