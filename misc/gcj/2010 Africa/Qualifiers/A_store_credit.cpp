/**
 * Problem: A. Store Credit (CodeJam Qual Africa 2010)
 * Lang: C++11
 * @author: babhishek21
 */

#include <bits/stdc++.h> // using GCC
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  int n, c, p, i, arr[2000];

  cin >> n;

  for(int t=0; t<n; t++) {
    cin >> c >> i;

    for(int j=0; j<i; j++)
      cin >> arr[j];

    for(int j=0; j<i-1; j++)
      for(int k=j+1; k<i; k++) {
        if(arr[j] + arr[k] == c) {
          cout << "Case #" << t+1 << ": " << j+1 << " " << k+1 << endl;
          cerr << "Case #" << t+1 << ": " << j+1 << " " << k+1 << endl; // debug
          break;
        }
      }
  }

  return 0;
}
