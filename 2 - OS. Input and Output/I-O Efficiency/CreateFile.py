f = open('f.scratch','wb')
for i in xrange(10000000):
	f.write(str(i))
f.close()
