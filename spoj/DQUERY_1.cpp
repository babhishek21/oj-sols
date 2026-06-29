/**
 * Problem: DQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved offline using Mo's algorithm.
 *
 * Related: KQUERY
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
constexpr int MAXVAL = 1000002;
constexpr int BLOCK_LEN = 180; // roughly sqrt(MAXN)

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

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int n, q, l, r;

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

  return 0;
}
