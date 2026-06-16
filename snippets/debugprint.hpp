#ifndef H_DEBUG_PRINT
#define H_DEBUG_PRINT

#include <iostream>
#include <string>
#include <bitset>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>
#include <unistd.h>
#include <cstring>

const bool __dbg_use_color = ::isatty(STDERR_FILENO);

inline void __pr(int x) { std::cerr << x; }
inline void __pr(long x) { std::cerr << x; }
inline void __pr(long long x) { std::cerr << x; }
inline void __pr(unsigned long long x) { std::cerr << x; }
inline void __pr(float x) { std::cerr << x; }
inline void __pr(double x) { std::cerr << x; }
inline void __pr(long double x) { std::cerr << x; }
inline void __pr(bool x) {
  if (__dbg_use_color)
    std::cerr << (x ? "\033[1;32mT\033[0m" : "\033[1;31mF\033[0m");
  else
    std::cerr << (x ? "T" : "F");
}
inline void __pr(char x) { std::cerr << '\'' << x << '\''; }
inline void __pr(const char *x) { std::cerr << '\"' << x << '\"'; }
inline void __pr(const std::string &x) { std::cerr << '\"' << x << '\"'; }

template <typename T1, typename T2>
void __pr(const std::pair<T1, T2> &x) {
  std::cerr << '('; __pr(x.first); std::cerr << ", "; __pr(x.second); std::cerr << ')';
}
template <std::size_t N>
void __pr(const std::bitset<N> &x) { std::cerr << x; }

template <typename... Args, std::size_t... Is>
void __pr_tuple(const std::tuple<Args...>& x, std::index_sequence<Is...>) {
  std::cerr << '(';
  (((Is == 0 ? void() : (void)(std::cerr << ", ")), __pr(std::get<Is>(x))), ...);
  std::cerr << ')';
}

template <typename... Args>
void __pr(const std::tuple<Args...> &x) {
  __pr_tuple(x, std::index_sequence_for<Args...>{});
}

template <typename M>
void __pr_map(const M &x) {
  int f = 0, n = (int)x.size();
  if (n > 4) {
    std::cerr << "{\n";
    for (const auto& p : x) {
      if (f++) std::cerr << ",\n";
      std::cerr << "  "; __pr(p.first); std::cerr << ": "; __pr(p.second);
    }
    std::cerr << "\n}";
  } else {
    std::cerr << '{';
    for (const auto& p : x) {
      if (f++) std::cerr << ", ";
      std::cerr << '('; __pr(p.first); std::cerr << ": "; __pr(p.second); std::cerr << ')';
    }
    std::cerr << '}';
  }
}

template <typename K, typename V> void __pr(const std::map<K, V> &x) { __pr_map(x); }
template <typename K, typename V> void __pr(const std::multimap<K, V> &x) { __pr_map(x); }
template <typename K, typename V> void __pr(const std::unordered_map<K, V> &x) { __pr_map(x); }
template <typename K, typename V> void __pr(const std::unordered_multimap<K, V> &x) { __pr_map(x); }

inline void __pr(const std::vector<bool> &v) {
  int f = 0; std::cerr << '{';
  for (auto i : v) {
    if (f++) std::cerr << ", ";
    __pr(i);
  }
  std::cerr << '}';
}

template <typename T>
void __pr(const T &x) { std::cerr << x; }  // fallback: picks up prettyprint's operator<<

inline void _dbg() { std::cerr << std::endl; }
inline void _dbg(const char*) { std::cerr << std::endl; }
template <typename H, typename... T>
void _dbg(const char* s, const H& h, const T&... t) {
  const char* comma = strchr(s, ',');
  std::cerr.write(s, comma ? comma - s : strlen(s));
  std::cerr << ": "; __pr(h);
  if constexpr (sizeof...(t) > 0) std::cerr << ", ";
  _dbg(comma ? comma + 2 : "", t...);
}

#endif  // H_DEBUG_PRINT
