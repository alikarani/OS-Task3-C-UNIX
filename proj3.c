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

    printf("It created a child process with fork!\n");
     pid_t cpid;
     if (fork() == 0)
         exit(0); /* terminate child */

     else
        cpid = wait(NULL); /* reaping parent */
     printf("Parent pid = %d\n", getpid());
     printf("Child pid = %d\n", cpid);



    int save_stdout = dup(1);
    dup2(fd, STDOUT_FILENO);
    for (int i = 1; i < argc; i++)
    {
        printf("%s", argv[i]);
    }
    fflush(stdout);
    dup2(save_stdout, 1);
    printf("Output Success\n");
    close(fd);
    return 0;
}
