CFLAGS += -Wall
PROG := stat

all: $(PROG)

$(PROG): $(PROG).o
	gcc -o $@ $^

clean:
	$(RM) *.o *~*
