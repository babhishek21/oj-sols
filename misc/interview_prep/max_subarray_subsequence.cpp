/**
 * Max Subarray and Max Subsequence and Array DP techniques
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/**
 * Kadane's Algorithm for 1D Array
 * Maximum contiguous subarray sum
 */
int kadane(vector<int> arr) {
  int localmax = arr[0], globalmax = arr[0];

  for(int i=1; i<arr.size(); i++) {
    localmax = max(arr[i], localmax+arr[i]);
    globalmax = max(globalmax, localmax);
  }

  return globalmax;
}

/**
 * Max sum subsequence of an array
 * (May or may not be contiguous)
 */
int maxSumSubsequence(vector<int> arr) {
  int sum = 0, maxi = numeric_limits<int>::min(), mini = numeric_limits<int>::max();

  for(int i=0; i<arr.size(); i++) {
    sum = max(sum, sum+arr[i]);
    maxi = max(maxi, arr[i]);
    mini = min(mini, arr[i]);
  }

  if(sum == 0) sum = mini;

  return max(maxi, sum);
}

/**
 * Max sum subsequence of array such that
 * no two adjacent elements present
 *
 * DP solution exists:
 * dp[i] = max(dp[i-1], dp[i-2] + arr[i])
 * where dp[0] = arr[0], dp[1] = max(dp[0], arr[1])
 */
int maxSumSubsequenceNonAdjacent(vector<int> arr) {
  int dp_0 = arr[0], dp_1 = max(arr[0], arr[1]), temp;

  for(int i=2; i<arr.size(); i++) {
    temp = max(dp_1, dp_0 + arr[i]);
    dp_0 = dp_1;
    dp_1 = temp;
  }

  return max(dp_0, dp_1);
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  vector<int> arr = {2, -1, 2, 3, 4, -5}; // C++11 only

  cout << kadane(arr) << " " << maxSumSubsequence(arr) << endl;
  // assert: 10 11

  arr = {5, 5, 10, 100, 10, 5};

  cout << maxSumSubsequenceNonAdjacent(arr) << endl;
  // assert: 110

  return 0;
}

