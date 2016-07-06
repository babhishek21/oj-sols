/**
 * Problem: C. Card Game (APAC 2015 Round B)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

// globals
long long n, k;
vector<long long> arr, todo;

// debug util
inline void debug_dump() {
  cout << "arr:  ";
  for(auto &val: arr)
    cout << val << " ";
  cout << endl;

  cout << "todo: ";
  for(auto &val: todo)
    cout << val << " ";
  cout << endl;
}

void scout(int j) {
  if(n < 3)
    return;

  for(int i = max(1, j+3); i<n-1; i++) {
    if((arr[i] - arr[i-1] == k) && (arr[i+1] - arr[i] == k)) {
      todo.pb(i);
      i += 2;
    }
  }
}

long long solve() {
  cin >> n >> k;

  arr.clear();
  todo.clear();

  arr.resize(n);

  for(int i=0; i<n; i++) {
    cin >> arr[i];
  }

  for(int i=1; i<n-1; i++) {
    if((arr[i] - arr[i-1] == k) && (arr[i+1] - arr[i] == k)) {
      todo.pb(i);
      i += 2;
    }
  }

  // debug_dump(); // debug

  while(!todo.empty() && n>=0) {
    // debug(n);

    int idx = todo.back();
    todo.pop_back();
    arr.erase(arr.begin() + idx-1, arr.begin() + idx+2);
    n -= 3;

    // debug_dump();

    idx = (todo.empty() ? -2 : todo.back());
    scout(idx);

    // debug_dump();
  }

  return n;
}


int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cout << "Case #" << tc+1 << ": " << solve() << endl;
  }

  return 0;
}
