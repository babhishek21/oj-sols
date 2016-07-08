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
  int minCost(vector<vector<int>> &costs) {
    if(costs.empty()) return 0;

    int n = costs.size();
    for(int i=1; i<n; i++) {
      int red = costs[i-1][0], green = costs[i-1][1], blue = costs[i-1][2];

      costs[i][0] += min(green, blue);
      costs[i][1] += min(red, blue);
      costs[i][2] += min(red, green);
    }

    return *(min_element(costs[n-1].begin(), costs[n-1].end()));
  }

  int minCost1(vector<vector<int>> &costs) {
    if(costs.empty()) return 0;

    int n = costs.size();
    for(int i=1; i<n; i++) {
      int red = costs[i][0], green = costs[i][1], blue = costs[i][2];

      costs[i][0] = min(green, blue) + costs[i-1][0];
      costs[i][1] = min(red, blue) + costs[i-1][1];
      costs[i][2] = min(red, green) + costs[i-1][2];
    }

    return *(min_element(costs[n-1].begin(), costs[n-1].end()));
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

  cout << minCost(costs) << " " << minCost1(costs) << endl;

  return 0;
}
