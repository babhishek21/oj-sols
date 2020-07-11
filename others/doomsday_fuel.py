################################
# Problem: Doomsday Fuel (Google foobar)
# Author: babhishek21
# Lang: Python 2.7
#
# Hint: Absorbing Markov Chains
#
# This solution follows the wikipedia format of canonizing the transition matrix `P`:
#   https://en.wikipedia.org/wiki/Absorbing_Markov_chain
#
# Problem Solution at:
#   https://github.com/ivanseed/google-foobar-help/blob/master/challenges/doomsday_fuel/doomsday_fuel.md
################################

# fraction ops
from fractions import Fraction, gcd

def lcm(x, y):
  return (x*y)//abs(gcd(x, y))

# matrix ops
# all matrices are assumed square

def transpose(mat):
  return map(list, zip(*mat))

def cross(mat1, mat2):
  res = []

  for i in xrange(len(mat1)):
    res.append([])

    for j in xrange(len(mat2[0])):
      res[i].append(Fraction(0, 1))

      for k in xrange(len(mat2)):       # assuming len(mat1[0]) == len(mat2)
        res[i][j] += mat1[i][k] * mat2[k][j]

  return res

def inverse(mat):
  order = len(mat)
  id_mat = [[Fraction(int(i==j), 1) for j in xrange(order)] for i in xrange(order)]

  for fd in xrange(order):
    fd_scaler = Fraction(1, 1) / mat[fd][fd]

    for j in xrange(order):
      mat[fd][j] *= fd_scaler
      id_mat[fd][j] *= fd_scaler

    for i in xrange(order):
      if i == fd:
        continue

      cr_scaler = mat[i][fd]
      for j in xrange(order):
        mat[i][j] -= cr_scaler * mat[fd][j]
        id_mat[i][j] -= cr_scaler * id_mat[fd][j]

  return id_mat

## solution

# transforms an ordinary step matrix to P matrix of Absorbing Markov Chain
# See: https://en.wikipedia.org/wiki/Absorbing_Markov_chain
def canonize(mat):
  row_sums = map(sum, mat)
  terminal_row_index = set([i for i, x in enumerate(row_sums) if x == 0])

  frac_mat = [[Fraction(x, row_sums[i]) if row_sums[i] != 0 else Fraction(0, 1) for x in row] for i, row in enumerate(mat)]
  # frac_mat = mat

  nS = len(frac_mat)              # total number of states
  nR = len(terminal_row_index)    # number of terminal / absorbing states
  nQ = nS - nR                    # number of non-terminal / non-absorbing states
  Q = []       # Q is a (nQ x nQ) matrix
  R = []       # R is a (nQ x nR) matrix

  Q = [row[:] for idx, row in enumerate(frac_mat) if idx not in terminal_row_index]
  R = [row[:] for row in Q]

  Q = [[x for i, x in enumerate(row) if i not in terminal_row_index] for row in Q]
  R = [[x for i, x in enumerate(row) if i in terminal_row_index] for row in R]

  # print pprint(locals())

  return Q, R, nQ, nR

def solution(mat):
  Q, R, nQ, nR = canonize(mat)

  if nQ + nR == 1:
    return [1, 1]

  I_sub_Q = [[Fraction(int(i==j), 1) - Q[i][j] for j in range(nQ)] for i in range(nQ)]

  N = inverse(I_sub_Q)

  N_mult_R = cross(N, R)

  # get probabilities for starting at state 0
  denom = map(lambda x: x.denominator, N_mult_R[0])
  denom_lcm = reduce(lambda x, y: lcm(x, y), denom)
  ans = [int(f.numerator * denom_lcm / f.denominator) for f in N_mult_R[0]] + [denom_lcm]

  # import pprint
  # pprint.pprint(locals())

  return ans


if __name__ == "__main__":

  print solution([
    [0, 1, 0, 0, 0, 1],
    [4, 0, 0, 3, 2, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0]
  ])

# Test cases from https://sskaje.me/2017/05/googles-foo-bar-doomsday-fuel/

  assert (
      solution([
          [0, 2, 1, 0, 0],
          [0, 0, 0, 3, 4],
          [0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0]
      ]) == [7, 6, 8, 21]
  )

  assert (
      solution([
          [0, 1, 0, 0, 0, 1],
          [4, 0, 0, 3, 2, 0],
          [0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0]
      ]) == [0, 3, 2, 9, 14]
  )

  assert (
      solution([
          [1, 2, 3, 0, 0, 0],
          [4, 5, 6, 0, 0, 0],
          [7, 8, 9, 1, 0, 0],
          [0, 0, 0, 0, 1, 2],
          [0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0]
      ]) == [1, 2, 3]
  )

  assert (
      solution([
          [0]
      ]) == [1, 1]
  )

  assert (
      solution([
          [0, 0, 12, 0, 15, 0, 0, 0, 1, 8],
          [0, 0, 60, 0, 0, 7, 13, 0, 0, 0],
          [0, 15, 0, 8, 7, 0, 0, 1, 9, 0],
          [23, 0, 0, 0, 0, 1, 0, 0, 0, 0],
          [37, 35, 0, 0, 0, 0, 3, 21, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      ]) == [1, 2, 3, 4, 5, 15]
  )

  assert (
      solution([
          [0, 7, 0, 17, 0, 1, 0, 5, 0, 2],
          [0, 0, 29, 0, 28, 0, 3, 0, 16, 0],
          [0, 3, 0, 0, 0, 1, 0, 0, 0, 0],
          [48, 0, 3, 0, 0, 0, 17, 0, 0, 0],
          [0, 6, 0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      ]) == [4, 5, 5, 4, 2, 20]
  )

  assert (
      solution([
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      ]) == [1, 1, 1, 1, 1, 5]
  )

  assert (
      solution([
          [1, 1, 1, 0, 1, 0, 1, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 1, 1, 1, 0, 1, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 1, 0, 1, 1, 1, 0, 1, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 1, 0, 1, 0, 1, 1, 1, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 1, 0, 1, 0, 1, 0, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      ]) == [2, 1, 1, 1, 1, 6]
  )

  assert (
      solution([
          [0, 86, 61, 189, 0, 18, 12, 33, 66, 39],
          [0, 0, 2, 0, 0, 1, 0, 0, 0, 0],
          [15, 187, 0, 0, 18, 23, 0, 0, 0, 0],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      ]) == [6, 44, 4, 11, 22, 13, 100]
  )

  assert (
      solution([
          [0, 0, 0, 0, 3, 5, 0, 0, 0, 2],
          [0, 0, 4, 0, 0, 0, 1, 0, 0, 0],
          [0, 0, 0, 4, 4, 0, 0, 0, 1, 1],
          [13, 0, 0, 0, 0, 0, 2, 0, 0, 0],
          [0, 1, 8, 7, 0, 0, 0, 1, 3, 0],
          [1, 7, 0, 0, 0, 0, 0, 2, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
      ]) == [1, 1, 1, 2, 5]
  )
