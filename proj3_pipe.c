#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pipe_1[2];
    int pipe_2[2];
    int return1;
    int return2;

    char w_msg1[30]="This Is Pipe1 Msg";
    char w_msg2[30]="This Is Pipe2 Msg";
    char r_msg[30];

    return1=pipe(pipe_1);
    if(return1==-1)
    {
        printf("Unable to create pipe 1\n");
    }

    return2=pipe(pipe_2);
    if (return2==-1)
    {
        printf("Unable to create pipe 2\n");
    }

    int pid=fork();

    //Is Parent process me humne pipe1 k read end ko close kia or pipe2 k write end ko close kia
    //write kia pipe1 se or read kia pipe2 se
    if(pid!=0)//pipe2=read , pipe1=write
    {
        close(pipe_1[0]);//close kia pipe1 k read end ko
        close(pipe_2[1]);//close kia pipe2 k write end ko
        printf("Write on parent process Pipe 1:%s\n",w_msg1);
        write(pipe_1[1],w_msg1,sizeof(w_msg1));//write kia pipe1 p
        read(pipe_2[0],r_msg,sizeof(r_msg));//read kia pipe2 se
        printf("Read from  parent process Pipe 2:%s\n",r_msg);
    }
    
    //Is child process me humne pipe1 k write end ko close kia or pipe2 k read end ko close kia
    //write kia pipe2 se or read kia pipe1 se
    else
    {
        close(pipe_1[1]);//close kia pipe1 k writre end ko
        close(pipe_2[0]);//close kia pipe2 k read end ko
        read(pipe_1[0],r_msg,sizeof(r_msg));//read kia pipe1 se
        printf("Read from child process Pipe 1:%s\n",r_msg); 
        printf("Write on child process Pipe 2:%s\n",w_msg2);
        write(pipe_2[1],w_msg2,sizeof(w_msg2));//write kia pipe2 p
                
    }
    
}