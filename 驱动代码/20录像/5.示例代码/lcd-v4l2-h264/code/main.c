#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "color.h"
#include "v4l2-function.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
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

int main(int agrc, char *argv[])
{
    int ret;
	const char *video_dev=NULL;
  
	if(agrc==2){
		video_dev = argv[1];
	}
	
    ret =  fb_init(LCD_DEVICE);   //lcd 初始化
    if(ret < 0) {
        printf(" error fb_init\r\n");
        return -1;
    }
    fb_clear();                  //清屏
    cli_init();
    /* YUV格式的数据转换成rgb888，需要使用的的数据表格初始化 */
    initLut();
    
    printf("video init start ……\r\n");
    /* 初始化摄像头设备 */
    ret =  video_device_init(video_dev);
    if(ret < 0) {
        perror(" video_device_init\r\n");
        return -1;
    }

    /* 循环采集数据,显示在lcd屏上并发送到服务器 */
    video_mainloop(&sockfd);

    /*反向初始化视频设备工作*/
    video_device_uninit(4);

    /* 释放lcd资源 */
    fb_close();
    freeLut();

    return 0;
}


#if  0   //测试过程
以下测试使用了硬件浮点编译的x264以及应用程序，软解码下压缩320*240 ,12帧情况下基本正常。
[root@zhifachen home]# ./app-v4l2-h264
xres: 800, yres: 480, bpp: 32
red.offset: 16, red.length: 8
video init start ……
{ pixelformat = 'YUYV', description = 'YUV 4:2:2 (YUYV)' }
DISCRETE:
w*h: 640x480
DISCRETE:
w*h: 160x120
DISCRETE:
w*h: 176x144
DISCRETE:
w*h: 320x176
DISCRETE:
w*h: 320x240
DISCRETE:
w*h: 352x288
DISCRETE:
w*h: 432x240
DISCRETE:
w*h: 544x288
DISCRETE:
w*h: 640x360
DISCRETE:
w*h: 752x416
DISCRETE:
w*h: 800x448
DISCRETE:
w*h: 800x600
DISCRETE:
w*h: 864x480
DISCRETE:
w*h: 960x544
DISCRETE:
w*h: 960x720
DISCRETE:
w*h: 1024x576
DISCRETE:
w*h: 1184x656
DISCRETE:
w*h: 1280x720
DISCRETE:
w*h: 1280x960
{ pixelformat = 'MJPG', description = 'MJPEG' }
DISCRETE:
w*h: 640x480
DISCRETE:
w*h: 160x120
DISCRETE:
w*h: 176x144
DISCRETE:
w*h: 320x176
DISCRETE:
w*h: 320x240
DISCRETE:
w*h: 352x288
DISCRETE:
w*h: 432x240
DISCRETE:
w*h: 544x288
DISCRETE:
w*h: 640x360
DISCRETE:
w*h: 752x416
DISCRETE:
w*h: 800x448
DISCRETE:
w*h: 800x600
DISCRETE:
w*h: 864x480
DISCRETE:
w*h: 960x544
DISCRETE:
w*h: 960x720
DISCRETE:
w*h: 1024x576
DISCRETE:
w*h: 1184x656
DISCRETE:
w*h: 1280x720
DISCRETE:
w*h: 1280x960
== == = after set fmt
fmt.fmt.pix.width = 320
fmt.fmt.pix.height = 240
fmt.fmt.pix.sizeimage = 153600
fmt.fmt.pix.bytesperline = 640
fps: 30
x264 [warning]:
lookaheadless mb - tree requires intra refresh or infinite keyint
x264 [info]:
using cpu capabilities:
ARMv6 NEON
x264 [info]:
profile High 4: 2: 2, level 1.2, 4: 2: 2 8 - bit
sesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesesex264 [info]:
frame I: 9     Avg QP: 18.52  size:  8924
x264 [info]:
frame P: 35    Avg QP: 20.33  size:  4324
x264 [info]:
frame B: 35    Avg QP: 22.71  size:  1421
x264 [info]:
consecutive B - frames: 21.2 % 47.5 % 26.2 %  5.0 %  0.0 %  0.0 %
x264 [info]:
mb I  I16..4:  5.9 % 81.7 % 12.4 %
x264 [info]:
mb P  I16..4:  1.5 % 16.0 %  2.4 %  P16..4: 39.2 % 26.3 % 13.5 %  0.0 %  0.0 %    skip: 1.2 %
x264 [info]:
mb B  I16..4:  0.4 %  1.7 %  0.2 %  B16..8: 40.3 %  6.9 %  1.2 %  direct: 12.0 %  skip: 37.2 %  L0: 36.5 % L1: 52.5 % BI: 11.1 %
x264 [info]: 8x8 transform intra: 80.8 % inter: 79.2 %
x264 [info]:
coded y, uvDC, uvAC intra: 84.0 % 99.4 % 95.3 % inter: 32.5 % 72.6 % 40.8 %
x264 [info]:
i16 v, h, dc, p: 14 % 12 % 10 % 65 %
x264 [info]:
i8 v, h, dc, ddl, ddr, vr, hd, vl, hu: 14 % 15 % 19 %  9 %  8 %  7 %  9 % 10 %  9 %
x264 [info]:
i4 v, h, dc, ddl, ddr, vr, hd, vl, hu: 19 % 18 % 12 %  7 % 11 %  9 % 10 %  7 %  6 %
x264 [info]:
i8c dc, h, v, p: 59 %  8 % 16 % 18 %
x264 [info]:
Weighted P - Frames:
Y: 22.9 % UV: 14.3 %
x264 [info]:
ref P L0: 68.2 % 11.0 % 12.6 %  7.0 %  1.3 %
x264 [info]:
ref B L0: 85.5 % 14.5 %
x264 [info]:
kb / s: 341.92



录制出来的视频可以使用Mplayer 进行播放
mplayer -cache 8192 -fps 25  yuyu422toh264.h264

也可以使用ffmpeg转换为其他格式视频，使用WINdows下播放器播放
ffmpeg  -i yuyu422toh264.h264 -f avi test.avi -y

#endif
