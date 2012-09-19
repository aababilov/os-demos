#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
        mkfifo(argv[1], 0666);
        return 0;
}
