/**
 * Bomb Guy (LeetCode) (https://discuss.leetcode.com/topic/10/bomb-enemy)
 * Assume 'W' == wall, 'E' == enemy
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/**
 * 1. Naive solution. O(mn(m+n)) time complexity.
 */
int maxKilledEnemiesNaive(vector<vector<char>>& grid) {
  int m = grid.size(), n = (!grid.empty()) ? grid[0].size() : 0;
  int ans = 0, hits = 0, lo, hi;

  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++) {
      if(grid[i][j] == 'W')
        continue;

      hits = (grid[i][j] == 'E') ? 1 : 0;

      // process row
      lo = j-1, hi = j+1;
      while(lo >= 0 && grid[i][lo] != 'W')
        hits += (grid[i][lo--] == 'E') ? 1 : 0;
      while(hi < n && grid[i][hi] != 'W')
        hits += (grid[i][hi++] == 'E') ? 1 : 0;

      // process col
      lo = i-1, hi = i+1;
      while(lo >= 0 && grid[lo][j] != 'W')
        hits += (grid[lo--][j] == 'E') ? 1 : 0;
      while(hi < m && grid[hi][j] != 'W')
        hits += (grid[hi++][j] == 'E') ? 1 : 0;

      ans = max(ans, hits);
    }

  return ans;
}

int main() {
  vector<vector<char>> grid = {
    {'0','E','0','0'},
    {'E','0','W','E'},
    {'0','E','0','0'}
  };

  cout << "Grid is:" << endl;
  for(auto &row: grid) {
    for(auto &cell: row)
      cout << cell << " ";
    cout << endl;
  }

  cout << "Naive Implementation: " << maxKilledEnemiesNaive(grid) << endl;

  return 0;
}
