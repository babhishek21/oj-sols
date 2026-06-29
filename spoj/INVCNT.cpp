/**
 * Problem: INVCNT - Inversion Count (SPOJ)
 * Author: babhishek21
 *
 * There are a few different ways to do this:
 * 1. Modified merge sort
 * 2. Order Statistics Tree (self-balanced BST / RB-Tree augmented with rank and order in nodes)
 * 3. Segment Tree (Wavelet Tree)
 * 4. BIT (Fenwick Tree)
 * 5. Tries
 *
 * Note the problem constraints:
 * - arrays have **distinct** integers.
 * - inversion is: if i < j and arr[i] > arr[j]
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

#define debug(x) cerr << #x << ": " << x << endl;

namespace fenwick_tree_classic {
  // 1-index based BIT
  constexpr int MAX_BIT_VAL = 10000003;
  int bit[MAX_BIT_VAL];

  void update(int idx, int delta) {
    for(; idx < MAX_BIT_VAL; idx += (idx & -idx))
      bit[idx] += delta;
  }

  int query(int idx) {
    int sum = 0; // prefix sum

    for(; idx > 0; idx -= (idx & -idx))
      sum += bit[idx];

    return sum;
  }

  void solve() {
    int n, x;
    long long ans = 0LL;

    cin >> n;
    memset(bit, 0, sizeof(bit));

    for(int i=1; i<=n; i++) {
      cin >> x;

      ans += i - query(x) - 1;
      update(x, 1);
    }

    cout << ans << '\n';
  }
}

namespace fenwick_tree_coordinate_compression {
  // 1-index based BIT
  int bit[200003], bit_sz = 0;

  void update(int idx, int delta) {
    for(; idx <= bit_sz; idx += (idx & -idx))
      bit[idx] += delta;
  }

  int query(int idx) {
    int sum = 0; // prefix sum

    for(; idx > 0; idx -= (idx & -idx))
      sum += bit[idx];

    return sum;
  }

  void solve() {
    int n, x;
    long long ans = 0LL;

    cin >> n;
    // debug(n)

    bit_sz = n;
    memset(bit, 0, sizeof(bit[0])*(bit_sz+1));

    vector<int> arr(n), sorted;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    sorted = vector<int>(arr);
    sort(sorted.begin(), sorted.end());

    // debug(arr)
    // debug(sorted)

    for(int i=0; i<n; i++) {
      int idx = distance(sorted.begin(), lower_bound(sorted.begin(), sorted.end(), arr[i]));

      update(idx+1, 1);

      ans += i+1 - query(idx+1);
    }

    cout << ans << '\n';
  }
}

namespace modified_merge_sort {
  int arr[200003], n;

  long long merge(int l, int mid, int r) {
    int left = l, right = mid+1;
    long long inv = 0;

    while(left <= mid && right <= r) {
      if(arr[left] <= arr[right])
        left++;
      else {
        inv += mid - left + 1;
        right++;
      }
    }

    inplace_merge(arr+l, arr+mid+1, arr+r+1);

    return inv;
  }

  long long sort(int l, int r) {
    if(l >= r)
      return 0;

    int mid = l + (r-l)/2;
    long long invLeft = sort(l, mid), invRight = sort(mid+1, r);

    return invLeft + invRight + merge(l, mid, r);
  }

  void solve() {
    long long ans = 0LL;

    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    cout << sort(0, n-1) << '\n';
  }
}

namespace trie {
  constexpr int TRIE_BITS = 24; // enough for integers <= 10^7
  constexpr int MAX_NODES = 5000000; // enough for 24 * 200000

  int nxt[MAX_NODES][2], cnt[MAX_NODES];
  int tot = 1; // node 0 is root

  void reset() {
    memset(nxt[0], 0, sizeof(nxt[0])*tot);
    memset(cnt, 0, sizeof(cnt[0])*tot);
    tot = 1;
  }

  void insert(int val) {
    int node = 0;

    for(int i = TRIE_BITS-1; i>=0; i--) {
      int b = (val>>i) & 1;

      if(!nxt[node][b])
        nxt[node][b] = tot++;

      node = nxt[node][b];
      cnt[node]++;
    }
  }

  long long count_greater_than(int val) {
    long long res = 0LL;
    int node = 0;

    for(int i = TRIE_BITS-1; i>=0; i--) {
      int b = (val>>i) & 1;

      if(!b)  // all numbers to the right subtree (bit==1) must be greater than val
        res += cnt[nxt[node][1]];

      node = nxt[node][b];
      if(!node)
        break;
    }

    return res;
  }

  void solve() {
    long long ans = 0LL;
    int n, x;

    reset();

    cin >> n;

    for(int i=0; i<n; i++) {
      cin >> x;

      ans += count_greater_than(x);
      insert(x);
    }

    cout << ans << '\n';
  }
}

int main() {
  int t;

  cin >> t;

  while(t--) {
    // fenwick_tree_classic::solve();
    // fenwick_tree_coordinate_compression::solve();
    // modified_merge_sort::solve();
    trie::solve();
  }

  return 0;
}
