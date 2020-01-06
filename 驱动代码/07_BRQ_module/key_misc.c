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

#define BTN_SIZE 5
char key_buf[BTN_SIZE+1];
//ÒÔÏÂÊÇÎÄŒþ²Ù×÷·œ·šµÄŸßÌåÊµÏÖŽúÂë
static int xxx_open(struct inode *pinode, struct file *pfile )
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
//读取引脚电平

static ssize_t xxx_read(struct file *pfile,char __user *buf, size_t count, loff_t *poff)
{
    if(count>BTN_SIZE)
        count=BTN_SIZE;
    if(count==0)
        return 0;
    if(copy_to_user(buf,key_buf,count))
    {
        printk("error copy_to_user\n");
        return -EFAULT;
    }
    return BTN_SIZE;
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
//cat proc/interrupts | -name
irqreturn_t key0_handler(int irq,void *dev_id)
{
    int value;
    value=gpio_get_value(5);
    if(!value)
    {
        key_buf[5]='0';
        printk("key0 is pull down\n");
    }
    else
    {
        key_buf[5]='1';
        printk("key0 is pull up\n");
    }
    return IRQ_HANDLED;

}
irqreturn_t key1_handler(int irq,void *dev_id)
{
    int value;
    value=gpio_get_value(50);
    if(!value)
    {
        key_buf[0]='0';
        printk("key1 is pull down\n");
    }
    else
    {
        key_buf[0]='1';
    }
    return IRQ_HANDLED;

}
irqreturn_t key2_handler(int irq,void *dev_id)
{
    int value;
    value=gpio_get_value(54);
    if(!value)
    {
        key_buf[1]='0';
        printk("key2 is pull down\n");
    }
    else
    {
        key_buf[1]='1';
    }
    return IRQ_HANDLED;

}
irqreturn_t key3_handler(int irq,void *dev_id)
{
    int value;
    value=gpio_get_value(55);
    if(!value)
    {
        key_buf[2]='0';
        printk("key2 is pull down\n");
    }
    else
    {
        key_buf[2]='1';
    }
    return IRQ_HANDLED;
}
irqreturn_t key4_handler(int irq,void *dev_id)
{
    int value;
    value=gpio_get_value(48);
    if(!value)
    {
        key_buf[3]='0';
        printk("key3 is pull down\n");
    }
    else
    {
        key_buf[3]='1';
    }
    return IRQ_HANDLED;

}
static void my_key_init(void)
{
    int irq=0;
    unsigned long flags= IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING;
    irq=gpio_to_irq(5);//0 A5 
    request_irq(irq,key0_handler,flags,"KEY0",NULL);
    enable_irq(irq);
    irq=gpio_to_irq(50);//1 C2 
    request_irq(irq,key1_handler,flags,"KEY1",NULL);
    enable_irq(irq);
    irq=gpio_to_irq(54);//1 C6
    request_irq(irq,key2_handler,flags,"KEY2",NULL);
    enable_irq(irq);
    irq=gpio_to_irq(55); //1 C7
    request_irq(irq,key3_handler,flags,"KEY3",NULL);
    enable_irq(irq);
    irq=gpio_to_irq(56);//1 D0
    enable_irq(irq);
    request_irq(irq,key4_handler,flags,"KEY4",NULL);
    enable_irq(irq);

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
    my_key_init();
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
    int irq;
    misc_deregister(&misc);
    irq=gpio_to_irq(50);//1 C2 
    free_irq(irq,NULL);
    irq=gpio_to_irq(55);//1 C2 
    free_irq(irq,NULL);
    irq=gpio_to_irq(54);//1 C2 
    free_irq(irq,NULL);
    irq=gpio_to_irq(48);//1 C2 
    free_irq(irq,NULL);
    irq=gpio_to_irq(5);//1 C2 
    free_irq(irq,NULL);
    //灭灯并恢复默认输入
    printk("misc_deregister ok\n");
}
module_init(my_misdevice_init);
module_exit(my_misdevice_exit);
MODULE_LICENSE("GPL");