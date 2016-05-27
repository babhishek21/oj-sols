# Both players play optimally. Hence there is always a way for the first player to start the game such that he/she always wins.

t = int(raw_input())

for tc in xrange(t):
	n, p = map(int, raw_input().split())
	print "Airborne wins." if p == 0 else "Pagfloyd wins."