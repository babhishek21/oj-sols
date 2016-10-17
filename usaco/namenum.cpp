/*
ID: babhish1
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define debug(x) cout << #x << " = " << x << endl;

string serialize(const string &str) {
  string ret;
  for(auto&& ch: str) {
    if(ch == 'Q' || ch == 'Z')
      return "1";
    else if(ch < 'Q')
      ret += (ch - 'A')/3 + '2';
    else
      ret += (ch - 'Q')/3 + '7';
  }
  return ret;
}

int main() {
  ofstream fout("namenum.out");
  ifstream fin("namenum.in"), fdict("namenumdict.txt");

  string serial, candidate;
  bool nil = true;

  fin >> serial;

  while(fdict >> candidate) {
    if(candidate.length() == serial.length() && serialize(candidate) == serial) {
      nil = false;
      fout << candidate << endl;
    }
  }

  if(nil)
    fout << "NONE" << endl;

  return 0;
}
