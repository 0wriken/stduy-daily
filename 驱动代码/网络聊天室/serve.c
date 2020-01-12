#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <pthread.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_SIZE 256
short PORT=8888;
char * IP="0";
char name_buf[100];
char name[100][100];
char rcv_buf[100]={0};
 char sbuf[100]={0};
int fds[MAX_SIZE];
int i;
int j;
int a;
int  new_user;
int sockfd;
int ret;
int  test;
int max_sock;
int check_mode;
/*select 多路复用聊天室*/
static int s_fd[0];
fd_set readfds; 
fd_set writefds; 
struct timeval tv;
void Ser_init(void);
void Sendall(char *p);
void flush(int a);
void Sendfd(int *fd,char *buf);
void *Serv_thread(void *p);
int main(int argc,char *argv[])
{ 
        Ser_init();
        while(1)
        {             
            for(int a=0;a<i+1;a++)
            {
                FD_SET(s_fd[a],&readfds);
                //FD_SET(s_fd[a],&writefds);
                
            }
            FD_SET(sockfd,&readfds);
            ret=select(max_sock+1,&readfds,NULL,NULL,&tv);
            //printf("timeout\n");   
            if(FD_ISSET(sockfd,&readfds))
            {
                printf("进入客户端连接中...\n");
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
                char sbuf[100]={0};
                int test=0;
                if(fd==-1)
                {
                    perror("accept");
                    exit(0);
                }
                new_user=1;
                fds[i]=fd;
                s_fd[i]=fd;
                if(s_fd[i]>max_sock)
                    max_sock=s_fd[i]; 
                i++;//存放群聊fd
                FD_SET(sockfd,&readfds);
                for(int a=0;a<i+1;a++)
                {
                    FD_SET(s_fd[a],&readfds);
                    //FD_SET(s_fd[a],&writefds);
                    
                }
                ret=select(max_sock+1,&readfds,NULL,NULL,&tv);
            }
            for(a=0;a<i+1;a++)
            {
                if(FD_ISSET(s_fd[a],&readfds))
                {
                    if(new_user)
                    {
                        memset(rcv_buf,0,strlen(rcv_buf));
                        //接受客户端发送来的数据,无则产生阻塞
                        test=recv(s_fd[a],rcv_buf,100,0);
                        if(test==-1)
                        {
                            perror("recv");
                            exit(0);
                        }
                        strcpy(*(name+j),rcv_buf);//拷贝名字
                        j++;
                        printf("ok\n");
                        sprintf(sbuf,"%s用户加入聊天室!",rcv_buf);
                        memset(rcv_buf,0,strlen(rcv_buf));
                        Sendall(sbuf);
                        int *newfd=malloc(sizeof(int));
                        *newfd=s_fd[a];
                        //存储服务端信息后，创建线程用于通信
                        //判断客户端的信息是否达到最大值
                        if(i==MAX_SIZE)
                        {
                           char *bb="该群聊已达上限";
                           test=send(s_fd[a],bb,strlen(bb),0);
                           if(test==-1)
                           {
                               perror("send bb");
                               exit(0);
                           }
                           close(s_fd[a]);
                        }
                        new_user=0;
                    }
                    else
                    {
                        char r_buf[1024]={0};
                        memset(r_buf,0,1024);

                    str:
                        test=recv(s_fd[a],r_buf,sizeof(r_buf),0);
                        //线程退出要释放空间
                        if(test==0)
                        {
                            //printf("ptread_exit%ld\n",pthread_self());
                            perror("receve is error\n");
                            close(s_fd[a]);
                            exit(-1);
                            //pthread_exit(NULL);
                        }
                        if(test==-1)
                        {
                            perror("exit recieve");
                            //pthread_exit((void*)&i);
                            exit(0);
                        }
                        //判断客户端发送数据，若为私聊则开启单单对模式
                        if(strcmp(r_buf,"person")==0)
                            check_mode=1;
                        //群发则开启群发模式
                        if(!check_mode)
                        {
                            Sendall(r_buf);
                            memset(r_buf,0,strlen(r_buf));
                        }
                        else
                        {
                            printf("当前对话已保密请输入:\n");
                            memset(r_buf,0,strlen(r_buf));
                            test=recv(s_fd[a],r_buf,sizeof(r_buf),0);
                            if(test==-1)
                            {
                                perror("私人recv\n");
                                exit(0);
                            }
                            printf("r_buf:%s\n",r_buf);
                            //判断昵称所在的fd
                            for(a=0;a<=j;a++)
                            {
                                printf("name:%s\n",*(name+a));
                                if((strcmp(r_buf,*(name+a))==0))
                                    break;
                                if(a==j)
                                {
                                    printf("未找到该昵称成员\n");
                                    goto str;
                                }
                            }

                            int fd=fds[a];
                            printf("找到用户：%s\n",*(name+a));
                            flush(a);
                            printf("ok\n");
                            memset(r_buf,0,strlen(r_buf));
                            if(FD_ISSET(s_fd[a],&readfds))
                            {
                                test=recv(s_fd[a],r_buf,sizeof(r_buf),0);
                                if(test==-1)
                                {
                                    perror("私人recv\n");
                                    //pthread_exit((void*)&i);
                                    exit(0);
                                }
                                Sendfd(&fd,r_buf);
                                if(strcmp(r_buf,"quit")==0)
                                {
                                    fds[i]=fd;
                                    //s_fd[a]=fd;
                                    fd=0;
                                    i++;
                                    check_mode=0;
                                //     goto str;
                                }
                                memset(r_buf,0,strlen(r_buf));
                            }
                        }
                    }
                }
            }
        }
        return 0;
}
/*服务端初始化函数*/
void Ser_init(void)
{
    struct sockaddr_in addr;
    //得到套接字
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("sockfd");
        exit(0);
    }
    //复用套接字
    tv.tv_sec=0;
    tv.tv_usec=30;//30微妙超时
    sockfd;
    max_sock=sockfd;
    FD_ZERO(&readfds);
    FD_SET(sockfd,&readfds);
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

