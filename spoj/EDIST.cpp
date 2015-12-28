#include <bits/stdc++.h>
using namespace std;

int dp[2001][2001];

inline int min_util(int x, int y, int z) {
  return min(x, min(y, z));
}

int main() {
  int t;
  string a, b;

  cin >> t;

  while(t--) {
    cin >> a;
    cin >> b;

    int na = a.size(), nb = b.size();

    // Wagner-Fischer Algorithm for Edit Distance

    for(int i=0; i<=na; i++)
      dp[i][0] = i; // i insertions
    for(int j=0; j<=nb; j++)
      dp[0][j] = j; // j deletions

    for(int i=1; i<=na; i++)
      for(int j=1; j<=nb; j++) {

        if(a[i-1] == b[j-1])
          dp[i][j] = dp[i-1][j-1];
        else
          dp[i][j] = min_util(
            dp[i-1][j] + 1, // deletion
            dp[i][j-1] + 1, // insertion
            dp[i-1][j-1] + 1 // substitution
            );
      }

    cout << dp[na][nb] << endl;
  }

  return 0;
}
