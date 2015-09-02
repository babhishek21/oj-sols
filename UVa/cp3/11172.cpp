#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  int a, b;
  char c;

  scanf("%d", &t);

  while(t--) {
    scanf("%d %d", &a, &b);

    printf("%c\n", c = ((a==b) ? '=' : ((a > b) ? '>' : '<')));
  }
  return 0;
}
