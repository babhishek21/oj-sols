/**
 * CTCI 6th (Indian) Edition.
 * Chapter 1: Arrays & Strings
 * C++11 or C++14 required
 */
#include <bits/stdc++.h> // using GCC/G++11
using namespace std;

/**
 * Utility functions
 */
unsigned int countSpaces(const vector<char> &str, unsigned int trueLen) {
  // count spaces in a char array till only given length
  unsigned int ret = 0;
  for(int i=0; i<trueLen; i++) {
    if(isspace(str[i]))
      ret++;
  }
  return ret;
}

bool isSubstring(const string &a, const string &b) {
  if(a.find(b) != string::npos)
    return true;
  return false;
}

void printMatrix(int **matrix, int N) {
  // print NxN matrix
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
}


/* ====== Problem Solutions ======== */

/**
 * 1.1 Is Unique
 * Character Set agnostic solution in O(nlogn)
 */
bool isUnique(string str) {
  sort(str.begin(), str.end());

  for(int i=1; i<str.size(); i++)
    if(str[i] == str[i-1])
      return false;

  return true;
}

/**
 * 1.2 Check Permutation
 * O(nlogn) sort solution
 */
bool checkPerm(string a, string b) {
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  return a == b;
}

/**
 * 1.3 URLify
 * In place O(n) algorithm. `url` has enough
 * space and does not require resizing.
 */
void URLify(vector<char> &url, unsigned int trueLen) {
  int writerHead = 2*countSpaces(url, trueLen) + trueLen - 1, readerHead = trueLen - 1;

  while(readerHead >= 0) {
    if(!isspace(url[readerHead]))
      url[writerHead--] = url[readerHead--];
    else {
      url[writerHead--] = '0';
      url[writerHead--] = '2';
      url[writerHead--] = '%';
      readerHead--;
    }
  }
}

/**
 * 1.4 Palindrome Permutation
 * O(|alpha|) extra space + O(n) time algorithm
 */
bool palinPerm(string str) {
  unordered_map<char, int> charMap; // C++11 only
  bool singleSolitary = true;

  transform(str.begin(), str.end(), str.begin(), ::tolower);
  for(char &c: str)
    if(!isspace(c))
      charMap[c]++;

  for(auto &tup: charMap)
    if(tup.second == 1)
      if(singleSolitary)
        singleSolitary = false;
      else
        return false;

  return true;
}

/**
 * 1.5 One Away
 * Simple O(n) algorithm with O(n) extra space
 */
bool oneAway(const string &a, const string &b) {
  if(abs(a.size() - b.size()) > 1)
    return false;

  string shorter = (a.size() < b.size() ? a : b);
  string longer = (a.size() < b.size() ? b : a);

  int shorterindex = 0, longerindex = 0;
  bool alreadyMismatch = false;

  while(shorterindex < shorter.size() && longerindex < longer.size()) {
    // Mismatch occurs
    if(shorter[shorterindex] != longer[longerindex]) {
      // already had a Mismatch, return false
      if(alreadyMismatch)
        return false;

      // register this Mismatch
      alreadyMismatch = true;

      // sizes are same. we can do a replace
      if(shorter.size() == longer.size())
        shorterindex++;

      // else looks like a insertion/deletion. stay put

    } else
    // no miss-match till now, move shorter index
      shorterindex++;

    // always move longer index
    longerindex++;
  }

  return true;
}

/**
 * 1.6 String Compression
 * O(n) time + O(n) space
 */
string compressString(const string &str) {
  int count = 1;
  char prev = str[0];
  string ret;

  for(int i=1; i<str.size(); i++)
    if(str[i] == prev)
      count++;
    else {
      ret += prev + ((count > 1) ? to_string(count) : "");
      count = 1;
      prev = str[i];
    }

  if(count > 0)
    ret += prev + ((count > 1) ? to_string(count) : "");

  return ret;
}

/**
 * 1.7 Rotate Matrix
 * We need to rotate matrix right my 90 degrees
 * (which is effectively a +270 degree rotation)
 * This is similar to spiral matrix printing
 * O(N^2) algorithm
 */
