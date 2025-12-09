/**
 * Problem: Advent of Code 2025 - Day 5: Cafeteria
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 only
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

using ull = unsigned long long;

vector<string> split(const string &input, const string &delimiter) {
  vector<string> result;

  if (delimiter.empty()) {
    result.push_back(input);
    return result;
  }

  size_t start = 0;
  size_t end;

  while ((end = input.find(delimiter, start)) != string::npos) {
    result.emplace_back(input, start, end - start);     // works in C++11 and later
    start = end + delimiter.length();
  }

  result.emplace_back(input, start);
  return result;
}

template <typename T>
vector<pair<T, T>> sort_and_merge(vector<pair<T, T>> &intervals) {
  vector<pair<T, T>> result;

  if(intervals.empty())
    return result;

  whole(sort, intervals); // lexicographical sort

  T curr_begin = intervals[0].first, curr_end = intervals[0].second;

  for(const auto& cand: intervals) {
    if(cand.first > curr_end) {
      result.eb(curr_begin, curr_end);

      curr_begin = cand.first;
      curr_end = cand.second;
    } else {
      curr_begin = min(curr_begin, cand.first);
      curr_end = max(curr_end, cand.second);
    }
  }

  result.eb(curr_begin, curr_end);

  return result;
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int ans1 = 0;
  ull ans2 = 0;
  vector<pair<ull, ull>> ranges;
  ull inp, rb, re;
  string line;

  while(getline(cin, line)) {
    if(line.empty())
      break;

    auto range = split(line, "-");

    rb = stoull(range[0]);
    re = stoull(range[1]);

    assert(rb <= re);

    ranges.eb(rb, re);
  }

  // sort and merge
  ranges = sort_and_merge<ull>(ranges);

  while(getline(cin, line)) {
    inp = stoull(line);

    for(auto& cand: ranges)
      if(cand.first <= inp && inp <= cand.second) {
        ans1++;
        // debug(inp);
        // debug(cand);
        break;
      }
  }

  for(auto &range: ranges)
    ans2 += range.second - range.first + 1;

  cout << "answers: " << ans1 << " " << ans2 << endl;

  return 0;
}
