all: libwrite_rev.so.1.0

libwrite_rev.so.1.0: write_rev.o
	gcc -shared -Wl,-soname,libwrite_rev.so.1 -Wl,-e,my_main -o $@ $^

write_rev.o: write_rev.c
	gcc -g -c -fPIC -DPIC -Wall -o $@ $^

clean:
	rm -rf *~ *.o

.PHONY: all clean
