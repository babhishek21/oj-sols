/*
ID: babhish1
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  // ************************
  // Don't mess with this
  ofstream fout ("ride.out");
  ifstream fin ("ride.in");
  // ************************

  string a, b;
  int num1 = 1, num2 = 1;

  fin >> a;
  fin >> b;

  for(auto it = a.begin(); it != a.end(); it++)
    num1 = (num1 * (*it - 'A' + 1))%47;
  for(auto it = b.begin(); it != b.end(); it++)
    num2 = (num2 * (*it - 'A' + 1))%47;

  fout << ((num1 == num2) ? "GO" : "STAY") << endl;

  // ***********************
  return 0;
}
