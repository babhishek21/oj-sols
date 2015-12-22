import math
tc = int(raw_input())

for t in xrange(tc):
  n = int(raw_input())
  ans = int(math.log(n-1, 2)) + 2
  print ans
