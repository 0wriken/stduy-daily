#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#define CRU_BASE 0XFF750000
#define GPIO0_BASE 0XFF720000
#define GPIO0_SIZE 0XFFFF
#define CRU_SIZE 0XFFFF
//ÐéÄâÓ³Éä
void *va_base =NULL;
void *gpio0_base=NULL;
void *gpio1_base=NULL;
#define CRU_CLACK_COM1 *(volatile unsigned int *)(va_base+0x0104)

#define GPIO0_DDR  *(volatile unsigned int *)(gpio0_base+0x0004) 
#define GPIO0_EXT  *(volatile unsigned int *)(gpio0_base+0x0050) 
#define GPIO0_DR  *(volatile unsigned int *)(gpio0_base+0x0000) 


//ÒÔÏÂÊÇÎÄŒþ²Ù×÷·œ·šµÄŸßÌåÊµÏÖŽúÂë
static int xxx_open(struct inode *pinode, struct file *pfile )
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
//读取引脚电平
static  int  gpio_read(int num)
{
    int ret;
    GPIO0_DDR &=~ (0X1<<5);
    if(num==0)
    {
        ret= !!(GPIO0_EXT&(1<<5));
    }
    else if(num==1)
    {

    }
    return ret;
}
static ssize_t xxx_read(struct file *pfile,char __user *buf, size_t count, loff_t *poff)
{
    int i=0;
    char *kdata=kzalloc(count+1,GFP_KERNEL);
    if(kdata==NULL)
    {
        return -ENOMEM;
    }
     for(i=0;i<count;i++)
     {
        if(gpio_read(i))
        {
            kdata[i]='1';
        }
        else
        {
            kdata[i]='0';
        }
     }
    if(copy_to_user(buf,kdata,count))
    {
        printk("error copy_to_user\n");
        kfree(kdata);
        return -EFAULT;
    }
    kfree(kdata);
    return count;
}

static ssize_t xxx_write(struct file *pfile, const char __user *buf, size_t count, loff_t *poff)
{

    char *kbuf=NULL;
    //char kbuf[LED_SIZE+1]={0};
    GPIO0_DDR&=~(0X1<<5);//输入模式
    
    if(count==0)
        return 0;
    kbuf=kzalloc(count+1,GFP_KERNEL);
    if(kbuf==NULL)
    {
        return -ENOMEM;
    }
    if(copy_from_user(kbuf,buf,count))
    {
        printk("error copy_from_user\n");
         
        goto error1;
    }
    kfree(kbuf);
    return count;
error1:
    kfree(kbuf);
    return -EFAULT;
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

static void my_key_init(void)
{
    GPIO0_DDR&=~(0X1<<5);
}
/*初始化时钟*/

//ÎÄŒþ²Ù×÷·œ·šŒ¯ºÏÖžÕë
static const struct file_operations xxx_fops = {
    .open           =   xxx_open,
    .read           =   xxx_read,
    .write          =   xxx_write,
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
    va_base= ioremap_nocache(CRU_BASE,CRU_SIZE);
    if(va_base==NULL)
    {
        goto error_base0;
        ret=-EFAULT;
    }

    gpio0_base= ioremap_nocache(GPIO0_BASE,GPIO0_SIZE);
    if(gpio0_base==NULL)
    {
        goto error_base1;
        ret=-EFAULT;
    }
    CRU_CLACK_COM1|=(0X1<<19);
    CRU_CLACK_COM1&=~(0X1<<3);
    my_key_init();
    printk("key:%d\n",gpio_read(0));
    //×¢²áºËÐÄœá¹¹
    ret = misc_register(&misc);
    if(ret < 0) {
        printk("misc_register error\n");
        return ret;
    }

    printk("misc_register  ok\n");

    printk("Device:/dev/%s\r\n",DEV_NAME);
    return 0;
error_base1:
    iounmap(va_base);
    return ret;
error_base0:
    return ret;

}

static void __exit my_misdevice_exit(void)
{
    
    misc_deregister(&misc);
    
    //灭灯并恢复默认输入
    iounmap(gpio0_base);
    iounmap(va_base);
    printk("misc_deregister ok\n");
}

module_init(my_misdevice_init);
module_exit(my_misdevice_exit);
MODULE_LICENSE("GPL");


