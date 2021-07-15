#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<strings.h>
#include<fcntl.h>

//打开和关闭文件夹
void mycp(const char* src,const char* dest,int pos)
{
	if(src==NULL||dest==NULL)
	{
		perror("parameter wrong");
		}
	int fd1=open(src,O_RDWR);
	int fd2=open(dest,O_RDWR|O_CREAT,0664);
//通过打开读写指针位置来区分每个进程的工作内容，避免冲突
	lseek(fd1,pos,SEEK_SET);
	lseek(fd2,0,SEEK_END);
	char buf[10];
	read(fd1,buf,sizeof(buf));
	write(fd2,buf,strlen(buf));
	close(fd1);
	close(fd2);
	}



int main(int argc,char* argv[])
{

	if(argc<4)
	{
		perror("参数过少?\n");
		exit(0);
		}
	printf("in\n");	
	mycp(argv[1],argv[2],atoi(argv[3]));

	return 0;
	}
