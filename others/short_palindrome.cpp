/**
 * Problem: Short Palindrome (HackerRank - World Codesprint 5)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cout << #x << " : " << x << endl;

/**
 * We are looking for combos of increasing indexes to form the character set "X_a, Y_b, Y_c, X_d"
 * where:
 *   X_a and X_d are the same character X occurring at index a and d
 *   Y_b and Y_c are the same character Y occurring at index b and c
 * The condition a < b < c < d must be met. Also note that X == Y is allowed.
 *
 * Thus we need:
 *   pos[C][] is map of indexes at which character C occurs
 *   dp_left[i][Y] is the count of Y_c=i-1 for X_d>=i
 *   dp_right[i][Y] is the count of Y_b=i+1 for X_a<=i
 *
 * Once these quantities are avialable, we choose two characters X and Y (which may be same)
 * and try to count occurences of the sets "XY" and "YX". Any combination of these two sets
 * gives a valid answer.
 */
#define MAXN 1000005
vector<int> pos[26]; // indexes of characters
int dp_left[MAXN][26], dp_right[MAXN][26]; // dp arrays

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  string s;
  cin >> s;

  int n = s.length();

  pos[s[0] - 'a'].pb(0);
  for(int i=1; i<n; i++) {
    pos[s[i] - 'a'].pb(i); // map characters to index positions

    for(int j=0; j<26; j++)
      dp_left[i][j] = dp_left[i-1][j]; // build dp_left[][]

    dp_left[i][s[i-1] - 'a']++;
  }

  for(int i=n-2; i>=0; i--) {
    for(int j=0; j<26; j++)
      dp_right[i][j] = dp_right[i+1][j]; // build dp_right[][]

    dp_right[i][s[i+1] - 'a']++;
  }

  /* DEBUG

  debug(dp_left);
  for(int j=0; j<26; j++) {
    if(!pos[j].empty()) {
      cout << "left[" << (char)('a' + j) << "]: ";
      for(int i=0; i<n; i++)
        cout << dp_left[i][j] << " ";
      cout << endl;
    }
  }

  debug(dp_right);
  for(int j=0; j<26; j++) {
    if(!pos[j].empty()) {
      cout << "right[" << (char)('a' + j) << "]: ";
      for(int i=0; i<n; i++)
        cout << dp_right[i][j] << " ";
      cout << endl;
    }
  }

  */

  long long ans = 0;

  // count combos of form "XYYX"
  for(int x = 0; x < 26; x++) { // choose a character X
    if(pos[x].size() < 2) continue;

    for(int y = 0; y < 26; y++) { // choose a character Y
      long long lterm = 0;
      int nx = pos[x].size();

      for(int i = nx-2; i>=0; i--) {
        lterm += dp_right[pos[x][i+1]][y]; // count occurrence of set "XY"

        ans += lterm * dp_left[pos[x][i]][y]; // multiply with count of occurrence of set "YX"
        ans %= MOD;
      }
    }
  }

  cout << ans << endl;

  return 0;
}
