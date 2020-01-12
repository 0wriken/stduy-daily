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
#include <linux/input.h>
#define  BTN_SIZE    5                  //按键数量

#define  DEV_NAME    "/dev/input/event" //默认设备名
struct input_event ev;
int main(int argc, char *argv[])
{
	int fd, ret, i;
	const char *devname; 
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

		ret = read(fd, &ev, sizeof(ev));  //读取按键数据
		if(ret < 0 ) {
			if( errno != EAGAIN) {
				perror("read");
				exit(-1);
			} else {
				continue;
			}
		}

		switch(ev.type)
		{
			case EV_KEY:
				if(ev.code==KEY_L)
				{
					if(ev.value)
						printf("L is presure\n");
					else
						printf("L is song\n");
				}
				break;
			case EV_SYN:
				printf("EV_SYN\n");
				break;
			default:
				break;
		}
		
	}

	return 0;

}






