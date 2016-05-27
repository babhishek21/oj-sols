/**
 * This solution uses two BFS to find the diameter of
 * the tree-graph.
 * This works because, the first BFS finds a leaf node
 * at the farthest distance from an aribtrary starting
 * node. When we run the second BFS from this leaf node,
 * it will find another farthest leaf node, hence giving
 * the diameter.
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

vector<int> graph[10010];
bool done[10010];
int dist[10010];
int max_dist, farthest;

void bfs(int size, int start) {
  // fix done[] and dist[]
  for(int i=0; i<size+1; i++) {
    done[i] = false;
    dist[i] = 0;
  }

  queue<int> que;

  // push starting node in queue
  que.push(start);
  done[start] = true;

  // start iteration
  while(!que.empty()) {
    int curr = que.front();
    que.pop();

    for(auto x: graph[curr]) {
      if(!done[x]) {
        que.push(x);
        dist[x] = dist[curr] + 1;
        done[x] = true;
      }
    }
  }

  max_dist = 0;
  for(int i=1; i<size+1; i++) {
    max_dist = max(max_dist, dist[i]);
    farthest = (max_dist == dist[i]) ? i : farthest;
  }
}


int main() {
  int n, u, v;

  cin >> n;

  for(int i=0; i<n-1; i++) {
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  // run bfs
  bfs(n, 1);
  // run again
  bfs(n, farthest);

  cout << max_dist << endl;

  return 0;
}
