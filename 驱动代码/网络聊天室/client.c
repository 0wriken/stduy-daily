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
#include <poll.h>
#include <termios.h>
short  PORT = 8888; 
char * IP= "192.168.18.153";
int sockfd;
int ret;
fd_set readfds;
fd_set writefds;  
struct timeval tv;
void cli_init(void);
void *recv_thread(void *p);
struct termios stored_settings;
struct termios new_settings;
//客户端初始化
void cli_init()
{

    tcgetattr (0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr (0, TCSANOW, &new_settings);
    struct sockaddr_in addr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
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
    tv.tv_sec=0;
    tv.tv_usec=30;
    FD_ZERO(&readfds);
    FD_SET(sockfd,&readfds);
    FD_SET(0,&readfds);
    ret=select(sockfd+1,&readfds,NULL,NULL,&tv);
    if(ret<0)
    {
      perror("select \n");
      exit(-1);
    }
}

int main(int argc,char *argv[])
{
    char buf[100];
    int test;
    char name_buf[1024];
    char s_buf[1024];
    pthread_t id;
    cli_init();
    printf("请输入的昵称:\n");
    scanf("%s",buf);
    strcpy(name_buf,buf);
    //发送群ID给服务器处理
    if( send(sockfd,buf,strlen(buf),0)==-1)
    {
      perror("send name");
      exit(0);
    }
   while(1)
   {  
        tv.tv_sec=0;
        tv.tv_usec=30;
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds);
        FD_SET(0,&readfds);
        ret=select(sockfd+1,&readfds,NULL,NULL,&tv);
        if(FD_ISSET(sockfd,&readfds))
        { 
            char buf[1024]={0};
            memset(buf,0,strlen(buf));
            int test=0;
            test=recv(sockfd,buf,100,0);
            if(test==-1)
            {
                perror("recv thread");
                exit(0);
            }
            if(test!=0)
            {
            printf("%s\n",buf);
            memset(buf,0,strlen(buf));
            }
          }

      if(FD_ISSET(0,&readfds))
      {
       printf("please input:\n");
       scanf("%s",buf);
       //选择私聊
       getchar();
       //fflush(0);
       if(strcmp(buf,"person")==0)
       {
           send(sockfd,buf,strlen(buf),0);
           goto leep;
       }
       //退出聊天
       if(strcmp(buf,"quit")==0)
       {
           goto leap;
       }
       sprintf(s_buf,"%s说:%s",name_buf,buf);
       //发送数据给服务端
       test=send(sockfd,s_buf,strlen(s_buf),0);
       if(test==-1)
       {
           perror("send");
           exit(0);
       }
       if(strcmp(buf,"person")==0)
       {
leep:      
           memset(buf,0,strlen(buf));
           printf("请输入要私聊的对象昵称\n");
           //输入私聊的对象 
           scanf("%s",buf);
leap:      test=send(sockfd,buf,strlen(buf),0);
           if(test==-1)
           {
               perror("私聊昵称\n");
               exit(0);
           }
        }
        memset(buf,0,strlen(buf));
       memset(s_buf,0,strlen(s_buf));

      }
    }
   tcsetattr (0, TCSANOW, &stored_settings); 
   return 0;
}















