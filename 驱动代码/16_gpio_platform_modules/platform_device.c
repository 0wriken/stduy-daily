
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
设备
struct platform_device led_dev
{
    name,id,;
    resource;
    num_resource;
    dev;release
    //内核分配到驱动中
    struct platform_device_id *id_entry; 
}   
资源 传给驱动 ioremap
struct resource []
{
    中断
    [0]=
    {
    .start=
    .end=
    .flag= 
    .name=
    }
    内存
    [1]
    寄存器
    [2]
}
struct device
{
    bus;
    void *platfrom_data;//数据交互
}
platform_device_register(&led_dev)










*/

