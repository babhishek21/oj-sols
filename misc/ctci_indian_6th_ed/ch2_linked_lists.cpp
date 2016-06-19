#include <bits/stdc++.h> // using GCC/G++
using namespace std;

// linked list node class
class Node {
public:
  int val;
  Node *next;

  Node(int x) {
    val = x;
    next = nullptr;
  }
};

/**
 * 2.1 Remove Duplicates
 * O(N^2) time algorithm
 */
void removeDuplicates(Node *head) {
  Node *curr = head;

  while(curr->next) {
    Node *scout = curr;

    while(scout->next) {
      if(scout->next->val == curr->val) {
        scout->next = scout->next->next;
      }
      scout = scout->next;
    }

    curr = curr->next;
  }
}
/*
 * Alternate approach with Hash Table/Set
 * O(n) run time + O(n) extra space
 */
void removeDuplicatesSet(Node *head) {
  unordered_set<int> HashSet;
  Node *curr = head;
  HashSet.insert(curr->val);

  while(curr->next) {
    if(HashSet.find(curr->next->val) != HashSet.end())
      curr->next = curr->next->next;
    else
      HashSet.insert(curr->next->val);

    curr = curr->next;
  }
}

/**
 * 2.2 Kth to Last Element
 * O(n) algorithm with two pointers
 */
Node* kthToLast(Node *head, unsigned int k) {
  Node *curr = head, *ret = nullptr;
  unsigned int count = 0;

  while(curr) {
    count++;

    if(count >= k) {
      if(count == k) ret = head;
      ret = ret->next;
    }

    curr = curr->next;
  }

  return ret;
}

/**
 * 2.3 Delete Middle Node
 * O(1) time algorithm. Not really
 * deleting the node, just overwriting.
 */
void deleteMiddleNode(Node *node) {
  Node *temp = node->next;
  node->val = temp->val;
  node->next = temp->next;
  delete temp; // No GC in C++
}

/**
 * 2.4 Partition List
 * O(n) time algo with O(n) extra space
 * This paritioning is unstable.
 */
Node* partitionList(Node *head, int pivot) {
  Node *newHead = head, *newTail = head, *curr=head;

  while(curr) {
    Node *temp = curr;
    if(curr->val < pivot) {
      curr->next = newHead;
      newHead = curr;
    } else {
      newTail->next = curr;
      newTail = newTail->next;
    }
    curr = temp->next;
  }

  newTail->next = nullptr;
  return newHead;
}

/**
 * 2.5 Sum Lists
 * Case 1: Numbers stored in reverse order
 * O(max(n, m)) iterative algorithm
 * with O(max(n, m)) extra space
 */
Node* listSum(Node *a, Node *b) {
  if(!a) return b;
  if(!b) return a;

  Node *newHead, *curr, *curra = a, *currb = b;
  int carry = 0, temp;

  while(curra || currb) {
    temp = (curra ? curra->val : 0) + (currb ? currb->val : 0);
    curr = new Node(temp%10 + carry);

    if(!newHead)
      newHead = curr;

    carry = temp/10;
    curr = curr->next;
  }

  if(carry > 0)
    curr = new Node(carry);

  return newHead;
}

/**
 * 2.5 Sum Lists
 * Case 2: Numbers stored in normal decimal order
 *
 */
Node* listSumRec(Node *a, Node *b) {
  int lena = getLen(a), lenb = getLen(b);
}


int main() {


  return 0;
}
