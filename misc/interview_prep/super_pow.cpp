/**
 * SuperPow (LeetCode)
 * Calculate a**b mod 1337 where a is a positive integer and b is an extremely
 * large positive integer given in the form of an array
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

const int MOD = 1337;

/**
 * 1. Naive Method of Binary multiplication
 * Traditonally complexity is O(log(b)). In this case, if length of b is |b|
 * then complexity is O(log(10**|b|) * |b|) == O(|b|**2)*c (where c is a constant)
 * which is onviously too slow.
 */
namespace NaiveBinary {
  inline bool all_same(vector<int> &b, int k) {
    return all_of(b.begin(), b.end(), [&](int i) { return i == k; });
  }

  inline void reduceby2(vector<int> &b) {
    int carry = 0;
    for(int i=0; i<b.size(); i++) {
      b[i] += carry*10;
      carry = b[i]%2;
      b[i] /= 2;
    }
  }

  int superPow(int a, vector<int>& b) {
    if(all_same(b, 0)) return 1;
    if(all_same(b, 1)) return a%MOD;

    bool odd_flag = (b.back()&1 != 0);
    reduceby2(b);

    if(odd_flag)
      return (a%MOD * superPow(((a%MOD) * (a%MOD))%MOD, b))%MOD;
    else
      return superPow(((a%MOD) * (a%MOD))%MOD, b)%MOD;
  }
}

/**
 * 2. Much Faster Method of Linear Reduction
 * a ** {b1,b2,b3...bn} == (..(((a**b1)**10 + a**b2)**10 + a**b3)**10 + ...)
 * Complexity is O(|b| * log(10)) == O(|b|)*c (where c is a constant)
 */
namespace LinearReduction {
  int fast_pow_mod(int a, int b) { // assuming a < MOD
    if(a == 1 || b == 0) return 1;
    if(b == 1) return a;

    if(b&1)
      return (a * fast_pow_mod((a*a)%MOD, b/2))%MOD;
    else
      return fast_pow_mod((a*a)%MOD, b/2);
  }

  int superPow(int a, vector<int> &b) {
    int result = 1;
    for(auto &e: b) {
      result = (fast_pow_mod(result, 10)%MOD * fast_pow_mod(a%MOD, e)%MOD)%MOD;
    }
    return result;
  }
}

/**
 * 3. The repeated remainder pattern.
 * For a increasing powers of a number A, its remainder when divided by a number M
 * tends to repeat after a while. Suppose A**i % M repeats every p times (i.e. after every
 * i such that p|i). Then A**B % M can easily be found out by finding the remainder_pattern[B % p].
 *
 * Finding the pattern takes atmost O(M) time. Hence complexity is O(M+|b|) time and O(p) extra space;
 */
namespace RemainderRepeat {
  vector<int> getRemainderPattern(int a) {
    // NOTE: a < MOD
    vector<int> pattern;
    unordered_set<int> prevRemainders;

    int rem = a % MOD;
    while(prevRemainders.count(rem) <= 0) {
      prevRemainders.insert(rem);
      pattern.push_back(rem);

      rem = (a * rem) % MOD;
    }

    return pattern;
  }

  int getRemainderIndex(vector<int> &b, int patternSize) {
    auto reduceOp = [&](const int &rem, int bi) {
      return (rem*10 + bi) % patternSize;
    };

    return accumulate(b.begin(), b.end(), 0, reduceOp);
  }

  int superPow(int a, vector<int> &b) {
    if(a == 0 || a == MOD || b.empty()) return 0;
    if(a == 1) return 1;

    if(a > MOD) a %= MOD;
    auto remainderPattern = getRemainderPattern(a);
    int remainderIndex = getRemainderIndex(b, remainderPattern.size());
    remainderIndex = (remainderIndex == 0) ? remainderPattern.size() : remainderIndex;

    return remainderPattern[remainderIndex-1];
  }
}

/**
 * 4. Using Fermat's Little Theorem & Chinese Remainder Theorem
 *
 * Fermat's Little Theorem: For a prime number p, a**p % p = a.
 * If p|a is not true, then a**(p-1) % p = 1.
 *
 * So if we need to calculate A**B % M and M is a prime number, then we could find
 * E = B % (M-1) and instead calculated A**E % M.
 *
 * However in this case M = 1337 = 7 * 191 (Both 7 and 191 are primes). So instead we apply
 * the above for M = 7 and  M = 191 and then use the Chinese remainder theorem to combine the results.
 *
 */



