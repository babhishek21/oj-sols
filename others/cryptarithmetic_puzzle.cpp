/**
 * Problem: Cryptarithmetic Puzzle (Only for addition)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

/**
 * Cryptarithmetic Puzzle
 *
 * For example:
 *
 *   SEND
 * + MORE
 * -------
 *  MONEY
 *
 * The problem (simpler version) is to assign a digit to
 * each letter, so that the expression is valid. A valid
 * solution is known to exist for the above expression.
 */

vector<string> arr(3); // store the operands and result
map<char, int> mp; // associate a digit to a char
set<int> use; // check if digit is blocked
vector<char> vc; // list of chars

// check if possible solution
bool check_sol() {
  vector<int> ans(3, 0);
  int i = 0;

  for(auto&& str: arr) {
    for(auto&& ch: str) {
      ans[i] *= 10;
      ans[i] += mp[ch];
    }
    i++;
  }

  return ((ans[0] + ans[1]) == ans[2]);
}

// permute all options
void permute(int idx) {
  if(idx == vc.size()) {
    if(check_sol()) {
      // solution found!
      cout << "A valid solution found:" << endl;
      cout << mp << endl;
    }
    return;
  }

  for(int i=0; i<10; i++) {
    if(use.count(i) <= 0) {
      use.insert(i);
      mp[vc[idx]] = i;

      permute(idx+1);

      use.erase(i);
    }
  }
}

// prelim checks
void prelim_check() {
  for(auto&& str: arr)
    for(auto&& ch: str) {
      if(mp.count(ch) <= 0)
        vc.push_back(ch);
      mp[ch] = 0;
    }
}

// solve puzzle
void solve_crypt_puzzle() {
  mp.clear();
  vc.clear();
  use.clear();

  prelim_check();

  if(vc.size() > 10) {
    cout << "A valid solution is not possible for this puzzle!" << endl;
    return;
  }

  permute(0);
}

int main() {

  cout << "Enter three strings: (for augend, addend and sum)" << endl;
  cin >> arr[0];
  cin >> arr[1];
  cin >> arr[2];

  cout << "Trying to solve expression:" << endl
      << "\t\t" << arr[0] << endl
      << "\t    +   " << arr[1] << endl
      << "\t  -------------------" << endl
      << "\t\t" << arr[2] << endl;

  solve_crypt_puzzle();

  return 0;
}
