/**
 * Problem: ABA12C (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

int n, k, t;
int arr[200], dp[200];

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  while(t--) {
    cin >> n >> k;

    fill_n(dp, k+10, INF);
    dp[0] = 0;

    for(int i=0; i<k; i++) {
      cin >> arr[i];
      dp[i+1] = arr[i] != -1 ? arr[i] : dp[i+1];
    }

    for(int i=1; i<=k; i++)
      for(int j=1; j<=i; j++)
        dp[i] = arr[j-1] != -1 ? min(dp[i], dp[i-j] + arr[j-1]): INF;

    // debug(pretty_print_array(dp, n));

    cout << (dp[k] < INF ? dp[k] : -1) << endl;
  }

  return 0;
}
