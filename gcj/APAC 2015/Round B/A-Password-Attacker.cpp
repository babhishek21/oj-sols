/**
 * Problem: A. Password Attacker (APAC 2015 Round B)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007

int t, m, n;
long long dp[105][105]; // dp[n][m] = numbers of ways to have n length string with m distinct keys

void prep() {
  /*
  dp[n][1] = 1
  dp[n][m] = 0 if m > n (since question constrains m <= n)
  dp[n][m] = (m * dp[n-1][m-1]) + (m * dp[n-1][m]) if m <= n
    WHY?? => For a string of n-1 length, there can be two cases:
              1. You append a new distinct key. So from dp[n-1][m-1],
                adding the mth key will give m new permutations
              2. You choose one of the m distinct keys available to append
                to string. From dp[n-1][m], m choices for the key to append.
   */

  // init
  for(int i=1; i<=100; i++)
    dp[i][1] = 1LL;

  for(int i=2; i<=100; i++)
    for(int j=2; j<=i; j++) {
      dp[i][j] = j * (dp[i-1][j-1] + dp[i-1][j])% MOD;
      dp[i][j] %= MOD;
    }
}

long long solve() {
  cin >> m >> n;

  return dp[n][m];
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  prep();

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": " << solve() << endl;
  }

  return 0;
}
