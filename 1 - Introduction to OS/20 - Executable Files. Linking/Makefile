all: two_files

two_files: main.o aux.o
	gcc -o $@ $^

clean:
	rm -f *.o *~

.PHONY: all clean
