/**
 * Problem: C. Not So Random (APAC 2017 Practice Round)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int t, n, x, k;
double a, b, c, dp[100010][2];

double solve() {
  double ans = 0.0;
  long long checker = 1LL;
  int bx, bk;

  for(int bit=0; bit<33; bit++) {
    bx = (x&checker) == checker;
    bk = (k&checker) == checker;

    // cout << checker << " " << bx << " " << bk << endl;

    dp[0][0] = 0.0;
    dp[0][1] = 1.0;

    for(int i=1; i<=n; i++) {
      dp[i][0] = dp[i][1] = 0.0;

      dp[i][0] += a*dp[i-1][bk&0];
      dp[i][0] += b*dp[i-1][bk|0];
      dp[i][0] += c*dp[i-1][bk^0];

      dp[i][1] += a*dp[i-1][bk&1];
      dp[i][1] += b*dp[i-1][bk|1];
      dp[i][1] += c*dp[i-1][bk^1];
    }

    ans += dp[n][bx]*(double)checker;
    checker <<= 1;
  }

  return ans;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n >> x >> k >> a >> b >> c;
    a /= 100;
    b /= 100;
    c /= 100;

    cout << "Case #" << tc+1 << ": " << fixed << setprecision(10) << solve() << endl;
  }

  return 0;
}
