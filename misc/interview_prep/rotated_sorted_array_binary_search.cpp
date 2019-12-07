/**
 * Problem: Find an element in rotated sorted array
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

/**
 * Binary Search based O(log(n)) approach. The array can be:
 *   1. The perfectly rotated array                          ===OR===
 *     e.g. {1, 2, 3, 4}    <== perfectly rotated array
 *   2. The array with a pivot point where there is a sudden drop in magnitude
 *     e.g. {5, 6, 1, 2, 3, 4}
 *              ^^^^        <== sudden change in magnitude
 *
 * We can use simple one-pass binary search with enhanced checking:
 *
 * + If mid_element == target_element, return
 * + Otherwise if {start_element...mid_element} is sorted:
 *   + If key lies in [start, mid] search in this range
 *   + Else recur for in [mid+1, end]
 * + Else {mid_element...end_element} must be sorted:
 *   + If key lies in [mid, end] search in this range
 *   + Else recur for in [start, mid]
 *
 *
 * Note that this can't handle duplicates, in which case you'd need to check with the right most element which is
 * not the same as the `mid` element. Which reduces to O(n) linear search.
 */

int binary_search_rsa(const vector<int>& arr, int target) {
  size_t lo = 0, hi = arr.size()-1, mid;

  while(lo < hi) {
    mid = lo + (hi-lo)/2;

    // if target found
    if(arr[mid] == target)
      return mid;

    // if left half is sorted   => {5, 6, |7|, 8, 2, 3}
    if(arr[lo] <= arr[mid]) {
      if(arr[lo] <= target && target <= arr[mid])
        hi = mid-1;
      else
        lo = mid+1;
    }

    // right half must be sorted  => {7, 8, |2|, 3, 5, 6}
    else {
      if(arr[mid] <= target && target <= arr[hi])
        lo = mid+1;
      else
        hi = mid-1;
    }

  }

  return (arr[lo] == target ? lo : -1);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  vector<int> arr = {5, 6, 1, 2, 3, 4};
  cout << "Input arr: " << arr << endl;
  cout << "Found Target=6: " << binary_search_rsa(arr, 6) << endl;
  cout << "Found Target=3: " << binary_search_rsa(arr, 3) << endl;
  cout << "Found Target=5: " << binary_search_rsa(arr, 5) << endl;
  cout << "Found Target=4: " << binary_search_rsa(arr, 4) << endl;
  cout << "Found Target=1: " << binary_search_rsa(arr, 1) << endl;
  cout << "Cannot find Target=7: " << binary_search_rsa(arr, 7) << endl;

  arr = {1, 2, 3, 4};
  cout << "Input arr: " << arr << endl;
  cout << "Found Target=1: " << binary_search_rsa(arr, 1) << endl;
  cout << "Found Target=4: " << binary_search_rsa(arr, 4) << endl;
  cout << "Found Target=3: " << binary_search_rsa(arr, 3) << endl;

  arr = {1, 2};
  cout << "Input arr: " << arr << endl;
  cout << "Found Target=2: " << binary_search_rsa(arr, 2) << endl;
  cout << "Found Target=1: " << binary_search_rsa(arr, 1) << endl;

  arr = {2, 1};
  cout << "Input arr: " << arr << endl;
  cout << "Found Target=2: " << binary_search_rsa(arr, 2) << endl;
  cout << "Found Target=1: " << binary_search_rsa(arr, 1) << endl;

  arr = {3, 4, 1, 2};
  cout << "Input arr: " << arr << endl;
  cout << "Found Target=3: " << binary_search_rsa(arr, 3) << endl;
  cout << "Found Target=1: " << binary_search_rsa(arr, 1) << endl;
  cout << "Found Target=2: " << binary_search_rsa(arr, 2) << endl;

  arr = {2, 3, 4, 1};
  cout << "Input arr: " << arr << endl;
  cout << "Found Target=2: " << binary_search_rsa(arr, 2) << endl;
  cout << "Found Target=3: " << binary_search_rsa(arr, 3) << endl;
  cout << "Found Target=4: " << binary_search_rsa(arr, 4) << endl;

  return 0;
}
