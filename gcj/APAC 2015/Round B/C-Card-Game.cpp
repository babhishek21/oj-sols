/**
 * Problem: C. Card Game (APAC 2015 Round B)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, n, k, arr[200], dp[200][200];
unordered_map<int, vector<int>> store;

int best(int lo, int hi) {
  if(hi-lo+1 < 3) return hi-lo+1;

  // check for memoized value
  if(dp[lo][hi] != -1)
    return dp[lo][hi];

  // case 1
  int ans = 1 + best(lo+1, hi);

  // case 2
  if(store.count(arr[lo]+k) > 0 && store.count(arr[lo]+k+k) > 0) {
    for(auto &i: store[arr[lo]+k])
      for(auto &j: store[arr[lo]+k+k]) {
        if((lo < i && i < j && j <= hi) && (best(lo+1, i-1) == 0 && best(i+1, j-1) == 0))
          ans = min(ans, best(j+1, hi));
      }
  }

  dp[lo][hi] = ans;
  return ans;
}

int solve() {
  cin >> n >> k;

  store.clear();
  fill_n(*dp, sizeof dp / sizeof **dp, -1);

  for(int i=0; i<n; i++) {
    cin >> arr[i];
    store[arr[i]].pb(i);
  }

  return best(0, n-1);
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++)
    cout << "Case #" << tc+1 << ": " << solve() << endl;

  return 0;
}

/**
 * Explanation of DP solution: http://qr.ae/1uxiBo
 *
 * best(i, j) is the smallest length left of the subarray arr[i..j] (both inclusive) after
 * all removal operations are done.
 *
 * best(i, j) = j-i+1 (for j-i+1 < 3) (as no removals are possible for 2 or less elements)
 *
 * For j-i > 1 (i.e 3 or more elemnts), optimally we can either remove a card arr[i] or not.
 * Thus there are two cases:
 * 1. arr[i] is not removed. Thus best(i, j) = 1 + best(i+1, j)
 * 2. arr[i] is also removed. This is only possible if a triplet (i,l,m) can be found such that:
 *
 *            i < l < m <= j AND arr[l] - arr[i] = arr[m] - arr[l] = K
 *
 *    This is possible only if arr[i+1...l-1] can be fully removed (or is empty) and arr[l+1...m-1]
 *    can be fully removed (or is empty). Hence among the above found triplets, only the ones satisfying:
 *
 *                       best(i+1, l-1) = 0 AND best(l+1, m-1) = 0
 *
 *    can give removable positions. Hence if we remove arr[i], we are effectively leaving arr[m+1..j]
 *    to be processed further. Hence best(i,j) = min(best(m+1, j)) over all such triplets (i,l,m).
 *
 * Finally answer best(i,j) is the minimum of Case 1 and 2. Memoize it to convert plain recusion to DP.
 */
