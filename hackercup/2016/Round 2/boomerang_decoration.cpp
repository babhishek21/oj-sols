/**
 * Problem: Boomerang Decoration (FB HackerCup 2016 Round 2)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define INF 1e9
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, n, maxcost;
string lefts, rights;
int pref[100010], suff[100010];

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n;

    cin >> lefts;
    cin >> rights; // need to transform `lefts` to `rights`

    // cost of painting a prefix or suffix on `lefts` to match `rights` once the optimal order of painting `lefts` is decided
    pref[1] = 1;
    for(int i=2; i<=n; i++)
      pref[i] = pref[i-1] + (rights[i-1] != rights[i-2] ? 1 : 0);

    suff[n] = 1;
    for(int i=n-1; i>0; i--)
      suff[i] = suff[i+1] + (rights[i-1] != rights[i] ? 1 : 0);

    // debug
    // debug(pretty_print_array(pref+1, n))
    // debug(pretty_print_array(suff+1, n))

    // determine optimal painting order
    maxcost = INF;
    for(int i=0; i<=n; i++) { // choose a x for pref[x]
      int l = i, r = i+1;

      // find first discrepancy in either prefix or suffix
      while(l > 0 && lefts[l-1] == rights[l-1]) l--;
      while(r <= n && lefts[r-1] == rights[r-1]) r++;

      maxcost = min(maxcost, max(
        l > 0 ? pref[l] : 0,
        r <= n ? suff[r] : 0
      ));
    }

    cout << "Case #" << tc+1 << ": " << maxcost << endl;
  }

  return 0;
}
