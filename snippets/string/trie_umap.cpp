/**
 * Problem: Trie (with unordered_map and dynamic allocation)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

struct TrieNode {
  char ch;
  int words, prefs;
  unordered_map<char, TrieNode*> nxt;

  TrieNode(char c): ch(c), words(0), prefs(0) {}
};

struct Trie {
  TrieNode *root;

  Trie() {
    root = new TrieNode(0);
  }

  void addWord(const string &str) {
    if(str.empty()) return;

    TrieNode *curr = root;
    curr->prefs++;

    for(auto&& ch: str) {
      if(curr->nxt.count(ch) <= 0)
        curr->nxt[ch] = new TrieNode(ch);

      curr = curr->nxt[ch];
      curr->prefs++;
    }

    curr->words++;
  }

  int countWords(const string &str) {
    if(str.empty()) return root->words; // always 0

    TrieNode *curr = root;

    for(auto&& ch: str) {
      if(curr->nxt.count(ch) <= 0)
        return 0;

      curr = curr->nxt[ch];
    }

    return curr->words;
  }

  int countPrefs(const string &str) {
    if(str.empty()) return root->prefs;

    TrieNode *curr = root;

    for(auto&& ch: str) {
      if(curr->nxt.count(ch) <= 0)
        return 0;

      curr = curr->nxt[ch];
    }

    return curr->prefs;
  }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  Trie myTrie = Trie();

  myTrie.addWord("abhi");
  myTrie.addWord("abhishek");
  myTrie.addWord("abhishake");
  myTrie.addWord("abhinav");
  myTrie.addWord("abhishake");
  myTrie.addWord("abhilol");

  assert(myTrie.countWords("abhi") == 1);
  assert(myTrie.countWords("abhishake") == 2);
  assert(myTrie.countWords("abhishek") == 1);
  assert(myTrie.countWords("abhinav") == 1);

  assert(myTrie.countPrefs("abhil") == 1);
  assert(myTrie.countPrefs("abhishak") == 2);
  assert(myTrie.countPrefs("abhishake") == 2);

  assert(myTrie.countPrefs("abhi") > 3);
  debug(myTrie.countPrefs("abhi"));
  assert(myTrie.countPrefs("abhish") > 1);
  debug(myTrie.countPrefs("abhish"));

  return 0;
}
