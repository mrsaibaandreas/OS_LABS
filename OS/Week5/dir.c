#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define MAX_PATH 1024
#define STR_LEN 2048
void parseDirectory(char *path, int fd)
{
	DIR *dir = NULL;
	char new_path[MAX_PATH] = {0};
	char data[STR_LEN] = {0};
	if((dir = opendir(path)) == NULL)
	{
	  perror(path);
	  exit(-1);
	}
	struct dirent *d = NULL;
	while ((d = readdir(dir)) != NULL )
	{	if( (strcmp(d->d_name, ".") == 0) || (strcmp(d->d_name,"..")) == 0 )
		{
			continue;
		}
		snprintf(new_path,MAX_PATH,"%s/%s",path,d->d_name);
		//printf("newpath %s\n",new_path);
		struct stat buff;
		
		if(lstat(new_path, &buff) < 0)
		{
			perror(d->d_name);
			exit(-1);
		}
		char is_dir;
		if (S_ISDIR(buff.st_mode))
		{	
			is_dir = 'd';	
			parseDirectory(new_path, fd);
		}
		if (S_ISLNK(buff.st_mode))
		{
			is_dir = 's';
		}
		if(S_ISREG(buff.st_mode))
		{
			is_dir = 'r';
		}
		snprintf(data,STR_LEN,"file-path:%s, file size: %li, file mode:%c\n",new_path,buff.st_size,is_dir);
		long int length = strlen(data);
		
		if (write(fd, data, length) < length) 
		{
			printf("Didn't write\n");
			exit(-1);
		}
	}
	if (closedir(dir) < 0 )
	{
	  perror(path);
	  exit(-1);
	}
}

int main(int argc, char **argv)
{
	if(argc < 3)
	{
	  fprintf(stderr, "Incorrect usage\n");
	  exit(-1);
	}
	int fd = 0;
	if ((fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU)) < 0)
	{
		perror(argv[2]);
		exit(-1);
	}	
	
	
	parseDirectory(argv[1], fd);
	if(close(fd) < 0)
	{
		perror(argv[2]);
		exit(-1);
	}
  return 0;
}
