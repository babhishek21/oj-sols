/**
 * Some basic number theory algos.
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

/**
 * Sieve of Eratosthenes (with negative logic)
 */
bool notprime[1002002];

void buildSieve() {
  notprime[0] = notprime[1] = true;

  for(int i=2; i<1001; i++) {
    if(!notprime[i]) {
      for(int j=i*i; j<1002001; j+=i)
        notprime[j] = true;
    }
  }
}

bool isPrime(long long n) {
  return !notprime[(int)(n)];
}

/**
 * Sieve of Eratosthenes (on demand)
 */
vector<bool>* sieve(unsigned int n) {
  vector<bool>* prime = new vector<bool>(n, true);

  (*prime)[0] = (*prime)[1] = false;

  for(int i=2; i<(int)sqrt(n)+1; i++) {
    if((*prime)[i]) {
      for(int j=i*i; j<n; j+=i)
        (*prime)[j] = false;
    }
  }

  return prime;
}

/**
 * Euclidean Algorithm for GCD
 */

// Assumption: a >= b
// Assumption: a and b cannot be zero simultaneously
int rGCD(int a, int b) {
  if(b == 0)
    return a;
  else
    return euclidGCD(b, a%b);
}

int iGCD(int a, int b) {
  while(b != 0) {
    int temp = b;
    b = a%b;
    a = temp;
  }
}

int LCM(int a, int b) {
  return b*a/rGCD(a,b);
}

/**
 * Base conversions
 */

// Number n in base b (b <= 10) to base 10 (decimal)
int toDecimal(int n, int b) {
  int ans = 0, multiplier = 1;

  while(n > 0) {
    ans += (n%10) * multiplier;
    n /= 10;
    multiplier *= b;
  }

  return ans;
}

// Number n in base 10 (decimal) to base b (b <= 10)
int fromDecimal(int n, int b) {
  int ans = 0, multiplier = 1;

  while(n > 0) {
    ans += (n%b) * multiplier;
    n /= b;
    multiplier *= 10;
  }

  return ans;
}

// Number n in base 10 (decimal) to base b (10 < b <= 16)
string fromDecimalHex(int n, int b) {
  string chars = "0123456789ABCDEF", ans = "";

  while(n > 0) {
    ans = chars[n%b] + ans;
    n /= b;
  }

  return ans;
}

int main() {
  // testing sieve (on-demand)

  // by pointer
  vector<bool> *prime = sieve(30);

  for(auto it = prime->begin(); it != prime->end(); it++)
    cout << *it << " ";
  cout << "$" << (*prime)[5] << endl;


  // by static reference
  vector<bool> &prime1 = *(sieve(30));

  for(auto it = prime1.begin(); it != prime1.end(); it++)
    cout << *it << " ";
  cout << "$" << prime1[5] << endl;

  return 0;
}
