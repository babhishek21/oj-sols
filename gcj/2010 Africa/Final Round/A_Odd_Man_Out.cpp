/**
 * Problem: A_Odd_Man_Out (Codejam Finals Africa 2010)
 * Lang: C++11
 * @author: babhishek21/quirk
 */

#include <bits/stdc++.h> // using GCC
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  int n, g, num;
  set<int> s;

  cin >> n;

  for(int t=0; t<n; t++) {
    cin >> g;

    while(g--) {
      cin >> num;
      auto it = s.find(num);

      if(it != s.end())
        s.erase(it);
      else
        s.insert(num);
    }

    if(s.size() != 1) {
      cout << "Error. set size not 1." << endl;
      for(auto x: s)
        cout << x << " ";
      cout << endl;
    }
    else
      cout << "Case #" << t+1 << ": " << *(s.begin()) << endl;

    s.clear();
  }

  return 0;
}
