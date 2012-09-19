#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/vt.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int fd, num;
	fd = open("/dev/tty0", O_RDWR);
	num = atoi(argv[1]);
	ioctl(fd, VT_ACTIVATE, num);
	ioctl(fd, VT_WAITACTIVE, num);
	return 0;
}
