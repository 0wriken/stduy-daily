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
/*�ͻ��˵ĳ�ʼ��*/
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
    //��ʼ���ṹ��
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=inet_addr(IP);
    //���ӷ�����
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(struct sockaddr))==-1)
    {
        perror("connect");
        exit(0);
    }
    printf("connect ok\n");
}
/*�̴߳����������*/
void *recv_pthrad(void*p)
{
    char recv_buf[1024];
    /*�򿪴���ļ���*/
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
        /*���յ����ݴ��λ��*/
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
	/*�����������ʱ���д��ݲ���������������ͷ�豸��Ŀ������ͷ   */
	if(agrc==2){
		video_dev = argv[1];  //��������ͷ�豸
	}
    ret =  fb_init(LCD_DEVICE);   //lcd ��ʼ��
    if(ret < 0) {
        printf(" error fb_init\r\n");
        return -1;
    }
    
    fb_clear();                  //����
    //�ͻ��˳�ʼ��
    cli_init();
   /* while(1)
    {
        ;
    }*/
    //����ͷ����ʼ
    /* YUV��ʽ������ת����rgb888����Ҫʹ�õĵ����ݱ���ʼ�� */
    initLut();
    printf("video init start ����\r\n");

    /* ��ʼ������ͷ�豸 */
    video_device_init(video_dev);
    //�����߳̽�������
    //pthread_create(&id,NULL,recv_pthrad,(void *)sockfd);
    //����ͷ�ɼ���������

       /* ѭ���ɼ�����,��ʾ��lcd���� */
        video_mainloop();

        /*�����ʼ����Ƶ�豸����*/
        video_device_uninit(4);


    /* �ͷ�lcd��Դ */
    fb_close();
    return 0;
}


