/**
 * Problem: DQUERY (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Solved using sqrt decomposition + binary search on the decomposed blocks.
 * This problem degrades to KQUERY (find count of elements < k in given range), if you decompose on the "last seen index" array
 * If the last seen index of arr[i] is < l (for search range [l, r]), that element arr[i] is the first occurrence of it in that range
 *
 * Related: KQUERY, KQUERYO
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

constexpr int MAXN = 30004;
constexpr int BLOCK_LEN = 180; // roughly sqrt(MAXN)

int n,
  arr[MAXN],
  p[MAXN]; // index with previous occurrence of arr[i]
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

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

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

  return 0;
}
