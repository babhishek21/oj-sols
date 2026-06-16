/**
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

/* Split String */
vector<string> split(const string &s, char delim) {
  vector<string> res;
  istringstream ss(s); string item;
  while (getline(ss, item, delim)) res.push_back(item);
  return res;
}

/* Heap shortcuts */
template <typename T> using max_heap = priority_queue<T>;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

/*
Fenwick Tree (BIT) - 1-indexed.
pow2f == bit_floor(n)

To make Frequency BIT:
  add(val, 1) for each element → an order-statistic tree.
  kth smallest element = max_prefix(k-1)   (compressed to 0..n-1)
*/
template <typename T> struct BIT {
  int n; vector<T> tree; int pow2f;
  BIT(int n) : n(n), tree(n + 1), pow2f(n ? (1u << (31 - __builtin_clz(n))) : 0) {}

  void add(int i, T v) { for (; i <= n; i += i & -i) tree[i] += v; }
  T sum(int i) { T s = 0; for (; i > 0; i -= i & -i) s += tree[i]; return s; }
  T sum(int l, int r) { return sum(r) - sum(l - 1); }

  int max_prefix(T c) {
    T v{}; int at = 0;
    for (int len = pow2f; len; len >>= 1)
      if (at + len <= n && v + tree[at + len] <= c)
        v += tree[at + len], at += len;
    return at;
  }
};

/*
Coordinate Compression
usage: int idx = lower_bound(compressed.begin(), compressed.end(), val) - compressed.begin();
*/
template <typename T> vector<T> compress(vector<T> v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  return v;
}

/*
Safe Hash for unordered_map/set — defeats anti-hash-test on Codeforces/CodeChef
usage: unordered_map<int, int, safe_hash> mp;
*/
struct safe_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_SEED_FROM_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_SEED_FROM_RANDOM);
  }
};

/*
Pair hash (built on safe_hash via hash_combine)
usage: unordered_map<pair<int,int>, int, safe_pair_hash> pair_mp
*/
struct safe_pair_hash {
  template <typename T1, typename T2>
  size_t operator()(const pair<T1, T2> &p) const {
    return safe_hash{}(((uint64_t)hash<T1>{}(p.first) << 32) ^ hash<T2>{}(p.second));
  }
};

/* PBDS; using GNU/G++ only */
#if __has_include(<ext/pb_ds/assoc_container.hpp>)
#define USING_GNU_PB_DS
#include <ext/pb_ds/assoc_container.hpp>

// Order Statistic Tree
template <typename K, typename V, typename Comp = less<K>>
using ordered_map = __gnu_pbds::tree<
  K, V, Comp,
  __gnu_pbds::rb_tree_tag,
  __gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = less<K>>
using ordered_set = ordered_map<K, __gnu_pbds::null_type, Comp>;

template <typename K, typename V>
using ordered_multimap = ordered_map<K, V, less_equal<K>>;

template <typename K>
using ordered_multiset = ordered_set<K, less_equal<K>>;

// PBDS Hash Map/Set — defeats anti-hash-test, faster than unordered_map
template <typename K, typename V, typename Hash = safe_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = safe_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;
#endif

int main() {

  // --- safe_hash demo ---
  unordered_map<int, int, safe_hash> mp;
  mp[1] = 10; mp[2] = 20; mp[3] = 30;
  cout << "safe_hash map[2] = " << mp[2] << "\n";

  // --- safe_pair_hash demo ---
  unordered_map<pair<int, int>, string, safe_pair_hash> pair_mp;
  pair_mp[{1, 2}] = "edge";
  pair_mp[{2, 3}] = "vertex";
  cout << "safe_pair_hash ({1,2}) = " << pair_mp[{1, 2}] << "\n";

  // --- split demo ---
  auto parts = split("hello,world,foo", ',');
  cout << "split: ";
  for (auto &p : parts) cout << p << " ";
  cout << "\n";

  // --- BIT demo ---
  BIT<int> bit(5);
  bit.add(1, 3);
  bit.add(2, 5);
  bit.add(3, 7);
  cout << "BIT sum[1..3] = " << bit.sum(3) << "\n"; // 15
  cout << "BIT sum[2..4] = " << bit.sum(2, 4) << "\n";  // 12
  cout << "BIT max_prefix(<=10) = " << bit.max_prefix(10) << "\n";  // 2 (since indices 1 and 2 have sum 8)

  // --- BIT as frequency tree (k-th smallest) ---
  BIT<int> freq(10);
  freq.add(3, 3); // value 3 appears 3 times
  // freq.add(3, 1); freq.add(3, 1); freq.add(3, 1); // value 3 appears 3 times
  freq.add(5, 1);                                     // value 5 appears 1 time
  freq.add(7, 1);                                     // value 7 appears 1 time
  cout << "freq BIT kth(1) = " << freq.max_prefix(0) << "\n"; // 1st smallest = 3
  cout << "freq BIT kth(4) = " << freq.max_prefix(3) << "\n"; // 4th smallest = 5

  // --- coordinate compression demo ---
  vector<int> vals = {100, 50, 100, 25, 50};
  auto comp = compress(vals);
  cout << "compress: " << comp << "\n";

  // --- PBDS demo ---
#ifdef USING_GNU_PB_DS
  ordered_set<int> os;
  os.insert(5); os.insert(1); os.insert(3);
  cout << "ordered_set 2nd smallest = " << *os.find_by_order(1) << "\n";
  cout << "ordered_set order_of_key(3) = " << os.order_of_key(3) << "\n";

  ordered_multiset<int> oms;
  oms.insert(1); oms.insert(1); oms.insert(2);
  cout << "ordered_multiset order_of_key(1) = " << oms.order_of_key(1) << "\n";
  cout << "ordered_multiset order_of_key(2) = " << oms.order_of_key(2) << "\n";

  hash_map<int, string> hm;
  hm[42] = "answer";
  cout << "hash_map[42] = " << hm[42] << "\n";
#endif

  return 0;
}
