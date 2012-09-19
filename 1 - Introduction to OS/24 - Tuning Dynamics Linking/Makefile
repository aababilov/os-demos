all: libwrite_rev.so.1.0


libwrite_rev.so.1.0: write_rev.o
	gcc -shared -Wl,-soname,libwrite_rev.so.1 -o $@ $^ -ldl


write_rev.o: write_rev.c
	gcc -c -fPIC -DPIC -Wall -o $@ $^
