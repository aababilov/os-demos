all: c_main asm_main

c_main: c_main.c
	gcc -o $@ $<


asm_main: asm_main.o
	ld -o $@ $<


clean:
	rm -rf *~ *.o

.PHONY: all clean
