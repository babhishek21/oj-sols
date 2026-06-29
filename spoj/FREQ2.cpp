/**
 * Problem: FREQ2 (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Needs Mo's algorithm over sqrt-decomposition block-based sorting.
 *
 * One small optimization to apply is using natural sorting of queries when number of queries is less
 *  than ~950 ≈ 3·√n (since that will outcompete block based sorting). If you plan to use Chevron sorting,
 *  the cutoff is even lower, at ~480 ≈ 1.5·√n
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
#define mp make_pair

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 100005;
constexpr int BLOCK_LEN = 320;
constexpr int CUTOFF = 950;

struct Query {
  int idx, l, r;
  Query(int _idx, int _l, int _r): idx(_idx), l(_l), r(_r) {};

  // for debugging
  // friend ostream& operator<< (ostream& out, const Query& q) {
  //   out << make_tuple(q.idx, q.l, q.r);
  //   return out;
  // }
};

int arr[MAXN], n, q;
vector<Query> queries;

void sort_queries() {
  // auto compare = q < CUTOFF
  //   ? [](const Query& a, const Query& b) {      // Natural sort
  //     return mp(a.l, a.r) < mp(b.l, b.r);
  //   }
  //   : [](const Query& a, const Query& b) {      // Mo's algorithm -> sqrt-decomp block-based sorting
  //     return mp(a.l / BLOCK_LEN, a.r) < mp(b.l / BLOCK_LEN, b.r);
  //   };

  // alternatively we can try zig zag / Chevron sorting -> overall faster
  auto compare = [](const Query& a, const Query& b) {
    int block_a = a.l / BLOCK_LEN, block_b = b.l / BLOCK_LEN;

    return block_a != block_b
      ? block_a < block_b
      : (block_a & 1 ? a.r < b.r : a.r > b.r);
  };

  whole(sort, queries, compare);
  // debug(queries);
}

// Mo's algorithm
int freq[MAXN],      // freq[x] is the frequency of x in current lookup window
  cnt[MAXN],         // cnt[x] is the number of elements in current lookup window that have frequency = x (i.e. inverse frequency index)
  curr_mode_freq = 0;  // current mode's frequency

void add_to_window(int x) {
  cnt[freq[x]]--;
  freq[x]++;
  cnt[freq[x]]++;

  curr_mode_freq = max(curr_mode_freq, freq[x]);
}

void remove_from_window(int x) {
  if(freq[x] == curr_mode_freq and cnt[freq[x]] == 1) // current mode went out of the window, and it was the singular mode
    curr_mode_freq--;               // so it remains the mode, but at a reduced frequency

  cnt[freq[x]]--;
  freq[x]--;
  cnt[freq[x]]++;
}

int st = 0, ed = -1;  // window start & end indices
int query_range(int l, int r) {
  //expand first
  while(ed < r) { add_to_window(arr[++ed]); }
  while(st > l) { add_to_window(arr[--st]); }

  // then contract
  while(ed > r) { remove_from_window(arr[ed--]); }
  while(st < l) { remove_from_window(arr[st++]); }

  return curr_mode_freq;
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int l, r, ans;
  vector<int> results;

  cin >> n >> q;

  for(int i=0; i<n; i++)
    cin >> arr[i];

  // debug(pretty_print_array(arr, n));

  queries.reserve(q);
  for(int i=0; i<q; i++) {
    cin >> l >> r;
    queries.emplace_back(i, l, r);
  }

  sort_queries();

  results.assign(q, 0);
  for(auto& qq: queries)
    results[qq.idx] = query_range(qq.l, qq.r);

  for(auto& num: results)
    cout << num << "\n";

  return 0;
}
