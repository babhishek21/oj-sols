/**
 * Problem: BALLOT (SPOJ)
 * Author: babhishek21
 * Lang: C++11
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

int n, b;
vector<int> arr;

int p(int dist) {
  int cnt = 0;

  for(auto&& pop: arr) {
    cnt += max(1, (pop/dist) + (pop%dist > 0));
  }

  return cnt;
}

void solve() {
  arr.resize(n, 0);

  for(int i=0; i<n; i++)
    cin >> arr[i];

  // binary search to find optimal assignment
  int lo = 1, hi = 5000000, mid;

  while(lo < hi) {
    mid = lo + (hi-lo)/2;

    if(p(mid) <= b)
      hi = mid;
    else
      lo = mid+1;
  }

  cout << lo << endl;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> n >> b;

  while(n != -1 && b != -1) {
    solve();

    cin >> n >> b;
  }

  return 0;
}
