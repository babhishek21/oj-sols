/**
 * Problem: Advent of Code 2025 - Day 1: Secret Entrance
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // C++11 only
using namespace std;

#define debug(x) cerr << "\033[31m [DBG] \033[0m" << #x << " : " << x << endl;

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int curr = 50,  // curr pointer; always normalized to range [0, 99]
    prev = 50,
    val = 0,      // absolute pointer movement; presumably in range [1, ∞)
    ans1 = 0,     // pointer landings on 0
    ans2 = 0;     // pointer crossings across 0
  char dir;       // direction of pointer movement
  string line;

  #ifdef DBG
  debug(curr);
  #endif

  while(getline(cin, line)) {
    dir = line[0];
    val = stoi(line.substr(1));

    prev = curr;
    curr += (val % 100) * (dir == 'L' ? -1 : 1);
    ans2 += val / 100;

    if(curr == 0) {
      ans1++;

      // if pointer was previously at 0, val must have been a multiple of 100
      // if pointer was at k, val%100 must also have been k (movement in negative direction)
      ans2 += (prev != 0);
    }
    else if(curr < 0) {
      assert(curr >= -99);

      ans2 += (prev != 0);

      curr += 100; // normalize curr
    }
    else if(curr > 99) { // movement must be in positive direction
      assert(curr <= 198);

      if(curr == 100)
        ans1++;

      ans2++;  // atleast 1 crossing was made by tipping over 0

      curr -= 100; // normalize curr
    }

    assert(curr >= 0 && curr <= 99);

    cerr << line << " -> " << curr << " :: " << ans1 << ' ' << ans2 << '\n'; // debug
  }

  cout << "answers: " << ans1 << ' ' << ans2 << endl;

  return 0;
}
