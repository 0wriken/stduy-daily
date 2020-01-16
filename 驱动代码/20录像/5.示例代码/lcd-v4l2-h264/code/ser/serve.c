#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_SIZE 256
#define PATH_FILE "/home/wriken/work/rootfs/home/myvideo/data"
short PORT=8866;
char * IP="0";
char name_buf[100];
char name[100][100];
int fds[MAX_SIZE];
int a;
int i;
int sockfd;
int  test;
char path_buf[100];
void Ser_init(void);
void Server();
void *Serv_thread(void *p);
int main(int argc,char *argv[])
{
    Ser_init();
    Server();
    return 0;
}
/*服务端初始化函数*/
void Ser_init(void)
{
    struct sockaddr_in addr;
    //得到套接字
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1)
    {
        perror("sockfd");
        exit(0);
    }
    int reuse = 1;
    test = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    memset(&addr,0,sizeof(addr));
    //初始化结构体 族 端口 IP
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=0;
    //开启监视
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(struct sockaddr))==-1)
    {
        perror("bind");
        exit(0);
    }
    //开启监听并设置最大的监听数目
   if( listen(sockfd,MAX_SIZE)==-1)
   {
       perror("listen");
       exit(0);
   }
   printf("服务器初始化完成\n");
}
/*服务端接受客户端连接函数*/
void Server(void)
{
    while(1)
    {
        //义结构体接受客户端数据
        struct sockaddr s_addr;
        int len=sizeof(s_addr);
        memset(&s_addr,0,sizeof(s_addr));/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //接受客户端连接并存储客户端数据信息,返回文件操作符
        int fd= accept(sockfd,&s_addr,&len);
        if(fd<0)
        {
            perror("accept");
            exit(0);
        }
        char rcv_buf[100]={0};
        char sbuf[100]={0};
        int test=0;
        if(fd==-1)
        {
            perror("accept");
            exit(0);
        }
        printf("accepct ok\n");
        memset(rcv_buf,0,strlen(rcv_buf));
        pthread_t id;
        int *newfd=malloc(sizeof(int));
        *newfd=fd;
        //存储服务端信息后，创建线程用于存放监控视频信息
        mkdir(PATH_FILE,0666);
        printf("created the directory %s . \n" ,PATH_FILE );
        pthread_create(&id,0,Serv_thread,newfd);
        //判断客户端的信息是否达到最大值
        if(i==MAX_SIZE)
        {
           char *bb="该可监控数目已达上限";
           test=send(fd,bb,strlen(bb),0);
           if(test==-1)
           {
               perror("send bb");
               exit(0);
           }
           close(fd);
        }
    }

}
/*线程服务函数，并使用发送函数处理
参数：用于处理的客户端文件操作符*/
void *Serv_thread(void *p)
{
    //创建存放视屏的文件
    sprintf(path_buf,"%s/%d.h264",PATH_FILE,i);
    i++;
    char recv_buf[1024];
    /*打开存放文件*/
    int recv_fd=open(path_buf,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(recv_fd<0)
    {
        printf("open recv_fd fail\n1");
        return 0;
    }
    while(1)
    {
        memset(recv_buf,0,1024);
        int test=0;
        test=recv(*(int *)(p),recv_buf,1000,0);
        if(test==-1)
        {
            perror("recv thread\n");
            exit(0);
        }
        /*接收的数据存放位置*/
        if(test!=0)
        {
            printf("start recvieve data\n");
            write(recv_fd,recv_buf,strlen(recv_buf));
        }
    }
}