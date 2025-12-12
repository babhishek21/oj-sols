/**
 * Problem: Advent of Code 2025 - Day 11: Reactor
 * Author: babhishek21
 * Lang: C++17
 *
 * Note: We use memoized DFS to count all paths between src and dest nodes in the graph. The alternative
 * (assuming, given a DAG) is to do a topological sort, and then run a backwards DP from dest.
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

template<typename T>
void split_and_copy(const string& line, vector<T>& sink) { // splits on whitespace
  stringstream ss(line);
  sink.clear();

  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(sink));
  // debug(sink);
}

auto string_pair_hash = [](const pair<string, string>& p) {
  size_t h1 = hash<string>{}(p.first),
    h2 = hash<string>{}(p.second);

  h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2); // from Boost
  return h1;
};

unordered_map<pair<string, string>, long, decltype(string_pair_hash)> memo(0, string_pair_hash);
unordered_map<string, vector<string>> graph; // adjacency list; assume DAG

long find_all_paths(const string &src, const string &dest) { // dfs + memoization
  if(src == dest)
    return 1L;

  if(memo.count(mp(src, dest)) > 0)
    return memo.at(mp(src, dest));

  long paths = 0;
  for(auto& next_src: graph[src])
    paths += find_all_paths(next_src, dest);

  memo[mp(src, dest)] += paths;
  return paths;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  string line;
  vector<string> edge;

  long ans1, ans2;

  while(getline(cin, line)) {
    split_and_copy(line, edge);
    edge[0].pop_back(); // pop the colon character

    if(graph.count(edge[0]) > 0)
      graph[edge[0]].insert(graph[edge[0]].end(), next(edge.begin()), edge.end());
    else
      graph.emplace(edge[0], vector<string>(next(edge.begin()), edge.end()));
  }

  // debug(graph)

  ans1 = find_all_paths("you", "out");

  // debug(ans1);

  long svr_dac = find_all_paths("svr", "dac"),
    dac_fft = find_all_paths("dac", "fft"),
    fft_out = find_all_paths("fft", "out"),
    svr_fft = find_all_paths("svr", "fft"),
    fft_dac = find_all_paths("fft", "dac"),
    dac_out = find_all_paths("dac", "out");

  // debug(svr_dac)
  // debug(dac_fft)
  // debug(fft_out)
  // debug(svr_fft)
  // debug(fft_dac)
  // debug(dac_out)

  ans2 = svr_dac * dac_fft * fft_out;
  ans2 += svr_fft * fft_dac * dac_out;

  cout << "answers: " << ans1 << " " << ans2 << endl;

  return 0;
}
