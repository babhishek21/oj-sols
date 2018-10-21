/**
 * Problem: Maximum Sum of 3 Non-Overlapping Subarrays (LeetCode)
 * Problem link: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/
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

vector<int> maxSumOfThreeSubarrays(vector<int>& arr, int k) {
  int n = arr.size(), psum = 0, best, x, y, z;
  vector<int> win(n-k+1), left(n-k+1), right(n-k+1);
  
  // calculate all k size windows as win[]
  for(int i=0; i<n; i++) {
    psum += arr[i];
    
    if(i >= k) psum -= arr[i-k];
    if(i >= k-1) win[i-k+1] = psum;
  }

  // calculate left[].
  // left[i] holds the max subarray of lenght k starting from index <= i
  best = 0;
  for(int i=0; i<win.size(); i++) {
    best = (win[i] > win[best]) ? i : best;
    left[i] = best;
  }

  // calculate right[].
  // right[i] holds the max subarray of lenght k ending at index >= i
  best = win.size() - 1;
  for(int i=win.size()-1; i>=k; i--) {
    best = (win[i] >= win[best]) ? i : best;
    right[i] = best;
  }

  // calculate the 3 subarray combo
  // we are essentially looking for a combo such that w[x] + w[y] + w[z] is maximised
  // for a fixed y = j, the max subarray to the left is at index x = left[j - k]
  // likewise, the max subarray to the right is at index z = right[j + k]
  x = y = z = -1;
  for(int j=k; j<win.size()-k; j++) {
    psum = win[left[j-k]] + win[j] + win[right[j+k]];

    if(x == -1 || psum > win[x] + win[y] + win[z]) {
      x = left[j-k];
      y = j;
      z = right[j+k];
    }
  }
  
  return {x, y, z};
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int n, k, temp;
  vector<int> arr;

  cin >> n >> k;

  while(n--) {
    cin >> temp;
    arr.push_back(temp);
  }
  
  cout << maxSumOfThreeSubarrays(arr, k) << endl;

  return 0;
}