/**
 * Problem: Tourist (FB HackerCup Quals 2018)
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

long long n, k, v;
string str;
vector<pair<int, string>> arr, out;

void solve() {
  cin >> n >> k >> v;

  arr.clear();
  out.clear();

  for(size_t i=0; i<n; i++) {
    cin >> str;
    arr.eb(i, str);
  }

  long long st = ((v-1)*k)%n;

  for(size_t i=0; i<k; i++)
    out.pb(arr[(st+i)%n]);

  whole(sort, out);

  for(auto&& tup: out)
    cout << tup.second << " ";
  cout << endl;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int tc;

  cin >> tc;

  for(int i=0; i<tc; i++) {
    cout << "Case #" << i+1 << ": ";
    solve();
  }

  return 0;
}