/**
 * Problem: Fighting the Zombie (FB HackerCup 2017 Qualification Round)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define debug(x) cerr << #x << " : " << x << endl;

int m, n = 20;

// make probability table using dp
// Range of sum possible is 1 (for 1 roll of 4 faced dice)
// to 400 (for 20 rolls of 20 faced dice)
// Dice faces can be {4, 6, 8, 10, 12, 20}
// Max rolls can be 20
double prob[6][22][410];
int dice[6] = {4, 6, 8, 10, 12, 20};

// Calculate probability to get sum X using N rolls
// of a M faced dice
// That is given by the recurrence:
// prob(m, n, X) = 1/m * {
//    prob(m, n-1, X-1)
//  + prob(m, n-1, X-2)
//  + ...
//  + prob(m, n-1, X-m)
// }
//

void dp() {
  // for each of the 6 different die
  for(int idx = 0; idx<6; idx++) {
    m = dice[idx]; // M faced die

    // prob is 1/m for 1st roll
    for(int j=1; j<=m; j++)
      prob[idx][1][j] = 1.0/m;

    // prob for all other n-1 subsequent rolls
    for(int i=2; i<=n; i++) // N rolls
      for(int j=1; j<=m*n; j++) { // M*N sum
        for(int k=1; k<=m && k<j; k++)
          prob[idx][i][j] += prob[idx][i-1][j-k];
        prob[idx][i][j] /= m;
      }
  }
}

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  // build dp table
  dp();

  int t, h, s, X, Y, Z;
  double localans, globalans;
  string spellList, spell;

  cin >> t;

  for(int tc=0; tc<t; tc++) {
    cin >> h >> s;
    globalans = 0;

    getline(cin, spellList); // for trailing '\n' after previous line
    getline(cin, spellList);

    stringstream iss(spellList);

    while(iss >> spell) {
      // Parsing
      // spell is of the form XdY+Z or XdY-Z
      auto dpos = spell.find("d");
      auto pospos = spell.find("+");
      auto negpos = spell.find("-");

      X = stoi(spell.substr(0, dpos));

      if(pospos != string::npos) {
        Y = stoi(spell.substr(dpos+1, pospos));
        Z = stoi(spell.substr(pospos));
      } else if(negpos != string::npos) {
        Y = stoi(spell.substr(dpos+1, negpos));
        Z = stoi(spell.substr(negpos));
      } else {
        Y = stoi(spell.substr(dpos+1));
        Z = 0;
      }

      // Processing
      localans = 0;
      int idx = distance(dice, find(dice, dice + 6, Y));

      if(Z+X >= h) {
        globalans = 1.0;
        break;
      }

      for(int probsum = h-Z; probsum <= X*Y; probsum++)
        localans += prob[idx][X][probsum];

      globalans = max(globalans, localans);
    }

    cout << "Case #" << tc+1 << ": " << fixed << setprecision(6) << globalans << endl;
  }

  return 0;
}
