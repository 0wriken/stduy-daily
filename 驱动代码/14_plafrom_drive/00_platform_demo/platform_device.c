
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

#define rGPIO0       0xFF730000  //GPIO1  物理地址
#define rGPIO0SIZE   0xFFFF      //GPIO0  占用空间大小


static struct resource led_resource[] = {
    [0] = {
        .start = rGPIO0,
        .end   = rGPIO0 + rGPIO0SIZE - 1,
        .flags = IORESOURCE_MEM,
    },
};


static void led_release(struct device * dev)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__);
}


static struct platform_device led_dev = {
    .name = "rk3399-leds",
    .id   = -1,
    .num_resources = ARRAY_SIZE(led_resource),
    .resource = led_resource,
    .dev = {
        .release = led_release,
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



