/*
ID: babhish1
PROG: palsquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

#define debug(x) cout << #x << " = " << x << endl;

int base;

string getBaseRep(int i) {
  string ret;
  while(i > 0) {
    int temp = i%base;
    i /= base;

    ret += (temp >= 10 ? 'A' + temp-10 : '0' + temp);
  }

  reverse(ret.begin(), ret.end());
  return ret;
}

bool isPalin(const string &str) {
  for(size_t i = 0; i<str.length()/2; i++)
    if(str[i] != str[str.length()-1 - i])
      return false;
  return true;
}

int main() {
  ofstream fout("palsquare.out");
  ifstream fin("palsquare.in");

  fin >> base;

  for(int i=1; i<=300; i++)
    if(isPalin(getBaseRep(i*i)))
      fout << getBaseRep(i) << " " << getBaseRep(i*i) << endl;

  return 0;
}
