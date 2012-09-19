CFLAGS += -Wall

all: copy mkfifo pipe

copy: copy.o
	gcc -o $@ $^

mkfifo: mkfifo.o
	gcc -o $@ $^

pipe: pipe.o
	gcc -o $@ $^


clean:
	$(RM) *.o *~*
