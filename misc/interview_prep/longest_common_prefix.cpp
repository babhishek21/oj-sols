/**
 * Longest Common Prefix of an array of strings
 */
#include <bits/stdc++.h> // using GCC/G++
using namespace std;

void printVector(vector<string> &strs) {
  for(auto &str: strs)
    cout << str << " ";
  cout << endl;
}

namespace LongestCommonPrefix {

  /**
   * Horizontal scanning
   * findPrefix(S1, findPrefix(S2, findPrefix(...)))
   */
  string horizontalLCP(vector<string> &strs) {
    if(strs.size() == 0)
      return string();

    string prefix = strs[0];

    for(auto &str: strs) {
      while(str.find(prefix) != 0) {
        prefix.erase(prefix.length()-1, string::npos);

        if(prefix.length() < 1)
          return string();
      }
    }

    return prefix;
  }

  /**
   * Vertical scanning
   * Check characters at same position for each string in list.
   */
  string verticalLCP(vector<string> &strs) {
    if(strs.size() == 0)
      return string();

    for(int i=0; i<strs[0].length(); i++) {
      for(int j=1; j<strs.size(); j++) {
        if(i == strs[j].length() || strs[j][i] != strs[0][i])
          return strs[0].substr(0, i);
      }
    }

    return strs[0];
  }

  /**
   * Divide & Conquer
   */
  string mergeCommonPrefix(string leftPrefix, string rightPrefix) {
    for(int i=0; i<min(leftPrefix.length(), rightPrefix.length()); i++)
      if(leftPrefix[i] != rightPrefix[i])
        return leftPrefix.substr(0, i);

    return leftPrefix.substr(0, min(leftPrefix.length(), rightPrefix.length()));
  }

  string DACLCP(vector<string> &strs, int start, int end) {
    if(start >= end)
      return strs[start];

    int mid = start + (end - start)/2;
    string leftPrefix = DACLCP(strs, start, mid);
    string rightPrefix = DACLCP(strs, mid+1, end);
    return mergeCommonPrefix(leftPrefix, rightPrefix);
  }

  string DACLCP(vector<string> &strs) {
    if(strs.size() == 0)
      return string();

    return DACLCP(strs, 0, strs.size()-1);
  }

}

int main() {
  vector<string> strs = {"leets", "leetcode", "leet", "leeds"};

  cout << "Input vector: ";
  printVector(strs);

  cout << "HorizontalLCP: " << LongestCommonPrefix::horizontalLCP(strs) << endl;
  cout << "verticalLCP: " << LongestCommonPrefix::verticalLCP(strs) << endl;
  cout << "Divide&CounquerLCP: " << LongestCommonPrefix::DACLCP(strs) << endl;

  return 0;
}
