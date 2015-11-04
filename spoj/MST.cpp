/**
 * Problem: Prim's MST (Lazy)
 * Lang: C++11
 */
#include <bits/stdc++.h>
using namespace std;

#define maxV 1001

vector<pair<int,int> > G[maxV]; // G[i] = edge from i to j costing $c
bool fin[maxV]; // keeps tracked of finished vertices
// p_q has format (cost, vertex). Cost is taken first so that std::greater<T> can be used
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> >> Que;

void Prim(int org) {
  // init
  long long cost = 0;
  Que.push(make_pair(0, org)); // give zero cost to origin vertex

  while(!Que.empty()) {
    pair<int,int> top = Que.top(); Que.pop();

    if(!fin[top.second]) {
      cost += top.first;
      fin[top.second] = true;
    }

    for(auto it = G[top.second].begin(); it != G[top.second].end(); it++) {
      if(!fin[it->first])
        Que.push(make_pair(it->second, it->first));
    }
  }

  cout << cost << endl;
}

int main() {
  int N, E;
  int src, dest, cost;

  cin >> N >> E;

  while(E--) {
    cin >> src >> dest >> cost;
    G[src].push_back(make_pair(dest, cost));
    G[dest].push_back(make_pair(src, cost));
  }

  Prim(1);

  return 0;
}