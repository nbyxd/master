#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<strings.h>
#include<string.h>

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		perror("wrong\n");
		exit(0);
		}
	int fd=open(argv[1],O_RDWR);
	char buf[1024];
	bzero(buf,sizeof(buf));
	for(int i=0;i<100;i++)
	{

		
		 if((i+1)%10==0)
			{buf[i]='\n';
			
			}
		
		else
			buf[i]=48+(i+1)%10;
		}
		buf[99]=0;
	write(fd,buf,strlen(buf));
	return 0;
	}
