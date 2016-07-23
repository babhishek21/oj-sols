/**
 * CTCI 6th (Indian) Edition.
 * Chapter 2: Linked Lists
 * C++11 or C++14 required
 */
#include <bits/stdc++.h> // using GCC/G++11
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

  ~Node() {
    cout << "Deleting: " << this << ":" << this->val << endl;
    // for debugging
  }
};

// utils
void printList(Node* head, unsigned int limit = 15) {
  Node *curr = head;
  unsigned int count = 0;

  cout << "HEAD => ";
  while(curr != nullptr && count < limit) {
    cout << curr->val << " -> ";
    curr = curr->next;
    count++;
  }
  cout << (count >= limit ? "..." : "NULL") << endl;
}

void deleteList(Node* head, int limit = -1) {
  int count = 0;

  if(limit < 0)
    count = limit - 1;

  while(head != nullptr && count < limit) {
    Node *old = head;
    head = head->next;
    delete old;

    count += (limit < 0) ? 0 : 1;
  }
}

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

/**
 * 2.1 Remove Duplicates
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
    else {
      HashSet.insert(curr->next->val);
      curr = curr->next;
    }
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
      else ret = ret->next;
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
    Node *temp = curr->next;
    if(curr->val < pivot) {
      curr->next = newHead;
      newHead = curr;
    } else {
      newTail->next = curr;
      newTail = newTail->next;
    }
    curr = temp;
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

  Node *newHead = nullptr, *curr = new Node(0), *curra = a, *currb = b;
  int carry = 0, temp;

  while(curra || currb) {
    temp = (curra ? curra->val : 0) + (currb ? currb->val : 0);
    curr->next = new Node(temp%10 + carry);

    if(!newHead)
      newHead = curr->next;

    carry = temp/10;
    curr = curr->next;

    if(curra)
      curra = curra->next;

    if(currb)
      currb = currb->next;
  }

  if(carry > 0)
    curr = new Node(carry);

  return newHead;
}

/**
 * 2.5 Sum Lists
 * Case 2: Numbers stored in normal decimal order
 */
inline unsigned int getListLen(Node *node) {
  unsigned int ret = 0;
  while(node) {
    ret++;
    node = node->next;
  }
  return ret;
}

Node* listSumHelper(Node *a, Node *b, unsigned int la, unsigned int lb, int &carry) {
  if(la == 0 && lb == 0)
    return nullptr;

  Node *head = new Node(0);

  if(la > lb)
    head->next = listSumHelper(a->next, b, la-1, lb, carry);
  else if(lb > la)
    head->next = listSumHelper(a, b->next, la, lb-1, carry);
  else
    head->next = listSumHelper(a->next, b->next, la-1, lb-1, carry);

  int temp = (la >= lb ? a->val : 0) + (lb >= la ? b->val : 0) + carry;
  carry = temp/10;
  temp %= 10;

  head->val = temp;

  return head;
}

Node* listSumRec(Node *a, Node *b) {
  unsigned int lena = getListLen(a), lenb = getListLen(b);
  int carry = 0;

  Node *newHead = listSumHelper(a, b, lena, lenb, carry);

  if(carry > 0){
    Node *temp = new Node(carry);
    temp->next = newHead;
    newHead = temp;
  }

  return newHead;
}

/**
 * 2.6 Palindrome
 * Recursive strategy O(n) + O(n) call stack space
 */
Node* isListPalinHelper(Node *head, unsigned int len) {
  if(len < 1)
    return head;
  if(len == 1)
    return head->next;

  Node *ret = isListPalinHelper(head->next, len-2);

  if(ret == nullptr)
    return nullptr;

  if(head->val != ret->val)
    return nullptr;

  return (ret->next ? ret->next : ret);
}

bool isListPalin(Node* head) {
  unsigned int len = getListLen(head);

  return (isListPalinHelper(head, len) != nullptr);
}

/**
 * 2.7 Intersection of Lists
 * Simple O(m+n) time algorithm
 */
Node* listIntersection(Node *a, Node *b) {
  unsigned int alen = getListLen(a), blen = getListLen(b);
  Node *curra = a, *currb = b;

  while(alen > blen) {
    curra = curra->next;
    alen--;
  }

  while(blen > alen) {
    currb = currb->next;
    blen--;
  }

  while(curra && currb) {
    if(curra == currb)
      return curra;

    curra = curra->next;
    currb = currb->next;
  }

  return curra;
}

/**
 * 2.8 Loop Detection
 * Fast + slow pointer approach
 */
Node* getLoopHead(Node *head) {
  Node *fast = head, *slow = head;

  do {
    slow = slow->next;
    fast = fast->next->next;
  } while(slow != fast);

  slow = head;

  while(slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }

  return slow;
}

