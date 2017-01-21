# Problem: Carnival Coins (FB HackerCup 2016 Round 2)
# Author: babhishek21
# Lang: Python 2

inp = raw_input # alias

def solve(n, k, p):
  # precompute probabilities for getting atleast k heads in n coin flips
  prob = {}
  for i in xrange(n+1):
    for j in xrange(k+1):
      prob[i, j] = (
        1 if j == 0 else
        0 if i == 0 else
        prob[i-1, j-1] * p + prob[i-1, j] * (1-p)
      )

  # find optimal playing strategy
  prize = {}
  for i in xrange(n+1):
    prize[i] = (
      0 if i == 0 else
      max(prob[j, k] + prize[i-j] for j in xrange(1, i+1))
    )

  return prize[n]

for t in xrange(int(inp())):
  n, k, p = inp().split()
  print "Case #{}: {:.9f}".format(t+1, solve(int(n), int(k), float(p)))

