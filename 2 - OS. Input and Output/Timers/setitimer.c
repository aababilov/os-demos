#include <stdio.h>

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>


const char *time_str()
{
	static char buf[512];
	struct timeval tv;
	gettimeofday(&tv, NULL);
	strftime(buf, sizeof(buf), "%F %T", localtime(&tv.tv_sec));
        return buf;
}


void timer_handler(int signum) 
{
        printf("%s: SIGALRM\n", time_str());
}


int main(int argc, char *argv[])
{
        struct sigaction act = {};
	act.sa_handler = timer_handler;
	sigaction(SIGALRM, &act, NULL);

	struct itimerval timer = {};
	timer.it_value.tv_sec = 2;
	timer.it_interval.tv_sec = 5;

	setitimer(ITIMER_REAL, &timer, NULL);
        printf("%s: START\n", time_str());
	for (;;)
		pause();
	return 0;
}
