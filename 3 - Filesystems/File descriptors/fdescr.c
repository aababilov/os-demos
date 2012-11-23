#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


void wait_a_bit()
{
	char buf[1];
	printf("Press enter\n");
	read(STDIN_FILENO, buf, sizeof(buf));
}

int main(int argc, char*argv[])
{
	char buf[1024];
	char const *filename = "./f.to_remove";
	int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR);
	write(fd, "hello", 5);
	wait_a_bit();
	unlink(filename);

	write(fd, "...and bye", 10);
	wait_a_bit();

	lseek(fd, 0, SEEK_SET);

	buf[read(fd, buf, sizeof(buf))] = 0;
	printf("file contained: %s\n", buf);
	close(fd);
	printf("we have closed it\n");
	wait_a_bit();
	return 0;
}
