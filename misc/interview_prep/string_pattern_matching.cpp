/**
 * String/Pattern matching algorithms
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/**
 * Knuth-Morris-Pratt Searching Algorithm
 *
 * O(|s|+|p|) runtime, where `s` is searchable string and `p` is pattern to be
 * matched. Uses an auxiliary array lps[] (also called failure function) by
 * preprocessing the pattern char-array p[]
 *
 * lps[i] holds the length of the longest proper prefix of substring p[0..i]
 * which is also a suffix of this same substring.
 *
 * For the pattern p[] = "ababaca", the lps[] = [0, 0, 1, 2, 3, 0, 1]
 *
 * # | String    | P(#)| Longest matching prefix-suffix
 * 0 | "a"       |  0  | ""
 * 1 | "ab"      |  0  | ""
 * 2 | "aba"     |  1  | "a" -- a ]b[ a
 * 3 | "abab"    |  2  | "ab" -- ab ][ ab
 * 4 | "ababa"   |  3  | "aba" -- ab [a] ba
 * 5 | "ababac"  |  0  | ""
 * 6 | "ababaca" |  1  | "a" -- a ]babac[ a
 *
 * Searching Algo:
 * Start matching from p[0] and s[0]. If the entire pattern p[] matches, great!
 * If a mismatch occurs at p[j] and s[i], then we can simply start over by moving
 * our matching window by +lps[j]. Thus we start matching from s[i-j+lps[j]].
 *
 * Preprocessing Algo:
 * Construct the lps[] array by keeping track of longest prefix suffix value based on
 * previous index.
 */
class KMP {
  string pattern, searchable;
  vector<int> lps;

public:
  KMP(string p) : pattern(p) {
    buildLPS();
  }

  KMP(string p, string s) : pattern(p), searchable(s) {
    buildLPS();
  }

  void setPattern(string p) {
    pattern = p;
    buildLPS();
  }

  void resetSearchable() {
    searchable.clear();
  }

  void buildLPS() {
    lps.clear();
    lps.resize(pattern.length());

    lps[0] = -1;
    lps[1] = 0;

    size_t pos = 2, len = 0;
    while(pos < pattern.length()) {

      if(pattern[pos-1] == pattern[len]) // the substring continues to match
        lps[pos++] = ++len;

      else if(len > 0) // failed to match. fall back
        len = lps[len];

      else // we ran out of candidates. len == 0
        lps[pos++] = 0;
    }
  }

  size_t findMatch(const string &s = string()) {
    if(!s.empty()) searchable = s;
    if(searchable.empty()) return string::npos;

    size_t m = 0, i = 0;

    while(m+i < searchable.length()) {

      if(pattern[i] == searchable[m+i]) { // match

        if(i == pattern.length()-1)
          return m;

        i++;
      } else { // fail/mismatch

        if(lps[i] > -1) {
          m += i - lps[i];
          i = lps[i];
        } else {
          m++; i = 0;
        }

      }
    }

    return string::npos; // no match found
  }
};

int main() {
  string s = "ABABDABACDABABCABAB", p = "ABABCABAB";

  KMP KMPtest(p, s);

  cout << "Searchable string: " << s << endl
      << "Pattern: " << p << endl;

  auto pos = KMPtest.findMatch();
  if(pos != string::npos)
    cout << "Match found at index " << pos << endl;
    // assert pos == 10
  else
    cout << "No match found" << endl;

  return 0;
}
