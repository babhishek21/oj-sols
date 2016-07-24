/**
 * Topological Sort of a DAG
 */
#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

// pretty print cutom class for showing order in topological sorts
struct MyDelims {
  static const pretty_print::delimiters_values<char> values;
};
const pretty_print::delimiters_values<char> MyDelims::values = { "", " -> ", "" };

// Graph in global scope
int V, E; // vertices and edges
unordered_map<int, vector<int>> g; // adjacency list for Directed Graph
unordered_set<int> visited; // visited set to prevent cycles
stack<pair<bool, int>> st; // for dfs. Boolean tells me whether node is for postprocessing
vector<int> indegree; // for indegree of a node
queue<int> que; // for Kahn's algo bfs based on indegree

/**
 * 1. DFS based solution
 * TOPOLOGICAL-SORT(V, E):
 *   1. Call DFS(V, E) to compute finishing times f[v] for all v in V
 *   2. Output vertices in order of decreasing finish times
 */
vector<int> toposort() {
  stack<pair<bool, int>>().swap(st);
  visited.clear();

  vector<int> topo_order;

  for(int i=0; i<V; i++) {
    if(visited.count(i) <= 0)
      st.emplace(false, i);

    while(!st.empty()) {
      auto node = st.top();
      st.pop();

      if(node.first) {
        topo_order.push_back(node.second);
        continue;
      }

      visited.insert(node.second);
      st.emplace(true, node.second);

      for(auto &j: g[node.second])
        if(visited.count(j) <= 0)
          st.emplace(false, j);
    }
  }

  reverse(topo_order.begin(), topo_order.end());
  return topo_order;
}

/**
 * 2. Kahn's Algorithm.
 * TOPOLOGICAL-SORT-KAHN(V, E):
 *   1. Compute indegree[v] for all v in V. Pick all those v with indegree[v] = 0 and put them in a queue
 *   2. Until queue is empty:
 *     2.1 Decrease indegree[u] for all neighbours u of v
 *     2.2 If indegree[u] = 0, put it in queue
 *   3. When done, if all nodes are visited, we have a valid topological sort
 */
namespace Kahn {
  void computeIndegrees() {
    indegree.clear();
    indegree.resize(V, 0);

    for(auto &tup: g)
      for(auto &v: tup.second)
        indegree[v]++;
  }

  vector<int> toposort() {
    computeIndegrees();

    queue<int>().swap(que);
    visited.clear();

    for(int i=0; i<V; i++)
      if(indegree[i] == 0)
        que.push(i);

    vector<int> topo_order;

    while(!que.empty()) {
      int u = que.front();
      que.pop();

      topo_order.push_back(u);
      visited.insert(u);

      for(auto &v: g[u])
        if(--indegree[v] == 0)
          que.push(v);
    }

    return topo_order;
  }
}

int main() {
  V = 8, E = 12;
  g[0] = {1, 2};
  g[1] = {2, 3};
  g[2] = {3, 4, 7};
  g[3] = {4};
  g[4] = {5};
  g[5] = {6, 7};
  g[7] = {6};

  cout << "Topological sort on graph is: " << pretty_print::custom_delims<MyDelims>(toposort()) << endl;
  // assert [0, 1, 2, 3, 4, 5, 7, 6] (left most has no in degree and righmost has no out degree)

  auto v = Kahn::toposort();
  cout << "\nTesting Kahn's algo: Does a topological ordering exist? " << boolalpha << (visited.size() == V) << endl
      << "Topological sort on graph is: " << pretty_print::custom_delims<MyDelims>(v) << endl;
      // assert [0, 1, 2, 3, 4, 5, 7, 6]

  return 0;
}
