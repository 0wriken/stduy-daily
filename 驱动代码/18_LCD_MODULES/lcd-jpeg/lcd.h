
#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>


//lcd 设备文件路径
#define LCD_DEVICE    "/dev/fb0"


extern int size, bytes_per_pixel;
extern unsigned char* fbp ;
extern struct fb_fix_screeninfo finfo;
extern struct fb_var_screeninfo vinfo;


//lcd 初始化,成功返回0,失败返回-1
int  fb_init(const char * path);

//取消映射，关闭文件
void fb_close(void);

//清屏为白色
void fb_clear(void);

//画点函数
//x,y 坐标点  ；  c 是颜色
void fb_show_pixel(unsigned int x, unsigned int y, unsigned int c);


#endif 



