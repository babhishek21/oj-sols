/**
 * Problem: ONP (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

inline bool isop(const char &ch) {
  return (set<char>{'+', '-', '*', '/', '^'}.count(ch) > 0);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n;
  string str;
  stack<char> opst;

  cin >> n;

  while(n--) {
    cin >> str;

    for(auto&& ch: str) {
      if(isalpha(ch))
        cout << ch;
      else if(isop(ch))
        opst.push(ch);
      else if(ch == ')') {
        cout << opst.top();
        opst.pop();
      }
    }

    cout << endl;
  }

  return 0;
}

