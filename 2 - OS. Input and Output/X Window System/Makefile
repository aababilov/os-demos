CFLAGS := -Wall `pkg-config --cflags xscrnsaver`
LDFLAGS := -Wall `pkg-config --libs xscrnsaver`

all: dpms

dpms: main.o
	$(CC) -o $@ $^ $(LDFLAGS)