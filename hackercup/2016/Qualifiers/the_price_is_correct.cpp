#include <bits/stdc++.h>
using namespace std;

long long arr[100100];

int main() {
  int t, n, p;
  long long ans;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> n >> p;

    for(int i=0; i<n; i++)
      cin >> arr[i];

    long long curr_sum = 0;
    int start = 0;
    ans = 0;

    for(int i=0; i<=n; i++) {
      while(curr_sum > p and start < i-1) {
        curr_sum -= arr[start];
        start++;
      }

      if(curr_sum <= p) {
        ans += i - start;
      }

      if(i < n) curr_sum += arr[i];
    }

    cout << "Case #" << tc+1 << ": " << ans << endl;
  }

  return 0;
}
