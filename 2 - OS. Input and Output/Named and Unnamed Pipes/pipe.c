#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define COLOR_YELLOW "\033[1;33m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_CLEAR "\033[0m"

int main(int argc, char *argv[])
{
        printf(COLOR_YELLOW "Let the story begin\n");
	printf("I am a parent, my pid = %d\n", getpid());

	char c;
	int pipes[2];
	int child_pid;
	pipe(pipes);
	printf("I have two pipes: %d %d\n", pipes[0], pipes[1]);
	printf(COLOR_CLEAR);
	
	child_pid = fork();
	if (child_pid > 0) {
		printf(COLOR_GREEN "I am still a parent, my pid = %d\n"COLOR_CLEAR, getpid());

		int f_random = open("/dev/urandom", O_RDONLY);
		read(f_random, &c, 1);
		close(f_random);

		printf(COLOR_GREEN"I read a random number `%d' and send it to pipes[1]\n"COLOR_CLEAR, (int)c);
		write(pipes[1], &c, 1);
		c = 0;

		printf(COLOR_GREEN"Now I wait for a response from pipes[0]\n"COLOR_CLEAR);
		read(pipes[0], &c, 1);
		printf(COLOR_GREEN "I have read number `%d'. Good night, sweet pipes.\n"COLOR_CLEAR, (int)c);
	} else {
		printf(COLOR_RED "I am a child, my pid = %d\n" COLOR_CLEAR, getpid());

		read(pipes[0], &c, 1);
		printf(COLOR_RED "I read a number `%d' from pipes[0]\n"COLOR_CLEAR, (int)c);

		printf(COLOR_RED "Then I slowly divide it by 2 and send it to pipes[1]\n"COLOR_CLEAR);
		c /= 2;
		sleep(5);
		write(pipes[1], &c, 1);

		printf(COLOR_RED "And that's my farewell.\n"COLOR_CLEAR);
	}
	close(pipes[0]);
	close(pipes[1]);
      
        return 0;
}
