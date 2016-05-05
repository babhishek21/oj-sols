/**
 * Binary Min Heap. And also HeapSort.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

class MinHeap {
  int *heapArr;
  int heapCapacity;
  int heapSize;

public:
  MinHeap(int capacity) {
    heapSize = 0;
    heapCapacity = capacity;
    heapArr = new int[capacity];
  }

  int parent(int index) {
    return (index-1)/2;
  }

  int left(int index) {
    return 2*index + 1;
  }

  int right(int index) {
    return 2*index + 2;
  }

  int getMin() {
    return heapArr[0];
  }

  int insertKey(int key) {
    if(heapSize == heapCapacity)
      return -1; // overflow

    // add to end of heap
    int i = ++heapSize;
    heapArr[i] = key;

    // fix the min heap property
    while(i != 0 && heapArr[parent(i)] > heapArr[i]) {
      swap(heapArr[parent(i)], heapArr[i]);
      i = parent(i);
    }

    return i;
  }

  int updateKey(int i, int newKey) {
    heapArr[i] = newKey;

    // fix the min heap property
    while(i != 0 && heapArr[parent(i)] > heapArr[i]) {
      swap(heapArr[parent(i)], heapArr[i]);
      i = parent(i);
    }

    return i;
  }

  int extractMin() {
    if(heapSize <= 0)
      return numeric_limits<int>::max(); // INT_MAX

    if(heapSize == 1)
      return heapArr[--heapSize]; // return root of complete heap

    // get and store mininum value
    int root = getMin();
    heapArr[0] = heapArr[--heapSize]; // get last element and store in first. also decrement size
    // heapify again
    MinHeapify(0);

    return root;
  }

  int deleteKey(int i) {
    int key = heapArr[i];
    updateKey(i, numeric_limits<int>::min()); // set to INT_MIN
    extractMin(); // remove min value from heap
    return key;
  }

  void MinHeapify(int i) {
    // recursive method to heapify a subtree rooted at index i
    int l = left(i), r = right(i);
    int smallestElement = i;

    if(l < heapSize && heapArr[l] < heapArr[i])
      smallestElement = l;
    if(r < heapSize && heapArr[r] < heapArr[smallestElement])
      smallestElement = r;

    if(smallestElement != i) {
      swap(heapArr[i], heapArr[smallestElement]);
      MinHeapify(smallestElement);
    }
  }
};



int main() {
  int arr[] = {3, 2, 1, 5, 6, 4, 7};

  // MinHeap *myHeap = new MinHeap();
  MinHeap myHeap(16);

  for(int i=0; i<(sizeof(arr)/sizeof(arr[0])); i++)
    myHeap.insertKey(arr[i]);

  cout << "extractMin: " << myHeap.extractMin() << endl;
  cout << "getMin: " << myHeap.getMin() << endl;

  myHeap.updateKey(2, 1);
  cout << "getMin after decrement: " << myHeap.getMin() << endl;

  cout << "Rest of the heap: ";
  for(int i=0; i<(sizeof(arr)/sizeof(arr[0]))-1; i++)
    cout << myHeap.extractMin() << " ";
  cout << endl;

  return 0;
}
