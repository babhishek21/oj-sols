/**
 * Binary Tree Traversals
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
  int val;
  TreeNode *left = nullptr, *right = nullptr, *parent = nullptr;

  TreeNode(int val): val(val) {}
};

/********** INORDER TRAVERSAL ***********/
namespace inorderTraversal {

  // 1. Recursive
  void helper(TreeNode *root, vector<int> &result) {
    if(!root) return;

    helper(root->left, result);
    result.push_back(root->val);
    helper(root->right, result);
  }

  vector<int> recursive(TreeNode *root) {
    vector<int> result;
    helper(root, result);
    return result;
  }

  // 2. Iterative with Stack
  vector<int> iterative(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while(curr || !st.empty()) {
      while(curr) {
        st.push(curr);
        curr = curr->left;
      }

      curr = st.top();
      st.pop();
      result.push_back(curr->val);

      curr = curr->right;
    }

    return result;
  }

  // 3. Morris Traversal (no extra space, O(2*n) - original algorithm for this use case)
  vector<int> Morris(TreeNode *root) {
    vector<int> result;
    TreeNode *curr = root, *pre;

    while(curr) {
      if(!curr->left) {
        result.push_back(curr->val);
        curr = curr->right;
      } else {

        // find inorder predecessor of curr in left subtree of curr
        pre = curr->left;
        while(pre->right && pre->right != curr)
          pre = pre->right;

        // set curr as predecessor's right child (threading)
        if(!pre->right) {
          pre->right = curr;
          curr = curr->left;
        }

        // revert changes made to tree
        else {
          pre->right = nullptr;

          result.push_back(curr->val);
          curr = curr->right;
        }
      }
    }

    return result;
  }
}

/********** PREORDER TRAVERSAL ***********/
namespace preordeTraversal {

  // 1. Recursive
  void helper(TreeNode *root, vector<int> &result) {
    if(!root) return;

    result.push_back(root->val);
    helper(root->left, result);
    helper(root->right, result);
  }

  vector<int> recursive(TreeNode *root) {
    vector<int> result;
    helper(root, result);
    return result;
  }

  // 2. Iterative with Stack
  vector<int> iterative(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while(curr || !st.empty()) {
      while(curr) {
        result.push_back(curr->val);
        st.push(curr);
        curr = curr->left;
      }

      curr = st.top();
      st.pop();

      curr = curr->right;
    }

    return result;
  }

  // 3. Morris Traversal (no extra space, O(2*n))
  vector<int> Morris(TreeNode *root) {
    vector<int> result;
    TreeNode *curr = root, *pre;

    while(curr) {
      if(!curr->left) {
        result.push_back(curr->val);
        curr = curr->right;
      } else {

        // find inorder predecessor to curr in left subtree of curr
        pre = curr->left;
        while(pre->right && pre->right != curr)
          pre = pre->right;

        // set curr as predecessor's right child (threading)
        if(!pre->right) {
          pre->right = curr;

          result.push_back(curr->val);
          curr = curr->left;
        }

        // revert changes made to tree
        else {
          pre->right = nullptr;
          curr = curr->right;
        }
      }
    }

    return result;
  }
}

/********** POSTORDER TRAVERSAL ***********/
namespace postorderTraversal {

  // 1. Recursive
  void helper(TreeNode *root, vector<int> &result) {
    if(!root) return;

    helper(root->left, result);
    helper(root->right, result);
    result.push_back(root->val);
  }

  vector<int> recursive(TreeNode *root) {
    vector<int> result;
    helper(root, result);
    return result;
  }

  // 2. Iterative with Stack
  vector<int> iterative(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> st;
    TreeNode *curr = root, *visited = nullptr;

    while(curr || !st.empty()) {
      while(curr) {
        st.push(curr);
        curr = curr->left;
      }

      curr = st.top();

      if(curr->right && curr->right != visited)
        curr = curr->right;
      else {
        result.push_back(curr->val);
        st.pop();

        visited = curr;
        curr = nullptr;
      }
    }

    return result;
  }

  // 3. Iterative with Stack (reverse process of Preorder)
  vector<int> iterativeReverse(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> st;
    TreeNode *curr = root, *visited = nullptr;

    while(curr || !st.empty()) {
      while(curr) {
        st.push(curr);
        result.push_back(curr->val);
        curr = curr->right;
      }

      curr = st.top();
      st.pop();

      curr = curr->left;
    }

    reverse(result.begin(), result.end());

    return result;
  }

  // 4. Morris Traversal (no extra space, O(2*n) - mirror approach of Morris traversal for Preorder)
  vector<int> Morris(TreeNode *root) {
    vector<int> result;
    TreeNode *curr = root, *pre;

    while(curr) {
      if(!curr->right) {
        result.push_back(curr->val);
        curr = curr->left;
      } else {

        // find inorder predecessor to curr in right subtree of curr
        pre = curr->right;
        while(pre->left && pre->left != curr)
          pre = pre->left;

        // set curr as predecessor's left child (threading)
        if(!pre->left) {
          pre->left = curr;

          result.push_back(curr->val);
          curr = curr->right;
        }

        // revert changes made to tree
        else {
          pre->left = nullptr;
          curr = curr->left;
        }
      }
    }

    reverse(result.begin(), result.end());

    return result;
  }
}

// TODO: Level order traversal

int main() {

  TreeNode *root = new TreeNode(4);
  root->left = new TreeNode(2);
  root->right = new TreeNode(5);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);

  cout << "Current Tree state:" << endl
      << "    4  " << endl
      << "   / \\" << endl
      << "  2   5" << endl
      << " / \\  " << endl
      << "1   3  " << endl;

  cout << "\nInorder traversals:" << endl
      << "1. Recursive: " << inorderTraversal::recursive(root) << endl
      << "2. Iterative: " << inorderTraversal::iterative(root) << endl
      << "3. Morris:    " << inorderTraversal::Morris(root) << endl;

  cout << "\nPreorder traversals:" << endl
      << "1. Recursive: " << preordeTraversal::recursive(root) << endl
      << "2. Iterative: " << preordeTraversal::iterative(root) << endl
      << "3. Morris:    " << preordeTraversal::Morris(root) << endl;

  cout << "\nPostorder traversals:" << endl
      << "1. Recursive: " << postorderTraversal::recursive(root) << endl
      << "2. Iterative: " << postorderTraversal::iterative(root) << endl
      << "3. Iterative: " << postorderTraversal::iterativeReverse(root) << " (reverse of Preorder)" << endl
      << "4. Morris:    " << postorderTraversal::Morris(root) << " (mirror of Preorder Morris traversal)" << endl;

  return 0;
}
