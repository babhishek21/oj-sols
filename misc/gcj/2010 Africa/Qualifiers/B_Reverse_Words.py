# Problem: B_Reverse_Words (CodeJam Qual Africa 2010)
# Lang: Python2.7
# @author: babhishek21

n = int(raw_input())

for tc in xrange(n):
  sentence = reversed(filter(lambda word: word != '', raw_input().split()))
  print "Case #" + str(tc+1) + ":",
  for word in sentence:
    print word,
  print
