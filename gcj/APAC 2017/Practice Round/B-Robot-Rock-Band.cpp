/**
 * Problem: B. Robot Rock Band (APAC 2017 Practice Round)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int t, n, k, a[1005], b[1005], c[1005], d[1005];

long long solve() {
  map<int, long long> cache;

  for(int i=0; i<n; i++)
    cin >> a[i];
  for(int i=0; i<n; i++)
    cin >> b[i];
  for(int i=0; i<n; i++)
    cin >> c[i];
  for(int i=0; i<n; i++)
    cin >> d[i];

  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      cache[a[i]^b[j]]++;

  long long ans = 0LL;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++) {
      long long temp = c[i]^d[j]^k;
      if(cache.find(temp) != cache.end())
        ans += cache[temp];
    }

  return ans;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n >> k;

    cout << "Case #" << tc+1 << ": " << solve() << endl;
  }

  return 0;
}
