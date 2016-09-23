/**
 * Problem: C. Watson and Intervals (APAC 2017 Round B)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp"
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define debug(x) cout << #x << " : " << x << endl;
#define stpp stack<pair<long long, long long>>

int t;
long long n, l, r, a, b, c1, c2, m, x, y, temp, ans;
vector<pair<long long, long long>> vv;
stpp st;

long long solve() {
  cin >> n >> l >> r >> a >> b >> c1 >> c2 >> m;
  vv.clear();
  ans = numeric_limits<long long>::max();

  // generate intervals
  // a %= m;
  // b %= m;

  vv.eb(l, r);
  for(int i=2; i<=n; i++) {
    x = l;
    y = r;
    l = (a * x + b * y + c1) % m;
    r = (a * y + b * x + c2) % m;

    vv.eb(min(l, r), max(l, r));
  }

  sort(vv.begin(), vv.end());

  // debug(vv); // debug

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if (i == j)
        continue;
      else if (st.empty() || st.top().second < vv[j].first)
        st.push(vv[j]);
      else {
        l = st.top().first, r = max(st.top().second, vv[j].second);
        st.pop();
        st.emplace(l, r);
      }
    }

    temp = 0;
    while(!st.empty()) {
      temp += (st.top().second - st.top().first + 1);
      st.pop();
    }

    ans = min(ans, temp);
  }

  return ans;
}


int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": " << solve() << endl;
  }

  return 0;
}
