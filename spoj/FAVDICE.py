# This is the famous Coupon Collector Problem
# It is a sibling problem to the Birthday Paradox

tc = int(raw_input())

for t in xrange(tc):
  n = int(raw_input())
  ans = 0
  for i in xrange(1,n+1):
    ans += 1/float(i)
  ans *= n
  print '%.2f' % ans
