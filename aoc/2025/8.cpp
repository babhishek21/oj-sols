/**
 * Problem: Advent of Code 2025 - Day 8: Playground
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

#define OPS 1000

using pt = tuple<long, long, long>;
using sld = tuple<double, size_t, size_t>;  // straight line distance and indices of points

template <typename T>
typename enable_if<!is_same<T, string>::value, vector<T>>::type
split(const string &line, char delimiter = '\0') {
  vector<T> result;

  if (delimiter == '\0') {
    // Split on whitespace (original behavior)
    stringstream ss(line);
    copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(result));
  } else {
    // Split on delimiter using getline
    stringstream ss(line);
    string token;

    while (getline(ss, token, delimiter)) {
      if (!token.empty()) {
        stringstream token_ss(token);
        T value;

        // Use stream extraction for type conversion
        if (token_ss >> value) {
          result.push_back(std::move(value));
        }
      }
    }
  }

  return result;
}

double calc_sld(const pt& a, const pt& b) {
  long long dx = get<0>(a) - get<0>(b),
    dy = get<1>(a) - get<1>(b),
    dz = get<2>(a) - get<2>(b);

  return sqrt(static_cast<double>(dx*dx + dy*dy + dz*dz));
}

class DSU {
  vector<size_t> parent;

public:
  vector<int> sizes;

  DSU(size_t n) {
    parent = vector<size_t>(n);
    whole(iota, parent, 0);

    sizes = vector<int>(n, 1);
  }

  void unionize(size_t i, size_t j) {
    auto pi = find_parent(i),
      pj = find_parent(j);

    if(pi == pj)
      return; // already unionized

    if(sizes[pi] > sizes[pj]) {
      parent[pj] = pi;
      sizes[pi] += sizes[pj];
      sizes[pj] = 0;
    } else {
      parent[pi] = pj;
      sizes[pj] += sizes[pi];
      sizes[pi] = 0;
    }

    // debug(mp(i, j))
    // debug(mt(pi, parent[pi], sizes[pi]))
    // debug(mt(pj, parent[pj], sizes[pj]))
  }

  size_t find_parent(size_t i) {  // return <parent[i], size[i]>
    if(parent[i] != i)
      parent[i] = find_parent(parent[i]);
    return parent[i];
  }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  vector<tuple<long, long, long>> points;
  priority_queue<sld, vector<sld>, greater<sld>> min_heap;

  string line;
  long x,y,z, ans1, ans2 = -1;
  size_t i, j;

  while(getline(cin, line)) {
    auto pt = split<long>(line, ',');
    points.eb(pt[0], pt[1], pt[2]);
  }

  // debug(points.size());

  for(int i=0; i<points.size()-1; i++)
    for(int j=i+1; j<points.size(); j++)
      min_heap.emplace(calc_sld(points[i], points[j]), i, j);

  // debug(min_heap.size())

  // Part 1
  DSU circuits(points.size());

  for(int k=0; k<OPS; k++) {
    assert(!min_heap.empty());

    auto min_sld = min_heap.top();
    min_heap.pop();

    i = get<1>(min_sld), j = get<2>(min_sld);
    circuits.unionize(i, j);

    if(ans2 == -1) {
      if(circuits.sizes[circuits.find_parent(i)] == points.size()
        || circuits.sizes[circuits.find_parent(j)] == points.size())
        ans2 = get<0>(points[i]) * get<0>(points[j]);
    }
  }

  vector<int> sizes(3);
  partial_sort_copy(circuits.sizes.begin(), circuits.sizes.end(), sizes.begin(), sizes.end(), greater<>{});

  ans1 = whole(accumulate, sizes, 1L, multiplies<>{});

  // Part 2
  while(ans2 == -1 && !min_heap.empty()) {
    auto min_sld = min_heap.top();
    min_heap.pop();

    i = get<1>(min_sld), j = get<2>(min_sld);
    circuits.unionize(i, j);

    if(ans2 == -1) {
      if(circuits.sizes[circuits.find_parent(i)] == points.size()
        || circuits.sizes[circuits.find_parent(j)] == points.size())
        ans2 = get<0>(points[i]) * get<0>(points[j]);
    }
  }

  cout << "answers: " << ans1 << " " << ans2 << endl;

  return 0;
}
