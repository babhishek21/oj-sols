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

long long ma[100000], mb[100000];

int t;
long long a, b, n, k, ans, fact, eq, ai, bi;

long long solve() {
  cin >> a >> b >> n >> k;

  for(int i=0; i<=k; i++)
    ma[i] = mb[i] = 0;

  fact = (n/k)%MOD;
  eq = 0;
  for(int i=0; i<k; i++) {
    ai = fastPowMod(i, a, k)%k;
    bi = fastPowMod(i, b, k)%k;
    ma[ai]++;
    mb[bi]++;

    if((ai + bi)%k == 0) eq++;
  }

  for(int i=0; i<k; i++) {
    ma[i] = (ma[i] * fact)%MOD;
    mb[i] = (mb[i] * fact)%MOD;
  }
  eq = (eq * fact)%MOD;

  for(int i=1; i<=n%k; i++) {
    ai = fastPowMod(i, a, k)%k;
    bi = fastPowMod(i, b, k)%k;
    ma[ai] = (ma[ai]+1)%MOD;
    mb[bi] = (mb[bi]+1)%MOD;

    if((ai + bi)%k == 0) eq = (eq+1)%MOD;
  }

  ans = (ma[0]*mb[0])%MOD;
  for(int i=1; i<k; i++)
    ans = (ans + (ma[i] * mb[k-i])%MOD)%MOD;

  ans = (ans - eq + MOD)%MOD;

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
