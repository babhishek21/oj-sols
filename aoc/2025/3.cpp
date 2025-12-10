/**
 * Problem: Advent of Code 2025 - Day 3: Lobby
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

const long long pow10[13] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000 };

/*
  Greedy solution
  ===============

  1. To determine the best joltage for most significant battery in a bank at budget k,
  you must look for the first maximal joltage in the prefix of the bank such that there are enough batteries
  left to meet budget with the rest of the batteries. i.e. look in bank[0] to bank[len(bank)-k-1]

  2. Once you find a significant battery, the best joltage for the next significant battery must in the
  suffix bank of the more significant battery. i.e. if significant battery was found at index 'x', look next
  in bank[x+1] to bank[len(bank)-(k-1)-1]

  3. Repeat the above process until you exhaust the budget. The resultant battery joltage is the best.

  Proof of correctness (proof by contradiction)
  ---------------------------------------------
  Let's assume that at any budget step, we can do better than the scheme proposed (say, maximal joltage m found at index i):

  Case 1: we find another battery with lesser joltage in the same prefix (say, n < m)
    => choosing the battery with lesser joltage is guaranteed to result in lesser joltage overall as the most significant battery joltage is lesser
    ==> contradiction!

  Case 2: we find another battery with same joltage in the same prefix, but at later index j > i:
    => all batteries at latter indices (i.e. index >= j) of the searchable prefix must be of lesser or equal joltage
    => all batteries at infix indices (i.e. index between i and j) must be of lesser or equal joltage

    examples: 53186782735 and 53188882735
                 ^  ^            ^  ^
                 i  j            i  j
    => by choosing index j, we cannot include the maximal elements at indices i+1 to j as second most significant joltage.
      => resultant second most significant joltage is lower => resultant overall joltage is lower
      ==> contradiction!

    examples: 53186782835 and 53188882835
                 i  j            i  j
    => by choosing index j, we forego the ability to include maximal element at index i
      => which reduces how many significant joltages can be stuffed with maximal joltage battery (by atleast 1)
      => resultant overall joltage is of lesser digits OR of the same value as the scheme proposed (i.e. not better)
      ==> contradiction!
*/
long long seek_best_greedy(const vector<int>& bank, int budget) {
  long long best = 0;
  auto it = bank.begin();

  while(budget--) {
    it = max_element(it, prev(bank.end(), budget));

    best *= 10;
    best += *it;

    it = next(it);
  }

  return best;
}

/*
  Top-down Iterative DP solution
  ==============================

  dp[l][b] = maximal joltage with prefix bank[0...l] within budget b

  dp[l][b] = max(
    dp[l-1][b-1]*10 + bank[l],
    dp[l-1][b]
  )

  dp[0][b] = bank[0]
  dp[l][0] = 0

  This basically follows the same principle as the greedy solution. This works because the greedy algorithm is correct and optimal.
*/
long long seek_best_dp(const vector<int>& bank, int budget) {
  int l = bank.size(), b = budget;

  vector<vector<long long>> dp(l, vector<long long>(b+1, 0));

  for(int i=1; i<=b; i++)
    dp[0][i] = bank[0];

  for(int i=1; i<l; i++)
    for(int j=1; j<=b; j++)
      dp[i][j] = max(dp[i-1][j-1] * 10 + bank[i], dp[i-1][j]);

  // debug(dp);

  return dp[l-1][b];
}

/*
  TODO: Add a Bottoms-up Iterative DP solution
*/

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int ans1 = 0, best2;
  long long ans2 = 0, best12;
  string line;
  vector<int> bank;

  while(getline(cin, line)) {
    best2 = best12 = 0;
    bank.clear();

    for(auto &ch: line)
      bank.push_back(ch - '0');

    best2 = seek_best_greedy(bank, 2);
    assert(best2 == seek_best_dp(bank, 2));
    // debug(best2);

    best12 = seek_best_greedy(bank, 12);
    assert(best12 == seek_best_dp(bank, 12));
    // debug(best12);

    ans1 += best2;
    ans2 += best12;
  }

  cout << "answers: " << ans1 << " " << ans2 << endl;

  return 0;
}
