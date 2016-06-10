/**
 * Elementary counting and bit magic
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

// swap by XOR
#define XORSWAP(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))

/* Utils */
void printArr(int arr[], int n) {
  for(int i=0; i<n; i++)
    cout << arr[i] << " ";
  cout << endl;
}

/**
 * Array Shift taken from Programming Pearls (2nd Edition)
 * Circular shift an array of size n by m units to the right
 * Assumption: n > m
 */
void shiftArray(int arr[], int m, int n) {
  reverse(arr, arr+n);
  reverse(arr, arr+m);
  reverse(arr+m, arr+n);
}
// A circular left shift can also be accomplished as
// a circular right shift with different parameters

/**
 * Bit twiddling hacks
 */

// detect if a and b are of opposite signs
inline bool checkOppositePolarity(int x, int y) {
  return ((x ^ y) < 0);
}

// compute abs() without branching
inline unsigned int abs1(int x) {
  const int mask = x >> sizeof(int) * CHAR_BIT - 1; // CHAR_BIT found in <climits>
  // this is essentially: mask = x >> (4*8 - 1) = x >> 31
  // return (x + mask) ^ mask;
  return (x ^ mask) - mask;
}

// min() and max() without branching
inline int min1(int x, int y) {
  return y ^ ((x ^ y) & -(x < y));
}

inline int max1(int x, int y) {
  return x ^ ((x ^ y) & -(x < y));
}

// check if power of 2
inline bool isPowerOf2(unsigned int v) {
  return v && !(v & (v-1));
}

// count set bits (Kernighan method)
inline unsigned int bitsetCount(unsigned int v) {
  unsigned int c;
  for(c = 0; v; c++) {
    v &= v-1; // clear the least significant set(1) bit
  }
  return c;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};

  // circulate right thrice
  shiftArray(arr, 3, 5);
  printArr(arr, 5);

  // circulate left thrice
  shiftArray(arr, 5-3, 5);
  printArr(arr, 5);

  // abs1
  cout << abs1(-36) << endl;

  return 0;
}
