/**
 * DSU (Disjoint Set Union) structures
 * with two heuristics:
 * 1. union by rank
 * 2. path compression
 * Worst case running time: O(m, alpha(m,n))
 * where m = number of all operations
 * and n = number of create operations
 * and alpha(m,n) is inverse of Ackerman function
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

class DSU {
  int *parent, *rank, n;

public:
  DSU(int n) {
    this->n = n;
    parent = new int[n];
    rank = new int[n];
  }

  void createSet(int x) {
    parent[x] = x;
    rank[x] = 0;
  }

  int findSet(int x) {
    if(parent[x] != x)
      parent[x] = findSet(parent[x]);
    return parent[x];
  }

  void unionSet(int x, int y) {
    int px = findSet(x);
    int py = findSet(y);

    if(rank[px] > rank[py])
      parent[py] = px;
    else
      parent[px] = py;

    if(rank[px] == rank[py])
      rank[py]++;
  }

  void debugDump() {
    cout << "parent[" << n << "]: ";
    for(int i=0; i<n; i++)
      cout << parent[i] << " ";
    cout << endl << "rank[" << n << "]:   ";
    for(int i=0; i<n; i++)
      cout << rank[i] << " ";
    cout << endl;
  }

  ~DSU() {
    delete[] parent;
    delete[] rank;
  }
};

int main() {
  DSU mydsu(5);

  for(int i=0; i<5; i++)
    mydsu.createSet(i);

  mydsu.debugDump();

  mydsu.unionSet(0, 1);
  mydsu.debugDump();

  mydsu.unionSet(1, 2);
  mydsu.debugDump();

  mydsu.unionSet(3, 2);
  mydsu.debugDump();

  return 0;
}
