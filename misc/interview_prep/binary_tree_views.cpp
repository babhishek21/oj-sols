/**
 * Binary Tree views
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

class TreeNode {
public:
  int val, hd; // horizontal distance
  TreeNode *left = nullptr, *right = nullptr, *parent = nullptr;
  TreeNode(int val): val(val) {}
};

namespace BinaryTreeViews {

  /**
   * Left view
   */
  void leftViewHelper(TreeNode *root, int currLevel, int &maxLevel, vector<int> &result) {
    if(!root) return;

    if(currLevel > maxLevel) {
      result.push_back(root->val);
      maxLevel = currLevel;
    }

    leftViewHelper(root->left, currLevel+1, maxLevel, result);
    leftViewHelper(root->right, currLevel+1, maxLevel, result);
  }

  vector<int> leftView(TreeNode *root) {
    vector<int> result;
    int maxLevel = 0;
    leftViewHelper(root, 1, maxLevel, result);
    return result;
  }

  /**
   * Right view (like mirrored Left view)
   */
  void rightViewHelper(TreeNode *root, int currLevel, int &maxLevel, vector<int> &result) {
    if(!root) return;

    if(currLevel > maxLevel) {
      result.push_back(root->val);
      maxLevel = currLevel;
    }

    rightViewHelper(root->right, currLevel+1, maxLevel, result);
    rightViewHelper(root->left, currLevel+1, maxLevel, result);
  }

  vector<int> rightView(TreeNode *root) {
    vector<int> result;
    int maxLevel = 0;
    rightViewHelper(root, 1, maxLevel, result);
    return result;
  }

  /**
   * Bottom view (Level order / BFS)
   * The last node seen at that horizontal distance is
   * the one visible from the bottom
   */
  vector<int> bottomView(TreeNode *root) {
    vector<int> result;

    if(!root) return result;

    map<int, TreeNode *> treeMap; // sorted map
    queue<TreeNode *> que;
    TreeNode *curr;

    root->hd = 0;
    que.push(root);

    while(!que.empty()) { // level order/bfs
      curr = que.front();
      que.pop();

      treeMap[curr->hd] = curr;

      if(curr->left) {
        curr->left->hd = curr->hd-1;
        que.push(curr->left);
      }

      if(curr->right) {
        curr->right->hd = curr->hd+1;
        que.push(curr->right);
      }
    }

    for(auto &tup: treeMap)
      result.push_back(tup.second->val);

    return result;
  }

  /**
   * Top view (Level order / BFS)
   * The first node seen at that horizontal distance is
   * the one visible from the bottom
   */
  vector<int> topView(TreeNode *root) {
    vector<int> result;

    if(!root) return result;

    map<int, TreeNode *> treeMap; // ordered map
    queue<TreeNode *> que;
    TreeNode *curr;

    root->hd = 0;
    que.push(root);

    while(!que.empty()) {
      curr = que.front();
      que.pop();

      if(treeMap.count(curr->hd) <= 0) {
        treeMap[curr->hd] = curr;
      }

      if(curr->left) {
        curr->left->hd = curr->hd-1;
        que.push(curr->left);
      }

      if(curr->right) {
        curr->right->hd = curr->hd+1;
        que.push(curr->right);
      }
    }

    for(auto &tup: treeMap)
      result.push_back(tup.second->val);

    return result;
  }
}

int main() {

  TreeNode *root = new TreeNode(20);
  root->left = new TreeNode(8);
  root->right = new TreeNode(22);
  root->left->left = new TreeNode(5);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(4);
  root->right->right = new TreeNode(25);
  root->left->right->left = new TreeNode(10);
  root->left->right->right = new TreeNode(14);

  cout << "Current tree state: \n"
          "        20     ---> 20, 3, 4 are in same vertical position\n"
          "      / | \\        \n"
          "     /  |  \\       \n"
          "    8   |   22      \n"
          "   / \\  |  /  \\   \n"
          "  5   3 - 4    25   \n"
          "     / \\           \n"
          "   10   14  " << endl;

  cout << "Left View: " << BinaryTreeViews::leftView(root) << endl;
  cout << "Right View: " << BinaryTreeViews::rightView(root) << endl;
  cout << "Bottom View: " << BinaryTreeViews::bottomView(root) << endl;
  cout << "Top View: " << BinaryTreeViews::topView(root) << endl;

  return 0;
}
