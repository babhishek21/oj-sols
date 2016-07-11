/**
 * All major comparison sorts.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/* Utils */
// just for reference. C++ inbuilt swap is great!
void mySwap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void printArr(int arr[], int n) {
  for(int i=0; i<n; i++)
    cout << arr[i] << " ";
  cout << endl;
}

/* Bubble Sort */
void bubbleSort(int arr[], int n) {
  for(int i=0; i<n-1; i++)
    for(int j=0; j<n-i-1; j++) { // last i elements already in place
      if(arr[j] > arr[j+1])
        swap(arr[j], arr[j+1]);
    }
}

/* Insertion Sort */
void insertionSort(int arr[], int n) {
  for(int i=0; i<n; i++) {
    int key = arr[i]; // assuming all elements to the left of key are sorted
    int j = i-1;
    while(j >= 0 && arr[j] > key) {
      arr[j+1] = arr[j];
      j--;
    }
    arr[++j] = key;
  }
}

/* Selection Sort */
void selectionSort(int arr[], int n) {
  int min_idx; // min swappable index
  for(int i=0; i<n-1; i++) {
    min_idx = i;
    for(int j=i+1; j<n; j++) // find index of minimum swappable element
      min_idx = (arr[j] < arr[min_idx]) ? j : min_idx;
    swap(arr[i], arr[min_idx]);
  }
}

/* Merge Sort */
void merge(int arr[], int lo, int hi) {
  int mid = lo + (hi-lo)/2;
  int lenl = mid-lo+1, lenr = hi-mid;

  // temp arrays
  int l[lenl], r[lenr];
  // copy data
  memcpy(l, (arr+lo), sizeof(arr[0])*(lenl));
  memcpy(r, (arr+mid+1), sizeof(arr[0])*(lenr));

  // printArr(l, lenl);
  // printArr(r, lenr);

  // set pointers/indexes
  int i=0, j=0, k=lo;

  // compare and assign
  while((i < lenl) && (j < lenr)) {
    if(l[i] <= r[j]) arr[k++] = l[i++];
    else arr[k++] = r[j++];
  }

  // take care of leftovers
  while(i < lenl)
    arr[k++] = l[i++];
  while(j < lenr)
    arr[k++] = r[j++];
}

void mergeSort(int arr[], int lo, int hi) {
  if(!(lo < hi)) return;

  int mid = lo + (hi-lo)/2;
  mergeSort(arr, lo, mid);
  mergeSort(arr, mid+1, hi);

  merge(arr, lo, hi);
}

/* Quick Sort */
int partition(int arr[], int lo, int hi) {
  // Lomuto Scheme
  int pivot = arr[hi]; // choose pivot here. By default, last element.
  int i = lo-1; // leftmost swappable element
  for(int j=lo; j<hi; j++) {
    if(arr[j] <= pivot)
      swap(arr[++i], arr[j]);
  }
  swap(arr[++i], arr[hi]); // fix pivot's correct place
  return i;

  // Hoare scheme
  // int pivot = arr[lo];
  // int i = lo-1, j = hi+1;
  // while(true) {
  //   // look for inversions
  //   do {
  //     i++;
  //   } while(arr[i] < pivot);

  //   do {
  //     j--;
  //   } while(arr[j] > pivot);

  //   // fix inversion
  //   if(i < j)
  //     swap(arr[i], arr[j]);
  //   else
  //     return j;
  // }
}

void quickSort(int arr[], int lo, int hi) {
  if(!(lo < hi)) return;

  int pivot = partition(arr, lo, hi);
  quickSort(arr, lo, pivot-1);
  quickSort(arr, pivot+1, hi);
}

/* Heap Sort */
void maxHeapify(int arr[], int n, int i) {
  int l = 2*i+1, r = 2*i+2, largestElement = i;

  if(l < n && arr[l] > arr[largestElement])
    largestElement = l;
  if(r < n && arr[r] > arr[largestElement])
    largestElement = r;

  if(largestElement != i) {
    swap(arr[i], arr[largestElement]);

    // maintain the max heap property
    maxHeapify(arr, n, largestElement);
  }
}

int heapSort(int arr[], int n) {
  // rearrage array to make max heap
  for(int i = n/2-1; i>=0; i--)
    maxHeapify(arr, n, i);

  // now we know that the top most element of
  // the max heap is the largest. So we exttract it
  // from the heap and emplace it at the end
  // (which is its correct place in array). Similarly
  // do this for entire array.

  for(int i=n-1; i>=0; i--) {

    // move current root (max out-of-place element) to end
    swap(arr[0], arr[i]);

    // call maxHeapify to maintain heap property
    // on reduced heap
    maxHeapify(arr, i, 0);
  }
}

/* Main */
int main() {
  int orig[] = {5, 6, 9, 2, 8, 1, 3, 7, 4, 0};
  int n = sizeof(orig)/ sizeof(orig[0]);
  printArr(orig, n);

  int arr[n];

  memcpy(arr, orig, sizeof(orig[0])*n);
  bubbleSort(arr, n);
  printArr(arr, n);

  memcpy(arr, orig, sizeof(orig[0])*n);
  insertionSort(arr, n);
  printArr(arr, n);

  memcpy(arr, orig, sizeof(orig[0])*n);
  selectionSort(arr, n);
  printArr(arr, n);

  memcpy(arr, orig, sizeof(orig[0])*n);
  mergeSort(arr, 0, n-1);
  printArr(arr, n);

  memcpy(arr, orig, sizeof(orig[0])*n);
  quickSort(arr, 0, n-1);
  printArr(arr, n);

  memcpy(arr, orig, sizeof(orig[0])*n);
  heapSort(arr, n);
  printArr(arr, n);

  return 0;
}
