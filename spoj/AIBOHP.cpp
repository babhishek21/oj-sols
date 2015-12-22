/* Hint: LCS of input string and its reverse. */
#include <bits/stdc++.h>
using namespace std;

int dp[6101][6101];

int main() {
  int t;
  string str;

  cin >> t;

  while(t--) {
    cin >> str;
    string rev(str.rbegin(), str.rend());

    // cout << str << " " << rev << endl; // DEBUG

    // find lcs length
    int n = str.size();

    for(int i=0; i<=n; i++)
      dp[i][0] = dp[0][i] = 0;

    for(int i=1; i<=n; i++)
      for(int j=1; j<=n; j++) {
        if(str[i-1] == rev[j-1])
          dp[i][j] = dp[i-1][j-1] + 1;
        else
          dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }

    cout << n - dp[n][n] << endl;
  }

  return 0;
}
