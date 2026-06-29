/**
 * Problem: DQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Option 1: Solved online using sqrt decomposition + binary search on the decomposed blocks.
 *  This problem degrades to KQUERY (find count of elements < k in given range), if you decompose on the "last seen index" array
 *  If the last seen index of arr[i] is < l (for search range [l, r]), that element arr[i] is the first occurrence of it in that range
 *
 *  Related: KQUERY, KQUERYO
 *
 * Option 2: Solved offline using Mo's algorithm.
 *  By far the fastest option in raw runtime.
 *
 *  Related: KQUERY
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 30004;
constexpr int MAXVAL = 1000002;
constexpr int BLOCK_LEN = 180; // roughly sqrt(MAXN)

int n, arr[MAXN];

namespace sqrt_decomp {
  int p[MAXN]; // index with previous occurrence of arr[i]
  vector<vector<int>> blocks;

  void preprocess() {
    // build p[]
    unordered_map<int, int> last_seen;

    for(int i=0; i<n; i++) {
      p[i] = last_seen.count(arr[i]) ? last_seen[arr[i]] : -1;
      last_seen[arr[i]] = i;
    }

    // distribute p[] into blocks
    blocks.assign(n / BLOCK_LEN + 1, {});

    for(int i=0, sz = min(n-i, BLOCK_LEN); i < n; i+= BLOCK_LEN, sz = min(n-i, BLOCK_LEN)) {
      auto& blk = blocks[i / BLOCK_LEN];

      blk.assign(sz, 0);
      copy_n(p+i, sz, blk.begin());

      whole(sort, blk);
    }
  }

  int query(int l, int r) {
    int res = 0;

    for(int i=l; i<=r;) {
      if(i % BLOCK_LEN == 0 and i + BLOCK_LEN - 1 <= r) {
        auto& blk = blocks[i/BLOCK_LEN];
        res += distance(blk.begin(), whole(lower_bound, blk, l));     // find all P[] in the block which are < l
        i += BLOCK_LEN;
      } else {
        res += p[i++] < l;  // add all P[i] which are < l
      }
    }

    return res;
  }

  void solve() {
    int q, l, r;

    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    preprocess();

    cin >> q;

    while(q--) {
      cin >> l >> r;
      cout << query(l-1, r-1) << "\n";
    }
  }
}

namespace mos_algorithm {
  struct Q {
    int idx, l, r;
    // PRETTY_OSTREAM_COMPACT(Q, l, r, idx)
  };

  const auto zigzag_compare = [](const Q& a, const Q& b) {    // for Chevron sorting
    int blka = a.l / BLOCK_LEN, blkb = b.l / BLOCK_LEN;

    return blka != blkb
      ? blka < blkb
      : (blka & 1 ? a.r < b.r : a.r > b.r);
  };

  int arr[MAXN];

  // Mo's algorithm
  int freq[MAXVAL],
    cnt_uniq = 0;

  void add_to_window(int val) {
    freq[val]++;

    if(freq[val] == 1)
      cnt_uniq++;
  }

  void remove_from_window(int val) {
    freq[val]--;

    if(freq[val] == 0)
      cnt_uniq--;
  }

  int st = 0, ed = -1;
  int query(int l, int r) {
    while(st > l) add_to_window(arr[--st]);
    while(ed < r) add_to_window(arr[++ed]);

    while(st < l) remove_from_window(arr[st++]);
    while(ed > r) remove_from_window(arr[ed--]);

    // debug(pretty_print_array(freq, 5), cnt_uniq);

    return cnt_uniq;
  }

  void solve() {
    int q, l, r;

    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    cin >> q;

    vector<Q> queries(q);
    vector<int> ans(q);

    for(int i=0; i<q; i++) {
      cin >> l >> r;
      queries[i] = {i, l-1, r-1};
    }

    whole(sort, queries, zigzag_compare);

    // debug(queries);

    for(auto& qq: queries)
      ans[qq.idx] = query(qq.l, qq.r);

    for(int i=0; i<q; i++)
      cout << ans[i] << "\n";
  }
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  // sqrt_decomp::solve();
  mos_algorithm::solve();

  return 0;
}
