#include <bits/stdc++.h>
using namespace std;

int main() {
  int c;
  string s, t;
  scanf("%d", &c);

  for(int l=0; l<c; l++) {
    cin >> s;
    cin >> t;

    int ans = 0;
    int wc1 = 0, wc2 = 0; // count of mismatch wc1: S[0]T[1] and wc2: S[1]T[0]
    int oc1 = 0, oc2 = 0;
    for(int i=0; i<s.size(); i++) { // fix '?'
      if(s[i] == '?') ans++;
      else if(s[i] != t[i]) s[i] == '0' ? wc1++ : wc2++;
      if(s[i] == '1') oc1++;
      if(t[i] == '1') oc2++;
    }
    // cout << ans << " " << wc1 << " " << wc2 << endl; //Debug
    if(oc1 > oc2) {
      printf("Case %d: -1\n", l+1);
      continue;
    }
    // wc1 >= wc2. We make wc2 swaps. wc1-wc2 discrepancies left
    ans += max(wc1, wc2);

    printf("Case %d: %d\n", l+1, ans);
  }

  return 0;
}
