# The person who wins the last ball is the infallible winner.
# Since the match transcripts are correct and complete, the
# game ends as soon as the winner is found. Informally, there
# is no scope for reversal of advantage even after the last ball.

t = int(raw_input())

for tc in xrange(t):
  n,s = raw_input().split()
  print s[len(s)-1]
