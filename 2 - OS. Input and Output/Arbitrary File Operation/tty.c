#include <stdio.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


int main()
{
	int f;
	char buf[1024];
	struct termios term;
	
	f = open("/dev/tty", O_RDWR);
	ioctl(f, TCGETS, &term);
	term.c_lflag &= ~ECHO;
        ioctl(f, TCSETS, &term);

        printf("Echo is off. Try to type something!\n");
	fgets(buf, sizeof(buf), stdin);
	printf("You line was: `%s'\n", buf);

	term.c_lflag |= ECHO;
        ioctl(f, TCSETS, &term);

        printf("Echo is on. Try to type something again!\n");
	fgets(buf, sizeof(buf), stdin);
	printf("See?\n");
	
	close(f);

	return 0;
}
