#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "color.h"
#include "show-jpeg.h"
#include <sys/types.h>
#include "unistd.h"
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>       
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#define KEY_NAME  "/dev/xyd-buttons"
DIR *dir1;
int main(int agrc, char *argv[])
{
    int key_fd;
    int ret;
    struct dirent *ptr=(struct dirent *)malloc(sizeof(1024));
	char buf[1024];
    char check_buf[100];
    char check_buf1[100];
    char key_buf[2];
    printf(" show jpeg test \r\n");
    if(agrc != 2) {
        printf("Usage:%s path/to/file/xxx.jpeg\r\n",argv[0]);
        return 0;
    }
    ret =  fb_init(LCD_DEVICE);   //lcd 初始化
    if(ret < 0) {
        printf(" error fb_init\r\n");
        return -1;
    }
    //初始化按键
    key_fd=open(KEY_NAME,O_RDWR);
    if(key_fd<0)
    {
        printf("open key is fail\n");
        return -1;
    }

    fb_clear();                  //清屏
    sprintf(check_buf1,"%s..",argv[1]);
    sprintf(check_buf,"%s.",argv[1]);
    printf("%s\n",check_buf1);
    printf("%s\n",check_buf);
	//测试显示一张JPEG图片
    dir1=opendir(argv[1]);
    lcd_show_jpeg("./picture/logo-800x480.jpg",0,0);
    while(read(key_fd,key_buf,1))
    {
        if(key_buf[0]=='0') //按下
        {
            printf("1111111111\n");
        update:
            if((ptr=readdir(dir1))==NULL)
            {
                 closedir(dir1);
                 dir1=opendir(argv[1]);
                 printf("upadte\n");
            }
            //fb_clear(); 
            printf("lcd_key is press\n");
            memset(buf,0,1024);
            if(ptr==NULL)
                goto update;
            sprintf(buf,"%s%s",argv[1],ptr->d_name);
            printf("%s\n",buf);
            if((strcmp(buf,check_buf1)!=0)&&(strcmp(buf,check_buf)!=0))
            {
                printf("file name is %s\n",buf);
                lcd_show_jpeg(buf, 0, 0);
            }
        }
         memset(key_buf,0,2);
    }
    //fb_clear();
    /* 释放lcd资源 */
    closedir(dir1);
    fb_close();
    free(ptr);
    return 0;
}


