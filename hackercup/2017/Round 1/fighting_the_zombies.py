# Problem: Fighting the Zombies (FB HackerCup 2017 Round 1)
# Author: babhishek21
# Lang: Python 2

inp = raw_input # alias

def solve():
  n, r = map(int, inp().split())

  x, y = [0] * n, [0] * n
  sol = {}

  for i in xrange(n):
    x[i], y[i] = map(int, inp().split())

  for i in xrange(n):
    for j in xrange(n):
      # for every pair of points, make rectangle from them
      sol[i, j] = set()

      for k in xrange(n):
        # count how many points lie in this rectangle
        if x[i] <= x[k] <= x[i]+r and y[j] <= y[k] <= y[j]+r:
          sol[i, j].add(k)

  finalsol = set()
  for x in sol:
    finalsol.add(frozenset(sol[x]))

  ans = 0
  for x in finalsol:
    for y in finalsol:
      # for every pair of rectangles, find one with max union of points
      ans = max(ans, len((x | y)))

  return ans

for t in xrange(int(inp())):
  print "Case #{}: {}".format(t+1, solve())

