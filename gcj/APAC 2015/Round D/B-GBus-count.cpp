/**
 * Problem: B. GBus count (APAC 2015 Round D)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

int t, n, a, b, p;
vector<int> arr, res;

void solve() {
  cin >> n;

  arr.resize(5001, 0);
  // res.resize(n+1);

  for(int i=0; i<n; i++) {
    cin >> a >> b;
    // debug(a) debug(b)
    arr[--a]++; arr[b]--;
    // debug(arr[a]) debug(arr[b])
  }

  partial_sum(arr.begin(), arr.end(), arr.begin());

  cin >> p;

  while(p--) {
    cin >> a;
    cout << arr[--a] << " ";
  }
  cout << endl;

  arr.clear();
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": ";
    solve();
  }

  return 0;
}
