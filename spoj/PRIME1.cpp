/**
 * Problem: PRIME1 (SPOJ)
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

vector<int> pp;

void solve(int m, int n) {
  // check each number in range m...n
  for(int i=max(2, m); i<=n; i++) {

    // check if we have the prime testing set ready
    if(pp.back() < sqrt(i))
      for(int j = pp.back()+1; j < sqrt(i)+1; j++) {
        bool j_prime = true;

        for(auto&& p: pp) {
          if(p > sqrt(j))
            break;

          if(j % p == 0) {
            j_prime = false;
            break;
          }
        }

        if(j_prime)
          pp.pb(j);
      }

    // test the number
    bool i_prime = true;

    for(auto&& p: pp) {
      if(p > sqrt(i))
        break;

      if(i % p == 0) {
        i_prime = false;
        break;
      }
    }

    if(i_prime)
      cout << i << '\n';
  }

  cout << endl;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  pp.reserve(50000);
  pp.pb(2);

  int t, m, n;

  cin >> t;

  while(t--) {
    cin >> m >> n;

    solve(m, n);
  }

  return 0;
}
