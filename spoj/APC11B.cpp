// From constraints, it looks like Brute force will do
#include <bits/stdc++.h>
using namespace std;

int v1[1000], v2[1000];

int main() {
  ios::sync_with_stdio(false); // speed up I/O by desyncing streams

  int t, m1, m2, ans;

  cin >> t;

  while(t--) {
    cin >> m1;
    for (int i=0; i<m1; i++)
      cin >> v1[i];
    cin >> m2;
    for (int i=0; i<m2; i++)
      cin >> v2[i];

    ans = numeric_limits<int>::max();

    // brute force
    for(int i=0; i<m1; i++)
      for(int j=0; j<m2; j++) {
        ans = min(ans, abs(v1[i]-v2[j]));
      }

    cout << ans << endl;
  }
}
