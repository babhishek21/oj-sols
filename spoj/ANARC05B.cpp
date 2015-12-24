/**
 * Memoized approach to this problem.
 * This took a lot of time to understand.
 * Note that the sequences are strictly increasing.
 * Still can't figure out the Greedy + BS approach yet.
 *
 * Test I/P:
 * 4 1 2 3 4
 * 3 3 7 10
 * Test O/P:
 * 23
 */

#include <bits/stdc++.h>
using namespace std;

int a[10001], b[10001];

int main() {
  int m, n;

  cin >> m;

  while(m != 0) {
    for(int i=0; i<m; i++)
      cin >> a[i];

    cin >> n;
    for(int i=0; i<n; i++)
      cin >> b[i];

    int i=0, j=0;

    while(i<m && j<n) {
      if(a[i] == b[j]) {
        a[i] += (i==0) ? 0 : a[i-1];
        b[j] += (j==0) ? 0 : b[j-1];
        a[i] = b[j] = max(a[i], b[j]);
        i++; j++;
      } else if(a[i] < b[j]) {
        a[i] += (i==0) ? 0 : a[i-1];
        i++;
      } else if(a[i] > b[j]) {
        b[j] += (j==0) ? 0 : b[j-1];
        j++;
      }
    }

    while(i<m) {
      a[i] += (i==0) ? 0 : a[i-1];
      i++;
    }

    while(j<n) {
      b[j] += (j==0) ? 0 : b[j-1];
      j++;
    }

    cout << max(a[m-1], b[n-1]) << endl;

    cin >> m;
  }

  return 0;
}
