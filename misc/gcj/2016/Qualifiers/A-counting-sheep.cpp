#include <bits/stdc++.h>
using namespace std;

int arr[10];

bool allset(long long ans) {
  while(ans > 0) {
    arr[ans%10]++;
    ans /= 10;
  }
  for(int i=0; i<10; i++) {
    if(arr[i] < 1)
      return false;
  }
  return true;
}

int main() {
  int t, n;

  cin >> t;

  for(int i=0; i<t; i++){
    cin >> n;
    if(n == 0){
      cout << "Case #" << i+1 << ": " << "INSOMNIA" << endl;
      continue;
    }

    long long ans = n;
    memset(arr, 0, sizeof(arr[0])*10);

    while(!allset(ans))
      ans += n;

    cout << "Case #" << i+1 << ": " << ans << endl;
  }

  return 0;
}
