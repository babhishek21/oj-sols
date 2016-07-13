/**
 * Range Sum Query (Mutable) (Leetcode)
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/**
 * 1. Naive Brute Force.
 * O(n) per query
 * O(1) per update
 */

/**
 * 2. Square Root Decomposition
 * Divide a input array arr of size n into ceil(sqrt(n)) blocks. Later merge only those
 * blocks which lie inside given range.
 * O(n**0.5) per query
 * O(1) per update
 */
class SQRTDecomposition {
  vector<int> arr;
  vector<int> blocks;
  int len;
public:
  SQRTDecomposition(vector<int> &nums): arr(nums) {
    len = ceil(nums.size()/sqrt(nums.size())); // assuming nums.empty() == false
    blocks.clear();
    blocks.resize(len, 0);

    for(int i=0; i<nums.size(); i++)
      blocks[i/len] += nums[i];
  }

  int queryRangeSum(int i, int j) {
    int startBlock = i/len, endBlock = j/len, sum = 0;

    if(startBlock == endBlock) {
      for(int k=i; k<=j; k++)
        sum += arr[k];

      return sum;
    }

    for(int k=i; k < (startBlock+1)*len; k++)
      sum += arr[k];
    for(int k=startBlock+1; k<endBlock; k++)
      sum += blocks[k];
    for(int k=endBlock*len; k<=j; k++)
      sum += arr[k];

    return sum;
  }

  void updateVal(int i, int val) {
    blocks[i/len] += (val - arr[i]);
    arr[i] = val;
  }
};

/**
 * 3. Segment Trees
 * Build a tree whose nodes represent the entire range. It's two children represent the two halves
 * of this range. This continue down the tree with height log(n) until we reach the n individual
 * leaves of the tree (each representing a single element).
 *
 * O(logn) per query
 * O(logn) per update
 */
class SegTree {
  vector<int> tree; // 1-based indexing
  int n;
public:
  SegTree(vector<int> &nums) {
    n = nums.size();
    tree.clear();
    tree.resize(4*n, 0);

    buildSegTree(nums, 1, 0, n-1);
  }

  int queryRangeSum(int i, int j) {

    return querySegTree(1, 0, n-1, i, j);
  }

  void updateVal(int i, int val) {
    updateValSegTree(1, 0, n-1, i, val);
  }

  void buildSegTree(vector<int> &nums,int treeIndex, int lo, int hi) {
    if(lo == hi) {
      tree[treeIndex] = nums[lo];
      return;
    }

    int mid = lo + (hi-lo)/2;
    buildSegTree(nums, 2*treeIndex, lo, mid);
    buildSegTree(nums, 2*treeIndex+1, mid+1, hi);

    // merge build results
    tree[treeIndex] = tree[2*treeIndex] + tree[2*treeIndex+1];
  }

  int querySegTree(int treeIndex, int lo, int hi, int i, int j) { // query for arr[i..j]
    if(i == lo && j == hi)
      return tree[treeIndex];

    int mid = lo + (hi-lo)/2;

    if(i > mid)
      return querySegTree(2*treeIndex+1, mid+1, hi, i, j);
    else if(j <= mid)
      return querySegTree(2*treeIndex, lo, mid, i, j);

    int leftQuery = querySegTree(2*treeIndex, lo, mid, i, mid);
    int rightQuery = querySegTree(2*treeIndex+1, mid+1, hi, mid+1, j);

    // merge queries
    return leftQuery + rightQuery;
  }

  void updateValSegTree(int treeIndex, int lo, int hi, int arrIndex, int val) {
    if(lo == hi) {
      tree[treeIndex] = val;
      return;
    }

    int mid = lo + (hi-lo)/2;

    if(arrIndex > mid)
      updateValSegTree(2*treeIndex+1, mid+1, hi, arrIndex, val);
    else if(arrIndex <= mid)
      updateValSegTree(2*treeIndex, lo, mid, arrIndex, val);

    // merge updates
    tree[treeIndex] = tree[2*treeIndex] + tree[2*treeIndex+1];
  }
};

int main() {
  vector<int> nums = {1,2,3,4,5,6,7,8,9};

  cout << "Original input array: ";
  for(auto &val: nums)
    cout << val << " ";
  cout << endl;

  cout << "\nTesting SQRT Decomposition:" << endl;
  SQRTDecomposition testsqd(nums);

  cout << "GET (2, 7): " << testsqd.queryRangeSum(2, 7) << endl; // assert 33
  cout << "UPDATE (4, -5)" << endl;
  testsqd.updateVal(4, -5);
  cout << "GET (1, 8): " << testsqd.queryRangeSum(1, 8) << endl; // assert 34

  cout << "\nTesting Segment Trees:" << endl;
  SegTree testst(nums);

  cout << "GET (2, 7): " << testst.queryRangeSum(2, 7) << endl; // assert 33
  cout << "UPDATE (4, -5)" << endl;
  testst.updateVal(4, -5);
  cout << "GET (1, 8): " << testst.queryRangeSum(1, 8) << endl; // assert 34

  return 0;
}
