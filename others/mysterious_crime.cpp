/**
 * Problem: D. Mysterious Crime (Codeforces Round #519 by Botan Investments)
 * http://codeforces.com/contest/1043/problem/D
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

/**
 * arr[i][] holds the permutation for the `i` th row.
 * trans[i][] holds the indexes of the permutation in the `i` th row.
 *
 * e.g. arr[i] = [3, 4, 5, 1, 2]
 * then trans[i] = [x, 3, 4, 0, 1, 2]
 *
 * Basically, trans[i][k] = j if arr[i][j] = k
 */
int n, m, arr[12][100010], trans[12][100010];

/**
 * Checks if the subarray arr[0][i...j] is a contiguous subarray in other rows as well.
 */
bool valid(int i, int j) {

  int start = arr[0][i], finish = arr[0][j];

  for(int r=1; r<m; r++)
    if(trans[r][finish] - trans[r][start] != j-i)
      return false;

  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); // for fast I/O

  cin >> n >> m;

  for(int i=0; i<m; i++)
    for(int j=0; j<n; j++) {
      cin >> arr[i][j];
      trans[i][arr[i][j]] = j;
    }

  long long ans = 0;

  for(int i=0, j=0; i<n; i++) {
    while(j<n && valid(i, j))
      j++;

    ans += j-i;
  }

  cout << ans << endl;

  return 0;
}
