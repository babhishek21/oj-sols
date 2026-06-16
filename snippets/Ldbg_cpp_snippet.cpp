/**
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h>
#include "custom/prettyprint.hpp"
#include "custom/debugprint.hpp"
using namespace std;

#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

int main() {
  // --- scalar types ---
  int a = 42;
  long b = 1234567890L;
  long long c = 9876543210LL;
  unsigned long long d = 18446744073709551615ULL;
  float e = 3.14f;
  double f = 2.718281828;
  long double g = 1.41421356237L;
  debug(a, b, c, d, e, f, g);

  // --- bool, char, string ---
  bool t = true, f2 = false;
  char ch = 'x';
  const char *cstr = "hello";
  string s = "world";
  debug(t, f2, ch, cstr, s);

  // --- pair ---
  pair<int, double> p = {1, 2.5};
  pair<string, bool> p2 = {"key", false};
  tuple<string, int, bool> t2 = {"nice", 69, true};
  debug(p, p2, t2);

  // --- bitset ---
  bitset<8> bs("10101010");
  bitset<16> bs2(0b1100110011);
  debug(bs, bs2);

  // --- vector<bool> ---
  vector<bool> vb = {true, false, true, false, false};
  debug(vb);

  // --- STL containers (via prettyprint) ---
  vector<int> vi = {1, 2, 3, 4, 5};
  vector<vector<int>> vvi = {{1, 2}, {3, 4}, {5}};
  set<int> si = {3, 1, 4, 1, 5};
  multiset<int> msi = {3, 1, 4, 1, 5, 2, 2};
  map<string, int> mapsi = {{"one", 1}, {"two", 2}};
  multimap<string, int> mmapsi = {{"one", 1}, {"two", 2}, {"one", 0}};
  unordered_map<string, int> umapsi = {{"cat", 3}, {"dog", 2}};
  map<string, int> bigmap = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
  debug(vi);
  debug(vvi);
  debug(si);
  debug(msi);
  debug(mapsi);
  debug(mmapsi);
  debug(umapsi);
  debug(bigmap);

  // --- variadic mixed ---
  debug(a, ch, s, p, vi);

  return 0;
}
