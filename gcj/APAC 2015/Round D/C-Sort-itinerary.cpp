/**
 * Problem: C. Sort a scrambled itinerary (APAC 2015 Round D)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, n;
string src, dest;
map<string, string> iten;
set<string> dest_list;

void solve() {
  cin >> n;

  for(int i=0; i<n; i++) {
    cin >> src >> dest;
    iten[src] = dest;
    dest_list.insert(dest);
  }

  // find first src
  for(auto &tup: iten) {
    if(dest_list.find(tup.first) == dest_list.end()) {
      src = tup.first;
      break;
    }
  }

  while(n--) {
    dest = iten[src];
    cout << src << "-" << dest << " ";
    src = dest;
  }
  cout << endl;


  iten.clear();
  dest_list.clear();
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": ";
    solve();
  }

  return 0;
}
