/**
 * Problem: PK and interesting language (HackerEarth)
 * Uses DP and Matrix Exponentiation for optimization.
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 1000000007;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

//////////////////
// Matrix class //
//////////////////
static const long long MOD_MOD = (long long) MOD * MOD;

template <typename T>
struct Matrix {
  vector<vector<T>> mat;
  int rows, cols;

  Matrix() {}
  Matrix(vector<vector<T>> val): mat(val), rows(val.size()), cols(val[0].size()) {}

  vector<T> &operator[](int rowIdx) {
    return mat[rowIdx];
  }

  friend ostream &operator<<(ostream &out, const Matrix &matrix) {
    out << matrix.mat;
    return out;
  }

  static Matrix identity_matrix(int n) {
    vector<vector<T>> val(n, vector<T>(n, 0));

    while(n--)
      val[n][n] = 1;

    return Matrix(move(val));
  }

  Matrix operator*(const Matrix &other) const {
    int m = rows, n = other.cols;

    assert(cols == other.rows);

    vector<vector<T>> res(m, vector<T>(n, 0));

    for(int i=0; i<m; i++)
      for(int j=0; j<n; j++) {
        T tmp = 0;
        for(int k=0; k<cols; k++) {
          tmp += mat[i][k] * other.mat[k][j];

          while(tmp >= MOD_MOD)
            tmp -= MOD_MOD;
        }
        res[i][j] = tmp % MOD;
      }

    return Matrix(move(res));
  }

  Matrix operator^(long long power) const {
    auto res = Matrix<T>::identity_matrix(cols);   // choose dimension to match the matrix you'll multiply this with
    auto M = *this;

    while(power) {
      res = (power&1 ? res * M : res);
      M = M * M;
      power >>= 1;
    }

    return res;
  }

  bool is_square() const {
    return rows == cols;
  }
};

///////////////////////////////////
// Matrix Exponentiation Helpers //
///////////////////////////////////

template <typename U>
struct MatrixExponentiation {
  Matrix<U> M_powers[55]; // doubling powers of Matrix M, i.e. M, M^2, M^4, M^8 ...

  MatrixExponentiation(Matrix<U> M) {
    M_powers[0] = M;

    for(int i=1; i<55; i++)
      M_powers[i] = M_powers[i-1] * M_powers[i-1];
  }

  Matrix<U> fast_mexp_optim(long long power) {
    auto res = Matrix<U>::identity_matrix(M_powers[0].cols);  // choose dimension to match the matrix you'll multiply this with

    int idx = 0;
    while(power) {
      res = (power&1 ? res * M_powers[idx] : res);
      idx++;
      power >>= 1;
    }

    return res;
  }
};

///////////////////////////
// Boilerplate ends here //
///////////////////////////

int main() {
  // ios_base::sync_with_stdio(false); // for fast I/O

  int t;
  char c;
  long long l;

  vector<vector<long long>> m(26, vector<long long>(26, 0));

  for(int i=0; i<26; i++)
    for(int j=0; j<26; j++)
      cin >> m[i][j];

  MatrixExponentiation<long long> mexp((Matrix<long long>(m))); // extra parentheses to handle C++'s Most-Vexing-Parse problems

  cin >> t;

  while(t--) {
    cin >> c >> l;

    Matrix<long long> dp(vector<vector<long long>>(1, vector<long long>(26, 1)));

    /*
      (dp[a], dp[b] ... dp[z])[i+1] = (dp[a], dp[b] ... dp[z])[i] * M       where:

      1. dp[a][i] is the number of number of words of length `i+1` and ending at character `a`
      2. dp[a][0] = 1 (for any character)
      3. M is matrix such that M[a][b] is `1` if the character `b` can follow character `a` in a string

      So, dp[...][l-1] = dp[...][0] * M^(l-1)
     */

    cout << (dp * mexp.fast_mexp_optim(l-1))[0][c-'a'] << endl;
  }

  return 0;
}
