#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

static void pSigHandler(int signo)
{
    switch (signo)
    {
    case SIGTSTP:
        printf("TSTP");
        fflush(stdout);
        break;
    }
}

int main(int argc, char *argv[])
{

    // struct sigaction psa;
    // psa.sa_handler = pSigHandler;
    // sigaction(SIGTSTP, &psa, NULL);
    // for(;;) {}

    char *filename = "copyfile.txt";

    int fd = creat(filename, S_IRWXU);

    if (fd == -1)
    {
        printf("Failure");
        exit(1);
    }

    printf("It created a child process with fork!\n");
    // pid_t cpid;
    // if (fork() == 0)
    //     exit(0); /* terminate child */

    // else
    //     cpid = wait(NULL); /* reaping parent */
    // printf("Parent pid = %d\n", getpid());
    // printf("Child pid = %d\n", cpid);

    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        char *cmd = "ls";
        char *argv[3];
        argv[0] = "ls";
        argv[1] = "-la";
        argv[2] = NULL;

        //uncomment 1 at a time.
        // execlp("/bin/ls", cmd, NULL);  //This will run "ls"
        // execvp(cmd, argv); //This will run "ls -la"
    }
    else
    {
        wait(NULL);
        printf("child complete\n");
    }

    int pipe_1[2];
    int pipe_2[2];
    int return1;
    int return2;

    char w_msg1[30] = "This Is Pipe1 Msg";
    char w_msg2[30] = "This Is Pipe2 Msg";
    char r_msg[30];

    return1 = pipe(pipe_1);
    if (return1 == -1)
    {
        printf("Unable to create pipe 1\n");
    }

    return2 = pipe(pipe_2);
    if (return2 == -1)
    {
        printf("Unable to create pipe 2\n");
    }

    int pid1 = fork();

    //Is Parent process me humne pipe1 k read end ko close kia or pipe2 k write end ko close kia
    //write kia pipe1 se or read kia pipe2 se
    if (pid1 != 0) //pipe2=read , pipe1=write
    {
        close(pipe_1[0]); //close kia pipe1 k read end ko
        close(pipe_2[1]); //close kia pipe2 k write end ko
        printf("Write on parent process Pipe 1:%s\n", w_msg1);
        write(pipe_1[1], w_msg1, sizeof(w_msg1)); //write kia pipe1 p
        read(pipe_2[0], r_msg, sizeof(r_msg));    //read kia pipe2 se
        printf("Read from  parent process Pipe 2:%s\n", r_msg);
    }

    //Is child process me humne pipe1 k write end ko close kia or pipe2 k read end ko close kia
    //write kia pipe2 se or read kia pipe1 se
    else
    {
        close(pipe_1[1]);                      //close kia pipe1 k writre end ko
        close(pipe_2[0]);                      //close kia pipe2 k read end ko
        read(pipe_1[0], r_msg, sizeof(r_msg)); //read kia pipe1 se
        printf("Read from child process Pipe 1:%s\n", r_msg);
        printf("Write on child process Pipe 2:%s\n", w_msg2);
        write(pipe_2[1], w_msg2, sizeof(w_msg2)); //write kia pipe2 p
    }

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
//METHODS NOT USED
//open() As the functionality of open and creat was similar so Ali has used Creat.
//Group Members:
// Mohsin Ali Al Hussaini 9031 (Group Lead)
// Tanveer Khan 9022
// Ali Asghar Karani 8999
