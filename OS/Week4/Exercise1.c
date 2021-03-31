#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
int main(int argc, char **argv)
{	
	int fd = 0;
	int r;
	int i = 0;
	uint32_t counter = 0;
	uint32_t sum = 0;
	unsigned char buffer[5];
	uint32_t nr_of_chars = 0;
	if(argc < 4)
	{
		perror("Too few arguments\n");
		exit(-1);
	}
	if (( fd = open(argv[1],O_RDONLY)) < 0 )
	{
		perror(argv[1]);
		exit(-1);
	}
	while( (r = read(fd, buffer, 5)) > 0 )
	{
		if(buffer[0] == 0x98)
		{	nr_of_chars += 4;
			for(i = 1;  i < r; i++)
			{	if(argv[2][0] == buffer[i])
				{
					counter++;
				}	
			
			} 
		}
		else if(buffer[0] == 0x55)
		{
			uint32_t value = *(uint32_t*)(buffer+1);//cast to int32
			sum += value;	
		}
			
	}
	if( close(fd) < 0 )
	{
		perror(argv[1]);
		exit(-1);
	}
	if(( fd = open(argv[3], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU)) < 0 )
	{
		perror(argv[3]);
		exit(-1);
	} 
	char answer[64];
	printf("%u %u %u \n",nr_of_chars,counter,sum);
	sprintf(answer,"%u %u %u\n",nr_of_chars,counter,sum);
	int answer_len = strlen(answer);
	if (write(fd, answer, answer_len) < answer_len)
	{
		perror("Wrong\n");
		exit(-1);
	}
	if( close(fd) < 0 )
	{
		perror(argv[3]);
		exit(-1);
	}
	return 0;
}

