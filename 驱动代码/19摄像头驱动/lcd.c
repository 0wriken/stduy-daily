#include "lcd.h"

static int fd;   //�޶�lcd.c�ļ���ʹ��

int size, bytes_per_pixel;
unsigned char* fbp ;
struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;


//lcd ��ʼ��,�ɹ�����0,ʧ�ܷ���-1
int  fb_init(const char * path)
{
    int ret;

    //1. ��lcd�豸
    fd = open(path, O_RDWR);
    if(fd < 0) {
        perror("open");
        return -1;
    }

    //2. ��ÿɱ���Ϣ�͹̶���Ϣ
    //��ù̶���Ϣ��
    ret = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    if(ret < 0) {
        perror("ioctl 1");
        return -1;
    }

    //��ÿɱ���Ϣ��
    ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    if(ret < 0) {
        perror("ioctl 1");
        return -1;
    }

    //����ɱ���Ϣ
    printf("xres:%d,yres:%d,bpp:%d\r\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
    printf("red.offset:%d,red.length:%d\r\n", vinfo.red.offset, vinfo.red.length);

    //����ÿ������ռ�õ��ֽ������Լ��Դ�Ĵ�С
    if(vinfo.bits_per_pixel >= 24) {  //24,32bpp
        size = vinfo.xres * vinfo.yres * 4;
        bytes_per_pixel = 4;
    } else if(vinfo.bits_per_pixel == 16) { //16bpp
        size = vinfo.xres * vinfo.yres * 2;
        bytes_per_pixel = 2;
    } else { //����bpp��֧��
        printf("error!\r\n");
        return -1;
    }

    //3. �ڴ�ӳ��
    fbp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED , fd, 0);
    if(fbp == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    return 0;
}


//���㺯��
//x,y �����  ��  c ����ɫ
void fb_show_pixel(unsigned int x, unsigned int y, unsigned int c)
{
    //����ƫ������bytes ��ÿ������ռ�õ��ֽ�����
    int pos = (vinfo.xres * y   + x)  * bytes_per_pixel ;
    if(vinfo.bits_per_pixel >= 24) {       //24,32bpp
        *(unsigned int*)(fbp + pos) = c;
    } else if(vinfo.bits_per_pixel == 16) { //16bpp
        *(unsigned short*)(fbp + pos) = c;
    }
}


//��ɰ�ɫ
void fb_clear(void)
{
    memset(fbp, 0xff, size);
}


//ȡ��ӳ�䣬�ر��ļ�
void fb_close(void)
{
    munmap(fbp, size);
    close(fd);
}




