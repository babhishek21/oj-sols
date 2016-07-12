/**
 * Max Subarray and Max Subsequence and Longest Subsequence and Array DP techniques
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

/**
 * Longest Increasing Subsequence [O(n**2) DP].
 *
 * A DP solution exists:
 * lis[i] = 1 + max(lis[j]) where j < i and arr[j] < arr[i];
 *
 * The LIS is max(lis[i]) for all i in 1..len(arr)
 */
int longestIncreasingSubsequence(vector<int> arr) {
  vector<int> dp(arr.size(), 1);

  for(int i=1; i<arr.size(); i++)
    for(int j=0; j<i; j++) {
      dp[i] = (arr[i] > arr[j]) ? max(dp[i], 1 + dp[j]) : dp[i];
    }

  return *max_element(dp.begin(), dp.end());
}

/**
 * Longest Increasing Subsequence [Faster solution O(nlogn)]
 * based on Patience Sorting.
 *
 * Let our pile of numbers have top element as E. Note that all numbers
 * below E in the pile are actually equal or larger than E.
 *
 * For an incoming number C, there are two cases:
 *
 *
 */

int main() {
  vector<int> arr = {2, -1, 2, 3, 4, -5}; // C++11 only

  cout << kadane(arr) << " " << maxSumSubsequence(arr) << endl;
  // assert: 10 11

  arr = {5, 5, 10, 100, 10, 5};

  cout << maxSumSubsequenceNonAdjacent(arr) << endl;
  // assert: 110

  cout << longestIncreasingSubsequence(arr) << endl;
  // assert: 3

  return 0;
}

