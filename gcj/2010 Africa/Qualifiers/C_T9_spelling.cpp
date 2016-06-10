/**
 * Problem: C_T9_spelling (CodeJam Qual Africa 2010)
 * Lang: C++11
 * @author: babhishek21/quirk
 */

#include <bits/stdc++.h> // using GCC
using namespace std;

int arr[26][2];

void build_t9() {
  int j = 2;
  for(int i=0; i<26; j++) {
    arr[i][1] = j;
    arr[i++][0] = j;
    arr[i][1] = j;
    arr[i++][0] = 11*j;
    arr[i][1] = j;
    arr[i++][0] = 111*j;

    if(j == 7 || j == 9) {
      arr[i][1] = j;
      arr[i++][0] = 1111*j;
    }
  }

  // debug
  // for(int i=0; i<26; i++)
  //   cout << arr[i] << " ";
  // cout << endl;
}

int main() {
  int n;
  string s;

  build_t9();

  cin >> n;
  getline(cin, s);

  for(int t=0; t<n; t++) {
    getline(cin, s);
    cout << "Case #" << t+1 << ": ";

    int prev = 1;
    for(int i=0; i<s.size(); i++) {
      if(s[i] == ' '){
        if(prev == 0)
          cout << " ";
        cout << 0;
        prev = 0;
      }
      else {
        if(arr[s[i] - 'a'][1] == prev)
          cout << " ";
        cout << arr[s[i] -'a'][0];
        prev = arr[s[i] - 'a'][1];
      }
    }
    cout << endl;
  }

  return 0;
}
