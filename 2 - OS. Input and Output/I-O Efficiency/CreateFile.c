#include <stdio.h>

int main()
{
	FILE*f = fopen("f.scratch", "wb");
	int i;
	for (i = 0; i < 10000000; ++i)
		fprintf(f, "%d", i);
	fclose(f);
	return 0;
}
