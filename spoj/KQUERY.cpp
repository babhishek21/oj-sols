/**
 * Problem: KQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved using sqrt decomposition.
 * Not worth it to apply Mo's algorithm, since window ops (add, remove, query) can't be done in constant time.
 *
 * Related: KQUERYO
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
constexpr int BLOCK_LEN = 180;

int n, q, arr[MAXN];
vector<vector<int>> blocks;

void preprocess() {
  blocks.assign(n, {});

  for(int i=0, sz; i<n; i+=BLOCK_LEN) {
    auto& blk = blocks[i/BLOCK_LEN];
    sz = min(BLOCK_LEN, n-i);

    blk.assign(sz, 0);
    copy_n(arr+i, sz, blk.begin());

    whole(sort, blk);
  }
}

int query(int l, int r, int k) {
  int res = 0;

  l--; r--; // convert 1-based indexing to 0-based indexing

  for(int i=l; i<=r;) {
    if(i % BLOCK_LEN == 0 && i + BLOCK_LEN - 1 <= r) {
      res += distance(whole(upper_bound, blocks[i/BLOCK_LEN], k), blocks[i / BLOCK_LEN].end());
      i += BLOCK_LEN;
    } else
      res += (arr[i++] > k);
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int l, r, k;

  cin >> n;

  for(int i=0; i<n; i++)
      cin >> arr[i];

  preprocess();

  cin >> q;

  while(q--) {
    cin >> l >> r >> k;
    cout << query(l, r, k) << "\n";
  }

  return 0;
}
