/**
 * n == no. of die, k == exact aggregate sum of pips reqd.
 * For n > 1000 or k > 6000, the answer becomes zero. This is a general observation for a six-faced dice.
 * For the rest we can write a recurrence as:
 * dp[n][k] = (dp[n-1][k-1] + dp[n-1][k-2] + dp[n-1][k-2] + dp[n-1][k-3] + dp[n-1][k-4] + dp[n-1][k-5] + dp[n-1][k-6])/6
 * The reason for this recurrence is that for any throw of a die, we can get 1-6 pip(s) each with probability of 1/6.
 */

#include <bits/stdc++.h> // using GCC
using namespace std;

double dp[1000][6000];

int main() {
  int t, n, k;
  // memset(dp, 0, sizeof(dp[0][0])*1000*1000);

  // for(int i=0; i<1000; i++)
  //   dp[0][i] = dp[i][0] = 0;

  // for single dice, only sums of 1-6 are possible. Hence probability is 100.0/6 in %
  for(int i=1; i<7; i++)
    dp[1][i] = 1.0/6.0;

  for(int i=2; i<1000; i++) // no. of die
    for(int j=1; j<6000; j++) { // sum of pips till `i`th die
      switch(j) {
        case 1:
        dp[i][j] = dp[i-1][j-1]/6.0;
        break;

        case 2:
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j-2])/6.0;
        break;

        case 3:
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j-2] + dp[i-1][j-3])/6.0;
        break;

        case 4:
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j-2] + dp[i-1][j-3] + dp[i-1][j-4])/6.0;
        break;

        case 5:
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j-2] + dp[i-1][j-3] + dp[i-1][j-4] + dp[i-1][j-5])/6.0;
        break;

        default:
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j-2] + dp[i-1][j-3] + dp[i-1][j-4] + dp[i-1][j-5] + dp[i-1][j-6])/6.0;
      }
    }

  // for(int i=1; i<11; i++)
  //   cout << i << "\t";
  // cout << endl;
  // for(int i=1; i<11; i++) {
  //   for(int j=1; j<11; j++)
  //     cout << (int)(dp[i][j]*100) << "\t";
  //   cout << endl;
  // }

  cin >> t;

  while(t--) {
    cin >> n >> k;

    if(n<1000 and k<6000)
      cout << (int)(dp[n][k]*100) << endl;
    else
      cout << "0" << endl;
  }

  return 0;
}
