# An question entirely solved by recurrences.
# Memoization to chache answers is helpful.
# Apart from that I see no need for DP.
#
# It is helpful to note that if T(n) is the required answer
# for 3xn grid, then:
# T(0) = 1
# T(1) = 0
# T(2) = 3
# T(3) = 0
#
# There are a few ways to find the correct recurrence.
# Most popular is http://stackoverflow.com/a/16388865/2844164
# My favourite method (http://abitofcs.blogspot.in/2014/10/a-bit-of-dp-spoj-m3tile.html) is
# Let S(n,k) be the ways to fill up a grid where 1 to `k` rows
# of the columns 1 to `n` are already filled up. Then the
# following recurrences exist.
# For k = 0:   S(n,0) = S(n-2,0) + 2*S(n-1,1)
# + Case-1: || S(n,0) = S(n-2,0)
#           ==
# + Case-2: |  S(n,0) = 2*S(n-1,1)
#           ==
# For k = 1:   S(n,1) = S(n-1,0) + S(n-2,2)
# + Case-1: =
#           |  S(n,1) = S(n-1,0)
# + Case-2: =
#           == S(n,1) = 2*S(n-1,2)
#           ==
# For k = 2:   S(n,2) = S(n-1,1)
# + Case-1: =
#           =  S(n,2) = S(n-1,1)
#           ==
# Solving the recurrences, we get:
# S(n,0) = 4*S(n-2,0) - S(n-4,0)
# where S(n,0) = T(n).
#
# The solution recurrence is
# T(n) = 4*T(n-2) - T(n-4)
#
# Constraints of the questions make sure that n<31.

# Calculate and memoize
dp = [1,0,3,0] + [None]*27

for i in xrange(4,31):
  dp[i] = 4*dp[i-2] - dp[i-4]

n = int(raw_input())

while n != -1:
  print dp[n]
  n = int(raw_input())
