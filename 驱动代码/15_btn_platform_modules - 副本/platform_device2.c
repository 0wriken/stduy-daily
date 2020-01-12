
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

#define rGPIO1       0xFF730000  //GPIO1  物理地址
#define rGPIO1SIZE   0xFFFF      //GPIO1  占用空间大小

#define rGPIO0       0xFF720000  //GPIO1  物理地址
#define rGPIO0SIZE   0xFFFF      //GPIO1  占用空间大小

#define rCUR       0xFF750000  //GPIO1  物理地址
#define rCURSIZE   0xFFFF      //GPIO1  占用空间大小

static struct resource led_resource[] = {
    [0] = {
        .start = rGPIO1,
        .end   = rGPIO1 + rGPIO1SIZE - 1,
        .flags = IORESOURCE_MEM,
    },
    [1] = {
        .start = rGPIO0,
        .end   = rGPIO0 + rGPIO0SIZE - 1,
        .flags = IORESOURCE_MEM,
    },
    [2] = {
        .start = rCUR,
        .end   = rCUR + rCURSIZE - 1,
        .flags = IORESOURCE_MEM,
    },

};
struct pin_info
{
   int led_gpio;
   int active_low;
};
struct leds_info
{
    int  group_port;
    int led_size;
    struct led_info *data;
    
};
struct pin_info pin[]
{   
    [0]=
    {
        .led_gpio=13;
        active_low=0,
    },
    [1]=
    {
        .led_gpio=20;
        active_low=0,
    },
};
struct leds_info led_data
{
    .group_port=0;
    led_size=ARRAY_SIZE(led_resource);
    .data=pin;
    
};
static void led_release(struct device * dev)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__);
}


static struct platform_device led_dev = {
    .name = "rk3399-leds-2",
    .id   = -1,
    .num_resources = ARRAY_SIZE(led_resource),
    .resource = led_resource,
    .dev = {
        .release = led_release,
        .platform_data=&led_data ,
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



