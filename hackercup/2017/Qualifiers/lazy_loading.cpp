/**
 * Problem: Lazy Loading (FB HackerCup 2017 Qualification Round)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cerr << #x << " : " << x << endl;

int t, n, arr[510];

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc = 0; tc < t; tc++) {
    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    sort(arr, arr+n);

    int i = 0, j = n-1, cnt = 0;

    while(i <= j) {
      int top = arr[j--], val = top;

      while(val < 50) {
        if(i > j) { // fail
          cerr << "Epic fail" << endl;
          debug(tc+1)
          debug(i)
          debug(j)
          debug(val)

          cnt--;
          break;
        }

        i++;
        val += top;
      }

      cnt++;
    }

    cout << "Case #" << tc+1 << ": " << cnt << endl;
  }


  return 0;
}
