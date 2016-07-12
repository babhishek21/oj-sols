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
double c0, c1, c2, temp;
vector<int> c;

double solve() {
  cin >> m >> c0;

  double ans = 0.0;

  if(m == 1) {
    cin >> c1;

    ans = (c1/c0 - 1.0);
  }

  if(m == 2) {
    cin >> c1 >> c2;

    double t1 = sqrt(c1*c1 + 4*c0*c2);

    ans = (c1+t1)/(2.0*c0) - 1.0;
  }

  return ans;
}


int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": " << fixed << setprecision(10) << solve() << endl;
  }

  return 0;
}
