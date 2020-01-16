#include "lcd.h"

static int fd;   //限定lcd.c文件中使用

int size, bytes_per_pixel;
unsigned char* fbp ;
struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;


//lcd 初始化,成功返回0,失败返回-1
int  fb_init(const char * path)
{
    int ret;

    //1. 打开lcd设备
    fd = open(path, O_RDWR);
    if(fd < 0) {
        perror("open");
        return -1;
    }

    //2. 获得可变信息和固定信息
    //获得固定信息：
    ret = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    if(ret < 0) {
        perror("ioctl 1");
        return -1;
    }

    //获得可变信息：
    ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    if(ret < 0) {
        perror("ioctl 1");
        return -1;
    }

    //输出可变信息
    printf("xres:%d,yres:%d,bpp:%d\r\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
    printf("red.offset:%d,red.length:%d\r\n", vinfo.red.offset, vinfo.red.length);

    //计算每个像素占用的字节数量以及显存的大小
    if(vinfo.bits_per_pixel >= 24) {  //24,32bpp
        size = vinfo.xres * vinfo.yres * 4;
        bytes_per_pixel = 4;
    } else if(vinfo.bits_per_pixel == 16) { //16bpp
        size = vinfo.xres * vinfo.yres * 2;
        bytes_per_pixel = 2;
    } else { //其他bpp不支持
        printf("error!\r\n");
        return -1;
    }

    //3. 内存映射
    fbp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED , fd, 0);
    if(fbp == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    return 0;
}


//画点函数
//x,y 坐标点  ；  c 是颜色
void fb_show_pixel(unsigned int x, unsigned int y, unsigned int c)
{
    //计算偏移量：bytes 是每个像素占用的字节数量
    int pos = (vinfo.xres * y   + x)  * bytes_per_pixel ;
    if(vinfo.bits_per_pixel >= 24) {       //24,32bpp
        *(unsigned int*)(fbp + pos) = c;
    } else if(vinfo.bits_per_pixel == 16) { //16bpp
        *(unsigned short*)(fbp + pos) = c;
    }
}


//清成白色
void fb_clear(void)
{
    memset(fbp, 0xff, size);
}


//取消映射，关闭文件
void fb_close(void)
{
    munmap(fbp, size);
    close(fd);
}




