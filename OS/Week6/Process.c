#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int  argc, char **argv)
{	
	pid_t pid;

	int i = 0;
	if((pid = fork()) < 0)
	{
		perror("fork()");
		exit(-1);
	}
	if (pid == 0)
	{
		//child process
		i++;
		printf ("child code %d\n",i);
		exit(0);
	}
	else
	{
		//parent  process
	}
	//parent process
	int status = 0;
	printf ("parent code %d\n",i);
	while ((pid =wait(&status)) != -1)
	{
		printf ("Process with PID %d died\n", pid);
	}
	printf ("parent dies\n");
	return 0;
}
//the parent process needs to wait for all it's children to die
