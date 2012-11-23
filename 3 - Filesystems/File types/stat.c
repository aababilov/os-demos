#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof(a)/(sizeof(a[0])))

struct {
	int mask;
	char *msg;
} modes[] = {
	{S_IFMT, "bit mask for the file type bit fields"},
	{S_IFSOCK, "socket"},
	{S_IFLNK, "symbolic link"},
	{S_IFREG, "regular file"},
	{S_IFBLK, "block device"},
	{S_IFDIR, "directory"},
	{S_IFCHR, "character device"},
	{S_IFIFO, "FIFO"},
	{S_ISUID, "set UID bit"},
	{S_ISGID, "set-group-ID bit"},
	{S_ISVTX, "sticky bit"},
	{S_IRWXU, "mask for file owner permissions"},
	{S_IRUSR, "owner has read permission"},
	{S_IWUSR, "owner has write permission"},
	{S_IXUSR, "owner has execute permission"},
	{S_IRWXG, "mask for group permissions"},
	{S_IRGRP, "group has read permission"},
	{S_IWGRP, "group has write permission"},
	{S_IXGRP, "group has execute permission"},
	{S_IRWXO, "mask for permissions for others (not in group)"},
	{S_IROTH, "others have read permission"},
	{S_IWOTH, "others have write permission"},
	{S_IXOTH, "others have execute permission"},
};

int main(int argc, char*argv[])
{
	int i, j;
	for (j = 1; j < argc; ++j) {
		char *filename = argv[j];
		struct stat file_stat;
		stat(filename, &file_stat);
		printf("file %s has %d hard link(s)\n", filename, (int)file_stat.st_nlink);
		for (i = 0; i < ARRAY_SIZE(modes); ++i) {
			if ((modes[i].mask & file_stat.st_mode) == modes[i].mask) {
				printf("\t%s\n", modes[i].msg);
			}
		}
	}
	return 0;
}
