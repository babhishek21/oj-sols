/**
 * Problem: Advent of Code 2025 - Day 7: Laboratories
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // C++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

int solve1() {
  int ans = 0;
  string previous, current, curcopy;

  getline(cin, previous); // first line has source
  getline(cin, current);  // second and last lines have no splitters presumably

  int len = previous.length();

  debug(previous);

  for (int i = 0; i < len; i++) {
    if (previous[i] == 'S' && current[i] == '.')
      current[i] = '|';
  }

  debug(current);

  previous = current;

  while (getline(cin, current)) {
    curcopy = current;

    for (int i = 0; i < len; i++) {
      if (current[i] == '.' && previous[i] == '|')
        curcopy[i] = previous[i];
      else if(current[i] == '^' && previous[i] == '|') {
        // split beam
        ans++;

        if(i > 0)
          curcopy[i-1] = '|';
        if(i < len-1)
          curcopy[i+1] = '|';
      }
    }

    previous = curcopy;

    debug(curcopy);
  }

  return ans;
}

pair<int, unsigned long> solve1and2() {
  int ans1 = 0, len = -1;
  unsigned long ans2 = 0;
  string current;
  vector<int> cache1;
  vector<unsigned long> cache2;

  getline(cin, current);

  len = current.length();
  cache1 = vector<int>(len, 0);
  cache2 = vector<unsigned long>(len, 0UL);

  do {
    for(int i=0; i<len; i++) {
      if(current[i] == 'S')
        cache1[i] = cache2[i] = 1;

      else if(current[i] == '^' && cache1[i] == 1) {
        ans1++;

        if(i > 0) {
          cache1[i-1] = 1;
          cache2[i-1] += cache2[i];
        }

        if(i < len-1) {
          cache1[i+1] = 1;
          cache2[i+1] += cache2[i];
        }

        cache1[i] = cache2[i] = 0;
      }
    }

    // debug(cache1);
    // debug(cache2);

  } while(getline(cin, current));

  // debug(cache2);
  ans2 = whole(accumulate, cache2, 0UL);

  return {ans1, ans2};
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  // int ans1 = solve1();

  auto ans = solve1and2();

  cout << "answers: " << ans << endl;

  return 0;
}
