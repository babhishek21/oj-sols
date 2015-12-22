n = int(raw_input())

for tc in xrange(n):
  a, b = raw_input().split()
  a = int(a[::-1])
  b = int(b[::-1])
  print str(a+b)[::-1].lstrip('0')
