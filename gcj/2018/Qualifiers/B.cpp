/**
 * Problem: Trouble Sort
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

int t, n, arr[100010];

string solve() {
  cin >> n;

  for(int i=0; i<n; i++)
    cin >> arr[i];

  // trouble sort
  bool done = false;

  while(!done) {
    done = true;
    for(int i=0; i<n-2; i++) {
      if(arr[i] > arr[i+2]) {
        swap(arr[i], arr[i+2]);
        done = false;
      }
    }
    // debug(pretty_print_array(arr, n)); //debug
  }

  // check if sorted
  for(int i=0; i<n-1; i++)
    if(arr[i] > arr[i+1])
      return to_string(i);

  return "OK";
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> t;

  for(int tc=0; tc<t; tc++)
    cout << "Case #" << tc+1 << ": " << solve() << endl;


  return 0;
}
