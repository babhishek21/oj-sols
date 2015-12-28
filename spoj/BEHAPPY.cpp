#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<pair<int, int> > lims;

int solve(int mm, int nn) {
  if(nn < 0 or mm < 0) return 0;

  int mini = lims[m-mm].first, maxi = lims[m-mm].second, ans = 0;

  if(mm == 0 && nn == 0) return 1;

  for(int i=mini; i<=maxi; i++) {
    ans += solve(mm-1, nn-i);
  }

  return ans;
}

int main() {
  int a, b;

  cin >> m >> n;

  while(m!=0 and n!=0) {
    for(int i=0; i<m; i++) {
      cin >> a >> b;
      lims.push_back(make_pair(a,b));
    }

    cout << solve(m, n) << endl;

    cin >> m >> n;
  }

  return 0;
}
