CFLAGS += -Wall

all: setitimer select

setitimer: setitimer.o
	gcc -o $@ $^

select: select.o
	gcc -o $@ $^


clean:
	$(RM) *.o *~*