int main() {
  // set cout to display bool names instead of integer
  cout << boolalpha;

  // removing duplicates test
  Node* test = new Node(3);
  test->next = new Node(4);
  test->next->next = new Node(5);
  test->next->next->next = new Node(4);
  test->next->next->next->next = new Node(5);
  test->next->next->next->next->next = new Node(6);

  cout << "Testing removeDuplicates:" << endl
      << "Input list:" << endl;
  printList(test);
  removeDuplicates(test);
  cout << "Output list:" << endl;
  printList(test);

  test->next->next->next->next = new Node(4);
  test->next->next->next->next->next = new Node(3);

  cout << "Testing removeDuplicatesSet:" << endl
      << "Input list:" << endl;
  printList(test);
  removeDuplicatesSet(test);
  cout << "Output list:" << endl;
  printList(test);

  // kth to last test
  cout << "Testing kthToLast:" << endl
      << "Input list:" << endl;
  printList(test);
  cout << "1st last element: " << kthToLast(test, 1)->val << endl
      << "2nd last element: " << kthToLast(test, 2)->val << endl
      << "4th last element: " << kthToLast(test, 4)->val << endl;

  // delete Middle node test
  cout << "Testing deleteMiddleNode:" << endl
      << "Input list:" << endl;
  printList(test);
  deleteMiddleNode(test->next->next);
  cout << "Deleted 3rd node. Output list:" << endl;
  printList(test);

  // partition List test
  test->next->next->next = new Node(2);
  test->next->next->next->next = new Node(1);
  test->next->next->next->next->next = new Node(5);

  cout << "Testing partitionList:" << endl
      << "Input list:" << endl;
  printList(test);
  Node *newTest = partitionList(test, 3);
  cout << "Partitioned list about pivot value of 3. Output list:" << endl;
  printList(newTest);

  deleteList(newTest);

  // List Sum test
  // 356 + 4778 = 5134
  Node *aList = new Node(6);
  aList->next = new Node(5);
  aList->next->next = new Node(3);

  Node *bList = new Node(8);
  bList->next = new Node(7);
  bList->next->next = new Node(7);
  bList->next->next->next = new Node(4);

  cout << "Testing listSum:" << endl
      << "Input list:" << endl << "a: (356) ";
  printList(aList);
  cout << "b: (4778) ";
  printList(bList);
  test = listSum(aList, bList);
  cout << "Output list: (5134) " << endl;
  printList(test);

  deleteList(test);

  // List Sum Test (reversed)
  // 653 + 8774 = 9427
  bList->val = 9;

  cout << "Testing listSum:" << endl
      << "Input list:" << endl << "a: (653) ";
  printList(aList);
  cout << "b: (9774) ";
  printList(bList);
  test = listSumRec(aList, bList);
  cout << "Output list: (10427) " << endl;
  printList(test);

  deleteList(aList);
  deleteList(bList);

  // Palindrome test
  test->val = 7;
  test->next->val = 2;

  cout << "Testing isListPalin:" << endl
      << "Input list: ";
  printList(test);
  cout << "Output: " << isListPalin(test) << endl;

  test->next->next->val = 3;

  cout << "Testing isListPalin:" << endl
      << "Input list: ";
  printList(test);
  cout << "Output: " << isListPalin(test) << endl;

  test->next->val = 6;

  cout << "Testing isListPalin:" << endl
      << "Input list: ";
  printList(test);
  cout << "Output: " << isListPalin(test) << endl;

  test->next->val = 2;
  Node *temp = test->next->next;
  test->next->next = temp->next;

  cout << "Testing isListPalin:" << endl
      << "Input list: ";
  printList(test);
  cout << "Output: " << isListPalin(test) << endl;

  test->next->next = temp;

  // Intersection test
  aList = new Node(3);
  aList->next = new Node(1);
  aList->next->next = new Node(5);
  aList->next->next->next = new Node(9);
  aList->next->next->next->next = new Node(7);
  aList->next->next->next->next->next = new Node(2);
  aList->next->next->next->next->next->next = new Node(1);

  bList = new Node(4);
  bList->next = new Node(6);
  bList->next->next = aList->next->next->next->next;

  cout << "Testing listIntersection:" << endl
      << "Input List:" << endl
      << "a: ";
  printList(aList);
  cout << "b: ";
  printList(bList);
  newTest = listIntersection(aList, bList);
  cout << "Output: Intersection Point is: "
      << newTest << " : " << newTest->val << endl;

  // deleteList(bList);
  deleteList(aList);
  deleteList(bList,2);

  // Loop detection test
  test->next->val = 6;
  test->next->next->next->next->val = 4;
  test->next->next->next->next->next = new Node(1);
  test->next->next->next->next->next->next = new Node(8);
  test->next->next->next->next->next->next->next = new Node(5);
  test->next->next->next->next->next->next->next->next = test->next->next->next;

  cout << "Testing getLoopHead:" << endl
      << "Input List (cycled): ";
  printList(test);
  newTest = getLoopHead(test);
  cout << "Output: Cycle starting point is: "
      << newTest << " : " << newTest->val << endl;

  // cleanup
  deleteList(test, 8);

  return 0;
}
