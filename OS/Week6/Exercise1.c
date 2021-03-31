#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFF_SIZE 512

int main(int argc, char **argv)
{
    char buffer[BUFF_SIZE] = {};
    if (argc < 2)
    {
        perror("Not enough arguments");
        exit(-1);
    }
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("fork()");
        exit(-1);
    }
    if (pid == 0)
    {
        int fd = 0;
        if ((fd = open(argv[1], O_RDONLY)) < 0)
        {
            perror(argv[1]);
            exit(-1);
        }
            int r = 0;
            int letters = 0;
            while((r = read(fd,buffer, BUFF_SIZE)) > 0)
            {
                printf("%d\n",r);
                for(int i = 0 ; i < r; i++)
                {
                    if (isalpha(buffer[i]))

                    {
                        letters++;
                    }
                }
            }
         close(fd);
         exit(letters);
    }
    int status;
    if ((pid = wait(&status)) != -1)
    {
        printf("Child exit status is %d\n", WEXITSTATUS(status));
    }
    return 0;
}
