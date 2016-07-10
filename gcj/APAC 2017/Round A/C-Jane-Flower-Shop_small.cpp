/**
 * Problem: C. Jane's Flower Shop (APAC 2017 Round A)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, m;
vector<int> c;

bool almost_equal(double x, double y = 0) {
  double eps = 1e-9;

  if(x-y >= -eps && x-y <= eps)
    return true;

  return false;
}

double proc(double r) {
  double k = 1.0, ans = 0.0;

  for(int i=c.size()-1; i>=0; i--) {
    ans += (i > 0) ? k*(double)c[i] : -k*(double)c[i];
    k *= (1 + r);
  }

  return ans;
}

double solve() {
  cin >> m;

  c.clear();
  c.resize(m+1);

  for(int i=0; i<=m; i++)
    cin >> c[i];

  double lo = -1.0, hi = 1.0, mid, temp;

  while(!almost_equal(hi, lo)) {
    mid = lo + (hi-lo)/2.0;
    temp = proc(mid);

    if(almost_equal(temp))
      break;
    else if(temp < 0)
      hi = mid;
    else
      lo = mid;
  }

  return mid;
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++)
    cout << "Case #" << tc+1 << ": " << fixed << setprecision(10) << solve() << endl;

  return 0;
}
