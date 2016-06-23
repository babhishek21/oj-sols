/**
 * Leetcode OJ (Paint Fence)
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

class Solution {
public:
  int numWays(int n, int k) {
    if(n == 0) return 0;
    if(n == 1) return k;

    int dp[n];
    dp[0] = dp[1] = k;
    dp[1] *= k;

    for(int i=2; i<n; i++) {
      dp[i] = (k-1)*(dp[i-1] + dp[i-2]);
    }

    return dp[n-1];
  }

  int numWays1(int n, int k) {
    if(n == 0) return 0;
    else if(n == 1) return k;
    int diffColorCounts = k*(k-1);
    int sameColorCounts = k;
    for(int i=2; i<n; i++) {
      int temp = diffColorCounts;
      diffColorCounts = (diffColorCounts + sameColorCounts) * (k-1);
      sameColorCounts = temp;
    }
    return diffColorCounts + sameColorCounts;
  }

};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  Solution test;

  cout << test.numWays(7, 4) << endl;

  cout << test.numWays1(7, 4) << endl;

  return 0;
}

