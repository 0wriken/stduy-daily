#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>    //lseek
#include <sys/ioctl.h> //ioctl
#define  DEVNAME    "/dev/chrdev-misc"
#define LED_ON_ALL _IO('L',0)
#define LED_OFF_ALL _IO('L',1)
#define LED_ON_X   _IOW('L',2,int)
#define LED_OFF_X   _IOW('L',3,int)

int fd;                      //存放文件描述符号
char save_buf[1024]={0};     //存放数据使用

int main(int argc,char **argv)
{
	int ret;
	const char *path  = DEVNAME;
    char data[5][5]={"01111","10111","11011","11101","11110"};
	if(argc==1){
		path  = DEVNAME;
	}
	else if(argc==2){
		path  = argv[1];
	}
	else{
		printf("Usage:%s [/dev/devname]\r\n",argv[0]);
		return 0;
	}

	printf("open:%s \r\n",path);
	
	fd = open(path,O_RDWR); //以读写方式进行打开
	if(fd < 0){
		perror("open");
		return -1;
	}
	printf("fd=%d\r\n",fd);   //成功时候输出文件描述符
    while(1)
    {
		//读操作
		ret = read(fd, save_buf,5);
		if(ret < 0)
		{
			perror("read");
			return -1;
		}
	    printf("GET MEM is: %s\n",save_buf);

		//写操作

	    /*for(int i=0;i<5;i++)
	    {
	    	ret =write(fd,data[i], 5);
	        sleep(1);
	    }
		if(ret < 0){
			perror("write");
			return -1;
		}*/
	    //ioctl(fd,LED_ON_ALL,5);
	   /* for(int i=0;i<5;i++)
	    {
	       //ioctl(fd,LED_ON_X,&i);
	       
	        sleep(1);
	    }*/ 

 		write(fd,"123123123",10);
	    //ioctl(fd,LED_OFF_ALL,5);
	    sleep(1);
	    printf("8888888888\n");
	}
		//移动文件指针操作
		ret =lseek(fd,0,SEEK_SET);
		if(ret < 0){
			perror("lseek");
			return -1;
      }	
 
	//关闭文件
	close(fd);		

	return 0;
}










