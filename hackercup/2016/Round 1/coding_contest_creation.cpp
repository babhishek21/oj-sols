#include <bits/stdc++.h>
using namespace std;

int arr[100010];

int main() {
  int t, n, temp, ans, count;

  cin >> t;

  for(int tc=1; tc<=t; tc++) {
    cin >> n;

    for(int i=0; i<n; i++)
      cin >> arr[i];
    // arr[n] = arr[n-1];

    count = 1; ans = 0;
    for(int i=1; i<n; i++) {
      // cout << "DEB " << i << "=>" << count << " " << ans << endl; // DEBUG

      temp = arr[i] - arr[i-1];

      if(temp <= 0) { // cannot include arr[i] in current set
        ans += (4 - count) % 4;
        count = 0;
      } else if(temp > 10) {
        temp--;
        temp /= 10;

        if(temp + count >= 4) { // cannot include arr[i] in current set
          ans += (4 - count) % 4;
          count = 0;
        } else { // must include arr[i] in current set
          ans += temp;
          count += temp;
        }
      }

      count++;
      count %= 4;
    }

    ans += (4 - count) % 4;

    // cout << "DEB " << n << "=>" << count << " " << ans << endl; // DEBUG

    cout << "Case #" << tc << ": " << ans << endl;
  }


  return 0;
}
