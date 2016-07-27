/**
 * Conflicting Intervals/Appointments (Google)
 * O(nlogn) solution to count conflicts (sorting + binary search)
 * O(n**2) for printing all possible conflicting pairs
 */
#include <bits/stdc++.h> // using GCC/G++
#include "custom/prettyprint.hpp" // G++11 only
using namespace std;

struct Interval {
  int index, start, end;
};
ostream& operator << (ostream &stream, const Interval &it) {
  return stream << "[#" << it.index << ": " << it.start << " to " << it.end << "]";
}

vector<pair<Interval, Interval>> conflictingAppointments(vector<Interval> &appointments) {
  vector<pair<Interval, Interval>> result;

  auto comp = [](const Interval &a, const Interval &b) -> bool {
    return a.start == b.start ? a.index < b.index : a.start < b.start;
  };
  sort(appointments.begin(), appointments.end(), comp);

  for(int i=0; i<appointments.size(); i++) {
    int lo = i+1, hi = appointments.size()-1, curr = i;

    while(lo <= hi) {
      int mid = lo + (hi-lo)/2;

      if(appointments[mid].start >= appointments[i].end)
        hi = mid-1;
      else
        curr = mid, lo = mid + 1;
    }

    for(int j = i+1; j <= curr; j++)
      result.emplace_back(appointments[i], appointments[j]);
  }

  return result;
}

int main() {
  vector<Interval> appointments = {
    {0, 1, 5}, {1, 3, 7}, {2, 2, 6}, {3, 10, 15}, {4, 5, 6}, {5, 4, 100}
  };

  cout << "Appointments are: " << appointments << endl;

  cout << "Conflicting appointments are:" << endl;
  for(auto&& tup: conflictingAppointments(appointments))
    cout << tup.first << " conflicts with " << tup.second << endl;

  return 0;
}
