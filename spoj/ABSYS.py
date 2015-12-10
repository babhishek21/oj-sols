t = int(raw_input())

for tc in xrange(t):
  raw_input()
  expr = raw_input().split()
  a,b,c = [x for x in expr if x not in ["+", "="]]

  if "machula" in a:
    print int(c)-int(b), "+", b, "=", c
  elif "machula" in b:
    print a, "+", int(c)-int(a), "=", c
  elif "machula" in c:
    print a, "+", b, "=", int(a)+int(b)
