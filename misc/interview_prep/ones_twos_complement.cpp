/**
 * Problem: One's and Two's complement for Integral types
 * Author: babhishek21
 * Lang: C++20 (in a two's complement system)
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;

#define FULL_WIDTH_MODE false

/**
 * Get the two's complement binary notation of a signed integeral type.
 *
 * In full width mode, the MSB is always indicative of the signum of the number. Hence, binary literal outputs are prefixed with '0b'.
 *
 * In compact mode, common prefixes are truncated ('1...' for negative numbers, '0...' otherwise). Hence, binary literals for negative
 * numbers are prefixed with '-0b', and with '0b' for non-negative numbers.
 */
string binarify(signed_integral auto x, bool full_width = true) {
  bool signum = x >= 0; // true for non-negative
  string val = "";
  size_t bitsize = sizeof(x) << 3; // size (in bits) of type T

  val.reserve(bitsize);

  for(int i=0; i<bitsize; i++, x >>= 1)
    val += (x & 1) ? '1' : '0';

  reverse(val.begin(), val.end());

  if(!full_width) {
    auto it = find(val.begin(), val.end(), signum ? '1' : '0');

    if (it != val.end())
      val.erase(val.begin(), it);
    else
      val = val[0];
  }

  return (!full_width && !signum ? "-0b" : "0b") + val;
}

/**
 * One's complement - flip all bits (bitwise NOT)
 *
 * Equivalent to calculating 2^N - x, where N is bit size of type of x
 */
template <typename T>
T ones_complement(T x) {
  return ~x;
}

/**
 * Two's complement - take One's complement and add 1.
 *
 * This is equivalent to finding the least significant bit that is ON (1), and flipping all of the remaining more significant bits.
 * In our two's complement system, the unary minus operator (-) takes the two's complement of a number.
 */
template <typename T>
T twos_complement(T x) {        // refer: https://stackoverflow.com/a/25754304/2844164
  using U = make_unsigned_t<T>;
  return T(-uintmax_t(U(x)));
}

int main() {
  vector<int> tc = { 0, 1, 69, 420, 1234567890, -33, -128, -45698321 };

  for(auto &x: tc) {
    cout << x << " ( " << binarify(x, FULL_WIDTH_MODE) << " ):\n    1's complement "
      << ones_complement(x) << " ( " << binarify(ones_complement(x), FULL_WIDTH_MODE) << " )\n    2's complement "
      << twos_complement(x) << " ( " << binarify(twos_complement(x), FULL_WIDTH_MODE) << " )" << endl;

      assert(twos_complement(x) == ones_complement(x) + 1); // -x = ~x + 1
  }

  return 0;
}
