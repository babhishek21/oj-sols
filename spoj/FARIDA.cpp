#include <bits/stdc++.h>
using namespace std;

long long dp[10001];

int main() {
  int t, n;

  cin >> t;

  for(int tc=1; tc<=t; tc++) {
    cin >> n;

    for(int i=0; i<n; i++){
      cin >> dp[i];

      if(i == 1) dp[i] = max(dp[i], dp[i-1]);
      if(i > 1) dp[i] = max(dp[i-1], dp[i] + dp[i-2]);
    }

    cout << "Case " << tc << ": " << ((n == 0) ? 0 : dp[n-1]) << endl;
  }
}
