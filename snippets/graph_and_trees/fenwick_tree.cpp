/**
 * Binary Indexed Trees (Fenwick Trees)
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

///////////////////////
// BIT (1-idx based) //
///////////////////////

unordered_map<int, int> bit;
int maxIdx;

inline int lowbit(int x) { return x & -x; }

// read accumulation of data from 1..idx
int query(int idx) {
  int sum = 0;

  while(idx > 0) {
    sum += bit[idx];
    idx -= lowbit(idx);
  }

  return sum;
}

// update the tree when original data at idx changes by +val
void update(int idx, int val) {
  while(idx <= maxIdx) {
    bit[idx] += val;
    idx += lowbit(idx);
  }
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  vector<int> test = {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3, 1, 0, 2};
  vector<int> pre(test.size());

  partial_sum(test.begin(), test.end(), pre.begin());

  maxIdx = test.size();
  for(int i=0; i<test.size(); i++) {
    update(i+1, test[i]);
  }

  for(int i=0; i<test.size(); i++) {
    if(!(query(i+1) == pre[i])) {
      debug(i)
      debug(query(i+1))
      debug(pre[i])
      break;
    }
  }

  return 0;
}
