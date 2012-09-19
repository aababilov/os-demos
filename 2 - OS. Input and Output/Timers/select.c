#include <stdio.h>

#include <sys/select.h>

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

int main(int argc, char *argv[])
{
        printf("%s: START\n", time_str());
	for (;;) {
		struct timeval timeout = {};
		timeout.tv_sec = 5;
		select(0, NULL, NULL, NULL, &timeout);
		printf("%s: select\n", time_str());
	}

	return 0;
}
