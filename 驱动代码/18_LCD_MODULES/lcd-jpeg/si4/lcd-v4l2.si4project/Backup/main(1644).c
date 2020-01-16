#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "color.h"
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

    if(agrc != 2) {
        printf("Usage:%s path/to/file/xxx.jpeg\r\n");
        return 0;
    }

	//������ʾһ��JPEGͼƬ
    lcd_show_jpeg(argv[1], 0, 0);

    /* �ͷ�lcd��Դ */
   // fb_close();

    return 0;
}


