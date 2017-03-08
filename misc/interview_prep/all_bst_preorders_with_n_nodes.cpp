/**
 * Problem: All BST Preorders (CSAcademy)
 * Description: Print preorder traversals of all possible BSTs that can be made with N distinct nodes comprising of the numbers 1 to N. Print them in lexicographical order. Try to print them in `O(|output|)` time complexity and `O(n)` space complexity.
 * Author: babhishek21 (thanks to wefgef)
 * Lang: C++11
 */

#include <bits/stdc++.h>
using namespace std;

void back(vector<int>& order, int low, int high, function<void()> callback) {
  if (low > high) {
    callback();
    return;
  }
  for (int root = low; root <= high; ++root) {
    order.push_back(root);
    back(order, low, root - 1, [&]() {
      back(order, root + 1, high, callback);
    });
    order.pop_back();
  }
}

void allBstPreorders(int n) {
  vector<int> order;
  back(order, 1, n, [&]() {
    for (auto val : order) {
     cout << val << " ";
    }
    cout << "\n";
  });
}

int main() {
  int N;
  cin >> N;
  allBstPreorders(N);
  return 0;
}

/**
 * NOTE: The order of the output is the `n`th Catalan number. (That is the number of unique BSTs that can be made with `n` nodes.)
 */
