/**
 * Problem: Devaseva (https://www.codechef.com/problems/AMR15B)
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

/* Number Theory Utils */
template <class T> inline T fastPowMod(T p, T e, T M) { // (p^e)%M
  long long ret = 1;
  while(e > 0) {
    if(e&1) ret = (ret * p) % M;
    p = (p * p) % M;
    e >>= 1;
  }
  return (T)ret;
}

template <class T> inline T fixMod(T x, T M) { return ((x % M) + M) % M; }
template <class T> inline T modInverse(T a, T M) { return fastPowMod(a,M-2,M); }
template <class T> inline T gcd(T a, T b) { if(b == 0) return a; return gcd(b,a%b); }
template <class T> inline T lcm(T a, T b) { a = abs(a); b = abs(b); return (a/gcd(a,b))*b; }

#define MAXN 100010
int t, n, arr[MAXN], maxnum;
long long subs[MAXN], freq[MAXN], ans;

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  while(t--) {
    cin >> n;

    fill_n(freq, sizeof freq / sizeof freq[0], 0);
    fill_n(subs, sizeof subs / sizeof subs[0], 0);
    maxnum = 0;
    ans = 1;

    for(int i=0; i<n; i++) {
      cin >> arr[i];
      freq[arr[i]]++;
      maxnum = max(arr[i], maxnum);
    }

    for(int i=maxnum; i>0; i--) {
      long long totalSubs = freq[i], invalidSubs = 0;

      for(int j=2; i*j <= maxnum; j++) { // for all multiples of i, i.e. 2*i, 3*i, 4*i
        totalSubs += freq[i*j];
        invalidSubs = (invalidSubs + subs[i*j]) % (MOD-1); // by Fermat's Little Thoerem
      }

      long long validSubs = fixMod<long long>(fastPowMod<long long>(2, totalSubs, MOD-1) - 1 - invalidSubs, MOD-1); // by Fermat's Little Thoerem
      ans = (ans * fastPowMod<long long>(i, validSubs, MOD)) % MOD;

      subs[i] = validSubs;
    }

    cout << ans << endl;
  }

  return 0;
}
