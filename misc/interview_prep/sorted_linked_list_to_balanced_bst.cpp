/**
 * Convert sorted linked list to balanced BST
 * http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/
 */
#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

class ListNode {
public:
  int val;
  ListNode *next = nullptr;
  ListNode(int val): val(val) {}
};

class TreeNode {
public:
  int val;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int val): val(val) {}
};

int getLen(ListNode *head) {
  if(!head) return 0;
  return 1 + getLen(head->next);
}

ostringstream printList(ListNode *head) {
  ostringstream out;

  out << "HEAD -> ";
  while(head) {
    out << head->val << " -> ";
    head = head->next;
  }
  out << "NULL";

  return out;
}

ostringstream inorderPrint(TreeNode *root) {
  ostringstream out;

  if(!root) return out;

  out << inorderPrint(root->left).str();
  out << root->val << " ";
  out << inorderPrint(root->right).str();

  return out;
}

/**
 * The idea is similar to what we do with sorted array.
 * Let count of nodes be n. First we recursively construct the left
 * subtree with n/2 node. Then allocate the root node. and finally
 * recursively build the right subtree. This is inorder building.
 * Keeping track of the head pointer as the recursion takes place
 * helps to reduce run time complexity to O(n) from O(nlogn), for
 * preorder build. This however misplaces the list in memory, unless
 * a copy of the head is seperatly saved.
 */
TreeNode* sortedListToBST(ListNode *&head, int len) {
  if(len <= 0) return nullptr;

  // contruct left subtree
  TreeNode *temp = sortedListToBST(head, len/2);

  // make root
  TreeNode *root = new TreeNode(head->val);
  root->left = temp;

  // change head by reference (note pass by value won't work)
  head = head->next;

  // construct right subtree
  root->right = sortedListToBST(head, len-len/2-1);

  return root;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);

  cout << "Linked List: " << printList(head).str() << endl;

  TreeNode *root = sortedListToBST(head, getLen(head));
  cout << "Inorder of Tree: " << inorderPrint(root).str() << endl;

  return 0;
}
