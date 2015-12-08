/*
ID: babhish1
PROG: milk2
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

    vector<pair<int,int>> jobs;
    int n, i, j, temp;
    int active = 0, idle = 0;

    fin >> n;
    for(temp=0; temp<n; temp++) {
      fin >> i >> j;
      jobs.push_back(make_pair(i,j));
    }

    sort(jobs.begin(), jobs.end());

    temp = 0; // start time for active sequence
    for(i=0,j=0; i<n; i++) {
      if(jobs[i].first > jobs[j].second) {
        // check for active time
        temp = jobs[j].second - jobs[temp].first;
        active = max(active, temp);
        // idle time found
        temp = jobs[i].first - jobs[j].second;
        idle = max(idle, temp);
        // reset
        temp = j = i;
      }
      if(jobs[i].second > jobs[j].second)
        j = i;
      // cout << i << " " << j << endl; // debug
    }
    // check last interval
    temp = jobs[j].second - jobs[temp].first;
    active = max (active, temp);

    fout << active << " " << idle << endl;
    return 0;
}
