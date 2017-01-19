/**
 * Problem: Manic Moving (FB HackerCup 2017 Round 1)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define debug(x) cerr << #x << " : " << x << endl;
#define INF 10000000000000

int t, n, m, k, a, b, c;
long long g[110][110], dp[5050][2];
vector<int> s, d;

void prep(int n) {
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      g[i][j] = (i != j ? INF : 0);
}

void calc_fw(int n) { // Floyd-Warshall
  for(int k=1; k<=n; k++)
    for(int i=1; i<=n; i++)
      for(int j=1; j<=n; j++)
        g[i][j] = min(g[i][j],  g[i][k] + g[k][j]);

  // debug
  // for(int i=1; i<=n; i++)
  //   for(int j=1; j<=n; j++)
  //     if(g[i][j] != g[j][i])
  //       cerr << "Fail: (" << i << ", " << j << ")" << endl;
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    // debug(tc+1)

    cin >> n >> m >> k;

    prep(n);
    s.clear();
    d.clear();

    for(int i=0; i<m; i++) {
      cin >> a >> b >> c;
      g[a][b] = g[b][a] = min(g[a][b], min(g[b][a], (long long)c));
    }

    calc_fw(n);

    s.pb(1);
    d.pb(1);
    for(int i=0; i<k; i++) {
      cin >> a >> b;
      s.pb(a);
      d.pb(b);
    }

    // base cases
    dp[0][0] = 0;
    dp[0][1] = INF;

    for(int i=1; i<=k; i++) {
      // dp[i][0] is the cost accumulated by truck by delivering `i` families with no other load left
      dp[i][0] = min(
        dp[i-1][1] + g[d[i-1]][d[i]],                          // s[i-1] -> s[i] -> d[i-1] => d[i]
        dp[i-1][0] + g[d[i-1]][s[i]] + g[s[i]][d[i]]           // s[i-1] -> d[i-1] => s[i] -> d[i]
      );

      // dp[i][1] is the cost accumulated by truck by delivering `i` families with the `i+1` th family's load left
      dp[i][1] = (i>=k ? INF : min(
        dp[i-1][1] + g[d[i-1]][s[i+1]] + g[s[i+1]][d[i]],                    // s[i-1] -> s[i] -> d[i-1] => s[i+1] -> d[i]
        dp[i-1][0] + g[d[i-1]][s[i]] + g[s[i]][s[i+1]] + g[s[i+1]][d[i]]     // s[i-1] -> d[i-1] => s[i] -> s[i+1] -> d[i]
      ));

      // debug(dp[i][0])
      // debug(dp[i][1])
    }

    // cout << "Case #" << tc+1 << ": " << (dp[k][0] >= INF || dp[k][0] < 0 ? -1 : dp[k][0]) << endl;
    cout << "Case #" << tc+1 << ": " << (dp[k][0] >= INF? -1 : dp[k][0]) << endl;
  }

  return 0;
}
