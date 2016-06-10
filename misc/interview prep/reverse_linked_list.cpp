/**
 * Reverse Singly Linked List when only HEAD is given
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Iterative
ListNode* reverseList(ListNode* head) {
  ListNode *current = head; // pointer to current head to be processed
  ListNode *previous = NULL; // pointer trailing behind current

  while(current != NULL) {
    ListNode *temp = current->next; // temporary pointer

    current->next = previous; // current will point next to previous

    previous = current; // current and previous pointers are shifter further
    current = temp;
  }

  // previous points to last element
  // point head to new head (i.e. previous)
  return head = previous;
}

// Recursive
ListNode* reverseList(ListNode* head) {
  if(head == NULL || head->next == NULL)
    return head;

  ListNode* nextHead = head->next;

  // current head points back to previous element (i.e. NULL)
  head->next = NULL;
  ListNode* newHead = reverseListRecur(nextHead); // recurse for every element left in the list
  nextHead->next = head; // Element after head points back to head

  return newHead;
}

