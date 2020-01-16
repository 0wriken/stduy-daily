
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


//lcd �豸�ļ�·��
#define LCD_DEVICE    "/dev/fb0"


extern int size, bytes_per_pixel;
extern unsigned char* fbp ;
extern struct fb_fix_screeninfo finfo;
extern struct fb_var_screeninfo vinfo;


//lcd ��ʼ��,�ɹ�����0,ʧ�ܷ���-1
int  fb_init(const char * path);

//ȡ��ӳ�䣬�ر��ļ�
void fb_close(void);

//����Ϊ��ɫ
void fb_clear(void);

//���㺯��
//x,y �����  ��  c ����ɫ
void fb_show_pixel(unsigned int x, unsigned int y, unsigned int c);


#endif 



