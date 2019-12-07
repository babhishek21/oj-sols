/**
 * Bomb Enemy (LeetCode) (https://leetcode.com/problems/bomb-enemy)
 * Assume 'W' == wall, 'E' == enemy
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

// #define DEBUG

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

/**
 * 2. DP Solution. O(mn) run time with O(mn) extra space.
 */
int maxKilledEnemiesDP(vector<vector<char>>& grid) {
  int ans = 0, m = grid.size(), n = (!grid.empty()) ? grid[0].size() : 0;
  vector<vector<int>> dpRow(m, vector<int>(n, 0)), dpCol(m, vector<int>(n, 0));

  // process from top left to bottom right
  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++) {
      if(grid[i][j] == 'E') {
        dpRow[i][j] = 1 + (i > 0 ? dpRow[i-1][j] : 0);
        dpCol[i][j] = 1 + (j > 0 ? dpCol[i][j-1] : 0);
      } else if(grid[i][j] == '0') {
        dpRow[i][j] = (i > 0 ? dpRow[i-1][j] : 0);
        dpCol[i][j] = (j > 0 ? dpCol[i][j-1] : 0);
      } else {
        dpRow[i][j] = 0;
        dpCol[i][j] = 0;
      }
    }

  #ifdef DEBUG

  cout << endl << "DP processing:" << endl << "After top left to bottom right processing:" << endl;

  cout << "dpRow:" << endl;
  for(auto &row: dpRow) {
    for(auto &cell: row)
      cout << cell << " ";
    cout << endl;
  }

  cout << "dpCol:" << endl;
  for(auto &row: dpCol) {
    for(auto &cell: row)
      cout << cell << " ";
    cout << endl;
  }

  #endif

  // process from bottom right to top left
  for(int i=m-1; i>=0; i--)
    for(int j=n-1; j>=0; j--) {
      if(grid[i][j] == '0' || grid[i][j] == 'E') {
        dpRow[i][j] = max(dpRow[i][j], (i < m-1 ? dpRow[i+1][j] : 0));
        dpCol[i][j] = max(dpCol[i][j], (j < n-1 ? dpCol[i][j+1] : 0));
      } else if(grid[i][j] == 'W') {
        dpRow[i][j] = 0;
        dpCol[i][j] = 0;
      }
    }

  #ifdef DEBUG

  cout << "After bottom right to top left processing:" << endl;

  cout << "dpRow:" << endl;
  for(auto &row: dpRow) {
    for(auto &cell: row)
      cout << cell << " ";
    cout << endl;
  }

  cout << "dpCol:" << endl;
  for(auto &row: dpCol) {
    for(auto &cell: row)
      cout << cell << " ";
    cout << endl;
  }

  #endif

  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
      ans = max(ans, (grid[i][j] != 'W' ? dpRow[i][j] + dpCol[i][j] + (grid[i][j] == 'E' ? -1 : 0) : 0));

  return ans;
}

/**
 * 3. Counting Streaks efficiently. O(mn) runtime with O(n) extra space.
 */


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
  cout << endl;

  cout << "Naive Implementation: " << maxKilledEnemiesNaive(grid) << endl; // 3
  cout << "DP Implementation: " << maxKilledEnemiesDP(grid) << endl;

  grid[1][1] = 'E';

  cout << endl << "Grid is now:" << endl;
  for(auto &row: grid) {
    for(auto &cell: row)
      cout << cell << " ";
    cout << endl;
  }
  cout << endl;

  cout << "Naive Implementation: " << maxKilledEnemiesNaive(grid) << endl; // 4
  cout << "DP Implementation: " << maxKilledEnemiesDP(grid) << endl;

  return 0;
}
