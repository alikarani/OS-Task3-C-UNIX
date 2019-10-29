#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int a=creat("creatfuncfile.txt" , S_IRWXU);
    int save=dup(1);
    dup2(a,1);
    for (int  i = 1; i < argc; i++)
    {
        printf("%s",argv[i]); 
    }
    dup2(save,1); //also use (STDOUT_FILENO) for output like we use 1 for output bcz sometimes 1 is not use for output
    printf("\nOutput Successfull\n");
    
}