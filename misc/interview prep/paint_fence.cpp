/**
 * Paint Fence (Leetcode)
 * There is a fence with n posts, each post can be painted with one of the k colors.
 * You have to paint all the posts such that no more than two adjacent fence posts have the same color.
 * Return the total number of ways you can paint the fence.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

namespace paintFence {
  /**
   * My solution. Simple O(n) DP.
   * k ways to paint fence 1
   * k*k ways to paint fence 2
   * There are two cases for painting fence i:
   *  1. Fence i-1 and i-2 have different color. So k-1 choices for fence i coming from fence i-2
   *  2. Fence i-1 and i-2 have same color, k-1 choices for fence i
   */
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

  // Benchmark DP solution. Found online.
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

}

int main() {

  int ans1 = paintFence::numWays(7, 4), ans2 = paintFence::numWays1(7,4);

  assert(ans1 == ans2);
  cout << "paintFence for args: (7,4)" << endl
      << "numWays: " << ans1 << endl
      << "numWays1: " << ans2 << endl;


  return 0;
}

