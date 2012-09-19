BLOCK_SIZE = 4096 * 64

fin = open('f.scratch', 'rb')
fout = open("f.copy", "wb")

while True:
	bl = fin.read(BLOCK_SIZE)
	if not bl: break
	fout.write(bl)

fin.close()
fout.close()
