/**
 * Longest Increasing Subsequence Problem
 *
 * Can be solved with Brute force, DP, Interval Trees/BITs/Segment Trees/Fenwick Trees and Patience Sorting.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/**
 * Method 1: Brute force. O(n!) recursion.
 * (See DP method below for the recurrence expression)
 */

/**
 * Method 2: O(n**2) DP with O(n) space.
 *
 * A DP solution exists:
 * lis[i] = 1 + max(lis[j]) where j < i and arr[j] < arr[i];
 *
 * The LIS is max(lis[i]) for all i in 1..len(arr)
 *
 * NOTE: This method only gets the length of LIS.
 */
int longestIncreasingSubsequenceDP(vector<int> &arr) {
  vector<int> dp(arr.size(), 1);

  for(int i=1; i<arr.size(); i++)
    for(int j=0; j<i; j++) {
      dp[i] = (arr[i] > arr[j]) ? max(dp[i], 1 + dp[j]) : dp[i];
    }

  return *max_element(dp.begin(), dp.end());
}

/**
 * Method 3: Patience sorting based Greedy solution using Binary Search
 * O(nlogn) run time with O(n) extra space.
 *
 * The idea is to generate a psuedo sequence which is
 * a increasing sequence made from elements of the original array.
 * This sequence is not necessarily an LIS itself, but its length
 * is same as that of LIS of original array. This sequence is actually
 * a representation of the piles in patience sorting (in this case, they are
 * piles of subsequences in decreasing length order). The process is like this:
 *
 * 1. We start with empty sequence tails[]. tails[i] stores the smallest tail
 * of an always increasing sequence with length i+1.
 *
 * 2. For each incoming element arr[i] from input data stream/array:
 *
 *   2.1 If element arr[i] >= tails[-1], then arr[i] can be appended to
 *   tails[] to make it longer by 1 unit.
 *
 *   2.2 Else if arr[i] < tails[-1], then the element arr[i] will replace the smallest element
 *   tails[j] >= arr[i]. This doesn't really change our sequence length. However in the case,
 *   when the element replaced is tails[-1] (i.e. the last one), it reduces the lower bound for
 *   the next element to increase the overall sequence length. It is essentially an invesment
 *   into the future.
 *
 * 3. The final length of tails[] is the length of LIS. Had we maintained separate piles
 * (instead of replacing in case of 2.2), then maintaintaing back pointers would help us reconstruct
 * the actual LIS sequence.
 *
 * NOTE: This method only gets the length of LIS in its current implementation.
 */
int longestIncreasingSubsequenceBS(vector<int> &arr) {
  vector<int> tails;

  tails.push_back(arr[0]);
  for(int i=1; i<arr.size(); i++){
    auto it = lower_bound(tails.begin(), tails.end(), arr[i]);

    if(it != tails.end())
      *it = arr[i];
    else
      tails.push_back(arr[i]);
  }

  cout << endl << "tails[]: ";
  for(auto &val: tails)
    cout << val << " ";
  cout << endl;

  return tails.size();
}

int main() {
  vector<int> arr = {2, 4, 3, 6, 7, 3, 8, 9, 11, 10};

  cout << "Original input array: ";
  for(auto &num: arr)
    cout << num << " ";
  cout << "\n" << endl;

  cout << "DP Method: " << longestIncreasingSubsequenceDP(arr) << endl;
  cout << "BS + Patience Sorting Method: " << longestIncreasingSubsequenceBS(arr) << endl;

  return 0;
}
