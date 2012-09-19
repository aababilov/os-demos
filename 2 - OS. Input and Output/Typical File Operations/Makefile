CFLAGS += -Wall

all: regular directory

regular: regular.o
	gcc -o $@ $^


directory: directory.o
	gcc -o $@ $^


clean:
	$(RM) *.o *~*
