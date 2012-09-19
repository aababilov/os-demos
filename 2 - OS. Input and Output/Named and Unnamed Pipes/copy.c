#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>


enum {BLOCK_SIZE = 4096 * 64};

char block[BLOCK_SIZE];

int main(int argc, char *argv[])
{
        int fin = argc > 1 ? open(argv[1], O_RDONLY) : 0;
        int fout = argc > 2 ? open(
		argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666) : 1;
        while (1) {
                int sz = read(fin, block, BLOCK_SIZE);
                if (sz <= 0)
			break;
                write(fout, block, sz);
        }
        close(fin);
        close(fout);
        return 0;
}
