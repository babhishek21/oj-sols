/**
 * Problem: Pie Progress (FB HackerCup 2017 Round 1)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define debug(x) cerr << #x << " : " << x << endl;

vector<long long> arr;
long long taxes[350];
priority_queue<long long, vector<long long>, greater<long long>> min_heap;

void calc_taxes() {
  for(long long i=1; i<350; i++) {
    taxes[i] = i*i;
    // debug(taxes[i])
  }
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  calc_taxes();

  int t, n, m;
  long long ans, temp;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n >> m;

    ans = 0;
    priority_queue<long long, vector<long long>, greater<long long>> ().swap(min_heap);

    for(int i=0; i<n; i++) {
      arr.clear();

      for(int j=0; j<m; j++) {
          cin >> temp;
          arr.pb(temp);
      }

      // debug(arr);

      sort(arr.begin(), arr.end());

      for(int j=0; j<m; j++)
          min_heap.push(arr[j] + taxes[j+1] - taxes[j]);

      if(min_heap.empty()) {
          debug(tc+1)
          break;
      }

      ans += min_heap.top();

      // debug(min_heap.top())
      // debug(ans)

      min_heap.pop();
    }

    cout << "Case #" << tc+1 << ": " << ans << endl;
  }

  return 0;
}
