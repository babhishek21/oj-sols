/**
 * Problem: Sieve of Sundaram
 * Sieves out prime numbers between less than `2n+2` for input limit `n`
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MAXN = 1002002;

bool sieve[MAXN];

void sieve_of_sundaram(int n = MAXN) {
  for(int j=1; j<n; j++)
    for(int i=1; i<=j && (i+j+2*i*j <= n); i++)
      sieve[i+j+2*i*j] = true;
}

inline bool isprime(const int x) {
  return (x == 2) || (x > 2 && (x&1 != 0) && !sieve[(x-1)/2]);
}

int main() {
  int n = 100;

  sieve_of_sundaram(n);

  cout << boolalpha;

  for(int i=0; i < 2*n+2; i++)
    cout << i << " " << isprime(i) << endl;

  return 0;
}
