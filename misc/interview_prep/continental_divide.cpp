/**
 * Problem: Pacific Atlantic Continental Divide (Facebook)
 * ( https://www.careercup.com/question?id=5162862051852288 )
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

// point definition
typedef pair<int, int> Point;
#define x first
#define y second
vector<Point> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

/**
 * We start search from the ocean and go inland. That is simulate the
 * reverse process of water flowing into the ocean.
 */
namespace ContinentalDivide {
  enum class Ocean {Pacific, Atlantic}; // C++11
  set<Point> pacific, atlantic;

  void dfs_search(vector<vector<int>> &mat, Point src, Ocean curr) {
    int m = mat.size(), n = (m > 0 ? mat[0].size() : 0);

    for(auto&& dir: dirs) {
      Point nxt = {src.x + dir.x, src.y + dir.y};

      if(nxt.x < 0 or nxt.y < 0 or nxt.x >= m or nxt.y >= n or mat[nxt.x][nxt.y] < mat[src.x][src.y])
        continue;

      if(curr == Ocean::Pacific) {
        if(pacific.count(nxt) > 0)
          continue;

        pacific.insert(nxt);
      } else {
        if(atlantic.count(nxt) > 0)
          continue;

        atlantic.insert(nxt);
      }

      dfs_search(mat, nxt, curr);
    }
  }

  vector<Point> flowing_water(vector<vector<int>> &mat) {
    int m = mat.size(), n = (m > 0 ? mat[0].size() : 0);

    // process pacific
    pacific.clear();

    // process pacific - left
    for(int i=0; i<m; i++) {
      pacific.insert({i, 0});
      dfs_search(mat, {i, 0}, Ocean::Pacific);
    }

    // process pacific - up
    for(int i=0; i<n; i++) {
      pacific.insert({0, i});
      dfs_search(mat, {0, i}, Ocean::Pacific);
    }

    // process atlantic
    atlantic.clear();

    // process atlantic - right
    for(int i=0; i<m; i++) {
      atlantic.insert({i, n-1});
      dfs_search(mat, {i, n-1}, Ocean::Atlantic);
    }

    // process atlantic - down
    for(int i=0; i<n; i++) {
      atlantic.insert({m-1, i});
      dfs_search(mat, {m-1, i}, Ocean::Atlantic);
    }

    // find intersection
    vector<Point> result;
    for(auto &&pt: pacific)
      if(atlantic.count(pt) > 0)
        result.push_back({pt.y, pt.x}); // because output has different convention

    return result;
  }
}

int main() {
  vector<vector<int>> mat = {
    {1, 2, 2, 3, 5},
    {3, 2, 3, 4, 4},
    {2, 4, 5, 3, 1},
    {6, 7, 1, 4, 5},
    {5, 1, 1, 2, 4}
  };

  cout << ContinentalDivide::flowing_water(mat) << endl;
  // assert [(4, 0), (3, 1), (4, 1), (2, 2), (0, 3), (1, 3), (0, 4)]

  return 0;
}
