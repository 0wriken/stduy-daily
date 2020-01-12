#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>        // errno 全局变量
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#define  BTN_SIZE    5                  //按键数量

#define  DEV_NAME    "/dev/xyd-buttons"  //默认设备名

int main(int argc, char *argv[])
{
	int fd, ret, i;
	const char *devname;
	unsigned char pre_buf[BTN_SIZE+1],recv_buf[BTN_SIZE+1];
	memset(pre_buf,'0',BTN_SIZE);
	memset(recv_buf,0,BTN_SIZE);	
	struct pollfd fds;
	nfds_t nfds;
	int timeout;
	//参数检测，根据参数设置设备名
	if(argc == 1) {
		devname = DEV_NAME;
	} else if(argc == 2) {
		devname = argv[1];
	} else {
		printf("Usage:%s devname\r\n", argv[0]);
		return 0;
	}

	fd = open(devname, O_RDWR);  
	if(fd < 0) {
		perror("open");
		return -1;
	}
	
//  4 个按键   
//  本次读取状态和上次状态对比，不同说明变化，再根据本次读取到状态判断 是松开 还是按下了
	
	while(1) {
		fds.fd=fd;
		fds.events=POLLIN;
		fds.revents=0;
		ret=poll(&fds,1,0);
			
		/*
		多路复用
		fd_set readfds;
		struct timeval tv;
		FD_ZERO(&readfds);
		FD_SET(fd,&readfds);
		tv.tv_sec=1;
		tv.tv_usec=200;
		ret=select(fd+1,&readfds,NULL,NULL,&tv);
		if(FD_ISSET(fd,&readfds))
		*/
		if(ret<0)
		{
			perror("poll\n");
			return ret;
		}
		else if(ret>0)
		{
			if(fds.revents & POLLIN)
			{
				ret = read(fd, recv_buf, BTN_SIZE);  //读取按键数据
				if(ret < 0 ) {
					if( errno != EAGAIN) {
						perror("read");
						exit(-1);
					} else {
						continue;
					}
				}

				//只在状态发生变化时候才输出
				for(i = 0; i < BTN_SIZE; i++) {
					//分别判断每一个按键状态是否发生变化
					if(recv_buf[i] != pre_buf[i]) {
						//更新当前状态为上一次状态
						pre_buf[i] = recv_buf[i];

						//判断这次变化是按下还松开
						if(recv_buf[i] == '1') {
							printf("K%d is press!\r\n", i );
						} else {
							printf("K%d is up!\r\n", i );
						}
					}
				}
			}
		}
	}
	return 0;

}






