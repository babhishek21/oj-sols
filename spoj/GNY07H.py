# Similar to spoj/M3TILE. Can be easily solved by
# recurrences and some memoization.
#
# Some other direct methods exist as well. See
# http://math.stackexchange.com/q/134612/141388
#
# My favourite method:
# I will generate recurrences based on the repeating blocks.
# Let F(n) be the number of ways to tile 4xn grid with
# 2x1 dominos. Then following cases exist:
#
# + Case-1: |
#           |   F(n) = F(n-1)
#
# + Case-2: ==
#           ==  F(n) = 2*G(n-1)   // Let's call this block G(n)
#           |
#
# + Case-3: ==
#           |   F(n) = H(n-1)     // Let's call this block H(n)
#           ==
#
# + Case-4: ==
#           ==  F(n) = F(n-2)
#           ==
#
# Investigating G(n):
#
# + Case-1: ==
#           ==  G(n) = F(n-1)
#           ||
#
# + Case-2: ==
#           ==  G(n) = G(n-1)
#           |==
#
# Investigating H(n):
#
# + Case-1: ==
#           ||  H(n) = F(n-1)
#           ==
#
# + Case-2: ==
#           |==  H(n) = H(n-2)
#           ==
#
# In short the recurrences are:
# F(n) = F(n-1) + F(n-2) + 2*G(n-1) + H(n-1)
# G(n) = F(n-1) + G(n-1)
# H(n) = F(n-1) + H(n-2)
#
# An equivalent recurrence is:
# F(n) = F(n-1) + 5*F(n-2) + F(n-3) - F(n-4)
#
# I'll solve according to the three recurrences above.

# Calculate and memoize
f = [1,1] + [None]*48
g = [0,1] + [None]*48
h = [0,1] + [None]*48

for i in xrange(2, 50):
  f[i] = f[i-1] + f[i-2] + 2*g[i-1] + h[i-1]
  g[i] = f[i-1] + g[i-1]
  h[i] = f[i-1] + h[i-2]
  # print f[i], g[i], h[i] # DEBUG

n = int(raw_input())

for tc in xrange(n):
  w = int(raw_input())
  print tc+1, f[w]
