/**
 * Best Time to Buy and Sell Stocks I-IV (LeetCode)
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

namespace BuySellStock {

  /**
   * Best Time to Buy and Sell Stocks I (LeetCode)
   * You are given the stock prices of the ith day in arr[i].
   * Find the max profit if you were permitted to complete atmost
   * one transaction (ie, buy one and sell one share of the stock).
   *
   * Simple O(n) DP solution. You can do either of:
   *  1. Buy a stock that day because price was lower than ever before
   *  2. Try selling that day to see if you get max profit
   */
  int maxProfit1(vector<int> &prices) {
    if(prices.size() < 2) return 0;

    int min_price = numeric_limits<int>::max(), max_profit = 0;

    for(auto &price: prices) {
      max_profit = max(max_profit, price - min_price);
      min_price = min(min_price, price);
    }

    return max_profit;
  }

  /**
   * Best Time to Buy and Sell Stocks II (LeetCode)
   * You are given the stock prices of the ith day in arr[i].
   * Find the max profit if you were permitted to complete as many
   * transactions as you like (ie, buy one and sell one share of the stock
   * multiple times). However, you may not engage in multiple transactions
   * at the same time (ie, you must sell the stock before you buy again).
   *
   * Simple O(n) greedy solution. The idea is to sell whenever the price is
   * higher than previous day's price. You might wonder what about the case when
   * prices keep increasing. Well say for some time prices are like $3 $7 $9. Then
   * you can buy at $3 and sell at $7. Then buy at $7 (yes that same day) and sell
   * later at $9. This is essentially buying at $3 and selling at $9 (because the net
   * transaction at $7 is zero).
   */
  int maxProfit2(vector<int> &prices) {
    if(prices.size() < 2) return 0;

    int prev_price = numeric_limits<int>::max(), max_profit = 0;
    for(auto &price: prices) {
      if(price < prev_price)
        prev_price = price;
      else if(price > prev_price) {
        max_profit += price - prev_price;
        prev_price = price;
      }
    }

    return max_profit;
  }

  // remaining TODO

}

int main() {
  // TODO

  return 0;
}
