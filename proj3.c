#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    char *filename = "copyfile.txt";

    int fd = creat(filename, S_IRWXU);

    if (fd == -1)
    {
        printf("Failure");
        exit(1);
    }
    int save_stdout = dup(1);
    dup2(fd, STDOUT_FILENO);
    for (int i = 1; i < argc; i++)
    {
        printf("%s", argv[i]);
    }
    fflush(stdout);
    dup2(save_stdout, 1); //also use (STDOUT_FILENO) for output like we use 1 for output bcz sometimes 1 is not use for output
    printf("Output Success\n");
    close(fd);
    return 0;
}