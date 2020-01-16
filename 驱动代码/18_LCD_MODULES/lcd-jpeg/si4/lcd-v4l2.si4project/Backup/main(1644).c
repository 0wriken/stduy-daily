#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "color.h"
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

    if(agrc != 2) {
        printf("Usage:%s path/to/file/xxx.jpeg\r\n");
        return 0;
    }

	//测试显示一张JPEG图片
    lcd_show_jpeg(argv[1], 0, 0);

    /* 释放lcd资源 */
   // fb_close();

    return 0;
}


