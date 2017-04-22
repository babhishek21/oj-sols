/**
 * Problem: Design a Stock Ticker System (https://discuss.leetcode.com/topic/7/stock-ticker/)
 *
 * Give a stream of stock prices, design a data structure to support the following operations:
 *   1. StockSticker(int k) : Initialize the size of the ticker.
 *   2. void addOrUpdate(String stock, double price) : add or update the price of a stock to the data structure.
 *   3. List<Map.Entry<String, double>> top() : return the top k price stocks and their current prices.
 *
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

typedef unordered_map<string, double> stockDictType;

class StockTicker {
  class Comparator {
  public:
    stockDictType &_stockDictRef;

    explicit Comparator(stockDictType &stocksDict): _stockDictRef(stocksDict) {}

    inline bool operator() (const string &a, const string &b) const {
      return _stockDictRef.at(a) < _stockDictRef.at(b);
    }
  };

  stockDictType stocksDict;
  map<string, stockDictType::iterator, Comparator> stocksTicker{Comparator{stocksDict}};
  int tickerSize;

public:
  StockTicker(int k): tickerSize(k) {}

  void addOrUpdate(string name, double price) {
    stocksDict[name] = price;
    stocksTicker[name] = stocksDict.find(name);
  }

  vector<stockDictType::iterator> top() {
    vector<stockDictType::iterator> ret(tickerSize);

    auto it = stocksTicker.begin();
    for(int i = 0; i < tickerSize; i++, it++)
      ret[i] = it->second;

    return ret;
  }
};


int main() {

  StockTicker st(3);

  st.addOrUpdate("A", 3.0);
  st.addOrUpdate("B", 2.0);
  st.addOrUpdate("C", 5.0);

  for(auto&& it: st.top())
    cout << it->first << "@ $" << it->second << endl;

  st.addOrUpdate("A", 4.0);

  for(auto&& it: st.top())
    cout << it->first << "@ $" << it->second << endl;

  return 0;
}
