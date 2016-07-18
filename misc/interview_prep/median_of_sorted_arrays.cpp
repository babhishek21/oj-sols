/**
 * Median of two Sorted arrays (Leetcode)
 * Divide and Conquer based Binary Search
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

template<class T>
ostream& operator << (ostream &stream, const vector<T> &values) {
  stream << "[ ";
  copy(begin(values), end(values), ostream_iterator<T>(stream, " "));
  stream << "]";
  return stream;
}

/**
 * Method 1: This is the same as finding the kth element of merged array
 * where k = (A.length + B.length)/2
 * O(log(m+n)) run time
 */
namespace medianDAC {
  int findKth(vector<int> &A, vector<int> &B, int k, int alo, int ahi, int blo, int bhi) {
    int alen = ahi-alo+1, blen = bhi-blo+1;

    if(alen == 0)
      return B[blo + k];
    if(blen == 0)
      return A[alo + k];
    if(k == 0)
      return min(A[alo], B[blo]);

    int amid = k * (alen/(alen + blen)),
        bmid = k - amid - 1;

    amid += alo;
    bmid += blo;

    if(A[amid] > B[bmid]) {
      // first division of A and second division of B
      k -= (bmid - blo + 1);
      blo = bmid+1;
      ahi = amid;
    } else {
      // second division of A and second division of B
      k -= (amid - alo + 1);
      alo = amid+1;
      bhi = bmid;
    }

    return findKth(A, B, k, alo, ahi, blo, bhi);
  }

  double medianOfSortedArrays(vector<int> &A, vector<int> &B) {
    int m = A.size(), n = B.size();

    if((m+n)%2 == 0) {
      return (findKth(A, B, (m+n)/2, 0, m-1, 0, n-1)
            + findKth(A, B, (m+n)/2-1, 0, m-1, 0, n-1)) / 2.0;
    } else
      return findKth(A, B, (m+n)/2, 0, m-1, 0, n-1);
  }
}

/**
 * Method 2: Alternate implementation for Method 1.
 */
namespace medianDACAlternate {
  int findKth(vector<int> &A, vector<int> &B, int k, int alo, int blo) {
    if(alo >= A.size()) // remaining part of A is empty
      return B[blo+k-1];

    if(blo >= B.size()) // remaining part of B is empty
      return A[alo+k-1];

    if(k == 1)
      return min(A[alo], B[blo]);

    int amid = numeric_limits<int>::max(), bmid = amid;
    if(alo+k/2-1 < A.size()) amid = A[alo+k/2-1];
    if(blo+k/2-1 < B.size()) bmid = B[blo+k/2-1];

    if(amid > bmid)
      return findKth(A, B, k-k/2, alo, blo+k/2);
    else
      return findKth(A, B, k-k/2, alo+k/2, blo);
  }

  double medianOfSortedArrays(vector<int> &A, vector<int> &B) {
    int m = A.size(), n = B.size();

    if((m+n)%2 == 0) {
      return (findKth(A, B, (m+n+1)/2, 0, 0)
            + findKth(A, B, (m+n+2)/2, 0, 0)) / 2.0;
    } else
      return findKth(A, B, (m+n+1)/2, 0, 0);
  }
}

int main() {
  vector<int> a = {1, 12, 15, 26, 38}, b = {2, 13, 17, 30, 45};

  cout << "Vector A: " << a << endl
      << "Vector B: " << b << endl;

  cout << "Median of these two sorted arrays:" << endl;
  cout << "Method 1: " << medianDAC::medianOfSortedArrays(a, b) << endl;
  cout << "Method 2: " << medianDACAlternate::medianOfSortedArrays(a, b) << endl;

  a = {12, 15, 38}, b = {13, 17, 30, 45};

  cout << "\nVector A: " << a << endl
      << "Vector B: " << b << endl;

  cout << "Median of these two sorted arrays:" << endl;
  cout << "Method 1: " << medianDAC::medianOfSortedArrays(a, b) << endl;
  cout << "Method 2: " << medianDACAlternate::medianOfSortedArrays(a, b) << endl;

  return 0;
}
