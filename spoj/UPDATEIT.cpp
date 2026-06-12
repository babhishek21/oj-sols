#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int main() {
  long arr[16384];

  int t, n, u, l, r;
  long x;

  cin >> t;

  while(t--) {
    cin >> n >> u;

    memset(arr, 0L, sizeof(arr[0])*n);

    while(u--) {
      cin >> l >> r >> x;

      arr[l] += x;
      arr[r+1] -= x;
    }

    for(int i=1; i<n; i++)
      arr[i] += arr[i-1];

    cin >> u;

    while(u--) {
      cin >> x;
      cout << arr[x] << '\n';
    }
  }

  return 0;
}
