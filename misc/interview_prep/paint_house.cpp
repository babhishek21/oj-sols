/**
 * Paint House I-II (Leetcode)
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

namespace paintHouse {
  /**
   * Paint House I
   * There are a row of n houses, each house can be painted with one of the three colors: red, blue or
   * green. The cost of painting each house with a certain color is different. You have to paint all the
   * houses such that no two adjacent houses have the same color.
   * The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For
   * example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting
   * house 1 with color green, and so on... Find the minimum cost to paint all houses.
   */
  int minCost1(vector<vector<int>> &costs) {
    if(costs.empty()) return 0;

    int n = costs.size();
    vector<vector<int>> dp(n, vector<int>(3));
    dp[0][0] = costs[0][0];
    dp[0][1] = costs[0][1];
    dp[0][2] = costs[0][2];

    for(int i=1; i<n; i++) {
      int red = dp[i-1][0], green = dp[i-1][1], blue = dp[i-1][2];

      dp[i][0] = min(green, blue) + costs[i][0];
      dp[i][1] = min(red, blue) + costs[i][1];
      dp[i][2] = min(red, green) + costs[i][2];
    }

    return *min_element(dp[n-1].begin(), dp[n-1].end());
  }

  /**
   * Paint House II
   * There are a row of n houses, each house can be painted with one of the k colors. The cost of painting
   * each house with a certain color is different. You have to paint all the houses such that no two adjacent
   * houses have the same color.
   *
   * The cost of painting each house with a certain color is represented by a n x k cost matrix. For example,
   * costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with
   * color 2, and so on... Find the minimum cost to paint all houses.
   *
   * Note: All costs are positive integers.
   * Follow up: Could you solve it in O(nk) runtime?
   */

  /**
   * The DP solution (similar to Paint House I) is fairly straightforward:
   * dp[i][k] = cost[i][k] + min(dp[i][j] for all j != k)
   *
   * This is O(nk^2) with possibly O(nk) space (can be reduced to O(k) space).
   *
   * A better O(nk) solution exists! Note that everytime we try a colour for a house, we have to find the
   * minimum cost for all other colors painted on the previous house. If we can keep track of just the two
   * least colour costs at each house, we can find the best deal for the next house. Here's how:
   *
   * Say the min1 and min2 are the two least color costs of the previous house. For our current house, one
   * of two case will occur:
   *
   * 1. min1 is the cost of the same color as we are trying to paint our current house. In which case, we'd
   * end up choosing the next best cost: min2!
   *
   * 2. min1 is cost of a different color than the one we are trying to paint our current house in. We are good
   * to go choosing this chost: min1!
   *
   * Note that min1 == min2 is possible. Since two different colors are attributed to min1 and min2, we simply
   * choose one that doesn't match our current color; which is a redundant comparison since both costs are same.
   *
   * Keeping track of these two costs at each house is a bit tricky!
   *
   * Say, dp[k] holds the minimal cost after painting the color k in the current house. Having set both min1
   * and min2 to INF, we can go through each color:
   *
   * Case-1: min2 > dp[k] >= min1         --> min2 = dp[k]
   *
   * Case 2: min1 > dp[k]                 --> min2 = min1; min1 = dp[k]
   */
  int minCost2(vector<vector<int>> &costs) {
    if(costs.empty()) return 0;

    int n = costs.size(), k = costs[0].size();

    vector<int> dp(k);
    int min1 = 0, min2 = min1;

    for(int i=0; i<n; i++) {
      int prevMin1 = min1, prevMin2 = min2;
      min1 = numeric_limits<int>::max(); min2 = min1;

      for(int j=0; j<k; j++) {

        dp[j] = (dp[j] != prevMin1)
          ? prevMin1 + costs[i][j]
          : prevMin2 + costs[i][j];


        if(min1 <= dp[j])
          min2 = min(min2, dp[j]);
        else {
          min2 = min1;
          min1 = dp[j];
        }
      }
    }

    return min1;
  }

}

int main() {
  using namespace paintHouse;

  vector<vector<int>> costs = { // C++11 only
    {5,8,6},
    {19,14,13},
    {7,5,12},
    {14,15,17},
    {3,20,10}
  };

  int ans = minCost1(costs);
  int anss = minCost2(costs);

  assert(ans == 43);
  cout << "PaintHouse1: " << ans << endl;

  assert(anss == 43);
  cout << "PaintHouse2: " << anss << endl;

  return 0;
}
