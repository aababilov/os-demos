#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
	int f, f_random;
	int len = 1024 * 1024, i;
	char random;
	char *region;
	int is_writer;

	f_random = open("/dev/urandom", O_RDONLY);
	f = open("f.map", O_CREAT | O_RDWR, 0666);

	ftruncate(f, len);
	region = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
	close(f);

	is_writer = region[0] == 0;
	if (is_writer) {
		printf("I am a writer\n");
		region[0] = 1;
		for (i = 1; i <= 10; ++i) {
			read(f_random, &random, 1);
			printf("random number: %d\n", (int)random);
			region[i]  = random;
		}
	} else {
		printf("I am a reader\n");		
		for (i = 1; i <= 10; ++i) {
			printf("scanned number: %d\n", (int)region[i]);
		}
	}

	printf("Press any key to exit\n");
	read(0, &random, 1);

	if (is_writer)
		region[0] = 0;

	munmap(region, len);	
	return 0;
}
