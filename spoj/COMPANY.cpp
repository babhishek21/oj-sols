#include <bits/stdc++.h>
using namespace std;

int useless[1001][1001];

void bfs(vector<int> *A, int start) {
  int visited[1001] = {0};
  queue<int> q;
  q.push(start);

  while(!q.empty()) {
    int x = q.front();
    visited[x] = 1;
    q.pop();

    for(int i=0; i<A[x].size(); i++) {
      if(!visited[A[x][i]]) {
        q.push(A[x][i]);
        visited[A[x][i]] = 1;
      } else {
        useless[start][A[x][i]] = 1;
      }
    }
  }
 }

int main() {
  int n, m, s, d;
  vector<int> *A = new vector<int>[1001];
  vector<pair<int, int>> useful;

  scanf("%d %d", &n, &m);

  for(int i=0; i<m; i++) {
    scanf("%d %d", &s, &d);
    A[s].push_back(d);
  }

  for(int i=0; i<n; i++) {
    bfs(A, i+1);
  }

  int ans = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<A[i+1].size(); j++) {
      if(useless[i+1][A[i+1][j]] == 0){
        ans++;
        useful.push_back(make_pair(i+1, A[i+1][j]));
      }
    }
  }

  printf("%d\n", ans);
  for(auto it = useful.begin(); it != useful.end(); it++) {
    printf("%d %d\n", it->first, it->second);
  }

  return 0;
}