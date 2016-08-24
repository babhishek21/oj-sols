/**
 * Problem: RMID2 (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

priority_queue<int, vector<int>> pql;
priority_queue<int, vector<int>, greater<int>> pqr;

inline void clear_pq() { // C++11 and above
  priority_queue<int, vector<int>> ().swap(pql);
  priority_queue<int, vector<int>, greater<int>> ().swap(pqr);
}

/**
 * The idea is to keep two heaps. One (pql) will be max heap which keeps all elements less than or equal to current
 * median. The other (pqr) will be a min heap which keeps all elements greater than or equal to current median. This way
 * we can always get median by looking at the root of both the heaps.
 */
int get_running_median(int num, int median) {
  int diff = pql.size() - pqr.size();

  if(num == -1) { // deletion
    if(!pql.empty() && !pqr.empty() && median == pql.top() && median == pqr.top()) { // even number of elements
      if(diff < 0)
        pqr.pop();
      else
        pql.pop();
    }

    // odd number of elements
    else if(!pql.empty() && median == pql.top())
      pql.pop();
    else if(!pqr.empty() && median == pqr.top())
      pqr.pop();

    // return new median
    if(pql.empty() && pqr.empty())
      return 0;
    else if(pql.size() >= pqr.size())
      return pql.top();
    else
      return pqr.top();
  }

  // find new median
  if(diff == 0) { // guaranteed odd number of elements after insertion
    if(num < median) {
      pql.push(num);
      median = pql.top();
    } else {
      pqr.push(num);
      median = pqr.top();
    }
  }

  else if(diff > 0) {
    if(num < median) { // need to balance both heaps, so that top() hold medians
      pqr.push(pql.top());
      pql.pop();
      pql.push(num);
    } else
      pqr.push(num);

    median = min(pql.top(), pqr.top()); // even number of elements after insertion
  }

  else {
    if(num < median)
      pql.push(num);
    else {           // need to balance both heaps, so that top() hold medians
      pql.push(pqr.top());
      pqr.pop();
      pqr.push(num);
    }

    median = min(pql.top(), pqr.top()); // even number of elements after insertion
  }

  return median;
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  int t, num, median;

  cin >> t;

  while(t--) {
    median = 0;

    while(cin >> num, num != 0) {
      if(num == -1)
        // cout << median << "\n";
        printf("%d\n", median); // stupid spoj with stupid time limits

      median = get_running_median(num, median);
    }

    clear_pq();
  }

  return 0;
}
