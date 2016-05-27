# Same as M3TILE and GNY07H. The source limit is tight though.

# Calculate and memoize
a = [1,0] + [None]*34
b = [0,1] + [None]*34
c = [0,1] + [None]*34
d = [0,1] + [None]*34
e = [0,1] + [None]*34
f = [1,1] + [None]*34

for i in xrange(2,35):
  a[i] = a[i-2] + 2*b[i-1] + 2*c[i-1] + d[i-1] + 2*e[i-1]
  b[i] = a[i-1] + b[i-2] + c[i-2]
  c[i] = a[i-1] + 3*c[i-2] + f[i-1]
  d[i] = a[i-1] + d[i-2] + 2*f[i-1]
  e[i] = a[i-1] + e[i-2] + f[i-1]
  f[i] = c[i-1] + e[i-1] + d[i-1]
  # print a[i], b[i], c[i], d[i], e[i], f[i] # DEBUG

for i in xrange(1,18):
  print a[2*i]
