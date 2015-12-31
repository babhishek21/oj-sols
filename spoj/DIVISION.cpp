/**
 * Step-1: Notice that divisibility by 3 in binary format is similar to
 * that in decimal format. The alternating sum of bits from MSB to LSB
 * should be divisible by 3.
 *
 * Step-2: Notice the pattern for different binary lengths. The answers
 * for lower binary lengths also feature in higher binary lengths (as
 * leading zeroes can always be added.)
 *
 * Binary Length (N) => Answer
 * 1 => 1
 * 2 => 2 = 2*1
 * 3 => 3 = 2*2 - 1
 * 4 => 6 = 2*3
 * 5 => 11 = 2*6 - 1
 * 6 => 22 = 2*11
 * 7 => 43 = 2*22 - 1
 *
 * For (n is odd): ans(n) = 2*ans(n-1) - 1
 * For (n is even): ans(n) = 2*ans(n-1)
 * Solving the recurrences:
 * ans(n) = (2^n + 1)/3 <= if n is odd
 *        = (2^n + 2)/3 <= if n is even
 *
 * Step-3: Use Fast modular exponentiation to reduce (a^b mod p)
 * calculation to O(log p) time.
 *
 * NOTE: Had to use CSTDIO. Time limits too tight.
 */

#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define INV 333333336 // MMI of 3 wrt 1e9+7

unsigned long long mod_exp(unsigned long long base, unsigned long long exponent, unsigned int mod = MOD) {
  unsigned long long prod = 1;
  base = base % mod;

  while(exponent > 0) {
    if(exponent&1)    // if exponent is odd
      prod = (prod * base) % mod;

    exponent >>= 1;
    base = (base * base) % mod;
  }

  return prod;
}

int main() {
  unsigned long long n, ans;

  while(scanf("%llu", &n) != EOF) {
    if(n&1)
      ans = ((mod_exp(2, n) + 1) * INV) % MOD;
    else
      ans = ((mod_exp(2, n) + 2) * INV) % MOD;

    printf("%llu\n", ans);
  }

  return 0;
}
