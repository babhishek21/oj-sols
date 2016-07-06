/**
 * Problem: A. Cube IV (APAC 2015 Round D)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, s;
unordered_map<int, vector<int>> g;
vector<vector<int>> m;

inline void dump() {
  cout << "graph:" << endl;
  for(auto &tup: g) {
    cout << tup.first << ": ";
    for(auto &val: tup.second)
      cout << val << " ";
    cout << endl;
  }
}

long long dfs(int u) {
  // debug(u) debug(count)

  long long ans = 0LL;
  for(auto &v: g[u])
    ans = max(ans, dfs(v));
  return 1 + ans;
}

void solve() {
  cin >> s;

  m.resize(s, vector<int>(s));

  for(int i=0; i<s; i++)
    for(int j=0; j<s; j++)
      cin >> m[i][j];

  for(int i=0; i<s; i++)
    for(int j=0; j<s; j++) {
      if(i>0 && m[i-1][j] - m[i][j] == 1)
        g[m[i][j]].pb(m[i-1][j]);
      if(i<s-1 && m[i+1][j] - m[i][j] == 1)
        g[m[i][j]].pb(m[i+1][j]);
      if(j>0 && m[i][j-1] - m[i][j] == 1)
        g[m[i][j]].pb(m[i][j-1]);
      if(j<s-1 && m[i][j+1] - m[i][j] == 1)
        g[m[i][j]].pb(m[i][j+1]);
    }

  // dump(); //debug

  long long ans = 0, temp;
  int winner;
  for(int i=0; i<s*s; i++) {
    temp = dfs(i+1);
    if(temp > ans) {
      ans = temp;
      winner = i+1;
    }
  }

  cout << winner << " " << ans << endl;

  m.clear();
  g.clear();
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
