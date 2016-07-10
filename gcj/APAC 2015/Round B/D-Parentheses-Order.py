# Problem: D. Parentheses Order (APAC 2015 Round B)
# Author: babhishek21
# Lang: Python 2.7

dp = [[0 for i in xrange(101)] for j in xrange(101)]

def prep():
  global dp

  for i in xrange(101):
    dp[0][i] = 1
  dp[1][1] = 1

  for i in xrange(101):
    for j in xrange(i,101):
      dp[i][j] = dp[i-1][j] + dp[i][j-1]

def solve():
  n, k = map(int, raw_input().split())

  l, r, ans = 0, 0, ""

  if k > dp[n][n]:
    return "Doesn't Exist!"

  while len(ans) < 2*n:
    if k <= dp[n-l-1][n-r] and l < n:
      l += 1
      ans += '('
    elif k > dp[n-l-1][n-r]:
      k -= dp[n-l-1][n-r]
      r += 1
      ans += ')'
    else:
      ans += ')'

  return ans

if __name__ == '__main__':
  prep()

  t = int(raw_input())
  for tc in xrange(t):
    print "Case #{0}: {1}".format(tc+1, solve())

##### Explanation for solution: http://wrox.cn/article/100010891/ #######
#
# The process is two fold:
# 1. We need to find how many valid sequences are possible for any given n
# 2. We need to find the kth sequence among those valid sequences
#
# Let dp[i][j] = number of valid sequences with i number of '(' and j number of ')'
# We can see that:
# 1. dp[0][i] = 1 since a sequence "))))))..." can be reduced to empty sequence
# 2. dp[1][1] = 1 since "()" is valid but ")(" isn't
#
# 3. dp[i][j] = dp[i-1][j] + dp[i][j-1] since
#   3.1 we can add a '(' to a dp[i-1][j] sequence to make a valid dp[i][j] sequence
#   3.2 we can add a ')' to a dp[i][j-1] sequence to make a valid dp[i][j] sequence
# This solves the first part of our problem
#
# To generate the kth sequence:
# NOTE: '(' is lexicographically smaller than ')'
#
# If we need n '('s and n ')'s, and currently we have l '('s and r ')'s, then we need to check if
# k exceeds dp[n-l][n-r] on adding a '(' (i.e. l++). If k exceeds, then it is safe to put a '('.
# However if kth sequence lies in range of dp[n-l][n-r], then k must be reduced by dp[n-l][n-r]
# and we are forced to put a ')'. Finally when only stray '(' are left, we put matching ')'.
