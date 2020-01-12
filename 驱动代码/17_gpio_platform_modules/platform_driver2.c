#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include<linux/interrupt.h>
#include <asm/io.h>                  //包含了IO内存的相关操作
#include <linux/platform_device.h>
#define BTN_SIZE 5
char key_buf[BTN_SIZE+1];
struct pin_info
{
   int gpio;
   int value;
   char dri;
}; 

static struct pin_info *pin;

//探测函数
static int led_probe(struct platform_device *pdev)  
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
       
    pin=(struct pin_info *)pdev->dev.platform_data;
    printk("得到设备平台gpio号：%d gpio数值:%d\n",pin->gpio,pin->value);
    gpio_request(pin->gpio,"wriken");
    if(pin->dri=='I')
    {
         gpio_direction_input(pin->gpio);
         printk("输入模式下读取到的数据%d\n",gpio_get_value(pin->gpio));
    }
    else if(pin->dri=='O')
    {
        gpio_direction_output(pin->gpio, pin->value);
        printk("当前为输出模式\n");
        gpio_set_value(pin->gpio,pin->value);
    }
    printk(KERN_EMERG"pdev->name:%s\r\n", pdev->name);

    return 0;
}


//在删除设备时候会调用
static int led_remove(struct platform_device *pdev)
{
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__); //调度信息
    gpio_free(pin->gpio);
    return 0;
}

static struct platform_driver led_driver = {
    .probe  = led_probe,    
    .remove = led_remove,  
    .driver = {
        .owner    = THIS_MODULE,
        .name = "rk3399-leds",
        //.of_match_table = of_devs_table,
    },
    //.id_table = devs_table,
};
//ÒÔÏÂÊÇÎÄŒþ²Ù×÷·œ·šµÄŸßÌåÊµÏÖŽúÂë
static int xxx_open(struct inode *pinode, struct file *pfile )
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
//读取引脚电平

static ssize_t xxx_read(struct file *pfile,char __user *buf, size_t count, loff_t *poff)
{
    printk("我没有写读写驱动函数\n");
    return 0;
}


static loff_t xxx_llseek(struct file *pfile, loff_t off, int whence)
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return off;
}

static int xxx_release (struct inode *pinode, struct file *pfile)
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}

static long xxx_unlocked_ioctl (struct file *pfile,unsigned int cmd, unsigned long args)
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
static void my_led_init(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_driver_register(&led_driver);
    return ;
}
/*初始化时钟*/

//ÎÄŒþ²Ù×÷·œ·šŒ¯ºÏÖžÕë
static const struct file_operations xxx_fops = {
    .open           =   xxx_open,
    .read           =   xxx_read,
    .llseek         =   xxx_llseek,
    .release        =   xxx_release,
    .unlocked_ioctl =   xxx_unlocked_ioctl,
};

#define  DEV_NAME    "key_misc"
//¶šÒåºËÐÄœá¹¹ 
static struct miscdevice  misc = {
    .minor = 255,
    .name  = DEV_NAME,     //devÄ¿ÂŒÏÂµÄÉè±žÃû
    .fops  = &xxx_fops,
};

static int __init my_misdevice_init(void)
{
    int ret;
    my_led_init();
    //×¢²áºËÐÄœá¹¹
    ret = misc_register(&misc);
    if(ret < 0) {
        printk("misc_register error\n");
        return ret;
    }

    printk("misc_register  ok\n");

    printk("Device:/dev/%s\r\n",DEV_NAME);
    return 0;


}

static void __exit my_misdevice_exit(void)
{


    misc_deregister(&misc);
    platform_driver_unregister(&led_driver);
    //灭灯并恢复默认输入
    printk("misc_deregister ok\n");
}
module_init(my_misdevice_init);
module_exit(my_misdevice_exit);
MODULE_LICENSE("GPL");