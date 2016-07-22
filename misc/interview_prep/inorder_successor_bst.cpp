/**
 * Next Greatest element in BST (Inorder successor)
 * http://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

class Node {
public:
  int val;
  Node *left = nullptr, *right = nullptr;
  Node(int val): val(val) {};
};

int getInorderSuccessor(Node *root, Node *node) {
  if(!node->right) {
    // successor is parent
    Node *curr = root, *succ = nullptr;
    while(curr) {
      if(curr->val > node->val) {
        succ = curr;
        curr = curr->left;
      } else if(curr->val < node->val)
        curr = curr->right;
      else
        break;
    }

    if(succ)
      return succ->val;
  } else {
    // get min val in right subtree
    Node *curr = node->right;
    while(curr->left)
      curr = curr->left;

    if(curr)
      return curr->val;
  }

  return numeric_limits<int>::max();
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  Node *root = new Node(20);
  root->right = new Node(22);
  root->left = new Node(8);
  root->left->left = new Node(4);
  root->left->right = new Node(12);
  root->left->right->left = new Node(10);
  root->left->right->right = new Node(14);

  cout << "Node => Inorder Successor" << endl;
  cout << root->val << " => " << getInorderSuccessor(root, root) << endl; // 22
  cout << root->left->left->val << " => " << getInorderSuccessor(root, root->left->left) << endl; // 8
  cout << root->left->val << " => " << getInorderSuccessor(root, root->left) << endl; // 10
  cout << root->left->right->right->val << " => " << getInorderSuccessor(root, root->left->right->right) << endl; // 20

  return 0;
}
