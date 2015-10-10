#include <bits/stdc++.h>
using namespace std;

bool dec_cmp(int i, int j) { return i>j; }
int dp[1001][1001];

int main() {
  int t, m, n, temp;
  vector<int> x, y;

  cin >> t;

  while(t--) {
    cin >> m >> n;

    m--; n--;

    for(int i=0; i<m; i++) {
      cin >> temp;
      x.push_back(temp);
    }

    for(int i=0; i<n; i++) {
      cin >> temp;
      y.push_back(temp);
    }

    sort(x.begin(), x.end(), dec_cmp);
    sort(y.begin(), y.end(), dec_cmp);

    // reset
    memset(dp, 0 , sizeof(dp));

    // base case
    dp[0][0] = 0;

    // initialization
    for(int i=1; i<=m; i++)
      dp[i][0] = dp[i-1][0] + x[i-1];
    for(int j=1; j<=n; j++)
      dp[0][j] = dp[0][j-1] + y[j-1];

    // the shiz
    for(int i=1; i<=m; i++) {
      for(int j=1; j<=n; j++) {
        dp[i][j] = min(dp[i-1][j] + (j+1)*x[i-1], dp[i][j-1] + (i+1)*y[j-1]);
      }
    }

    // the answer
    cout << dp[m][n] << endl;

    // some cleanup
    x.clear(); y.clear();
  }

  return 0;
}
