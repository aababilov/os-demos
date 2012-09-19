#define _GNU_SOURCE

#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>

typedef ssize_t (*write_t)(int fd, const void *buf, size_t count);

ssize_t write(int fd, const void *buf, size_t count)
{
	write_t libc_write = dlsym(RTLD_NEXT, "write");
	char *xbuf = malloc(count);
	int i;
	for (i = 0; i < count; ++i)
		xbuf[count - 1 - i] = ((const char *)buf)[i];
	i = libc_write(fd, xbuf, count);
	free(xbuf);
	return i;
}
