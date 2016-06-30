/**
 * Problem: A. Lazy Spelling Bee (APAC 2017 Practice Round)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007

long long solve(string s) {
  long long ans = 1LL;
  int len = s.size();

  if(len == 1)
    return ans;

  for(int i=0; i<len; i++) {
    if(i == 0) {
      if(s[i] != s[i+1])
        ans *= 2LL;
    } else if(i == len-1) {
      if(s[i] != s[i-1])
        ans = (ans * 2LL)%MOD;
    } else {
      if(s[i] != s[i-1] && s[i] != s[i+1] && s[i+1] != s[i-1])
        ans = (ans * 3LL)%MOD;
      else if(s[i] == s[i-1] && s[i] == s[i+1])
        continue;
      else
        ans = (ans * 2LL)%MOD;
    }
  }

  return ans%MOD;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  string s;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> s;

    cout << "Case #" << tc+1 << ": " << solve(s) << endl;
  }

  return 0;
}
