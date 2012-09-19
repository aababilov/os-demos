#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char my_interp[] __attribute__((section(".interp"))) = "/lib/ld-linux-x86-64.so.2";

void my_main(int argc, char **argv)
{
	int i;

	write(1, "Called as:", 8);
	for (i = 0; i < argc; i++)
	    printf(" %s", argv[i]);
	printf("\n");
	exit(0);
}