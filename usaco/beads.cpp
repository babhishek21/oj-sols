/*
ID: babhish1
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string s;
int n;

int check_len(int i) {
  int ans = 2;

  int ls = i;
  while(s[ls] == 'w') {
    ls = (ls-1+n)%n;
    ans++;
    if(ans > n){
      ans = n;
      break;
    }
    // cout << "$ " << ans << endl;
  }
  char lcol = s[ls];

  int rs = (i+1)%n;
  while(s[rs] == 'w') {
    rs = (rs+1)%n;
    ans++;
    if(ans > n) {
      ans = n;
      break;
    }
    // cout << "& " << ans << endl;
  }
  char rcol = s[rs];

  // cout << "# " << ls << " " << lcol << " " << rs << " " << rcol << endl;

  int counter = 0;
  // forward from rcol
  int j = rs;
  while(counter < n) {
    j = (j+1)%n; counter++;
    if(s[j] == rcol || s[j] == 'w')
      ans++;
    else break;
  }

  // cout << "$$ " << ans << endl;

  counter = 0;
  // reverse from lcol
  j = ls;
  while(counter < n) {
    j = (j-1+n)%n; counter++;
    if(s[j] == lcol || s[j] == 'w')
      ans++;
    else break;
  }

  // cout << i << " " << ans << endl;
  if(ans > n)
    ans = n;

  return ans;
}

int main() {
  ofstream fout ("beads.out");
  ifstream fin ("beads.in");

  fin >> n;
  fin >> s;

  int curr_max = 0;

  for(int i=0; i<n; i++) {
    curr_max = max(curr_max, check_len(i));
  }

  fout << curr_max << endl;

  return 0;
}
