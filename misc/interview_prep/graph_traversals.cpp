/**
 * Graph Traversals
 */
#include <bits/stdc++.h> // using GCC/G++11
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

// Graph in global scope
int V, E; // vertices and edges
unordered_map<int, vector<int>> g; // adjacency list for Directed Graph
unordered_set<int> visited; // visited set to prevent cycles
vector<int> visit_order; // keep track of visit order
stack<int> st; // for dfs
queue<int> que; // for bfs

/**
 * 1. Depth First Search
 */
bool dfs(int src, int dest = V+1) {
  visited.clear();
  visit_order.clear(); // optional
  stack<int>().swap(st); // clear stack `st` by swapping it with an empty one

  st.push(src);

  while(!st.empty()) {
    int u = st.top();
    st.pop();

    if(visited.count(u) > 0) continue;

    visited.insert(u);
    visit_order.push_back(u); // optional

    if(u == dest) return true;

    for(auto &v: g[u])
      st.push(v);
  }

  return false;
}

/**
 * 2. Breadth First Search
 */
bool bfs(int src, int dest = V+1) {
  visited.clear();
  visit_order.clear(); // optional
  queue<int>().swap(que); // clear queue `que` by swapping it with an empty one

  que.push(src);

  while(!que.empty()) {
    int u = que.front();
    que.pop();

    if(visited.count(u) > 0) continue;

    visited.insert(u);
    visit_order.push_back(u); // optional

    if(u == dest) return true;

    for(auto &v: g[u])
      que.push(v);
  }

  return false;
}

int main() {

  // make graph
  V = 4; E = 6;
  g[0] = {1,2};
  g[1] = {2};
  g[2] = {3, 0};
  g[3] = {3};

  dfs(2,1);
  cout << "DFS on Graph: " << visit_order << endl;

  bfs(2,1);
  cout << "BFS on Graph: " << visit_order << endl;

  return 0;
}
