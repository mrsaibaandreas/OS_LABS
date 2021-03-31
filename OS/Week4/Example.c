#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main(int argc, char **argv)
{	int fd = 0;
	char buffer[16];
	int r = 0;
	if(argc < 3)
	{
		printf("error\n");
		exit(-1);
	}
	
	if ((fd = open(argv[1], O_RDONLY)) < -1)
	{
		perror(argv[1]);
		exit(-1);
	}	

	int i =0 ;
	while( (r = read(fd, buffer,16)) > 0)
	{
		//printf("%s\n",buffer); //WROMG !!!! NON-STRING NO \0
		//strlen(buffer);//wrong!! no \0 pusca memorie
		for(i=0; i < r; i++)
			printf("%c",buffer[i]);
	} 
	close(fd);
	read(fd, buffer, 16); //fread(buffer, 1, 16, ...) a similarity, but not the same
	//write();
	if((fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU) < 0)) // NEEDS THE LAST VALUE BECAUSE, THE SYSTEMS NEEDS TO KNOW THE OWNER RIGHTS OF THE FILE
	{
		perror(argv[2]);
		exit(-1);
	}
	const char text[] = "something";
	if(write (fd, text, strlen(text)) != strlen(text))
	{
		printf("error write\n");
		exit(-1);
	}
	close(fd);
	
	if (close(fd) < -1)
	{
		perror(argv[1]);
		exit(-1);
	}

return 0;
//5 bytes field - unlimited number of fields
//byte 1 - 0x98 - byte2 - byte 5 = text
//bte 1 - 0x55 bte2 bte5 = unsigned int (4byte) uint32_t
// ./p file_name L
// number of printable characters read
//  number of occurances of L
//  total sum of unsigned integere
