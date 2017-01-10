# Problem: Progress Pie (FB HackerCup 2017 Qualification Round)
# Author: babhishek21
# Lang: Python

import math
inp = raw_input

closeEnough = lambda a, b: (a-b) <= 10**(-6)

cx, cy, rr = 50, 50, 50
vx, vy = 0, 50

for t in xrange(int(inp())):
  p, x, y = map(int, inp().split())
  print "Case #%d:"%(t+1),

  # check if no progress
  if p == 0:
    print "white"
    continue

  # check against radius
  d = ((x-cx)**2 + (y-cy)**2)**0.5

  if not closeEnough(d, rr):
    # print "white", d
    print "white"
    continue

  if d == 0:
    print "white" if p <= 0 else "black"
    continue

  # check angle
  cosTheta = ((x-cx)*vx + (y-cy)*vy)/(d*rr)
  theta = math.acos(cosTheta)

  perc = theta/math.pi * 50.0
  perc = 100 - perc if x < cx else perc

  print ("black" if closeEnough(perc, p) else "white")
  # print ("black" if closeEnough(perc, p) else "white"),
  # print cosTheta, theta, perc, p
