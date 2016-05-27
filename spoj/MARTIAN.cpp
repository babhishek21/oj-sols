/**
 * Problem: MARTIAN (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h>
using namespace std;

int yeye[510][510], blog[510][510];

int main() {
  int n,m; // rows, cols

  cin >> n >> m;

  while((n != 0) and (m != 0)) {
    for(int i=0; i<n; i++)
      for(int j=0; j<m; j++)
        cin >> yeye[i][j];

    for(int i=0; i<n; i++)
      for(int j=0; j<m; j++)
        cin >> blog[i][j];

    for(int i=0; i<n; i++)
      for(int j=0; j<m; j++) {

      }

    cin >> n >> m;
  }


  return 0;
}
