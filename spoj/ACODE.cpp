#include <bits/stdc++.h>
using namespace std;

int dp[5001]; // dp[i] = no. of combos ending with s[i]
string s;

int isvalid(int i) {
  int a = s[i-1] - '0'; // number is ab
  int b = s[i] - '0';

  if(a == 0) {
    return 0; // number of the form 0b
  } else {
    int c = a*10 + b;
    if(c <= 26 and c >= 1) {
      if(b == 0) return 1; // number of the form a0
      else return 2; // number of the form ab
    } else if(b != 0) return 0; // ab is invalid. 0b must be used
  }

  return -1; // invalid. This never occurs.
}

int main() {
  cin >> s;
  do {
    // reset
    memset(dp, 0, sizeof(dp));
    // base cases
    dp[0] = 1; // s[0] always valid
    int valid = isvalid(1);
    // cout << valid << " 1" << endl; // debug
    dp[1] += ((valid == 2) ? dp[0] + 1 : 0)
          + ((valid == 1) ? dp[0] : 0)
          + ((valid == 0) ? 1 : 0);

    // the real shiz
    for(int i=2; i<s.size(); i++) {
      valid = isvalid(i);
      // cout << valid  << " " << i << endl; // debug
      dp[i] += ((valid == 2) ? dp[i-2] + dp[i-1] : 0)
            + ((valid == 1) ? dp[i-2] : 0)
            + ((valid == 0) ? dp[i-1] : 0);
    }

    // the answer
    cout << dp[s.size()-1] << endl;

    cin >> s;
  } while(s != "0");
  return 0;
}
