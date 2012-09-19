CFLAGS += -Wall

all: ioctl tty chvt

ioctl: ioctl.o
	gcc -o $@ $^

tty: tty.o
	gcc -o $@ $^

chvt: chvt.o
	gcc -o $@ $^


clean:
	$(RM) *.o *~*
