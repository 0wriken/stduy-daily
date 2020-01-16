
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
 
struct pin_info
{
   int gpio;
   int value;
   char dri;
}; 

static struct pin_info pin_gpio={13,1,'O'};



static void led_release(struct device * dev)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__);
}


static struct platform_device led_dev = {
    .name = "rk3399-leds",
    .id   = -1,
    .dev = {
        .release = led_release,
        .platform_data=(void *)&pin_gpio,
    },
};


static int leddev_init(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_device_register(&led_dev);
    return 0;
}

static void leddev_exit(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_device_unregister(&led_dev);
}

module_init(leddev_init);
module_exit(leddev_exit);

MODULE_LICENSE("GPL");

/*
映射: void* mmap(void*addr,size_t lenth,int port,
    int flag,int fd,offset_set offset)
    port->文件操作权限
    flag-> MAP_SHARED共享映射 MAP_PRIVATE私有映射

    munmap(void *addr,size_t lenth)

    （x,y）=fd_base+y*len+x*bpp/8;
LCD屏显示JPEG
    移植JPEG编码库  在linux下解压 进入./config --help
    系统配置 --prefix=存放路径 --bulid=BUILD 宿主机默认不用配置 --host=HOST 目标机交叉编译器
    --target默认与上述一样   -enable-share -enable-static
    编译配置：CC 编译器名称  CFLAGS 指定编译标志如依赖的库优化等等
            LDFLAGS -L库路径  LIBS -l库名 指定多个库"-l -l" 
            CPPFLAGS -I头文件路径
            CPP 指定预处理器 gcc -E   
            alisa sudo ="sudo env PATH=$PATH"

libjepg图片解码 
压缩：rgb -> jepg








*/

