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

    ret =  fb_init(LCD_DEVICE);   //lcd ��ʼ��
    if(ret < 0) {
        printf(" error fb_init\r\n");
        return -1;
    }
    fb_clear();                  //����

#if 0
    //����ͷ����ʼ
    /* YUV��ʽ������ת����rgb888����Ҫʹ�õĵ����ݱ���ʼ�� */
    initLut();

    printf("video init start ����\r\n");

    /* ��ʼ������ͷ�豸 */
    video_device_init(NULL);

    /* ѭ���ɼ�����,��ʾ��lcd���� */
    video_mainloop();

    /*�����ʼ����Ƶ�豸����*/
    video_device_uninit(4);
#endif

    if(agrc != 2) {
        printf("Usage:%s path/to/file/xxx.jpeg\r\n");
        return 0;
    }

    lcd_show_jpeg(argv[1], 0, 0);


    /* �ͷ�lcd��Դ */
    fb_close();

    return 0;
}