void rotateMatrix(int **matrix, int N) {
  for(int layer = 0; layer < N/2; layer++) {
    int lo = layer, hi = N-1-layer;

    for(int i=lo; i<hi; i++) {
      int offset = i - lo;

      // save top
      int temp = matrix[lo][i];

      // top <- left
      matrix[lo][i] = matrix[hi-offset][lo];

      // left <- bottom
      matrix[hi-offset][lo] = matrix[hi][hi-offset];

      // bottom <- right
      matrix[hi][hi-offset] = matrix[i][hi];

      // right <- top (saved before)
      matrix[i][hi] = temp;
    }
  }
}

/**
 * 1.8 Zero Matrix
 * Simple O(M+N) extra time algorithm
 * with O(M+N) extra space
 */
void zeroMatrix(int **matrix, int rowNum, int colNum) {
  vector<int> rows, cols;

  for(int i=0; i<rowNum; i++)
    for(int j=0; j<colNum; j++) {
      if(matrix[i][j] == 0) {
        rows.push_back(i);
        cols.push_back(j);
      }
    }

  for(int &row: rows) {
    for(int i=0; i<colNum; i++)
      matrix[row][i] = 0;
  }

  for(int &col: cols) {
    for(int i=0; i<rowNum; i++)
      matrix[i][col] = 0;
  }
}

/**
 * 1.9 String Rotation
 * Simple O(n) time + O(n) extra space
 * Check whether s1 is substring of s2+s2
 * or vice-versa
 */
bool stringRotation(const string &s1, const string &s2) {
  if(s1.length() == s2.length())
    return isSubstring(s1+s1, s2);
  return false;
}

/* ======== Testing ======== */
int main() {
  // set cout to display bool names instead of integer
  cout << boolalpha;

  // is unique test
  cout << "Testing isUnique: abcdaefgh "
      << isUnique("abcdaefgh") << endl;

  // check permutation test
  cout << "Testing checkPerm: abc, cab "
      << checkPerm("abc", "cab") << endl;

  // urlify test
  vector<char> url(17);
  string str = "Mr John Smith";
  copy(str.begin(), str.end(), url.begin());
  URLify(url, 13);
  cout << "Testing URLify: " << str << " "
      << string(url.begin(), url.end()) << endl;

  // palindrome permutation test
  cout << "Testing palinPerm: \"Tact Coa\" "
      <<  palinPerm("Tact Coa") << endl
      << "Testing palinPerm: \"TactTCa\" "
      <<  palinPerm("TactTCa") << endl;

  // one away test
  cout << "Testing oneAway: pale, ple "
      << oneAway("pale", "ple") << endl
      << "Testing oneAway: pales, pale "
      << oneAway("pales", "pale") << endl
      << "Testing oneAway: pale, bale "
      << oneAway("pale", "bale") << endl
      << "Testing oneAway: pale, bake "
      << oneAway("pale", "bake") << endl;

  // string compression test
  cout << "Testing compressString: aabcccccaa$$$ "
      << compressString("aabcccccaa$$$") << endl;

  // rotate matrix test
  int **mat = new int*[4];
  for(int i=0; i<4; i++)
    mat[i] = new int[4];

  for(int i=0; i<16; i++)
    mat[i/4][i - (i/4)*4] = i+1;

  cout << "Testing rotateMatrix:" << endl
      << "Original matrix:" << endl;
  printMatrix(mat, 4);
  rotateMatrix(mat, 4);
  cout << "Rotated matrix:" << endl;
  printMatrix(mat, 4);

  // zero matrix test
  mat[1][2] = mat[2][1] = 0;

  cout << "Testing zeroMatrix:" << endl
      << "Original matrix:" << endl;
  printMatrix(mat, 4);
  zeroMatrix(mat, 4, 4);
  cout << "Zeroed matrix:" << endl;
  printMatrix(mat, 4);

  // cleanup
  for(int i=0; i<4; i++)
    delete[] mat[i];
  delete[] mat;

  // string rotation test
  cout << "Testing stringRotation: watermelon, ermelonwat "
      <<  stringRotation("watermelon", "ermelonwat") << endl
      << "Testing stringRotation: watermelon, ermelonate "
      <<  stringRotation("watermelon", "ermelonate") << endl;

  return 0;
}
