/**
 * Output elements of a 2D matrix in circular/spiral fashion
 * NOTE: This snippet is C++11 compatible only
 */
#include <bits/stdc++.h> // using GCC/G++11
using namespace std;

vector<int> spiralOut(vector<vector<int>> arr) {
  int k = 0, l = 0, m = arr.size(), n = (arr.size() ? arr[0].size() : 0);
  vector<int> result;

  while(k < m and l < n) {
    // print out first remaining row
    for(int i=l; i<n; i++)
      result.push_back(arr[k][i]);
    k++;

    // print out last remaining column
    for(int i=k; i<m; i++)
      result.push_back(arr[i][n-1]);
    n--;

    if(k < m) {
      // print out last remaining row
      for(int i=n-1; i>=l; i--)
        result.push_back(arr[m-1][i]);
      m--;
    }

    if(l < n) {
      // print out first remaining column
      for(int i=m-1; i>=k; i--)
        result.push_back(arr[i][l]);
      l++;
    }
  }

  return result;
}

int main() {
  // test
  vector<vector<int>> arr {
    {1 , 2 , 3 , 4},
    {12, 13, 14, 5},
    {11, 16, 15, 6},
    {10, 9 , 8 , 7}
  };

  vector<int> res = spiralOut(arr);

  for(auto &x: res)
    cout << x << " ";
  cout << endl;

  return 0;
}
