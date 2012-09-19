#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
	DIR *a_dir = opendir(".");
	struct dirent *a_dirent;

	for (;;) {
		a_dirent = readdir(a_dir);
		if (!a_dirent)
			break;
		write(1, a_dirent->d_name, strlen(a_dirent->d_name));
		write(1, "\n", 1);
	}
	closedir(a_dir);     
	return 0;
}
