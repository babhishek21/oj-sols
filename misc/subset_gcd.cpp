/**
 * Problem: Subset GCD (Adobe Hackathon 2015)
 * Author: babhishek21
 * Description: For each number i of given n numbers, find the the number of non-empty subsets of this list, which have gcd as the i;
 * Lang: C++11
 */
#include <bits/stdc++.h>
using namespace std; // Damn you, I can't use the symbol `count` now as a variable.

#define N 1000001

int arr[N], cnt[N]; // arr stores the input numbers; count stores the count of appearances of an element in arr
long long ans[N], pwr[N]; // ans stores the answer corressponding to each element in arr (i.e. no. of non-empty subsets of `k` elements); pwr stores 2^k - 1 for a value `k`. It is the power table (taking care of MOD)
int MOD = 1000000007;

void buildPowerTable() { // build power table. Take care of MOD
  pwr[0] = 0; // 2^0 - 1 = 0; T(n) = 2^n - 1
  for(int i=1; i<N; i++) {
    pwr[i] = pwr[i-1]*2 + 1; // T(n) = 2*T(n-1) + 1
    if(pwr[i] >= MOD)
      pwr[i] -= MOD; // Same as taking modulo
  }
}

void init() { // initialize memory for use
  for(int i=0; i<N; i++) {
    arr[i] = 0;
    cnt[i] = 0;
    ans[i] = 0;
  }
}

void solve() {
  init();
  int n, mymax = 0;

  cin >> n;

  for(int i=0; i<n; i++) {
    cin >> arr[i];
    cnt[arr[i]]++; // keep count of appearances
    mymax = max(mymax, arr[i]); // keep track of max input
  }

  /**
   * The Algo:
   *   + Step - 1: For each number `k` (which may or may not exist in arr) till mymax (the largest number in arr), add the count of each multiple of `k` to answer corressponding to `k`. This is a build step. Necessary. Hence now ans[k] stores the total count of elements divisible by `k` in arr. This is done cleverly using a simple sieve approach. Finally actually store the total number of subsets possible for count of ans[i] in ans[i] (i.e. 2^(count value) - 1).
   *
   *   + Step - 2: For each number `k` from mymax down to 1, remove the count of subsets of all higher multiples of `k` (till mymax) from ans[k]. This finalizes the answer.
   *
   *   + An example:
   *           3 = n
   *           2 2 3 4 6
   *   Input step:
   *   for n = 2: count = 2;
   *   for n = 3: count = 1;
   *   for n = 4: count = 1;
   *   for n = 6: count = 1;
   *
   *   Step - 1:
   *   i=1: ans[i] = 0;
   *   i=2: ans[i] = 15; // So 2 is apprantly the gcd of 15 subsets. It isn't. The subset which only contains 4 (i.e. {4}, whose gcd is 4) and only 6 (i.e. {6}, whose gcd = 6) are wrongly counted.
   *   i=3: ans[i] = 3; // Wrongly counted {6} as subset
   *   i=4: ans[i] = 1;
   *   i=6: ans[i] = 1;
   *
   *   Step - 2:
   *   i=6: ans[i] = 1;
   *   i=4: ans[i] = 1;
   *   i=3: ans[i] = 3-1 = 2;
   *   i=2: ans[i] = 15-1-1 = 13;
   *   i=1: ans[i] = 1;   *
   */

  for(int i=1; i<=mymax; i++) {
    for(int j=i; j<=mymax; j+=i) { // O(nlogn) sieve style
      ans[i] += cnt[j];
    }

    ans[i] = pwr[ans[i]]; // store actual value n ans
    if(ans[i] < 0)
      ans[i] += MOD; // take care of MOD
  }

  for(int i=mymax; i>0; i--) {
    for(int j = 2*i; j<=mymax; j+=i) { // j starts form i+i = 2*i
      ans[i] -= ans[j];
      if(ans[i] < 0)
        ans[i] += MOD; // take care of MOD
    }
  }

  // output answer
  for(int i=0; i<n; i++) {
    cout << ans[arr[i]] << " ";
  }
  cout << endl;
}

int main() {
  buildPowerTable();

  solve();

  return 0;
}
