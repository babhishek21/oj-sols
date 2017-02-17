/**
 * Rolling Median in an infinite Data Stream
 * There is a LeetCode problem for this: https://leetcode.com/problems/find-median-from-data-stream/
 * A companion question for this is: https://leetcode.com/problems/sliding-window-median
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define INF 0x3f3f3f3f
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

priority_queue<int> lo; // max heap
priority_queue<int, vector<int>, greater<int>> hi; // min heap

void printHeaps() {
  vector<int> temp;

  while(!lo.empty()) {
    temp.pb(lo.top());
    lo.pop();
  }
  // whole(reverse, temp);
  cout << "MaxHeap lo: " << temp << endl;
  for(auto&& t: temp)
    lo.push(t);

  temp.clear();

  while(!hi.empty()) {
    temp.pb(hi.top());
    hi.pop();
  }
  cout << "MinHeap hi: " << temp << endl;
  for(auto&& t: temp)
    hi.push(t);
}

// Adds a number into the data structure.
void addNum(int num) {
  lo.push(num);
  hi.push(lo.top());
  lo.pop();

  if(lo.size() < hi.size()) {
    lo.push(hi.top());
    debug(hi.top())
    hi.pop();
  }
}

// Returns the median of current data stream
double findMedian() {
    return lo.size() > hi.size() ? (double)lo.top() : (lo.top() + hi.top())*0.5;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  for(int i=0; i<10; i++) {
    int temp = rand()&127;
    cout << "=======================\nAdding number " << temp << endl;
    addNum(temp);
    printHeaps();
    cout << "Median is " << findMedian() << endl;
  }

  return 0;
}
