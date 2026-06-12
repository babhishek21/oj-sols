/**
 * Problem: PON (SPOJ)
 * Author: babhishek21
 * Lang: C++17
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 and above
using namespace std;

/*
Deterministic Miller-Rabin Primality Test

Enough to test 32-bit integers by checking first 4 prime bases (2, 3, 5, 7)
Enough to test 64-bit integers by checking first 12 prime bases (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37)

See: https://cp-algorithms.com/algebra/primality_tests.html#deterministic-version
*/

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

bool DeterministicMillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int t;
long long x;

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O
  // cin.tie(NULL); // for fast I/O; remember to flush cout before subsequent uses of cin

  cin >> t;

  while(t--) {
    cin >> x;

    cout << (DeterministicMillerRabin(x) ? "YES" : "NO") << endl;
  }

  return 0;
}
