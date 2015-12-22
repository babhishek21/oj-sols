# Let's be systematic.
## Count of Squares:
# n -> ans
# 1 -> 1
# 2 -> 1
# 3 -> 1
# 4 -> 2
# 5 -> 2
# 9 -> 3
# In short count of squares = floor(sqrt(n))
## Count of rectangles:
# n -> ans
# 1 -> 0
# 2 -> 1
# 3 -> 2
# 4 -> 3
# 5 -> 4
# 6 -> 6
# No pattern here. Just count i,j pairs such that i<j and i*j = n
# I'll combine counting squares and rectangles in single loop.

n = int(raw_input())
ans = 0
for i in xrange(1, int(n**0.5) + 1):
  for j in xrange(i, n+1):
    ans += 1 if i*j <= n else 0
print ans
