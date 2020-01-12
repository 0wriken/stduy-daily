
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/ioctl.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/fs.h>
#include <asm/io.h>                  //������IO�ڴ����ز���
#include <linux/platform_device.h>

//̽�⺯��
static int led_probe(struct platform_device *pdev)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"pdev->name:%s\r\n", pdev->name);

    printk(KERN_EMERG"pdev->resource[0]->flags:%x\r\n",
           (unsigned int)pdev->resource[0].flags);

    printk(KERN_EMERG"pdev->resource[0]->start:%x,pdev->resource[0]->end:%x\r\n",
           (unsigned int)pdev->resource[0].start,
           (unsigned int)pdev->resource[0].end);

    return 0;
}


//��ɾ���豸ʱ������
static int led_remove(struct platform_device *pdev)
{
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__); //������Ϣ
    return 0;
}


//ƽ̨�豸�����ṹ
struct platform_driver led_driver = {
    .probe  = led_probe,    
    .remove = led_remove,  
    .driver = {
        .owner    = THIS_MODULE,
        .name = "rk3399-leds",
    },
};


//������ʼ������
static int __init leddrv_init(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_driver_register(&led_driver);
    return 0;
}

//����ж�غ���
static void __exit leddrv_exit(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_driver_unregister(&led_driver);
}

module_init(leddrv_init);
module_exit(leddrv_exit);

MODULE_LICENSE("GPL");
