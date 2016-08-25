/**
 * Problem: B. Rain (APAC 2017 Round A)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

const int dx[] = {0, 1, 0, -1}; // four cardinal directions
const int dy[] = {1, 0, -1, 0};

int t, r, c, h[60][60], w[60][60], ans;

int solve() {
  cin >> r >> c;

  for(int i=0; i<r; i++)
    for(int j=0; j<c; j++) {
      cin >> h[i][j];

      if(i == 0 || i == r-1 || j == 0 || j == c-1)
        w[i][j] = h[i][j];
      else
        w[i][j] = 10000; // infinity
    }

  bool trenchAvail = true;

  while(trenchAvail) {
    trenchAvail = false;

    for(int i=1; i<r-1; i++)
      for(int j=1; j<c-1; j++) {
        int curr = w[i][j];

        for(int k=0; k<4; k++) {
          int x = i + dx[k], y = j + dy[k];
          curr = min(curr, max(h[x][y], w[x][y]));
        }

        w[i][j] = (curr < w[i][j]) ? trenchAvail = true, curr : w[i][j];
      }
  }

  ans = 0;
  for(int i=0; i<r; i++)
    for(int j=0; j<c; j++)
      ans += (w[i][j] > h[i][j]) ? (w[i][j] - h[i][j]) : 0;

  return ans;

}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": " << solve() << endl;
  }

  return 0;
}
