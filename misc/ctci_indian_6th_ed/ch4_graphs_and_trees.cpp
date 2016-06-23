/**
 * CTCI 6th (Indian) Edition.
 * Chapter 4: Graphs & Trees
 * C++11 or C++14 required
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

// Graph utils
class Graph {
public:
  int vertex;
  // typedef map<int, vector<int>> adj; // adjacency list
  map<int, set<int>> adjList;

  Graph(int v) {
    vertex = v;
  }

  void addEdge(int src, int dest, bool undirected = false) {
    if(src > vertex || dest > vertex)
      return;

    adjList[src].insert(dest);
    if(undirected)
      adjList[dest].insert(src);
  }

  void printGraph() {
    cout << "Graph = {" << endl;
    for(auto it: adjList) {
      cout << it.first << ": ";
      for(auto &to: it.second)
        cout << to << " ";
      cout << endl;
    }
    cout << "}" << endl;
  }
};

// Tree utils
class TreeNode {
public:
  int val;
  TreeNode *left, *right, *parent;

  TreeNode(int val) {
    this->val = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

enum TraversalOrder {preorder, inorder, postorder};

void traversalHelper(TreeNode *root, TraversalOrder ord) {
  if(root == nullptr)
    return;

  if(ord == preorder)
    cout << root->val << " ";

  traversalHelper(root->left, ord);

  if(ord == inorder)
    cout << root->val << " ";

  traversalHelper(root->right, ord);

  if(ord == postorder)
    cout << root->val << " ";
}

void printTree(TreeNode *root, TraversalOrder ord) {
  cout << "Tree: ";
  traversalHelper(root, ord);
}

/**
 * 4.1 Route between nodes
 * Using DFS.
 */
bool isReachable(Graph &g, int src, int dest) {
  bool visited[g.vertex] = {false};
  // fill_n(visited, sizeof visited / sizeof *visited, false);
  stack<int> processStack;

  processStack.push(src);

  while(!processStack.empty()) {
    int curr = processStack.top();
    processStack.pop();

    if(curr == dest)
      return true;

    if(!visited[curr]) {
      for(auto &to: g.adjList[curr]) {
        processStack.push(to);
      }
    }

    visited[curr] = true;
  }

  return false;
}

/**
 * 4.2 Create Minimal Tree (BST)
 */
TreeNode* minimalBST(int arr[], int start, int end) {
  if(end < start)
    return nullptr;

  int mid = (start + end)/2;
  TreeNode *ret = new TreeNode(arr[mid]);

  ret->left = minimalBST(arr, start, mid-1);
  ret->right = minimalBST(arr, mid+1, end);

  return ret;
}

int main() {
  cout << boolalpha;

  // isReachable test
  Graph g(4);
  g.addEdge(1,4);
  g.addEdge(2,3);
  g.addEdge(1,2);
  g.addEdge(3,4);

  g.printGraph();
  cout << "Is 4 reachable from 1? " << isReachable(g, 1, 4) << endl;
  cout << "Is 4 reachable from 2? " << isReachable(g, 2, 4) << endl;
  cout << "Is 3 reachable from 4? " << isReachable(g, 4, 3) << endl;

  // testing minimalBST
  int test[] = {1,2,3,4,5,6,7,8,9,10};
  TreeNode *testRoot = minimalBST(test, 0, (sizeof test / sizeof *test) - 1);
  cout << "Testing minimalBST:" << endl;
  printTree(testRoot, inorder);



  return 0;
}
