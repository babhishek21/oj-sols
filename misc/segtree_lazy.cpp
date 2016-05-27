/**
 * Segement Trees. Minimal Range Sum Query.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

int *tree, *A;
bool *lazy; // boolean array. if True: Needs to be updated

// init the segtree
// size of array A is `N`
void initTree(int N, bool isLazy) {
  int sizeForTree = 1;
  while(sizeForTree < N)
    sizeForTree <<= 1;

  tree = new int[sizeForTree];
  if(isLazy)
    lazy = new bool[sizeForTree];
}

// build it once array A is ready
void buildTree(int node, int start, int end) {
  if(start == end)
    tree[node] = A[start]; // leaf node
  else {
    int mid = start + (end-start)/2;

    // build two children nodes
    buildTree(2*node+1, start, mid); // left child at 2*index+1
    buildTree(2*node+2, mid+1, end); // right child at 2*index+2

    // write merge logic here
    tree[node] = tree[2*node+1] + tree[2*node+2];
  }
}

// update a single element and recursively fix the tree
void updateTree(int node, int start, int end, int index, int newVal) {
  if(start == end)
    tree[node] = A[index] = newVal;
  else {
    int mid = start + (end-start)/2;

    // find the correct subtree to fix/update
    if(start <= index && index <= mid) // left subtree
      updateTree(2*node+1, start, mid, index, newVal);
    else                               // right subtree
      updateTree(2*node+2, mid+1, end, index, newVal);

    // write merge logic here
    tree[node] = tree[2*node+1] + tree[2*node+2];
  }
}

// OR update an entire range lazily
// assuming the value `addVal` is ADDED to entire range.
void updateTreeLazyRange(int node, int start, int end, int l, int r, int addVal) {
  // check if node need to be updated since last lazy call
  if(lazy[node]) {
    tree[node] += addVal;
  }

  // if node is completely oustside range
  if(start > end || start > r || end < l)
    return;

  // check if leaf node
  if(start == end) {
    tree[node] = newVal;
    return;
  }

  // not a leaf node. Recurse for children
  int mid = start + (end-start)/2;
  updateTreeLazyRange(2*node+1, start, mid, l, r, newVal);
  updateTreeLazyRange(2*node+2, mid+1, end, l, r, newVal);

  // write merge logic here
  tree[node] = tree[2*node+1] + tree[2*node+2];
}

// query an entire range
int queryTree(int node, int start, int end, int l, int r) { // query on l-r range
  // check if node completely outside range
  if(start > r || end < l)
    return 0; // or whatever program logic suggests

  // check if completely inside range
  if(l <= start && end <= r)
    return tree[node];

  // partial overlap of ranges. Need to recurse
  int mid = start + (end-start)/2;
  int leftQuery = queryTree(2*node+1, start, mid, l, r);
  int rightQuery = queryTree(2*node+2, mid+1, end, l, r);

  // write merge logic here
  return leftQuery + rightQuery;
}

int main() {



  return 0;
}
