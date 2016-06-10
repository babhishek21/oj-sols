#include <bits/stdc++.h>
using namespace std;

char grid[2010][2];

/**
 * O(n) greedy
 * Case-1: X.X  =>  XGX or XXX
 *         X.X      XXX    XGX
 * Case-2: X.X  =>  XGX
 *          X   =>   X
 * Case-3: Mirror of Case-2
 */

int main() {
  int t, n, ans;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n;

    grid[0][0] = grid[1][0] = 'X';
    grid[n+1][0] = grid[n+1][1] = 'X';

    for(int i=1; i<=n; i++)
      cin >> grid[i][0];
    for(int i=0; i<n; i++)
      cin >> grid[i][1];

    ans = 0;
    for(int i=1; i<=n; i++) {
      if(grid[i][0] == '.' and grid[i-1][0] == 'X' and grid[i+1][0] == 'X') {
        if(grid[i][1] == '.' and grid[i-1][1] == 'X' and grid[i+1][1] == 'X') {
          grid[i][0] = grid[i][1] = 'X';
        } else if(grid[i][1] == 'X') {
          grid[i][0] = 'X';
        }
        ans++;
      } else if(grid[i][1] == '.' and grid[i-1][1] == 'X' and grid[i+1][1] == 'X' and grid[i][0] == 'X') {
        grid[i][1] = 'X';
        ans++;
      }
    }

    // DEBUG
    for(int i=1; i<=n; i++)
      cout << grid[i][0];
    cout << endl;
    for(int i=0; i<n; i++)
      cout << grid[i][1];
    cout << endl;

    for(int j=0; j<2; j++) {
      int counter = 0;
      bool done = false;

      for(int i=1; i<=n; i++) {
        if(grid[i][j] == 'X') {
          if(counter > 1) ans++;
          counter = 0;
          done = false;
        } else {
          counter++;
          if(grid[i][1-j] == '.' and grid[i+1][1-j] == 'X' and grid[i-1][1-j] == 'X') {
            if(!done) done = true;
            else ans++;
          }
        }
      }
    }

    cout << "Case #" << tc+1 << ": " << ans << endl;
  }

  return 0;
}
