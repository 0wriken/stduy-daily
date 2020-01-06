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
#include <linux/timer.h>
#define BTN_SIZE 5
static int key_size;
static char *key_buf;
/*面向对象封装按键*/
struct key_info
{
    int key_id;
    int gpio;
    unsigned long flags;
    char *name;
    int irq;
    struct timer_list timer;
};
static struct key_info keys[5]=
{
    [0]=
    {
    .key_id=0,
    .gpio=5,
    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
    .name="KEY0",
    .irq=0,
    },
    [1]=
    {
    .key_id=1,
    .gpio=50,
    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
    .name="KEY1",
    .irq=0,
    },
    [2]=
    {
    .key_id=2,
    .gpio=54,
    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
    .name="KEY2",
    .irq=0,
    },
    [3]=
    {
    .key_id=3,
    .gpio=55,
    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
    .name="KEY3",
    .irq=0,
    },
    [4]=
    {
    .key_id=4,
    .gpio=48,
    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
    .name="KEY4",
    .irq=0,
    },
};
void btn_function(unsigned long data)
{
    struct key_info *pdata=(struct key_info *)data;
    int value;
    value=gpio_get_value(pdata->gpio);
    if(!value)
    {
        key_buf[pdata->key_id]='0';
        printk("key%d is pull down\n",pdata->key_id);
    }
    else
    {
        key_buf[pdata->key_id]='1';
        printk("key%d is pull up\n",pdata->key_id);
    }
    return ;
}

//ÒÔÏÂÊÇÎÄŒþ²Ù×÷·œ·šµÄŸßÌåÊµÏÖŽúÂë
static int xxx_open(struct inode *pinode, struct file *pfile )
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}



//读取引脚电平


static ssize_t xxx_read(struct file *pfile,char __user *buf, size_t count, loff_t *poff)
{
    if(count>key_size)
        count=key_size;
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


irqreturn_t key0_handler(int irq,void *dev_id)
{
    struct key_info *pdata=(struct key_info *)dev_id;
    mod_timer(&pdata->timer,jiffies+msecs_to_jiffies(20));
    return IRQ_HANDLED;

}

static void my_key_init(void)
{
    int i=0;
    for(i=0;i<BTN_SIZE;i++)
    {
        keys[i].irq=gpio_to_irq(keys[i].gpio);//0 A5 
        if(request_irq(keys[i].irq,key0_handler,keys[i].flags,keys[i].name,(void *)&keys[i])<0)
        {
            printk("error irq\n");
            goto error_btn;
        }
        //初始化定时器
        setup_timer(&keys[i].timer,btn_function,(unsigned long )&keys[i]);
        key_size++;
    }
    return ;
error_btn : 
    while(--i!=0)
    {
         free_irq(keys[i].irq,NULL);
    }
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
    key_buf=kzalloc(key_size+1,GFP_KERNEL);
    if(key_buf==NULL)
    {
        printk("kzalloc jey_buf fail\n");
        return -EFAULT;
    }
    ret = misc_register(&misc);
    if(ret < 0) {
        printk("misc_register error\n");
        kfree(key_buf);
        return ret;
    }
    printk("misc_register  ok\n");
    printk("Device:/dev/%s\r\n",DEV_NAME);
    return 0;
}

static void __exit my_misdevice_exit(void)
{
    int i=sizeof(keys)/sizeof(struct key_info);
    misc_deregister(&misc);
    while(--i!=0)
    {
        free_irq(keys[i].irq,(void *)&keys[i]);
    }
    //灭灯并恢复默认输入
    printk("misc_deregister ok\n");
}
module_init(my_misdevice_init);
module_exit(my_misdevice_exit);
MODULE_LICENSE("GPL");