/**
 * String Splitting in C++
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // C++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

/**
 * Dumb style: iterate, find and split
 */
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
 * Generator function, using C++ lambdas
 */
auto make_splitter(const string &input, const string &delimiter) {
  size_t pos = 0;

  return [pos, input, delimiter](string &out) mutable -> bool {
    if (pos > input.size())
      return false;

    size_t next = input.find(delimiter, pos);

    if (next == string::npos) {
      out = std::move(input.substr(pos));
      pos = input.size() + 1;
      return true;
    }

    out = input.substr(pos, next - pos);
    pos = next + delimiter.size();
    return true;
  };
}

/**
 * STL style Iterator
 */
class SplitIterator {
public:
  SplitIterator(const string &str, const string &delim, size_t start)
      : s(&str), d(&delim), pos(start) {
    advance();
  }

  const string &operator*() const { return current; }

  SplitIterator &operator++() {
    advance();
    return *this;
  }

  bool operator!=(const SplitIterator &other) const {
    return done != other.done;
  }

private:
  const string *s;
  const string *d;
  size_t pos;
  string current;
  bool done = false;

  void advance() {
    if (done)
      return;

    if (pos > s->size()) {
      done = true;
      return;
    }

    size_t next = s->find(*d, pos);

    if (next == string::npos) {
      current = s->substr(pos);
      pos = s->size() + 1;
    } else {
      current = s->substr(pos, next - pos);
      pos = next + d->size();
    }
  }
};

struct SplitRange {
  const string &s;
  const string &d;

  SplitIterator begin() const { return {s, d, 0}; }
  SplitIterator end() const { return {s, d, s.size() + 1}; }
};

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  debug(split("abc,def,ghi", ","));
  debug(split("abc,def,ghi,,", ","));
  debug(split(",abc,def,ghi", ","));

  const string input = ",,,xyz,,mno: pqr,stu,,";
  debug(input);

  auto next = make_splitter(input, ",");
  string next_token;

  while(next(next_token))
    debug(next_token);

  for(const auto& token: SplitRange{input, ","})
    debug(token);

  return 0;
}


