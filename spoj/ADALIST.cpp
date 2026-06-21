/**
 * Problem: ADALIST (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 *
 * Can be solved:
 * - online, via sqrt decomposition (but might need rebalancing blocks often, after mass deletes/inserts)
 * - offline, using Segment trees or Fenwick trees; quite complicated since you need to preprocess all updates beforehand
 * - allegedly, with just your regular STL deque (with fast enough I/O, hopes and prayers)
 * - elegantly, using a Tree + Heap = Treap (or any self-balancing BST really)
 */

#include <bits/stdc++.h>             // using GCC/G++
// #include "custom/prettyprint.hpp"  // C++11 and above
// #include "custom/debugprint.hpp"   // debug printing utils
using namespace std;

#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)
#define debug(x) cerr << #x << " : " << x << endl
// #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

// Merge-Split Treap with randomly assigned priorities
// Mathematically speaking, this should keep the tree more or less balanced at all times.
namespace Treap {
  mt19937 rng(1337);

  struct Node {
    int val, prio, sz;
    Node *l, *r;

    Node(int v): val(v), prio(rng()), sz(1), l(nullptr), r(nullptr) {}
  };

  // Fast Bump allocator
  constexpr int MAXN = 600005;
  char buf[MAXN * sizeof(Node)];
  int buf_ptr = 0;

  inline Node* make_node(int val) {
    Node *n = new (&buf[buf_ptr]) Node(val);  // Placement new to avoid overhead of repeated malloc
    buf_ptr += sizeof *n;
    return n;
  }

  // inline void reset_buf() {
  //   buf_ptr = 0; // leaves garbage in buf[], ready to be overwritten
  // }

  inline int get_size(Node* n) {
    return n ? n->sz : 0;
  }

  inline void update_size(Node* n) {
    if(n)
      n->sz = 1 + get_size(n->l) + get_size(n->r);
  }

  // Split Treap rooted at Node n into two Treaps rooted at Nodes l and r.
  // Treap rooted at Node l eventually has the first k elements
  // Treap rooted at Node r eventually has the rest of the elements
  void split(Node *n, int k, Node* &l, Node* &r) {
    if(!n) {
      l = r = nullptr;
      return;
    }

    if(get_size(n->l) >= k) {
      r = n;
      split(n->l, k, l, r->l);  // split left subtree further
      update_size(r);
    } else {
      l = n;
      split(n->r, k - get_size(n->l) - 1, l->r, r);   // split right subtree further
      update_size(l);
    }
  }

  // Merge Treaps rooted at Nodes l and r
  Node* merge(Node *l, Node *r) {
    if(!l)
      return r;

    if(!r)
      return l;

    if(l->prio > r->prio) {   // essentially maintain heap invariant using random priorities
      l->r = merge(l->r, r);
      update_size(l);
      return l;
    } else {
      r->l = merge(l, r->l);
      update_size(r);
      return r;
    }
  }

  Node *treap_root = nullptr; // Treap instance root

  void insert(int k, int val) {       // insert val at 0-indexed position k
    Node *l = nullptr, *r = nullptr;
    split(treap_root, k, l, r);       // l has elements arr[0..k-1]

    Node* n = make_node(val);
    treap_root = merge(merge(l, n), r);
  }

  void erase(int k) {      // erase element at 0-indexed position k
    Node *l = nullptr, *r = nullptr, *n;
    split(treap_root, k, l, r);     // l has elements arr[0..k-1]

    split(r, 1, n, r);              // n has element arr[k], r has rest of arr[]
    treap_root = merge(l, r);
  }

  int query(int k) {    // get element value at 0-indexed position k
    Node *l = nullptr, *r = nullptr, *n;
    split(treap_root, k, l, r);     // l has elements arr[0..k-1]

    split(r, 1, n, r);              // n has element arr[k], r has rest of arr[]
    int res = n->val;

    treap_root = merge(l, merge(n, r));
    return res;
  }
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int n, q, op, k, x;

  cin >> n >> q;

  for(int i=0; i<n; i++) {
    cin >> x;
    Treap::insert(i, x);
  }

  while(q--) {
    cin >> op >> k;

    switch (op) {
      case 1:
        cin >> x;
        Treap::insert(k-1, x);
        break;

      case 2:
        Treap::erase(k-1);
        break;

      case 3:
        cout << Treap::query(k-1) << '\n';
    }
  }

  return 0;
}
