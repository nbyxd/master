#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
//将创建子进程功能分开开来
void create_process(int num,const char* src,const char* dest,int size)
{
	int i;
//	int read_size;
	pid_t pid;
//创建子进程
	for( i=0;i<num;i++)
	{
		pid=fork();
//避免子进程在创建孙子进程
		if(pid==0)
			break;
		}

	if(pid==0)
		{
//出现int类型无法转化为字符串类型，出现参数错误
//用Buf1来转换成字符串
		//	printf("%d\n",size);
			char buf1[1024];
			bzero(buf1,sizeof(buf1));
			sprintf(buf1,"%d",i*size);
		printf("make successfully child id=%d\n",i);
		execlp("./mycp","./mycp",src,dest,buf1,NULL);
		}
	
	}
//回收子进程
void mywaitpid()
{
	pid_t wpid;
	while((wpid=waitpid(-1,NULL,WNOHANG))!=-1)
	{
		if(wpid==0)
		{
			printf("my son`s process still alive\n");
	sleep(1);
			}
		if(wpid>0)
		{
			printf("recovery my son`s process his pid=%d\n",wpid);
			}
		}
	
	}

int main(int argc,char* argv[])
{
	if(argc<3)
	{
		perror("too few\n");
		exit(0);
		}
	int fd=open(argv[1],O_RDWR);
	char buf[1024];
	bzero(buf,sizeof(buf));
	int size=read(fd,buf,sizeof(buf));
	close(fd);
	int read_size;
	read_size=size/(10);
//如果是3个参数默认创建十个子进程
	 if(argc==3)
	{
	create_process(10,argv[1],argv[2],read_size);
	mywaitpid();
		}
	else if(argc==4)
	{
		int num=atoi(argv[3]);
	create_process(num,argv[1],argv[2],read_size);		
	mywaitpid();
	}

//	close(fd);
	return 0;
	}
