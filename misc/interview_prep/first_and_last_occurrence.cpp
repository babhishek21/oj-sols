/**
 * Find first and last occurrence of an element in a sorted array.
 * Expected complexity: O(log(n))
 */

#include <iostream>
#include <vector>
using namespace std;

template<typename T>
size_t find_first_of(vector<T> arr, T x) {
  size_t lo = 0, hi = arr.size()-1;

  while(lo <= hi) {
    size_t mid = lo + (hi - lo)/2;

    if((mid == 0 || arr[mid-1] < x) && arr[mid] == x)
      return mid;
    else if(arr[mid] < x)
      lo = mid+1;
    else    // arr[mid] >= x
      hi = mid-1;
  }

  throw out_of_range("Argument not found in input!"); // throw exception
}

template<typename T>
size_t find_last_of(vector<T> &arr, T x) {
  size_t lo = 0, hi = arr.size()-1;

  while(lo <= hi) {
    size_t mid = lo + (hi - lo)/2;

    if((mid == arr.size()-1 || arr[mid+1] > x) && arr[mid] == x)
      return mid;
    else if(arr[mid] > x)
      hi = mid-1;
    else    // arr[mid] <= x
      lo = mid+1;
  }

  throw out_of_range("Argument not found in input!"); // throw exception
}

int main() {
  vector<int> lol = {1, 2, 2, 2, 2, 3, 4, 7, 8, 8, 9};

  try {
    cout << find_first_of<int>(lol, 2) << endl;
    cout << find_first_of(lol, 8) << endl;       // implicit type `int` identified for template
    cout << find_first_of(lol, 1) << endl;       // arr bound checks
    cout << find_first_of(lol, 9) << endl;       // arr bound checks
    cout << find_first_of(lol, 5) << endl;       // this should throw an exception
    cout << find_first_of(lol, 8) << endl;       // this should never execute
  } catch(const exception& e) {
    cout << e.what() << endl;
  }

  try {
    cout << find_last_of<int>(lol, 2) << endl;
    cout << find_last_of(lol, 8) << endl;       // implicit type `int` identified for template
    cout << find_last_of(lol, 1) << endl;       // arr bound checks
    cout << find_last_of(lol, 9) << endl;       // arr bound checks
    cout << find_last_of(lol, 5) << endl;       // this should throw an exception
    cout << find_last_of(lol, 8) << endl;       // this should never execute
  } catch(const exception& e) {
    cout << e.what() << endl;
  }

  cout << "Done!" << endl;

  return 0;
}
