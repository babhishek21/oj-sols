# I'll use python because it checks string membership quite well
for t in xrange(int(raw_input())):
  mystr = raw_input()
  flag = True
  for i in xrange(len(mystr)):
    for j in xrange(i, len(mystr)):
      temp = (mystr[i:j+1])
      # print temp, temp[::-1]
      if temp[::-1] not in mystr:
        flag = False
        break
  print "YES" if flag else "NO"
