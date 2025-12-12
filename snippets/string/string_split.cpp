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

// General template for all types
template <typename T>
typename enable_if<!is_same<T, string>::value, vector<T>>::type
split(const string &line, char delimiter = '\0') {
  vector<T> result;
  stringstream ss(line);

  if (delimiter == '\0') {
    // Split on whitespace using istream_iterator
    copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(result));
  } else {
    // Split on delimiter using getline
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

// Specialization for string - more efficient
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

/**
 * Dumb style: iterate, find and split
 * Can take any string as delimiter
 */
vector<string> split_string(const string &input, const string &delimiter) {
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
      out = move(input.substr(pos));
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

  debug(split_string("abc,def,ghi", ","));
  debug(split_string("abc,def,ghi,,", ","));
  debug(split_string(",abc,def,ghi", ","));

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


