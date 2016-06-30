/**
 * Problem: B. gCube (APAC 2016 Round A)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int t, n, m, l, r;
double arr[1005];

void solve() {
  cin >> n >> m;

  for(int i=0; i<n; i++) {
    cin >> arr[i];
    arr[i] = log10(arr[i]);
    arr[i] += (i > 0 ? arr[i-1] : 0);
  }

  while(m--) {
    cin >> l >> r;

    double val = arr[r] - (l > 0 ? arr[l-1] : 0);
    double root = (r-l+1);

    // cout << val << " " << root << endl; // debug

    cout << fixed << setprecision(9) << pow(10, val/root) << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ":" << endl;
    solve();
  }

  return 0;
}
