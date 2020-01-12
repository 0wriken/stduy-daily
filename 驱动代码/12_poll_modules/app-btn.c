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
#include <poll.h>
#define  BTN_SIZE    5                  //��������

#define  DEV_NAME    "/dev/xyd-buttons"  //Ĭ���豸��

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
		fds.fd=fd;
		fds.events=POLLIN;
		fds.revents=0;
		ret=poll(&fds,1,0);
			
		/*
		��·����
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
				ret = read(fd, recv_buf, BTN_SIZE);  //��ȡ��������
				if(ret < 0 ) {
					if( errno != EAGAIN) {
						perror("read");
						exit(-1);
					} else {
						continue;
					}
				}

				//ֻ��״̬�����仯ʱ������
				for(i = 0; i < BTN_SIZE; i++) {
					//�ֱ��ж�ÿһ������״̬�Ƿ����仯
					if(recv_buf[i] != pre_buf[i]) {
						//���µ�ǰ״̬Ϊ��һ��״̬
						pre_buf[i] = recv_buf[i];

						//�ж���α仯�ǰ��»��ɿ�
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






