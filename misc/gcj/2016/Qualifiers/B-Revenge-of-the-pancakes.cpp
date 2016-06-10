#include <bits/stdc++.h>
using namespace std;

int arr[10];

bool allset(string s) {
  for(auto x: s) {
    if(x != '+')
      return false;
  }

  return true;
}

int prefix(string s) {
  for(int i=1; i<s.size(); i++) {
    if(s[i] != s[0]) return i-1;
  }
  return s.size()-1;
}

string invertreverse(string s, int prefix) {
  for(int i=0; i<=prefix; i++) {
    s[i] = (s[i] == '+') ? '-' : '+';
  }
  reverse(s.begin(), s.begin()+prefix+1);
  return s;
}

int main() {
  int t;
  string s;

  cin >> t;

  for(int i=0; i<t; i++){
    cin >> s;

    int ans = 0;
    while(!allset(s)) {
      // find largest same sign prefix
      int pref = prefix(s);
      // invert stuff
      s = invertreverse(s, pref);
      // inc ans
      ans++;
    }

    cout << "Case #" << i+1 << ": " << ans << endl;
  }

  return 0;
}
