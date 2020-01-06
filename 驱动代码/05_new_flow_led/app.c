#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>    //lseek
#include <sys/ioctl.h> //ioctl
#define  DEVNAME    "/dev/chrdev-misc"
#define  IOC_LED_MIN 0
#define  IOC_LED_MAX 5
#define LED_ON_ALL _IO('L',0)
#define LED_OFF_ALL _IO('L',1)
#define LED_ON_X   _IOW('L',2,int)
#define LED_OFF_X   _IOW('L',3,int)
#define LED_POLL_ALL _IOW('L',4,int)
typedef struct sleek
{
    loff_t off ;
    int whence;   
}IO_sleek;
#define LED_LSEEK _IOW('L',5,IO_sleek)
int fd;                      //´æ·ÅÎÄ¼þÃèÊö·ûºÅ
char save_buf[1024]={0};     //´æ·ÅÊý¾ÝÊ¹ÓÃ

int main(int argc,char **argv)
{
	int ret;
	const char *path  = DEVNAME;
   	char IO_buf[100]={0};
    char data[5][5]={"01111","10111","11011","11101","11110"};
	 IO_sleek sleek1={0,SEEK_SET};
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
	
	fd = open(path,O_RDWR); //ÒÔ¶ÁÐ´·½Ê½½øÐÐ´ò¿ª
	if(fd < 0){
		perror("open");
		return -1;
	}
	printf("fd=%d\r\n",fd);   //³É¹¦Ê±ºòÊä³öÎÄ¼þÃèÊö·û
   
    while(1)
    {
		//¶Á²Ù×÷
		ret = read(fd, save_buf,1);
		if(ret < 0)
		{
			perror("read");
			return -1;
		}
	    printf("now led staus id: %s\n",save_buf);

	    /*for(int i=0;i<5;i++)
	    {
	    	ret =write(fd,data[i], 5);
	        sleep(1);
	    }
		if(ret < 0){
			perror("write");
			return -1;
		}*/
		ioctl(fd,LED_OFF_ALL,5);   
		sleep(1);
		ioctl(fd,LED_ON_ALL,5);
		sleep(1);
		ioctl(fd,LED_OFF_ALL,5);
		sleep(1);
	    for(int i=0;i<5;i++)
	    {
	        ioctl(fd,LED_ON_X,&i);
	        //write(fd,"1",1);

	        sleep(1);
	    }
	    //lseek(fd,0,SEEK_SET);
	    sleep(1);
	    ioctl(fd,LED_OFF_ALL,5);
	    ioctl(fd,LED_POLL_ALL,IO_buf);
	    printf("led status %s\n",IO_buf );
	    ioctl(fd,LED_LSEEK,&sleek1);

	    sleep(1);
    }
	//ÒÆ¶¯ÎÄ¼þÖ¸Õë²Ù×÷
	ret =lseek(fd,0,SEEK_SET);
	if(ret < 0){
		perror("lseek");
		return -1;
      	}	
	//¹Ø±ÕÎÄ¼þ
	close(fd);		

	return 0;
}










