/**
 * Problem: B. Rank and File (Codejam Round 1A 2016)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, n, temp;
unordered_map<int, int> cnt;

string solve() {
  cnt.clear();
  ostringstream out;
  vector<int> outv;

  cin >> n;

  for(int i=0; i<2*n-1; i++)
    for(int j=0; j<n; j++) {
      cin >> temp;
      cnt[temp]++;
    }

  for(auto&& tup: cnt) {
    if(tup.second%2 != 0)
      outv.push_back(tup.first);
  }

  sort(outv.begin(), outv.end());

  for(auto&& v: outv)
    out << v << " ";

  return out.str();
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++)
    cout << "Case #" << tc+1 << ": " << solve() << endl;

  return 0;
}
