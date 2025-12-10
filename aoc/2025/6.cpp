/**
 * Problem: Advent of Code 2025: Day 6: Trash Compactor
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;
using p_L_LL = pair<long, long long>;

vector<string> raw_lines;

template<typename T>
void split_and_copy(const string& line, vector<T>& sink) { // splits on whitespace
  stringstream ss(line);
  sink.clear();

  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(sink));
  // debug(sink);
}

long long solve1() {
  string line;
  vector<long> current;
  vector<char> ops;
  long long ans = 0;
  int len = 0;

  getline(cin, line);
  split_and_copy(line, current);

  len = current.size();
  vector<p_L_LL> nums(len, {0L, 1LL});
  ops.reserve(len);

  do {
    raw_lines.push_back(line); // for use in solve2()

    if(line[0] == '+' || line[0] == '*') {
      split_and_copy(line, ops);

      for(int i=0; i<len; i++)
        ans += (ops[i] == '+' ? nums[i].first : nums[i].second);

      break;
    } else {
      split_and_copy(line, current);

      for(int i=0; i<len; i++) {
        nums[i].first += current[i];
        nums[i].second *= static_cast<long long>(current[i]);
      }
    }

    // debug(nums);
  } while(getline(cin, line));

  return ans;
}

long long solve2() {
  long long ans = 0;

  size_t len = 0;
  for(const string& line: raw_lines)
    len = max(len, line.length());

  int num_lines = raw_lines.size();
  char op = '#'; // valid ops are '+' and '*'
  string cand;
  long long local_ans;

  // debug(len);
  // debug(num_lines);

  for(int i = len-1, k = len-1; i >= 0; i--) {  // i: current column to scan, k: current ops column
    while(raw_lines[num_lines-1][k] != '+' && raw_lines[num_lines-1][k] != '*')
      k--;

    if(op == '#') {
      op = raw_lines[num_lines-1][k];
      local_ans = op == '+' ? 0 : 1;
    }

    cand.clear();

    for(int j=0; j<num_lines-1; j++) {  // j: current number row to scan
      if(raw_lines[j][i] != ' ')
        cand += raw_lines[j][i];
    }

    if(cand.empty()) {
      k--;  // find next op in next iteration
      op = '#';
      ans += local_ans;
      // debug(ans);
    }
    else {
      local_ans = op == '+' ? local_ans + stol(cand) : local_ans * stol(cand);
      // debug(local_ans);
    }
  }

  ans += local_ans;

  return ans;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  cout << "answers: " << solve1() << " " << solve2() << endl;

  return 0;
}
