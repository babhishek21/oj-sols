/**
 * Problem: Advent of Code 2025 - Day 4: Printing Department
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

#define pb push_back
#define eb emplace_back

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

/* Direction Arrays */
const int di[] = {1, -1, 0, 0, 1, -1, 1, -1}; // vector directions
const int dj[] = {0, 0, 1, -1, 1, -1, -1, 1};

bool is_removable(const vector<vector<bool>>& padded_grid, int i, int j) {
  int cnt = 0;

  for(int k=0; k<8; k++)
    cnt += padded_grid[i+di[k]][j+dj[k]];

  return cnt < 4;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int ans1 = -1, ans2 = 0, m, n; // assume rectangular grid
  vector<vector<bool>> grid;
  vector<bool> grid_line;
  vector<string> lines;
  string line;

  while(getline(cin, line))
    lines.pb(line);

  m = lines[0].length();
  n = lines.size();

  // build grid
  grid = vector<vector<bool>>(n+2, vector<bool>(m+2));
  for(int i=0; i<m; i++) {
    whole(transform, lines[i], next(grid[i+1].begin()), [](const char ch) -> bool {
      return ch == '@';
    });
  }

  // debug(grid)

  // remove eligible rolls until we can't remove anymore
  int curr = 1;
  vector<pair<int, int>> to_remove;

  while(curr > 0) {
    curr = 0;
    to_remove.clear();

    for(int i=1; i<=m; i++)
      for(int j=1; j<=n; j++)
        if(grid[i][j] && is_removable(grid, i, j)) {
          to_remove.eb(i, j);
          curr++;
        }

    for(const auto& pt: to_remove)
      grid[pt.first][pt.second] = false;

    debug(curr)

    if(ans1 == -1)
      ans1 = curr;

    ans2 += curr;
  }

  cout << "answers: " << ans1 << " " << ans2 << endl;

  return 0;
}
