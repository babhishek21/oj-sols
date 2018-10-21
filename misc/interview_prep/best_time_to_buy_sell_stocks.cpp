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

  /**
   * Best Time to Buy and Sell Stock with Cooldown (LeetCode)
   * Say you have an array for which the ith element is the price of a given stock on day i.
   * Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
   * (ie, buy one and sell one share of the stock multiple times) with the following restrictions:
   * You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
   * After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
   *
   * O(n) DP solution based on state machines. There are three actions to perform any day: buy, sell, or cooldown.
   * 
   * Once you buy a stock, you get into the "buy" state. Once you sell stock, you are automatically put in the "cooldown"
   * state for atleast a day. Once you've cooled down for atleast a day, you can go back to a "buy" state, if you wish.
   * 
   * So on any single day:
   * 1. If you want to be in the "buy" state, you can sit tight on a previous purchase or buy after atleast a day of cooldown.
   * 2. If you want to be in the "sell" state, you can sell your previously bought stock, or you can sit tight from a previous sale.
   * 3. You can be in a cooldown stage, only by already being in there, or by selling the previous day.
   * 
   * In the end, the max profit is realised after you sell off any stock you might have had on the last day.
   */
  int maxProfitWithCooldown(vector<int>& prices) {
    if(prices.empty()) return 0;
    
    int n = prices.size();
    
    vector<int> buy(n),     // max profit from buying stock
    sell(n),                // max profit from selling stock
    cool(n);                // max profit earned with cooling down for a day
    
    buy[0] = -prices[0];  // can buy on first day; will get net loss
    sell[0] = 0;          // can't sell before buying
    cool[0] = 0;          // can't cool before selling
    
    for(int i=1; i<n; i++) {
      buy[i] = max(buy[i-1], cool[i-1] - prices[i]); // can keep yesterday's stock, or buy a stock today after a day of cooldown.
      sell[i] = max(buy[i-1] + prices[i], sell[i-1]); // can sell earlier bought stock, or keep tight by not buying anything / sitting tight.
      cool[i] = max(sell[i-1], cool[i-1]); // cooldown for a day after selling stock yesterday, or prolong an existing cooldown period / sit tight.
    }
    
    return sell[n-1];  // you can never make profit by sitting tight / cooling down (zero net profit) or buying stuff (net loss).
  }

  



  

}

int main() {
  // TODO

  return 0;
}
