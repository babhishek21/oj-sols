#include <bits/stdc++.h>
using namespace std;

int stars[2100][2];
int dist[2100][2100];
unordered_map<int, int> mymap;

int main() {
  int t, n, x, y, xx, yy, ans;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n;

    // memset(dist, -1, sizeof(dist[0][0])*2100*2100);
    for(int i=0; i<n; i++)
      cin >> stars[i][0] >> stars[i][1];

    for(int i=0; i<n-1; i++) {
      x = stars[i][0]; y = stars[i][1];
      for(int j=i+1; j<n; j++) {
        xx = stars[j][0] - x; yy = stars[j][1] - y;
        ans = xx*xx + yy*yy;
        dist[i][j] = dist[j][i] = ans;
      }
    }

    ans = 0;
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(dist[i][j] != -1) mymap[dist[i][j]]++;
      }
      for(auto &elem: mymap) {
        ans += (elem.second * (elem.second - 1))/2;
        // cout << elem.first << " $ " << elem.second; // DEBUG
      }
      // cout << endl; // DEBUG
      mymap.clear();
    }

    cout << "Case #" << tc+1 << ": " << ans << endl;
  }

  return 0;
}
