/**
 * Problem: Advent of Code 2025 - Day 12: Christmas Tree Farm
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

template <typename T>
typename enable_if<is_same<T, string>::value, vector<T>>::type
split(const string &line, char delimiter = '\0') {
  vector<string> result;
  stringstream ss(line);

  if (delimiter == '\0') {
    // Split on whitespace using istream_iterator
    copy(istream_iterator<string>{ss}, istream_iterator<string>{},
         back_inserter(result));
  } else {
    // Split on delimiter using getline; directly move tokens
    string token;

    while (getline(ss, token, delimiter)) {
      if (!token.empty()) {
        result.push_back(std::move(token)); // Direct move, no stream conversion
      }
    }
  }

  return result;
}

/*
  This is a meme solution to this AoC puzzle, for the express puzzle input provided.
  It works because all presents' shapes fit in a 3x3 grid, and the shapes are complementary
  enough to fit efficiently.
*/
bool solve_lulz(const vector<int>& shapes_areas,
                const int region_width, const int region_height,
                const vector<int>& required_presents) {

  int required_area = 0;
  for(size_t i=0; i<required_presents.size(); i++)
    required_area += required_presents[i] * shapes_areas[i];

  return (required_area < region_width * region_height);  // check if required presents' tile area is less than area of region
}

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  string line;
  int idx, rh, rw, ans = 0;

  unordered_map<int, vector<string>> shapes;

  while(getline(cin, line)) {
    if(line.empty()) {
      idx = -1;
      continue;
    }

    if(line.back() == ':') {
      line.pop_back();
      idx = stoi(line);
    }
    else if(line.front() == '#' || line.front() == '.') {
      assert(idx != -1);
      shapes[idx].push_back(line);
    }
    else if(line.find('x') != string::npos && line.find(": ") != string::npos)
      break;  // handle these inputs (for regions) in a separate loop
  }

  vector<int> req(shapes.size()); // region's expected configuration of presents

  vector<int> shapes_areas(shapes.size());
  for(auto &shape: shapes)
    shapes_areas[shape.first] = whole(accumulate, shape.second, 0, [](int sum, const string& ll) {
      return sum + count(ll.begin(), ll.end(), '#');
    });

  // process each region in input
  do {
    auto toks = split<string>(line);

    for(size_t i=0; i<req.size(); i++)
      req[i] = stoi(toks[i+1]);

    toks[0].pop_back(); // remove semicolon
    toks = split<string>(toks[0], 'x');
    rw = stoi(toks[0]);
    rh = stoi(toks[1]);

    ans += solve_lulz(shapes_areas, rw, rh, req);

  } while(getline(cin, line));

  cout << "answer: " << ans << endl;

  return 0;
}
