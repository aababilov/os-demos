#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main()
{
	char buf[4];
	int i;
	int fd = open("f.sparse", O_CREAT | O_RDWR, 0666);
	
	lseek(fd, 1024 * 1024, SEEK_SET);
	write(fd, "hello", 5);

	lseek(fd, 64, SEEK_SET);
	read(fd, buf, sizeof(buf));
	for (i = 0; i < ARRAY_SIZE(buf); ++i) {
		printf("%d", buf[i]);
	}
	printf("\n");
	
	close(fd);
	return 0;
}