int main() {
  using namespace RemainderRepeat;

  cout << "2**3 = " << superPow(2, vector<int>() = {3}) << endl // 8
      << "2**10 = " << superPow(2, vector<int>() = {1,0}) << endl // 1024
      << "3**200 = " << superPow(3, vector<int>() = {2,0,0}) << endl // 30
      << "2147483647**200 = " << superPow(2147483647, vector<int>() = {2,0,0}) << endl; // 1198

  int a = 2603206;
  vector<int> b = {7,0,4,5,1,7,0,8,7,9,7,7,1,7,7,0,5,9,7,1,3,1,0,2,5,8,5,1,7,3,7,5,6,4,2,9,1,3,7,1,4,5,0,8,4,8,8,2,7,6,3,2,9,5,6,6,6,1,7,5,7,4,3,3,0,5,4,4,0,2,5,5,7,5,3,3,5,3,5,4,9,0,8,0,6,5,6,4,8,3,9,5,0,2,0,2,0,5,6,0,9,3,7,6,1,2,1,8,6,7,3,7,7,3,8,5,8,4,9,9,0,1,4,2,3,7,6,3,4,3,6,3,8,3,1,9,6,2,8,2,1,3,9,1,6,9,6,5,6,8,6,6,9,2,0,4,9,6,0,3,1,6,6,0,1,7,9,7,2,9,1,3,2,3,4,9,2,3,6,8,1,2,6,2,4,8,8,4,5,8,9,8,6,8,8,0,7,0,7,9,1,1,3,4,4,7,3,8,0,1,9,3,3,5,7,9,6,6,5,3,6,5,1,5,3,2,5,2,4,4,2,5,5,5,1,9,4,6,0,5,7,9,0,2,4,8,2,2,4,7,5,2,4,7,7,9,9,4,2,5,9,4,0,4,9,2,6,3,8,6,0,8,5,1,0,1,9,2,4,5,2,9,9,6,8,7,6,7,1,8,4,0,2,7,7,3,9,3,6,9,9,9,9,6,2,0,7,3,4,3,8,6,3,9,3,1,6,9,1,0,9,5,2,1,2,1,4,3,4,2,5,5,3,4,1,5,6,1,8,1,4,8,9,7,8,2,1,6,3,4,8,2,1,1,5,6,2,9,9,9,4,6,4,7,3,8,3,9,9,1,2,3,2,2,3,0,6,4,6,2,0,5,4,1,8,2,7,2,3,9,1,7,5,8,7,8,6,0,0,5,3,4,8,5,6,3,7,5,7,4,7,7,1,3,1,9,5,8,1,9,7,5,8,5,5,5,5,1,7,5,8,1,0,6,8,8,0,6,5,9,2,2,9,3,8,0,4,3,0,7,4,8,2,3,3,9,8,8,0,6,6,8,9,8,7,9,8,9,7,4,0,1,8,9,4,6,1,0,2,4,8,6,2,2,9,7,2,0,7,4,6,5,3,7,5,2,8,4,1,6,8,1,7,8,3,4,5,6,4,7,0,4,5,4,7,5,3,1,7,3,5,5,8,0,2,4,2,0,0,3,8,0,7,6,8,2,2,3,8,8,2,1,3,8,5,2,5,9,3,2,2,0,7,2,1,1,8,3,3,8,9,2,8,8,0,7,0,4,2,8,2,7,9,5,7,7,9,2,8,4,6,0,5,5,4,8,6,3,3,9,3,2,3,2,0,5,9,2,9,3,1,2,0,2,9,7,9,9,1,7,3,9,9,0,4,6,8,2,1,2,4,4,4,9,6,7,5,7,9,4,1,2,6,3,7,8,3,8,7,6,8,2,6,9,3,2,5,1,7,6,3,1,3,0,0,9,9,5,9,0,2,0,5,0,5,2,8,0,0,5,7,8,8,5,0,1,9,5,4,6,4,8,9,7,0,2,8,9,9,7,1,1,9,6,2,5,8,0,7,1,8,4,1,8,1,1,9,3,9,5,9,5,3,1,2,5,3,0,4,2,0,6,6,9,4,8,6,3,0,4,6,8,0,7,6,2,1,7,5,0,3,6,5,8,9,9,4,2,1,0,7,1,8,3,3,3,3,9,6,3,5,4,4,6,1,2,0,4,0,7,4,5,5,1,3,5,2,9,9,4,0,8,7,8,3,0,1,6,2,9,2,7,3,8,5,7,0,5,1,0,2,8,7,8,1,3,3,4,2,4,0,2,3,9,3,6,2,6,5,4,8,7,3,3,5,9,2,5,4,6,8,9,4,7,7,7,0,2,1,3,6,3,7,1,3,2,8,5,9,5,9,9,2,4,2,9,3,5,6,0,3,6,9,7,4,6,6,4,0,8,9,8,3,7,0,6,1,0,1,0,5,2,1,9,7,6,0,2,1,6,2,4,5,3,3,9,1,9,5,1,9,5,0,3,4,2,9,5,4,3,8,9,7,9,0,4,5,0,9,8,8,3,4,3,7,9,4,8,1,2,0,2,9,2,5,3,6,7,0,0,2,8,1,9,0,1,6,7,3,5,8,3,0,4,9,7,6,3,6,7,7,8,9,6,2,7,9,8,6,0,8,8,0,9,7,2,2,5,2,5,2,2,8,3,6,7,0,2,3,8,1,0,6,1,7,0,0,8,8,6,0};

  cout << "a**b mod 1337 = " << superPow(a, b) << endl; // 387

  return 0;
}
