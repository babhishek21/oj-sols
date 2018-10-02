/**
 * Wavelet tree (aka Merge Sort Tree)
 * Ref: https://users.dcc.uchile.cl/~jperez/papers/ioiconf16.pdfgg
 * Ref: http://rachitiitr.blogspot.com/2017/06/wavelet-trees-wavelet-trees-editorial.html
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

// Wavelet tree / Merge-sort tree (1-idx based)
struct wavelet_tree {
  int lo, hi;                            // elements are in the range [lo, hi]
  wavelet_tree *left = 0, *right = 0;    // left[] represents all elements <= mid, right[] represents the rest
  vector<int> kos;                       // count of elements <= mid, of the elements seen till then
  vector<int> prfs;                      // prefix sum of elements

  // elements are in range [u, v]
  // array indices are in range [from, to)
  wavelet_tree(int *from, int *to, int u, int v) {
    lo = u, hi = v;

    if(from >= to) return;

    int mid = lo + (hi-lo)/2;

    kos.reserve(to-from+1);
    kos.pb(0);
    prfs.reserve(to-from+1);
    prfs.pb(0);

    for(auto it=from; it != to; ++it) {
      kos.pb(kos.back() + (*it <= mid));
      prfs.pb(prfs.back() + (*it));
    }

    auto pivot = stable_partition(from, to, [=](const int &x) { return x <= mid; });

    if(lo == hi) return;

    left = new wavelet_tree(from, pivot, lo, mid);
    right = new wavelet_tree(pivot, to, mid+1, hi);
  }

  // kth smallest element in index range [l, r]
  int kth(int l, int r, int k) {
    if(l > r) return 0;
    if(lo == hi) return lo;     // lo == hi == kth element

    int cnt_left_this_level = kos[r] - kos[l-1];
    int lkos = kos[l-1];                // count of elements from first (l-1) elemnts that go in left[];
    int rkos = kos[r];                  // count of elements from first (r) elemnts that go in left[];

    if(k <= cnt_left_this_level)        // kth element falls in the left half
      return left->kth(lkos+1, rkos, k);
    else
      return right->kth(l-lkos, r-rkos, k-cnt_left_this_level);
  }

  // count of elements in index range [l, r] which are <= k
  int LTEk(int l, int r, int k) {
    if(l > r or k < lo) return 0;
    if(k >= hi) return r-l+1;

    int lkos = kos[l-1];
    int rkos = kos[r];

    return left->LTEk(lkos+1, rkos, k) + right->LTEk(l-lkos, r-rkos, k);
  }

  // sum of elements in index range [l, r] which are <= k
  int sumLTEk(int l, int r, int k) {
    if(l > r or k < lo) return 0;
    if(k >= hi) return prfs[r] - prfs[l-1];

    int lkos = kos[l-1];
    int rkos = kos[r];

    return left->sumLTEk(lkos+1, rkos, k) + right->sumLTEk(l-lkos, r-rkos, k);
  }

  // count of elements in index range [l, r] which are > k
  int GEk(int l, int r, int k) {
    if(l > r or hi <= k) return 0;
    if(k < lo) return r-l+1;

    int lkos = kos[l-1];
    int rkos = kos[r];

    return left->GEk(lkos+1, rkos, k) + right->GEk(l-lkos, r-rkos, k);
  }

  // count of elements in index range [l, r] which are == k
  int cntk(int l, int r, int k) {
    if(l > r or k < lo or k > hi) return 0;
    if(lo == hi) return r-l+1;    // lo == hi == k

    int lkos = kos[l-1];
    int rkos = kos[r];
    int mid = lo + (hi-lo)/2;

    if(k <= mid)
      return left->cntk(lkos+1, rkos, k);
    else
      return right->cntk(l-lkos, r-rkos, k);
  }

  // count of elements in index range [l, r] which fall in value range [u, v]
  int range(int l, int r, int u, int v) {
    if(l > r) return 0;
    return val_range_upper_bound(r, u, v) - val_range_upper_bound(l-1, u, v);
  }

  // gives upper bound count of elements which fall in value ragne [u, v]
  int val_range_upper_bound(int i, int u, int v) {
    if(hi < u or v < lo) return 0;
    if(u <= lo and hi <= v) return i;

    int cnt = 0;
    if(left)
      cnt += left->val_range_upper_bound(kos[i], u, v);
    if(right)
      cnt += right->val_range_upper_bound(i-kos[i], u, v);
    return cnt;
  }

  ~wavelet_tree() {
    delete left;
    delete right;
  }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int arr[] = { 1, 2, 3, 3, 5, 4, 2 };

  cout << pretty_print_array(arr, 7) << endl;

  wavelet_tree T(arr, arr+7, 0, 10);

  cout << "kth smallest element in [5, 7] for k == 1: " << T.kth(5, 7, 1) << endl;
  cout << "kth smallest element in [5, 7] for k == 2: " << T.kth(5, 7, 2) << endl;
  cout << "kth smallest element in [1, 7] for k == 2: " << T.kth(1, 7, 2) << endl;
  cout << "kth smallest element in [1, 4] for k == 3: " << T.kth(1, 4, 3) << endl;

  cout << "count of elements <= k in [2, 6] for k == 4: " << T.LTEk(2, 6, 4) << endl;
  cout << "count of elements <= k in [1, 7] for k == 3: " << T.LTEk(1, 7, 3) << endl;

  cout << "count of elements == k in [1, 7] for k == 3: " << T.cntk(1, 7, 3) << endl;
  cout << "count of elements == k in [2, 4] for k == 2: " << T.cntk(2, 4, 2) << endl;

  cout << "sum of elements <= k in [2, 6] for k == 4: " << T.sumLTEk(2, 6, 4) << endl;
  cout << "sum of elements <= k in [1, 7] for k == 3: " << T.sumLTEk(1, 7, 3) << endl;

  cout << pretty_print_array(arr, 7) << endl;  // this should be sorted

  return 0;
}
