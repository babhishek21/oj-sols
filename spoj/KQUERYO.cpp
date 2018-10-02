/**
 * Problem: KQUERYO (SPOJ)
 * This solution used sqrt-decomposition. Strict TLE, so use C-style fast I/O.
 * Author: babhishek21
 * Lang: C++14
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

int arr[100010];
vector<int> sqarr[320];
int sq;

int query(int l, int r, int k) {
  if(r < l)
    return 0;

  int ll = l/sq, rr = r/sq, ans = 0;

  if(ll == rr) {
    for(int i=l; i<=r; i++)
      ans += (arr[i] > k);

  } else {
      ans += query(l, (ll+1)*sq - 1, k);
      ans += query(rr*sq, r, k);

      for(int i=ll+1; i<rr; i++)
        ans += distance(whole(upper_bound, sqarr[i], k), sqarr[i].end());
  }

  return ans;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, q, ans, a, b, c, ii, jj, kk;

  scanf("%d", &n);
  sq = sqrt(n);

  for(int i=0; i<n; i++) {
    scanf("%d", arr+i);
    sqarr[i / sq].pb(arr[i]);
  }

  for(int i=0; i<= n/sq; i++)
    whole(sort, sqarr[i]);

  scanf("%d", &q);

  ans = 0;
  while(q--) {
    scanf("%d %d %d", &a, &b ,&c);

    ii = a ^ ans;
    jj = b ^ ans;
    kk = c ^ ans;

    ii = max(1, ii);
    jj = min(jj, n);

    ii--, jj--;

    ans = query(ii, jj, kk);

    printf("%d\n", ans);
  }

  return 0;
}
