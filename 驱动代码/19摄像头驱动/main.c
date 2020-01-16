#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "color.h"
#include "v4l2-function.h"
#include "write-jpeg.h" 
#include "show-jpeg.h"
#include <arpa/inet.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#define DEST_PATH     "/home/jpg" 
short  PORT = 8866; 
char * IP= "192.168.1.124";
int sockfd;
void cli_init(void);
void *recv_thread(void *p);
/*客户端的初始化*/
void cli_init()
{
    struct sockaddr_in addr;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1)
    {
        perror("sockfd");
        exit(0);
    } 
    memset(&addr,0,sizeof(addr));
    //初始化结构体
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=inet_addr(IP);
    //连接服务器
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(struct sockaddr))==-1)
    {
        perror("connect");
        exit(0);
    }
    printf("connect ok\n");
}
/*线程处理接收数据*/
void *recv_pthrad(void*p)
{
    char recv_buf[1024];
    /*打开存放文件夹*/
    while(1)
    {
        memset(recv_buf,0,1024);
        int test=0;
        test=recv(sockfd,recv_buf,1000,0);
        if(test==-1)
        {
            perror("recv thread\n");
            exit(0);
        }
        /*接收的数据存放位置*/
        if(test!=0)
        {
            printf("start recvieve data\n");
            printf("recieve is %s\n",recv_buf);
        }
    }
}
int main(int agrc, char *argv[])
{
    int ret;
    int send_fd=open(DEST_PATH,O_RDONLY|O_TRUNC,0666);
    pthread_t id;
	char *video_dev=NULL;
    char send_buf[1024];
	/*如果启动程序时候有传递参数，则设置摄像头设备是目标摄像头   */
	if(agrc==2){
		video_dev = argv[1];  //设置摄像头设备
	}
    ret =  fb_init(LCD_DEVICE);   //lcd 初始化
    if(ret < 0) {
        printf(" error fb_init\r\n");
        return -1;
    }
    
    fb_clear();                  //清屏
    //客户端初始化
    cli_init();
   /* while(1)
    {
        ;
    }*/
    //摄像头程序开始
    /* YUV格式的数据转换成rgb888，需要使用的的数据表格初始化 */
    initLut();
    printf("video init start ……\r\n");

    /* 初始化摄像头设备 */
    video_device_init(video_dev);
    //创建线程接收数据
    //pthread_create(&id,NULL,recv_pthrad,(void *)sockfd);
    //摄像头采集发送数据

       /* 循环采集数据,显示在lcd屏上 */
        video_mainloop();

        /*反向初始化视频设备工作*/
        video_device_uninit(4);


    /* 释放lcd资源 */
    fb_close();
    return 0;
}


