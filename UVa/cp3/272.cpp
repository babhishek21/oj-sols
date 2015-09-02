#include <bits/stdc++.h>
using namespace std;

int main() {
  char c;
  int k = -1;

  while((c = getchar()) != EOF) {
    if(c == '`') {
      k++;
      if(k == 1) printf("\"\"");
    } else if(c == '\'') {
      k--;
      if(k == -1) printf("\"\"");
    } else
      putchar(c);
  }

  return 0;
}
