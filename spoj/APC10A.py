while True:
  a,b,c = map(int, raw_input().split())
  if a == 0 and b == 0 and c == 0: break;
  elif b-a == c-b: print "AP", c+b-a
  else: print "GP", c*b/a
