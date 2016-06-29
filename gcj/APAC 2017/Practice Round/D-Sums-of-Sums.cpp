/**
 * Problem: D. Sums of Sums (APAC 2017 Practice Round)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int t, n, q, arr[200005];
long long l, r;

void solve() {
  long long temp = 0LL;
  vector<long long> v;

  for(int i=0; i<n; i++)
    for(int j=i; j<n; j++) {
      temp = arr[j] - (i > 0 ? arr[i-1] : 0LL);
      v.push_back(temp);
    }

  sort(v.begin(), v.end());


  for(long long i=0LL; i<v.size(); i++)
    v[i] += (i > 0LL) ? v[i-1] : 0LL;


  while(q--) {
    cin >> l >> r;
    l--; r--;

    cout << (v[r] - (l > 0LL ? v[l-1] : 0LL)) << endl;
  }
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n >> q;

    for(int i=0; i<n; i++) {
      cin >> arr[i];
      arr[i] += (i > 0) ? arr[i-1] : 0;
    }

    cout << "Case #" << tc+1 << ":"<< endl;
    solve();
  }

  return 0;
}
