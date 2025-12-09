/**
 * Problem: KMP Algorithm
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

vector<int> build_overlap(const string& pat) {
  vector<int> olp(pat.size()+1);  // overlap

  olp[0] = -1;

  for(int i=0; i<pat.size(); i++) {
    olp[i+1] = olp[i]+1;

    while(olp[i+1] > 0 && pat[i] != pat[olp[i+1] - 1])
      olp[i+1] = olp[olp[i+1] - 1] + 1;
  }

  return olp;
}

vector<int> kmp(const string& txt, const string& pat) {
  vector<int> olp = build_overlap(pat), ans;

  int j=0, n = txt.size(), m = pat.size(), i;

  for(i=0; i<n; i++)
    while(true) {
      if(txt[i] == pat[j]) {
        j++;

        if(j == m) {
          ans.push_back(i-j);
          j = olp[j];
        }

        break;
      } else if(j == 0)
        break;
      else
        j = olp[j];
    }

  return ans;
}

static const int base = 101;

int next_hash(const string& str, int st, int sz, int hs) { // TODO: Recheck this hash algorithm
  int hash = 0, i = 0;

  if(st > 0)
    hash = (hs - str[st-1]*(base**sz));

  while(i < sz) {
    hash *= base;
    hash += str[i++];
  }

  return hash;
}

// See: https://liuzhenglaichn.gitbook.io/algorithm/string/rabin-karp
int rabin_karp(const string& txt, const string& pat) { // TODO: Optimize this by precomputing hashes
  int n = txt.size(), m = pat.size(), hashpat = next_hash(pat, 0, m, 0), hashtxt = 0;

  for(int i=0; i<n-m+1; i++) {
    hashtxt = next_hash(txt, i, m, hashtxt);

    if(hashtxt == hashpat && pat == txt.substr(i, m))
      return i;
  }

  return -1;
}


int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  return 0;
}
