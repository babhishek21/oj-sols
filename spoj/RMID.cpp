/**
 * Problem: RMID (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  list<int> li;
  list<int>::iterator it = li.begin(), temp = it;
  int num, cnt = 0;

  while(cin >> num) {
    if(num == 0) {
      li.clear();
      it = li.begin();
      cnt = 0;

      cout << "\n";
    }

    else if(num == -1) {
      cout << *it << "\n";

      temp = it;

      if(cnt&1)
        it--;
      else
        it++;

      li.erase(temp);
      cnt--;
    }

    else {
      cnt++;
      li.push_back(num);

      if(cnt&1) it++;
    }

    // cout << "$: " << li << endl; // debug
    // cout << "$$: " << *it << endl; // debug
  }

  return 0;
}
