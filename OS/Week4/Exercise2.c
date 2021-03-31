#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>


#define SIZE 512

int main(int argc, char **argv)
{	if(argc < 2)
	{
		perror(argv[1]);
		exit(1);
	}
	int fd = 0;
	int r;
	unsigned char buffer[SIZE];
	if( (fd = open(argv[1], O_RDONLY)) < 0 )
	{
		perror(argv[1]);
		exit(-1);//means file was not open with succes
	}
	unsigned char name[101];
	unsigned char user_id[9];
	unsigned char group_id[9];
	uint32_t size;
	unsigned *garbage_value = malloc(100*sizeof(char));	
	if( (r = read(fd, buffer, SIZE)) <= SIZE)//the header size is 500 bytes
	{	
		memcpy(name,buffer,100);
		name[101] = '\0';
		printf("fasfsa\n");
		memcpy(garbage_value,buffer,8);
		printf("Dsadas\n");
		memcpy(user_id, buffer + 108, 8);
		memcpy(group_id, buffer + 116, 8);
		user_id[9] = '\0';
		group_id[9] = '\0';
		
	}
	else
		printf("GHinion\n");
	printf("%s %s %s",name, user_id, group_id);
	
	return 0;
}
