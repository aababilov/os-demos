#define _XOPEN_SOURCE

#include <sys/select.h>
#include <stdio.h>      
#include <stdlib.h>	/* For errno, putenv, etc.	      */
#include <errno.h>	/* For errno on SunOS systems	      */
#include <termios.h>	/* tcgetattr(), struct termios, etc.  */
#include <sys/types.h>	/* Required by unistd.h below	      */
#ifdef HAVE_SYS_IOCTL_H
#   include <sys/ioctl.h> /* For ioctl() (surprise, surprise) */
#endif
#include <string.h>	/* strstr(), strcpy(), etc.	      */
#include <signal.h>	/* sigaction(), sigprocmask(), etc.   */
#include <sys/stat.h>	/* Required by dir.h & panel.h below  */
#include <ctype.h>	/* isalnum() */
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static struct termios shell_mode;
static int masterfd, slavefd;
static char *slavedevice;
static volatile int nochld = 0;

#define max(a, b) ((a) > (b) ? (a) : (b))

void
get_console_attributes(void)
{
    /* Get our current terminal modes */

    if (tcgetattr (STDOUT_FILENO, &shell_mode)) {
	fprintf (stderr, "Cannot get terminal settings: %s\r\n",
		 strerror(errno));
	return;
    }
}

int set_noncan(int desc)
{
	int result;
	struct termios raw_mode;
	raw_mode = shell_mode;
	
	raw_mode.c_lflag &= ~ICANON;  /* Disable line-editing chars, etc.   */
	raw_mode.c_lflag &= ~ISIG;    /* Disable intr, quit & suspend chars */
	raw_mode.c_lflag &= ~ECHO;    /* Disable input echoing		    */
	raw_mode.c_iflag &= ~IXON;    /* Pass ^S/^Q to subshell undisturbed */
	raw_mode.c_iflag &= ~ICRNL;   /* Don't translate CRs into LFs	    */
	raw_mode.c_oflag &= ~OPOST;   /* Don't postprocess output	    */
	raw_mode.c_cc[VTIME] = 0;     /* IE: wait forever, and return as    */
	raw_mode.c_cc[VMIN] = 1;      /* soon as a character is available   */

//	cfmakeraw(&new_termios);
	result = tcsetattr(desc, TCSANOW, &raw_mode);
	if (result < 0)	{
		perror ("error in tcgetattr");
		return 1;
	}
	return 0;
}

int restore_can(int desc)
{
	int result = tcsetattr(desc, TCSANOW, &shell_mode);
	if (result < 0)	{
		perror ("error in tcgetattr");
		return 1;
	}
	return 0;
}

void read_in()
{
	int out = open("f.out", O_WRONLY|O_TRUNC|O_CREAT, 0644);
	#define pty_buffer_size 512
	char pty_buffer[pty_buffer_size];
	fd_set read_set;		/* For `select' */
	int maxfdp;
	int bytes;			/* For the return value from `read' */
	int i;			/* Loop counter */

	struct timeval wtime;	/* Maximum time we wait for the subshell */
	struct timeval *wptr;

	/* we wait up to 10 seconds if fail_on_error, forever otherwise */
	wtime.tv_sec = 10;
	wtime.tv_usec = 0;
	wptr = NULL;//&wtime;
	
	while (1) {
		if (nochld)
			break;

		/* Prepare the file-descriptor set and call `select' */
		FD_ZERO (&read_set);
		FD_SET(masterfd, &read_set);
		FD_SET(STDIN_FILENO, &read_set);
		maxfdp = max(masterfd, STDIN_FILENO);

		if (select (maxfdp + 1, &read_set, NULL, NULL, wptr) == -1) {
			/* Despite using SA_RESTART, we still have to check for this */
			if (errno == EINTR)
				continue;	/* try all over again */
			tcsetattr (STDOUT_FILENO, TCSANOW, &shell_mode);
			fprintf (stderr, "select (FD_SETSIZE, &read_set...): %s\r\n",
				 strerror (errno));
			exit (1);
		}

		if (FD_ISSET(masterfd, &read_set))
			/* Read from the subshell, write to stdout */

			/* This loop improves performance by reducing context switches
			   by a factor of 20 or so... unfortunately, it also hangs MC
			   randomly, because of an apparent Linux bug.  Investigate. */
			/* for (i=0; i<5; ++i)  * FIXME -- experimental */
		{
			bytes = read (masterfd, pty_buffer, pty_buffer_size);

			/* The subshell has died */
			if (bytes == -1 && errno == EIO && nochld)
				break;

			if (bytes <= 0) {
				tcsetattr (STDOUT_FILENO, TCSANOW, &shell_mode);
				fprintf (stderr, "read (subshell_pty...): %s\r\n",
					 strerror (errno));
				exit (1);
			}
			write (STDOUT_FILENO, pty_buffer, bytes);
		}

		else if (FD_ISSET (STDIN_FILENO, &read_set))
			/* Read from stdin, write to the subshell */
		{
			bytes = read (STDIN_FILENO, pty_buffer, pty_buffer_size);
			if (bytes <= 0) {
				tcsetattr (STDOUT_FILENO, TCSANOW, &shell_mode);
				fprintf (stderr,
					 "read (STDIN_FILENO, pty_buffer...): %s\r\n",
					 strerror (errno));
				exit (1);
			}

			write (masterfd, pty_buffer, bytes);
			write (out, pty_buffer, bytes);			
		}
	}
	close(out);
	
}
void make_pty()
{
	masterfd = posix_openpt(O_RDWR|O_NOCTTY);

	if (masterfd == -1
	    || grantpt (masterfd) == -1
	    || unlockpt (masterfd) == -1
	    || (slavedevice = ptsname(masterfd)) == NULL) {
		perror("error while open pty");
		return;
	}
	printf("slave device is: %s\n", slavedevice);
}

int do_child_part()
{
	int fd;
	close(masterfd);

	slavefd = open(slavedevice, O_RDWR);
	if (slavefd < 0)
		return;

	dup2 (slavefd, STDIN_FILENO);
	dup2 (slavefd, STDOUT_FILENO);
	dup2 (slavefd, STDERR_FILENO);

	close(slavefd);
	execlp("/bin/bash", "bash", NULL);
}

int spawn_slave()
{
	int res = fork();
	if (res < 0) {
		perror("cannot fork");
		return;
	}
	if (res == 0) {
		printf("child.\n");
		do_child_part();
	}
}

static void clear_zombie()
{
	waitpid(-1, NULL, 0);
	nochld = 1;
}

void set_clear_zombie()
{
	struct sigaction actn = {0};
	actn.sa_handler = clear_zombie;
	sigaction(SIGCHLD, &actn, 0);
}

int main(int argc, char *argv[])
{
	get_console_attributes();
	set_clear_zombie();
	make_pty();
	spawn_slave();
	set_noncan(STDIN_FILENO);
	read_in();
	restore_can(STDIN_FILENO);
}
