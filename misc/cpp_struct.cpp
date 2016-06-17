#include <bits/stdc++.h> // using GCC/G++
using namespace std;

// sample linked list node struct
typedef struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x): val(x), next(nullptr) {};
} ListNode;

int main() {
  ListNode *head = new ListNode(3), *curr;
  head->next = new ListNode(5);
  head->next->next = new ListNode(4);

  curr = head;
  cout << "HEAD->";
  while(curr) {
    cout << curr->val << "->";
    curr = curr->next;
  }
  cout << "NULL" << endl;

  return 0;
}

/*

// C -style structs can behave like objects in C++
struct lol {
  int lolval;
  lol(int n): lolval(n) {} // this is apparantly a friggin' constructor
};                         // works like a class less object. WTF?

// make a new instance of lol
lol myNewLol(3); // this works in C++

// what if I want to use `new`?
// Make a friggin' pointer
lol *myNewLol = new lol(3);

[lang='hi'] bilkul object syntax bana diya.
[lang='hi'] DO alag alag syntax kaun rakhta hian? hadd hian :/

/////////////// After you are tired of this bullshit, let's see JAVA ////////

class lol {
  private int lolval;

  public lol(int n) {
    lolval = n;
  }

  public static void main(String args[]) throws Exception {
    lol myNewLol = new lol(3);
     // there is ONLY one syntax. this is how it should be!
  }
}

*/
