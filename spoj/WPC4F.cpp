/* SPOJ-WPC4F Looks like DP. Heck I
 * didn't even think of recursion.
 */

#include <bits/stdc++.h>
using namespace std;

int arr[20][3], dp[20][3]; // A,D,B

int main() {
  int t,n;

  cin >> t;

  while(t--) {
    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i][0] >> arr[i][1] >> arr[i][2];

    for(int i=0; i<3; i++)
      dp[0][i] = arr[0][i];

    for(int i=1; i<n; i++) {
      dp[i][0] = arr[i][0] + min(dp[i-1][1], dp[i-1][2]);
      dp[i][1] = arr[i][1] + min(dp[i-1][0], dp[i-1][2]);
      dp[i][2] = arr[i][2] + min(dp[i-1][1], dp[i-1][0]);
    }

    cout << min(dp[n-1][0], min(dp[n-1][1], dp[n-1][2])) << endl;
  }

  return 0;
}
