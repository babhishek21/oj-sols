# Problem: A. Country Leader (APAC 2017 Round A)
# Author: babhishek21
# Lang: Python 2.7

def proc(s):
  st = Set()

  for c in s:
    if c == ' ':
      continue
    st.add(c)

  return len(st)

def solve():
  n = int(raw_input())

  mini = -1
  mins = None
  for i in xrange(n):
    s = raw_input()

    if not mins:
      mins = s

    if proc(s) > mini:
      mini = proc(s)
      mins = s

    if proc(s) == mini:
      mins = min(s, mins)

  return mins

if __name__ == '__main__':
  t = int(raw_input())
  for tc in xrange(t):
    print "Case #{0}: {1}".format(tc+1, solve())
