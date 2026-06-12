#include <bits/stdc++.h> // using GCC/G++
using namespace std;

// 1-indexed BIT / Fenwick Tree

inline int lsb(int x) { return x & -x; }

// read accumulation of data from 1..idx
long long query(vector<long long>& bit, int idx) {
  long long sum = 0;

  while(idx > 0) {
    sum += bit[idx];
    idx -= lsb(idx);
  }

  return sum;
}

// update the tree when original data at idx changes by +val
void update(vector<long long>& bit, int idx, long long val) {
  while(idx <= bit.size()-1) {
    bit[idx] += val;
    idx += lsb(idx);
  }
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  int n, q, l, r, x;
  char op;

  cin >> n;
  vector<long long> bit(n+1, 0LL);	// fenwick tree

  for(int i=0; i<n; i++) {
  	cin >> x;
  	update(bit, i+1, x);
  }

  cin >> q;

  while(q--) {
  	cin >> op >> l >> r;

  	if(op == 'u')
  		update(bit, l, r);
  	else if(op == 'q')
  		cout << (query(bit, r) - query(bit, l-1)) << '\n';
  }

  return 0;
}