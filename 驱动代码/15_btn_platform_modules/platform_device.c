
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

#define rGPIO0       0xFF720000  //GPIO0  �����ַ
#define rGPIO0SIZE   0xFFFF      //GPIO0  ռ�ÿռ��С
static int irq;
static int gpio;   
static struct resource led_resource[] = {
    [0] = {
        .start = irq,
        .end   = irq,
        .flags = IORESOURCE_IRQ,
    },
};


static void led_release(struct device * dev)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__);
}


static struct platform_device led_dev = {
    .name = "wriken-Btn-1",
    .id   = -1,
    .num_resources = ARRAY_SIZE(led_resource),
    .resource = led_resource,
    .dev = {
        .release = led_release,
        .platfrom_data=&gpio;
    },
};


static int leddev_init(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
   // unsigned long flags= IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING;
    gpio=5;    
    irq=gpio_to_irq(gpio);//0 A5 
   //request_irq(irq,key0_handler,flags,"KEY0",NULL);
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
�豸
struct platform_device led_dev
{
    name,id,;
    resource;
    num_resource;
    dev;release
    //�ں˷��䵽������
    struct platform_device_id *id_entry; 
}   
��Դ �������� ioremap
struct resource []
{
    �ж�
    [0]=
    {
    .start=
    .end=
    .flag= 
    .name=
    }
    �ڴ�
    [1]
    �Ĵ���
    [2]
}
struct device
{
    bus;
    void *platfrom_data;//���ݽ���
}
platform_device_register(&led_dev)










*/

