/**
 * Problem: Advent of Code - Day 9: Movie Theater
 * Author: babhishek21
 * Lang: C++11
 * Tags: boundary overlap box rectangle intersection
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 only
using namespace std;

static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

#define pb push_back
#define eb emplace_back
#define mt make_tuple

using tuple_4L = tuple<long, long, long, long>;

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

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

/**
 * Make axis-aligned bounding rectangle with any two corner points
 * Returns the coordinates of top-left corner and bottom-right corner as tuple
 */
tuple_4L make_bounding_rect(const pair<long, long>& a, const pair<long, long>& b) {
  return mt(
    min(a.first, b.first), min(a.second, b.second), // top-left corner
    max(a.first, b.first), max(a.second, b.second)  // bottom-right corner
  );
}

int main() {
  vector<pair<long, long>> reds;
  vector<tuple_4L> greens;

  long x, y;
  long long ans1 = 0, ans2 = 0;

  string line;

  while(getline(cin, line)) {
    auto red = split(line, ",");
    x = stoul(red[0]);
    y = stoul(red[1]);

    reds.eb(x, y);
  }

  // green line segments with starting and ending points, such that start.x <= end.x and start.y <= end.y
  // since these line segments are axis-aligned, they are essentially unit-width rectangles.
  for(int i=0; i<reds.size()-1; i++)
    greens.pb(make_bounding_rect(reds[i], reds[i+1]));
  greens.pb(make_bounding_rect(reds.back(), reds.front()));

  // debug(greens)

  long u, v, p, q, r, s;
  long long area;

  for(int i=0; i<reds.size()-1; i++)
    for(int j=i+1; j<reds.size(); j++) {
      // candidate rectangle with top-left corner (u, v) and bottom-right corner (x, y)
      tie(u,v, x,y) = make_bounding_rect(reds[i], reds[j]);

      area = static_cast<long long>(x-u+1) * static_cast<long long>(y-v+1);
      ans1 = max(ans1, area);

      if(area > ans2) {
        // debug(tie(u,v, x,y))

        for(const auto& line_segment: greens) {
          tie(p,q, r,s) = line_segment;

          /*
            check if any green line segment cuts the candidate rectangle
            (i.e. intersect one of it's edges, but not lie on it)

            This is same as checking if a unit-width bounding rectangle of the line segment
            (a line segment is a very thin rectangle after all), has overlap with area of the
            candidate rectangle, without touching edges.

            given two rectangles A and B with top-left and bottom-right coordinates (top has lower
            coordinate value than bottom & left has lower coordinate value than right), they overlap if

              A.left < B.right and
              A.right > B.left and
              A.top < B.bottom and
              A.bottom > B.top

            See https://stackoverflow.com/a/306332/2844164 for derivation
          */

          if(u<r && x>p && v<s && y>q) {
            // debug(line_segment)

            area = -INFLL;
            break;
          }
        }

        // debug(area)

        ans2 = max(ans2, area);
      }
    }

  cout << "answers: " << ans1 << " " << ans2 << endl;

  return 0;
}
