#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[64];
	int sz;
	int f;

	f = open("f.out", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	lseek(f, 1024 * 1024, SEEK_SET);
	write(f, "hello", 5);
	close(f);

	f = open("regular.c", O_RDONLY);
	lseek(f, 16, SEEK_SET);
	sz = read(f, buf, sizeof(buf));
	close(f);

	write(1, "===\n", 4);
	write(1, buf, sz);
	write(1, "\n===\n", 5);
     
	return 0;
}
