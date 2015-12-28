#include <bits/stdc++.h>
using namespace std;

unordered_map<long long, long long> memo;

long long solve(long long n) {
  if(n == 0) return 0;

  if(memo[n] != 0)
    return memo[n];
  else
    return memo[n] = max(n, solve(n/2) + solve(n/3) + solve(n/4));
}

int main() {
  long long n;

  while(cin >> n)
    cout << solve(n) << endl;

  return 0;
}
