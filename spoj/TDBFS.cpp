/**
 * Problem: TDBFS (SPOJ)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

unordered_map<int, vector<int>> g;
unordered_set<int> visited;
queue<int> que;
stack<int> st;

void bfs(int src) {
  visited.clear();
  queue<int>().swap(que);

  que.push(src);
  visited.insert(src);

  while(!que.empty()) {
    int curr = que.front();
    que.pop();

    printf("%d ", curr);

    for(auto&& next: g[curr]) {
      if(visited.count(next) <= 0) {
        que.push(next);
        visited.insert(next);
      }
    }
  }

  printf("\n");
}

void dfsrec(int src) { // iterative dfs gives output in non-acceptable order
  printf("%d ", src);
  visited.insert(src);

  for(auto&& next: g[src]) {
    if(visited.count(next) <= 0) {
      dfsrec(next);
    }
  }
}

int main() {
  int t, n, m, u, v;

  scanf("%d", &t);

  for(int tc = 0; tc < t; tc++) {
    g.clear();
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
      scanf("%d %d", &u, &m);

      while(m--) {
        scanf("%d", &v);
        g[u].pb(v);
      }
    }

    cout << "graph " << tc+1 << endl;

    scanf("%d %d", &u, &v);
    while((u != 0) || (v != 0)) {
      if(v == 0) {
        visited.clear();
        dfsrec(u);
        printf("\n");
      }
      else
        bfs(u);

      scanf("%d %d", &u, &v);
    }
  }

  return 0;
}
