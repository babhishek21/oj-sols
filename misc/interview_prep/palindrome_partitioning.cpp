/**
 * Problem: Palindrome Partitioning (LeetCode)
 * Problem link: https://leetcode.com/problems/palindrome-partitioning/
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

vector<vector<string>> backtrack(string s, const vector<vector<bool>>& palin, int st) {
  if(st == s.size())
    return {{}};
  
  vector<vector<string>> ans;

  for(int i=st; i<s.size(); i++) {
    if(palin[st][i]) {
      for(auto&& temp: backtrack(s, palin, i+1)) {
        temp.push_back(s.substr(st, i-st+1));
        ans.push_back(temp);
      }
    }
  }

  return ans;
}

vector<vector<string>> partition(string s) {
  int n = s.size();

  // build palindromic table first
  vector<vector<bool>> palin(n, vector<bool>(n, false));

  for(int i=0; i<n; i++)
    palin[i][i] = true;

  for(int i=0; i<n-1; i++)
    palin[i][i+1] = s[i] == s[i+1];

  for(int k=3; k<=n; k++)
    for(int i=0, j=k-1; j<n; i++, j++)
      palin[i][j] = palin[i+1][j-1] && (s[i] == s[j]);

  // debug(palin)

  // backtracking on that table to find combos of contiguous palindromes over the entire string
  return backtrack(s, palin, 0);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  string s;

  cin >> t;

  while(t--) {
    cin >> s;

    cout << s << ": " << partition(s) << endl;
  }

  return 0;
}