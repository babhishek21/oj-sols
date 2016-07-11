/**
 * Wildcard Matching (Leetcode)
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

namespace wildcardMatching {

  /**
   * Method 1: Iterative O(|s|*|p|) solution. (20 ms)
   * Pointer i for string s, j for pattern string p
   *
   * Case 1: p[j] == '*'
   *   '*' can match any sequence (even empty ones). We can store the location where we found a '*'
   *   so we can backtrack to it later in case the next char in pattern doesn't match
   * > star_p = j++ (pointer advanced to next char in pattern after storing location of '*')
   * > star_s = i (pointer to string not advanced because of the case where '*' matches empty sequence)
   *
   * Case 2: s[i] == p[j] or p[j] == '?'
   * > i++, j++
   *
   * Case 3: No direct match
   *   We could check if previous pattern char was a '*' and backtrack accordingly
   *   Case 3.1: No previous '*' found. FAIL
   *   Case 3.2: '*' found previously
   *     i = ++star_s (s[star_s] matched successfully to '*')
   *     j = star_p + 1 (start matchign again from char next to '*' in pattern)
   *
   * If any excessive '*' left in pattern after string is exhausted, they are ignored
   */
  bool isMatch(string s, string p) {
    int i = 0, j = 0, m = s.length(), n = p.length(), star_s, star_p = -1;

    while(i < m) {
      if(j < n && p[j] == '*') {
        star_s = i;
        star_p = j++;
      } else if(j < n && (s[i] == p[j] || p[j] == '?')) {
        i++; j++;
      } else if(star_p >= 0) {
        i = ++star_s;
        j = star_p + 1;
      }
    }

    while(j < n && p[j] == '*')
      j++;

    return j == n;
  }

  /**
   * Method 2: Iterative DP O(|s|*|p|) solution with O(|s|) extra space. (192 ms)
   * Pointer i for string s, j for pattern string p, bool match[|s|+1] (Note: match[0] = true initially)
   *
   * For each char of pattern:
   * Case 1: p[j] == '*'
   *   For each char of string s:
   *     match[i+1] = match[i] || match[i+1]
   *   WHY? Because '*' can match arbitrary char and empty char.
   * Case 2: p[j] != '*'
   *   For each char of string s in reverse:
   *     match[i+1] = (p[j] == '?' || (s[i] == p[j])) && match[i]
   *   match[0] = false
   *   WHY? Bacause all previous matches should be true. Additionally current char should match.
   *
   * match[|s|] gives answer
   */
  bool isMatchDP(string s, string p) {
    int m = s.length(), n = p.length();

    // initial checks
    int count_stars = count(p.begin(), p.end(), '*');
    if(count_stars == 0 && m != n)  return false;
    if(n-count_stars > m) return false;

    // init dp match[] table
    vector<bool> match(m+1, false);
    match[0] = true;


    for(int j=0; j<n; j++) {
      if(p[j] == '*') {
        for(int i=1; i<=m; i++)
          match[i] = match[i] || match[i-1];
      } else {
        for(int i=m; i>=1; i--)
          match[i] = (p[j] == '?' || s[i-1] == p[j]) && match[i-1];
        match[0] = false;
      }
    }

    return match[m];
  }

  /**
   * Method 3: Good old 2D DP O(|s|*|p|) with O(|s|*|p|) extra space solution (1680ms)
   * bool dp[|s|+1][|p|+1] (DP array)
   * dp[i][j] stores whether s[0..i] and p[0..j] are a match
   *
   * dp[0][0] = true // empty matches empty
   * dp[i][0] = false // s doesn't match empty p
   * dp[0][j] = dp[0][j-1] && p[j-1] == '*' // empty s matches only when p is all '*'
   *
   * Case 1: p[j-1] == '?' or s[i-1] == p[j-1]
   *   dp[i][j] = dp[i-1][j-1]
   *   WHY? Because current characters match. So current result is same as previous result
   * Case 2: p[j-1] == '*'
   *   dp[i][j] = dp[i-1][j] || dp[i][j-1]
   *   WHY? Because current s[i-1] is now guaranteed to match with p[j-1] == '*'. So result depends on:
   *     1. p[j-1] (i.e. '*') matches s[i-1] as well
   *     2. p[j-1] (i.e. '*') matches empty string
   */
  bool isMatchDPClasssic(string s, string p) {
    int m = s.length(), n = p.length();

    // init dp
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));

    // base cases
    dp[0][0] = true;
    for(int j=1; j<=n; j++)
      dp[0][j] = dp[0][j-1] && p[j-1] == '*';

    // build bottom up
    for(int i=1; i<=m; i++)
      for(int j=1; j<=n; j++) {
        if(p[j-1] == '?' || s[i-1] == p[j-1])
          dp[i][j] = dp[i-1][j-1];
        else if(p[j-1] == '*')
          dp[i][j] = dp[i-1][j] || dp[i][j-1];
      }

    return dp[m][n];
  }
}

int main() {
  using namespace wildcardMatching;

  cout << boolalpha;

  string s = "babaaababaabababbbbbbaabaabbabababbaababbaaabbbaaab", p = "***bba**a*bbba**aab**b";

  cout << "String searchable: " << s << endl
      << "Pattern to search: " << p << endl
      << "isMatch: " << isMatch(s, p) << endl
      << "isMatchDP: " << isMatchDP(s,p) << endl
      << "isMatchDPClasssic: " << isMatchDPClasssic(s, p) << endl;

  s = "abed", p = "?b*d**";

  cout << endl << "String searchable: " << s << endl
      << "Pattern to search: " << p << endl
      << "isMatch: " << isMatch(s, p) << endl
      << "isMatchDP: " << isMatchDP(s,p) << endl
      << "isMatchDPClasssic: " << isMatchDPClasssic(s, p) << endl;

  return 0;
}
