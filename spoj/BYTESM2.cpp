#include <bits/stdc++.h>
using namespace std;

int dp[101][101];

int main() {
  int t, h, w, ans;

  cin >> t;

  while(t--) {
    cin >> h >> w;

    for(int i=0; i<w; i++)
      cin >> dp[0][i];

    for(int i=1; i<h; i++)
      for(int j=0; j<w; j++){
        cin >> dp[i][j];

        if(j == 0)
          dp[i][j] += max(dp[i-1][j], dp[i-1][j+1]);
        else if(j == w-1)
          dp[i][j] += max(dp[i-1][j-1], dp[i-1][j]);
        else
          dp[i][j] += max(dp[i-1][j], max(dp[i-1][j-1], dp[i-1][j+1]));

      }

    ans = 0;

    for(int i=0; i<w; i++)
      ans = max(ans, dp[h-1][i]);

    cout << ans << endl;
  }

  return 0;
}
