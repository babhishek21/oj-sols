#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  int t, n, m, x, y;

  while(cin >> t, (t != 0)) {
    cin >> n >> m;

    while(t--) {
      cin >> x >> y;

      if(x == n or y == m)
        cout << "divisa" << endl;

      else if(x > n and y > m)
        cout << "NE" << endl;
      else if(x > n and y < m)
        cout << "SE" << endl;
      else if(x < n and y > m)
        cout << "NO" << endl;
      else if(x < n and y < m)
        cout << "SO" << endl;
    }
  }

  return 0;
}
