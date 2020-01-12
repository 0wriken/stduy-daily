#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>        // errno ȫ�ֱ���
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#define  BTN_SIZE    5                  //��������

#define  DEV_NAME    "/dev/input/event" //Ĭ���豸��
struct input_event ev;
int main(int argc, char *argv[])
{
	int fd, ret, i;
	const char *devname; 
	//������⣬���ݲ��������豸��
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
	
//  4 ������   
//  ���ζ�ȡ״̬���ϴ�״̬�Աȣ���ͬ˵���仯���ٸ��ݱ��ζ�ȡ��״̬�ж� ���ɿ� ���ǰ�����
	while(1) {

		ret = read(fd, &ev, sizeof(ev));  //��ȡ��������
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






