/* Tight time constraints. Use C/C++ */
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false); // speed up I/O by desyncing streams

  int t, n;
  long long ans;

  cin >> t;

  while(t--) {
    cin >> n;
    int m = sqrt(n);
    ans = 0;

    if(n == 1)
      cout << ans << endl;
    else {
      for(int i=2; i<=m; i++) {
        if(n%i == 0)
          if(i == n/i) ans += i;
          else ans += i + n/i;
      }
      cout << ++ans << endl;
    }
  }

  return 0;
}