/*线程服务函数，判断私聊与群发，并使用发送函数处理
参数：用于处理的客户端文件操作符*/
void *Serv_thread(void *p)
{
     char r_buf[1024]={0};
     memset(r_buf,0,1024);

str:
    while(1)
    {
        test=recv(*(int*)p,r_buf,sizeof(r_buf),0);
        //线程退出要释放空间
        if(test==0)
        {
            printf("ptread_exit%ld\n",pthread_self());
            close(*(int *)p);
            pthread_exit(NULL);
        }
        if(test==-1)
        {
            perror("serv thread");
            pthread_exit((void*)&i);
            exit(0);
        }
        //判断客户端发送数据，若为私聊则开启单单对模式
        if(strcmp(r_buf,"person")==0)
            goto leap;
        //群发则开启群发模式
        Sendall(r_buf);
        memset(r_buf,0,strlen(r_buf));
    }
leap:
        printf("当前对话已保密请输入:\n");
        memset(r_buf,0,strlen(r_buf));
        test=recv(*(int *)p,r_buf,sizeof(r_buf),0);
        if(test==-1)
        {
            perror("私人recv\n");
            exit(0);
        }
        printf("r_buf:%s\n",r_buf);
        //判断昵称所在的fd
        for(a=0;a<=j;a++)
        {
            printf("name:%s\n",*(name+a));
            if((strcmp(r_buf,*(name+a))==0))
                break;
            if(a==j)
            {
                printf("未找到该昵称成员\n");
                goto str;
            }
        }

        int fd=fds[a];
        printf("找到用户：%s\n",*(name+a));
        flush(a);
        printf("ok\n");
        memset(r_buf,0,strlen(r_buf));
        while(1)
        {
            test=recv(*(int *)p,r_buf,sizeof(r_buf),0);
            if(test==-1)
            {
                perror("私人recv\n");
                pthread_exit((void*)&i);
                exit(0);
            }

            Sendfd(&fd,r_buf);
            if(strcmp(r_buf,"quit")==0)
            {
                fds[i]=fd;
                fd=0;
                i++;
                goto str;
            }
            memset(r_buf,0,strlen(r_buf));
        }
}



void Sendall(char *p)
{
    int test=0;
    for(int a=0;a<i;a++)
    {
        printf("name:%s\n",*(name+a));
        test=send(fds[a],p,strlen(p),0);
        if(test==-1)
        {
            perror("sendall");
            exit(0);
        }
    }
    printf("群发完毕\n");
}
void Sendfd(int *fd,char *buf)
{
    int test=0;
    test=send(*fd,buf,strlen(buf),0);
    if(test==-1)
    {
        perror("sendfd");
        exit(0);
    }
}
void flush(int a)
{
    for(a;a<i;a++)
    {
        fds[a]=fds[a+1];
    }
    i--;
}
