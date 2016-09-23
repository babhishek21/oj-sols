/**
 * Problem: B. Sherlock and Watson Gym Secrets (APAC 2017 Round B)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

long long fastPowMod(long long p, long long e, long long M) { // (p^e)%M
  long long ret = 1;
  while(e > 0) {
    if(e&1) ret = (ret * p) % M;
    p = (p * p) % M;
    e >>= 1;
  }
  return (long long)ret;
}

map<int, vector<int>> ma, mb;

int t, a, b, n, k, ans;

int solve() {
  cin >> a >> b >> n >> k;
  ma.clear();
  mb.clear();

  for(int i=1; i<=n; i++) {
    ma[fastPowMod(i, a, k)].pb(i);
    mb[fastPowMod(i, b, k)].pb(i);
  }

  ans = 0;
  for(auto&& ta: ma)
    for(auto&& tb: mb) {
      if((ta.first + tb.first)%k != 0) continue;
      for(auto&& a: ta.second)
        for(auto&& b: tb.second)
          if(a != b) ans = (ans+1)%MOD;
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
