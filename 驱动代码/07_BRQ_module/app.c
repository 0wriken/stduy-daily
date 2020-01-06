#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>    //lseek
#include <sys/ioctl.h> //ioctl
#include <string.h>
#define  DEVNAME    "/dev/chrdev-misc"
int fd;                      //???????????
char save_buf[1024]={0};     //???????
int fd_led;
int main(int argc,char **argv)
{
	int ret;
	 char path[1024]={0};
     char path1[1024]={0};
    char data[5][5]={"01111","10111","11011","11101","11110"};
	if(argc==1){
		strcpy(path,DEVNAME);
	}
	else if(argc==2){
		strcpy(path,argv[1]);
	}
    else if(argc==3)
    {
		strcpy(path,argv[1]);
		strcpy(path1,argv[2]);
    }
	else{
		printf("Usage:%s [/dev/devname]\r\n",argv[0]);
		return 0;
	}

	printf("open:%s \r\n",path);
	fd = open(path,O_RDWR); //???д??ʽ?????
	if(fd < 0){
		perror("open");
		return -1;
	}
    fd_led = open(path1,O_RDWR); //???д??ʽ?????
	if(fd_led < 0){
		perror("open");
		return -1;
	}
	printf("fd=%d\r\n",fd);   //?ɹ?ʱ??????????
    while(1)
    {
		//?????
		ret = read(fd, save_buf,1);
		if(ret < 0)
		{
			perror("read");
			return -1;
		}
	    printf("key status is%s\n",save_buf);
	    sleep(1);
    }
	//??????ָ????
	ret =lseek(fd,0,SEEK_SET);
	if(ret < 0){
		perror("lseek");
		return -1;
	}	
	//?ر?ļ?
	close(fd);		
	return 0;
}