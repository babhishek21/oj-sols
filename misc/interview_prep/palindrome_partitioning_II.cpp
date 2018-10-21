/**
 * Problem: Palindrome Partitioning II (LeetCode)
 * Problem link: https://leetcode.com/problems/palindrome-partitioning-ii/
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

int mincut(string s) {
  int n = s.size(), newMinCut;

  vector<int> dp(n);  // dp[k] = min cuts till first k chars
  whole(iota, dp, 0); // worst case

  for(int mid=1; mid < n; mid++) { // iterating through all chars as mid points of potential palindromes 

    // CASE 1: Odd length palindromes with centre at mid
    for(int st=mid, ed=mid; st>=0 && ed<n && s[st] == s[ed]; st--, ed++) {
      // if st == 0, then s[0...ed] is a palindrome, thus mincuts[ed] = 0
      // if st > 0, then we need a cut between s[0...st-1] and s[st...ed]. Thus mincuts[ed] = mincuts[st-1] + 1
      newMinCut = (st > 0) ? dp[st-1] + 1 : 0;
      dp[ed] = min(dp[ed], newMinCut);
    }

    // CASE 2: Even length palindromes with centre at mid
    for(int st=mid-1, ed=mid; st>=0 && ed<n && s[st] == s[ed]; st--, ed++) {
      newMinCut = (st > 0) ? dp[st-1] + 1 : 0;
      dp[ed] = min(dp[ed], newMinCut);
    }
  }

  return dp[n-1];
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  string s;

  cin >> t;

  while(t--) {
    cin >> s;

    cout << s << ": " << mincut(s) << endl;
  }

  return 0;
}