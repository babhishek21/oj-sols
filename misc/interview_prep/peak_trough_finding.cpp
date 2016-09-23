/**
 * Problem: Local minima in 1D and 2D arrays
 * Refer: http://courses.csail.mit.edu/6.006/spring11/lectures/lec02.pdf
 * Refer: https://www.careercup.com/question?id=8223978
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

/**
 * Local minima in 1D array
 * Expected complexity is O(logn), since O(n) scan is trivial.
 * Given conditions: A[1] >= A[2] and A[n-1] <= A[n] for A[1..n]
 * Algo: Modified binary search
 */

int find_local_minima_1d(const vector<int> &arr) {
  if(arr.empty())
    throw domain_error("Empty vector!");

  int lo = 0, hi = arr.size()-1, mid = lo + (hi-lo)/2;

  while(lo < hi) {

    mid = lo + (hi - lo)/2;

    if(arr[mid-1] >= arr[mid] && arr[mid] <= arr[mid+1]) // local minima
      return arr[mid];

    else if(arr[mid-1] <= arr[mid] && arr[mid] <= arr[mid+1]) // recurse left
      hi = mid;

    else if(arr[mid-1] >= arr[mid] && arr[mid] >= arr[mid+1]) // recurse right
      lo = mid;
  }

  return arr[mid];
}

/**
 * Local minima in 2D array
 * Expected complexity: O(logm + logn)
 * WARNING: Not sure if this works:
 * Use 1d search algo on a middle column (O(logn))
 * Check if the 1d local minima is also a 2d local minima. Else discard either left or right side of column (modified
 * bianry search). Do this till you find local maxima. (O(logm * cost of 1d algo))
 * Hence total cost = O(logm * logn). Still not O(logm + logn)
 */

int find_local_minima_2d(vector<vector<int>> arr) {
  if(arr.empty())
    throw domain_error("Empty vector!");

  // how do we do it?
}


int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  vector<int> arr = {9, 7, 7, 2, 1, 3, 7, 5, 4, 7, 3, 3, 4, 8, 6, 9};
  // vector<int> arr1d = {2, 1, 0, 2};

  try {

    cout << find_local_minima_1d(arr1d) << endl;

  } catch(const domain_error& excp) {
  // catch(...) to catch em' all!

    cout << "Something went wrong: " << excp.what() << endl;

  }

  return 0;
}
