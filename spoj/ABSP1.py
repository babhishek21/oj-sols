# SPOJ ABSP1

t = int(raw_input())
for x in xrange(t):
  n = int(raw_input())
  li = map(int, raw_input().split())

  sum = 0
  for i in xrange(n//2):
    sum += (n-1 - 2*i) * (li[n-1-i] - li[i])
    # print i, sum, (n-1 - 2*i)

  print sum
