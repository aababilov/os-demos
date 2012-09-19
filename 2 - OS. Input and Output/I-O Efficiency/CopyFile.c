#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

enum {BLOCK_SIZE = 4096 * 64};

char block[BLOCK_SIZE];

int main()
{
	int fin = open("f.scratch", O_RDONLY);
	int fout = open("f.copy", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	while (1) {
		int sz = read(fin, block, BLOCK_SIZE);
		if (sz <= 0) break;
		write(fout, block, sz);
	}
	close(fin);
	close(fout);
	return 0;
}
