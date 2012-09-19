#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int f;
	char buf[1];
	char *cmd = argc > 1 ? argv[1] : "no arg";
	struct flock lock = {0};
	
	f = open("f.lock", O_CREAT | O_WRONLY, 0666);

	if (cmd[0] != '1') {
		lock.l_type = F_WRLCK;
		fcntl(f, F_SETLKW, &lock);
	}
	
	write(f, cmd, strlen(cmd));
	fsync(f);
	read(1, buf, sizeof(buf));

	if (cmd[0] != '1') {
		lock.l_type = F_UNLCK;
		fcntl(f, F_SETLKW, &lock);
	}

	close(f);
	return 0;
}
