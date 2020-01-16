#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "color.h"
#include "v4l2-function.h"
#include "show-jpeg.h"
int main(int agrc, char *argv[])
{
    int ret;

    ret =  fb_init(LCD_DEVICE);   //lcd 初始化
    if(ret < 0) {
        printf(" error fb_init\r\n");
        return -1;
    }
    fb_clear();                  //清屏

#if 0
    //摄像头程序开始
    /* YUV格式的数据转换成rgb888，需要使用的的数据表格初始化 */
    initLut();

    printf("video init start ……\r\n");

    /* 初始化摄像头设备 */
    video_device_init(NULL);

    /* 循环采集数据,显示在lcd屏上 */
    video_mainloop();

    /*反向初始化视频设备工作*/
    video_device_uninit(4);
#endif

    if(agrc != 2) {
        printf("Usage:%s path/to/file/xxx.jpeg\r\n");
        return 0;
    }

    lcd_show_jpeg(argv[1], 0, 0);


    /* 释放lcd资源 */
    fb_close();

    return 0;
}


