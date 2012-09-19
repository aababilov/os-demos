#include <unistd.h>
#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>


int main()
{
	int f;

	f = open("/dev/cdrom", O_RDWR | O_NONBLOCK);
	ioctl(f, CDROMEJECT);
	close(f);

	return 0;
}
