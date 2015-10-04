/*
ID: babhish1
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  // ************************
  // Don't mess with this
  ofstream fout ("gift1.out");
  ifstream fin ("gift1.in");
  // ************************

  int np, moni, nom;
  string name;
  unordered_map<string, int> mymap;
  vector<string> myvec;

  fin >> np;
  for (int i=0; i<np; i++) {
    fin >> name;
    mymap[name] = 0;
    myvec.push_back(name);
  }

  for(int i=0; i<np; i++) {
    fin >> name;
    fin >> moni >> nom;

    mymap[name] += (nom != 0) ? moni%nom : moni;

    while(nom--) {
      fin >> name;
      mymap[name] += moni/nom;
    }
  }

  for(auto it = myvec.begin(); it != myvec.end(); ++it) {
    fout << *it << " " << mymap[*it] << endl;
  }

  // ***********************
  return 0;
}
