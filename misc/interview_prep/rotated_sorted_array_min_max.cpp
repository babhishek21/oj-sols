/**
 * Problem: Max/Min element in rotated sorted array
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
 * Binary Search based O(log(n)) approach. The max/min element belongs to:
 *   1. The boundaries of the array                          ===OR===
 *     e.g. {1, 2, 3, 4}    <= perfectly rotated array
 *   2. The pivot point where there is a sudden drop in magnitude
 *     e.g. {5, 6, 1, 2, 3, 4}
 *              ^^^^        <= sudden change in magnitude
 *
 * Simple binary search would check the neighbouring elements for the `mid` element we analyse to detect the
 * the max/min. For case 1, only one of the neighbours would be available
 *
 * To determine which half to discard:
 *   + If mid_element < end_element, pivot lies in left half (e.g 3 <= 4)
 *   + Else pivot lies in right half (e.g. 5 > 4)
 *
 * Note that this can't handle duplicates, in which case you'd need to check with the right most element which is
 * not the same as the `mid` element. Which reduces to O(n) linear search
 */

int min_element_rsa(const vector<int>& arr) {
  size_t lo = 0, hi = arr.size()-1, mid;

  while(lo < hi) {
    mid = lo + (hi-lo)/2;

    // check mid elements
    if(mid < hi && arr[mid] > arr[mid+1])
      return arr[mid+1];
    else if(mid > lo && arr[mid] < arr[mid-1])
      return arr[mid];

    // decide where to go next
    if(arr[mid] < arr[hi])
      hi = mid-1;
    else
      lo = mid+1;
  }

  return arr[lo];
}

int max_element_rsa(const vector<int>& arr) {
  size_t lo = 0, hi = arr.size()-1, mid;

  while(lo < hi) {
    mid = lo + (hi-lo)/2;

    // check mid elements
    if(mid < hi && arr[mid] > arr[mid+1])
      return arr[mid];
    else if(mid > lo && arr[mid] < arr[mid-1])
      return arr[mid-1];

    // decide where to go next
    if(arr[mid] < arr[hi])
      hi = mid-1;
    else
      lo = mid+1;
  }

  return arr[arr.size()-1-lo]; // handle perfectely rotated arrays
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  vector<int> arr = {5, 6, 1, 2, 3, 4};
  cout << "Input arr: " << arr << endl;
  cout << "Min element: " << min_element_rsa(arr) << endl;
  cout << "Max element: " << max_element_rsa(arr) << endl;

  arr = {1, 2, 3, 4};
  cout << "Input arr: " << arr << endl;
  cout << "Min element: " << min_element_rsa(arr) << endl;
  cout << "Max element: " << max_element_rsa(arr) << endl;

  arr = {1, 2};
  cout << "Input arr: " << arr << endl;
  cout << "Min element: " << min_element_rsa(arr) << endl;
  cout << "Max element: " << max_element_rsa(arr) << endl;

  arr = {2, 1};
  cout << "Input arr: " << arr << endl;
  cout << "Min element: " << min_element_rsa(arr) << endl;
  cout << "Max element: " << max_element_rsa(arr) << endl;

  arr = {3, 4, 1, 2};
  cout << "Input arr: " << arr << endl;
  cout << "Min element: " << min_element_rsa(arr) << endl;
  cout << "Max element: " << max_element_rsa(arr) << endl;

  arr = {2, 3, 4, 1};
  cout << "Input arr: " << arr << endl;
  cout << "Min element: " << min_element_rsa(arr) << endl;
  cout << "Max element: " << max_element_rsa(arr) << endl;

  return 0;
}
