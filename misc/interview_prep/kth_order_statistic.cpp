/**
 * Kth Order Statistics (finding the Kth smallest element)
 * (can be extended to find Kth largest element or K largest/smallest elements)
 */
#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

/**
 * 1. Trivial sorting. O(nlogn) runtime.
 */

/**
 * 2. Heap-select. Make min-Heap of n elements and extract
 * min value k times. O(n) for making heap, O(klogn) for
 * extracting k mins. O(n + klogn) runtime.
 */
int kthSmallestHeapSelect(vector<int> &arr, int k) {
  priority_queue<int, vector<int>, greater<int>> minHeap(arr.begin(), arr.end());

  int ret;
  while(k--) {
    ret = minHeap.top();
    minHeap.pop();
  }

  return ret;
}

/**
 * 3. Max Heaps. Make soft max heap of size k. Process all n elements
 * and maintain size of heap as k with popping as required. Once done,
 * we have the k smallest elements in the heap. The root of the heap is
 * the kth smallest element. O(k) for making heap. O((n-k) logk)
 * for the n-k pops. O(k + (n-k)logk) runtime.
 */
int kthSmallestSoftHeap(vector<int> &arr, int k) {
  priority_queue<int> maxHeap;

  for(auto &num: arr) {
    maxHeap.push(num);

    while(maxHeap.size() > k) {
      maxHeap.pop();
    }
  }

  return maxHeap.top();
}

/**
 * 4. Quickselect. O(n) average case, O(n**2) worst case runtime.
 */
namespace Quickselect {
  int medianOf3(vector<int> &arr, int lo, int hi) {
    int mid = lo + (hi-lo)/2;

    if(arr[lo] > arr[hi])
      swap(arr[lo], arr[hi]);

    if(arr[lo] > arr[mid])
      swap(arr[lo], arr[mid]);

    if(arr[mid] > arr[hi])
      swap(arr[mid], arr[hi]);

    return mid;
  }

  int randomPartition(vector<int> &arr, int lo, int hi) {
    int pivotIndex = medianOf3(arr, lo, hi); // you can also choose any other pivot
    swap(arr[pivotIndex], arr[hi]);         // you like, but then it might be
    int correctPivotIndex = lo;             // detetministic, not random.

    for(int i=lo; i<hi; i++) // Lomuto scheme
      if(arr[i] <= arr[hi])
        swap(arr[i], arr[correctPivotIndex++]);

    swap(arr[hi], arr[correctPivotIndex]);

    return correctPivotIndex;
  }

  int quickselect(vector<int> &arr, int k, int lo, int hi) {
    if(lo == hi)
      return arr[lo];

    int pivotIndex = randomPartition(arr, lo, hi);
    int sizeLeft = pivotIndex - lo + 1;

    if(sizeLeft == k)
      return arr[pivotIndex];
    else if(sizeLeft > k)
      return quickselect(arr, k, lo, pivotIndex - 1);
    else
      return quickselect(arr, k - sizeLeft, pivotIndex + 1, hi);
  }
}

/**
 * 5. Median of Medians (BFPRT Algorithm).
 * O(n) worst case running time.
 */

int main() {

  vector<int> arr = {12, 3, 5, 7, 19, 15};

  cout << "Array: " << arr << ", k = 4" << endl;

  cout << "Kth smallest element is " << kthSmallestHeapSelect(arr, 4) << " (Heapselect)" << endl;
  cout << "Kth smallest element is " << kthSmallestSoftHeap(arr, 4) << " (Soft Heaps)" << endl;
  cout << "Kth smallest element is " << Quickselect::quickselect(arr, 4, 0, arr.size()-1) << " (Quickselect)" << endl;
  cout << "Array after quickselect: " << arr << endl;

  return 0;
}
