CFLAGS += -Wall
PROG := sparse

all: $(PROG)

$(PROG): $(PROG).o
	gcc -o $@ $^

clean:
	$(RM) *.o *~*
