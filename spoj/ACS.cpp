#include <bits/stdc++.h>
using namespace std;

int rows[1234], cols[5678];

int main() {
  char c;

  for(int i=0; i<1234; i++)
    rows[i] = i;
  for(int j=0; j<5678; j++)
    cols[j] = j;

  int i,j;

  while(cin >> c) {
    switch(c) {
      case 'R':
      cin >> i >> j;
      swap(rows[i-1], rows[j-1]);
      break;

      case 'C':
      cin >> i >> j;
      swap(cols[i-1], cols[j-1]);
      break;

      case 'Q':
      cin >> i >> j;
      cout << rows[i-1]*5678 + cols[j-1] + 1 << endl;
      break;

      case 'W':
      cin >> i;
      int x = (i-1)/5678;
      int y = (i-1)%5678;
      for(i=0; i<1234; i++)
        if(rows[i] == x) {
          x = i+1;
          break;
        }
      for(j=0; j<5678; j++)
        if(cols[j] == y) {
          y = j+1;
          break;
        }
      cout << x << " " << y << endl;
      break;
    }
  }

  return 0;
}
