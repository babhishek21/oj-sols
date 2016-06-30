/**
 * Problem: A. Googol String (APAC 2016 Round A)
 * Author: babhishek21
 * Lang: C++11
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int t;
long long len[100], k;

int solve(long long k) {
  int l = 0;
  while(len[l] < k)
    l++;

  if(len[l-1] + 1 == k)
    return 0;

  long long dist = len[l] - k + 1;
  return solve(dist)^1;
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  len[0] = 0;
  for(int i=1; i<=61; i++)
    len[i] = 2*len[i-1] + 1;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> k;

    cout << "Case #" << tc+1 << ": "<< solve(k) << endl;
  }

  return 0;
}
