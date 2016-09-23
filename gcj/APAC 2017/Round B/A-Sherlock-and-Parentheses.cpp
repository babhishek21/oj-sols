/**
 * Problem: A. Sherlock and Parentheses (APAC 2017 Round B)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

long long t, l, r;

long long solve() {
  cin >> l >> r;

  l = min(l, r);

  return (l * (l+1))/2;
}


int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": " << solve() << endl;
  }

  return 0;
}
