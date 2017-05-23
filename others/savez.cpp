/**
 * Problem: COCI '15 Contest 2 #4 Savez (https://dmoj.ca/problem/coci15c2p4)
 * Trie with unordered_map used for prefix and suffix trees.
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

struct Trie {
  int id = 0;
  unordered_map<char, Trie*> nxt;
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, localmax, globalmax = 0;
  string str;

  Trie prefixTree, suffixTree;
  unordered_map<int, int> scores;

  cin >> n;

  for(int i=1; i<=n; i++) {
    cin >> str;

    int len = str.length();
    localmax = 0;

    Trie *pref = &prefixTree, *suff = &suffixTree;

    for(int j=0; j<len; j++) {
      // insert into prefix tree
      if(pref->nxt.count(str[j]) <= 0)
        pref->nxt[str[j]] = new Trie();
      pref = pref->nxt[str[j]];

      // insert into suffix tree
      if(suff->nxt.count(str[len-j-1]) <= 0)
        suff->nxt[str[len-j-1]] = new Trie();
      suff = suff->nxt[str[len-j-1]];

      // check if prefix and suffix are same Loda
      if(pref->id == suff->id)
        localmax = max(localmax, scores[pref->id] + 1);
    }
    pref->id = suff->id = i;
    scores[i] = localmax;

    globalmax = max(globalmax, localmax);
  }

  cout << globalmax << endl;

  return 0;
}
