/**
 * Problem: Water poured in pyramid of glasses
 * Refer: http://www.geeksforgeeks.org/find-water-in-a-glass/
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

/**
 * Water pouring on pyramid of glasses
 *
 *        1           -> row 1
 *      2   3         -> row 2
 *    4   5   6       -> row 3
 *  7   8   9   10    -> row 4
 */

double findWater(int rows, int col, double pouredWaterAmount) {
  if(rows < col or pouredWaterAmount < 0)
    throw invalid_argument("Wrong parameter.");

  if(pouredWaterAmount == 0)
    return 0;

  vector<double> glass((rows*(rows+1))/2, 0);
  int idx = 0;
  double temp = 0;

  glass[idx] = pouredWaterAmount;

  for(int i=1; i<=rows && pouredWaterAmount > 0; i++) {
    for(int j=1; j<=i; j++, idx++) {
      if(glass[idx] > 1.0) {
        temp = glass[idx] - 1.0;
        glass[idx] -= temp;
      }

      glass[idx + row] += temp/2;
      glass[idx + row + 1] += temp/2;
    }
  }

  return glass[(row*(row-1))/2 + col - 1];
}


int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  try {

    findWater(7, 5, 12);

  } catch(const invalid_argument& excp) {
  // catch(...) to catch em' all!

    cout << "Something went wrong" << endl;

  }


  return 0;
}
