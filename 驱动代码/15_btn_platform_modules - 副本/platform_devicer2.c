
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/ioctl.h>
#include <asm/io.h>                  //包含了IO内存的相关操作
#include <linux/platform_device.h>
/*#define CRU_BASE 0XFF750000
#define GPIO1_BASE 0XFF730000
#define GPIO0_BASE 0XFF720000
#define GPIO0_SIZE 0XFFFF
#define GPIO1_SIZE 0XFFFF
#define CRU_SIZE 0XFFFF*/
#define LED_SIZE 5
//ÐéÄâÓ³Éä
void *va_base =NULL;
void *gpio0_base=NULL;

void *gpio1_base=NULL;
#define CRU_CLACK_COM1 *(volatile unsigned int *)(va_base+0x0104)

#define GPIO0_DDR  *(volatile unsigned int *)(gpio0_base+0x0004) 
#define GPIO0_EXT  *(volatile unsigned int *)(gpio0_base+0x0050) 
#define GPIO0_DR  *(volatile unsigned int *)(gpio0_base+0x0000) 

#define GPIO1_DDR  *(volatile unsigned int *)(gpio1_base+0x0004) 
#define GPIO1_EXT  *(volatile unsigned int *)(gpio1_base+0x0050) 
#define GPIO1_DR  *(volatile unsigned int *)(gpio1_base+0x0000) 

typedef struct sleek
{
    loff_t off ;
    int whence;   
}IO_sleek;
#define  IOC_LED_MIN 0
#define  IOC_LED_MAX 5
#define LED_ON_ALL _IO('L',0)
#define LED_OFF_ALL _IO('L',1)
#define LED_ON_X   _IOW('L',2,int)
#define LED_OFF_X   _IOW('L',3,int)
#define LED_POLL_ALL _IOW('L',4,int)
#define LED_LSEEK _IOW('L',5,struct sleek)
struct pin_info
{
   int led_gpio;
   int active_low;
};
struct leds_info
{
    int  group_port;
    int led_size;
    struct pin_info *data;
};
static struct leds_info *led_data;
struct  Led_info
{
    int CRL;
    char *name;
    u32 gpio;
    struct resource res;
};
struct Led_info 
{
    [0]={
      .CRL=0,
        .name="wriken-Crl-0",  
         gpio_base=0,
    },
    [1]={
        .CRL=0,
        .name="wriken-Led-0",
        gpio_base=0,
    },
    [2]={
      .CRL=0,
        .name="wriken-Led-1",  
         gpio_bae=0,
    },

};
static struct platform_driver led_driver = {
    .probe  = led_probe,    
    .remove = led_remove,  
    .driver = {
        .owner    = THIS_MODULE,
        .name = "rk3399-leds",
        .of_match_table = of_devs_table,
    },
    //.id_table = devs_table,
};
//探测函数
static int led_probe(struct platform_device *pdev)  
{
    //平台数据
    //获得资源
    //处理资源
    //初始化硬件
    //用户层接口
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    for(i=0;i<3;i++)
    {
        &(led[i].res)= platfrom_get_resource_byname(pdev,Led[i].name);
        if(i==0)
        {
            va_base=ioremap_nocache(led[i].res.start,led[i].res.end-led[i].res.start+1);
            if(va_base==NULL)
            {
                goto error_base0;
                ret=-EFAULT;
            }
        }
        else if(i==1)
        {
            gpio0_base= ioremap_nocache(led[i].res.start,led[i].res.end-led[i].res.start+1);
            if(gpio0_base==NULL)
            {
                goto error_base1;
                ret=-EFAULT;
            }
        }
        else if(i==2)
        {
             gpio1_base= ioremap_nocache(led[i].res.start,led[i].res.end-led[i].res.start+1);
            if(gpio1_base==NULL)
            {
                goto error_base1;
                ret=-EFAULT;
            }
        }
        }
    //获得data
        led_data=(struct leds_info *)pdev->dev.platform_data;
        if(led_data==NULL)
        {
            printk("led_data is NULL");
            return -EFAULT;
        }
        if(led_data->group_port==1)
            gpio1_init();
        if(led_data->group_port==0)
            gpio1_init();
        for(int i=0;i<led_data->led_size;i++)
        {
            Gpiox_OUT(led_data->pin[i].led_gpio,led_data->pin[i].active_low);
        }
    //如何获得各自id下的data

    
    printk(KERN_EMERG"pdev->name:%s\r\n", pdev->name);

    printk(KERN_EMERG"pdev->resource[0]->flags:%x\r\n",
           (unsigned int)pdev->resource[0].flags);

    printk(KERN_EMERG"pdev->resource[0]->start:%x,pdev->resource[0]->end:%x\r\n",
           (unsigned int)pdev->resource[0].start,
           (unsigned int)pdev->resource[0].end);
    return 0;
}

//驱动获取data后的引脚处理
static void Gpiox_OUT(int i,int low)
{
    if(i>32||i<0)
    {
        printk("pin is error\n");
        return ;
    }
    if(i==0&&low==0)
    {
        GPIO0_DR|=(1<<i);
    }
    else if(low==1)
    {    
        GPIO1_DR&=~(1<<i);
    }
    else if(low==0)
    {
        GPIO1_DR|=(1<<i);   
    }
    return ;
}

//在删除设备时候会调用
static int led_remove(struct platform_device *pdev)
{
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__); //调度信息
    return 0;
}
//ÒÔÏÂÊÇÎÄŒþ²Ù×÷·œ·šµÄŸßÌåÊµÏÖŽúÂë
static int xxx_open(struct inode *pinode, struct file *pfile )
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
static void gpio_ctl( int num,int cmd)
{

    //同组设备决定
     GPIO0_DDR|=(0X1<<13);
     GPIO0_DDR|=(0X1<<1);
     GPIO0_DDR|=(0X1<<3);
     GPIO0_DDR|=(0X1<<4);
    //io口
    if(num==0)
    {
        if(cmd)
        {       
            GPIO0_DR |= (0X1<<13);
            printk("led_on\n");
        }
        else
        {
            GPIO0_DR &= ~(0X1<<13);
            printk("led_off\n");
        }
    }
    if(num==1)
    {
        if(cmd)
        {       
            GPIO1_DR |= (0X1<<1);
            printk("led1_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<1);
            printk("led1_off\n");
        }
    }
    if(num==2)
    {
        if(cmd)
        {       
            GPIO1_DR |= (0X1<<3);
            printk("led3_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<3);
            printk("led3_off\n");
        }
    }
    if(num==3)
    {
     if(cmd)
        {       
            GPIO1_DR |= (0X1<<4);
            printk("led4_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<4);
            printk("led4_off\n");
        }   
    }
    if(num==4)
    {
     if(cmd)
        {       
            GPIO1_DR |= (0X1<<18);
            printk("led4_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<18);
            printk("led4_off\n");
        }   
    }
    if(num==5)
    {
     if(cmd)
        {       
            GPIO1_DR |= (0X1<<22);
            printk("led4_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<22);
            printk("led4_off\n");
        }   
    }
    if(num==6)
    {
     if(cmd)
        {       
            GPIO1_DR |= (0X1<<23);
            printk("led4_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<23);
            printk("led4_off\n");
        }   
    }
    if(num==7)
    {
     if(cmd)
        {       
            GPIO1_DR |= (0X1<<24);
            printk("led4_on\n");
        }
        else
        {
            GPIO1_DR &= ~(0X1<<24);
            printk("led4_off\n");
        }   
    }
}
//读取引脚电平
static  int  gpio_read(int num)
{
    int ret;
    GPIO0_DDR &=~ (0X1<<13);
    if(num==0)
    {
        ret= !!(GPIO0_EXT&(1<<13));
    }
    else if(num==1)
    {
        ret= !!(GPIO1_EXT&(1<<1));
    }
        else if(num==2)
    {
        ret= !!(GPIO1_EXT&(1<<3));
    }
        else if(num==3)
    {
        ret= !!(GPIO1_EXT&(1<<4));
    }
        else if(num==4)
    {
        ret= !!(GPIO1_EXT&(1<<18));
    }
        else if(num==5)
    {
        ret= !!(GPIO1_EXT&(1<<22));
    }
        else if(num==6)
    {
        ret= !!(GPIO1_EXT&(1<<23));
    }
        else if(num==1)
    {
        ret= !!(GPIO1_EXT&(1<<24));
    }
    return ret;
}
static ssize_t xxx_read(struct file *pfile,char __user *buf, size_t count, loff_t *poff)
{
    char *kdata=kzalloc(count+1,GFP_KERNEL);
    int i=0;
    loff_t cur_fpos=pfile->f_pos;
    if(count>(LED_SIZE-cur_fpos))
        count=LED_SIZE-cur_fpos;
    if(count==0)
        return 0;
    if(kdata==NULL)
    {
        return -ENOMEM;
    }
     for(i=0;i<count;i++)
     {
        if(gpio_read(i+cur_fpos))
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
    pfile->f_pos+=count;
    kfree(kdata);
    return count;
}
char *kbuf=NULL;
static ssize_t xxx_write(struct file *pfile, const char __user *buf, size_t count, loff_t *poff)
{
    int i=0;
    
    //char kbuf[LED_SIZE+1]={0};
 /*   GPIO0_DDR|=(0X1<<13);//输出模式
    GPIO1_DDR|=(0X1<<1);
    GPIO1_DDR|=(0X1<<3);
    GPIO1_DDR|=(0X1<<4);
    GPIO1_DDR|=(0X1<<18);
    GPIO1_DDR|=(0X1<<22);
    GPIO1_DDR|=(0X1<<23);
    GPIO1_DDR|=(0X1<<24);
  */
    loff_t cur_fpos= *poff;
    if(count>(LED_SIZE-cur_fpos))
        count=LED_SIZE-cur_fpos;
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
    //循环判断并控制灯
    for(i=0;i<count;i++)
    {
        if(kbuf[i]=='1')
        {
            printk("led%d_on\n",i);
            gpio_ctl(cur_fpos+i,0);  
        }
        else if(kbuf[i]=='0')
        {
            printk(" led%d_off\n",i);
            gpio_ctl(cur_fpos+i,1);  
        }
        else
        {
            printk("nothing to do\n");
        }
    }
    *poff+=count;    
    kfree(kbuf);
    return count;
error1:
    kfree(kbuf);
    return -EFAULT;
}

static loff_t xxx_llseek(struct file *pfile, loff_t off, int whence)
{
    loff_t  tmp=0;
    if(whence==SEEK_SET)
    {
        tmp=off;
    }
     else if(whence==SEEK_CUR)
    {
        tmp=pfile->f_pos+off;
    }
    else if(whence==SEEK_END)
    {
        tmp=LED_SIZE+off;
    }
    else
    {
        printk("error pathsame\n ");
        return -EINVAL;
    }
    if((tmp<0)|| tmp>LED_SIZE )
    {
        printk("llseek error \n");
        return -EINVAL;
    }
    pfile->f_pos=tmp;
    return off;
}

static int xxx_release (struct inode *pinode, struct file *pfile)
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
/*  IOCTL*/
static long xxx_unlocked_ioctl (struct file *pfile,unsigned int cmd, unsigned long args)
{
    int i=0;
    int nr=0;
    char send_buf[10]={0};
    IO_sleek led_sleek={0,0};
    loff_t tmp=0;
    if(_IOC_NR(cmd)>IOC_LED_MAX||_IOC_NR(cmd)<IOC_LED_MIN)
    {
        printk("OUT OF NR\n");
        return -EINVAL;
    }
    switch(cmd)
    {
        case LED_ON_ALL: 
        case LED_OFF_ALL:
        {
            if(cmd==LED_ON_ALL)
            {
                for(i=0;i<LED_SIZE;i++)
                gpio_ctl(i,0);
                break;
            }
            else
            {
                for(i=0;i<LED_SIZE;i++)
                gpio_ctl(i,1);
                break;   
            }
        }
        case LED_ON_X:
        case LED_OFF_X:
        {
            if(copy_from_user(&nr,(void *)args,_IOC_SIZE(cmd)))
            {
            printk("error  ioctl copy_from_user\n");
            return -EFAULT;
            }
            printk("nr ******** :%d\n",nr);
            if(nr>LED_SIZE)
                nr=LED_SIZE;
            if(cmd ==LED_ON_X)
            {
                gpio_ctl(nr,0);
                break;
            }
            else
            {
                gpio_ctl(nr,1);
                break;   
            }
        }
        case LED_POLL_ALL:
        {
          for(i=0;i<LED_SIZE;i++)
          {

            if(gpio_read(i))  
                send_buf[i]='1';
            else
                send_buf[i]='0';
          }
          if(copy_to_user((char *)args,send_buf,LED_SIZE))
          {
            printk("error copy_to_user\n");
            return -EFAULT;
          }
          break;
        }
        case LED_LSEEK:
        {
            if(copy_from_user(&led_sleek,(void *)args,_IOC_SIZE(cmd)))
            {
                printk("error IOCTL llseek\n");
                return -EFAULT;
            }
            if(led_sleek.whence==SEEK_SET)
            {
                tmp=led_sleek.off;
            }
             else if(led_sleek.whence==SEEK_CUR)
            {
                tmp=pfile->f_pos+led_sleek.off;
            }
            else if(led_sleek.whence==SEEK_END)
            {
                tmp=LED_SIZE+led_sleek.off;
            }
            else
            {
                printk("error pathsame\n ");
                return -EINVAL;
            }
            if((tmp<0)|| tmp>LED_SIZE )
            {
                printk("llseek error \n");
                return -EINVAL;
            }
            pfile->f_pos=tmp;
            printk("addr is %lld\n",pfile->f_pos);
            break;
        }

        default:
        {
            printk("nothing\n");
            return -EINVAL;
        }
    }
    return args;
}

/*初始化时钟*/
static void gpio0_init(void)
{
    CRU_CLACK_COM1|=(0X1<<19);
    CRU_CLACK_COM1&=~(0X1<<3);
    GPIO0_DDR|=(0X1<<13);
}
static void gpio1_init(void)
{
    CRU_CLACK_COM1|=(0X1<<20);
    CRU_CLACK_COM1&=~(0x1<<4);
     GPIO1_DDR|=(0X1<<1);
     GPIO1_DDR|=(0X1<<3);
     GPIO1_DDR|=(0X1<<4);
     GPIO1_DDR|=(0X1<<18);
     GPIO1_DDR|=(0X1<<22);
     GPIO1_DDR|=(0X1<<23);
     GPIO1_DDR|=(0X1<<24);
    printk("flow light is ok\n");
}

//ÎÄŒþ²Ù×÷·œ·šŒ¯ºÏÖžÕë
static const struct file_operations xxx_fops = {
    .open           =   xxx_open,
    .read           =   xxx_read,
    .write          =   xxx_write,
    .llseek         =   xxx_llseek,
    .release        =   xxx_release,
    .unlocked_ioctl =   xxx_unlocked_ioctl,
};

#define  DEV_NAME    "led_misc"
//¶šÒåºËÐÄœá¹¹ 
static struct miscdevice  misc = {
    .minor = 255,
    .name  = DEV_NAME,     //devÄ¿ÂŒÏÂµÄÉè±žÃû
    .fops  = &xxx_fops,
};
//初始化
static int __init my_misdevice_init(void)
{
    int ret;   
    platform_driver_register(&led_driver);
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
    platform_driver_unregister(&led_driver);
    misc_deregister(&misc);
    
    //灭灯并恢复默认输入
    GPIO0_DDR &= ~(0X1<<13);
    gpio_ctl(0,0);
    iounmap(gpio0_base);
    iounmap(va_base);
    printk("misc_deregister ok\n");
}

module_init(my_misdevice_init);
module_exit(my_misdevice_exit);
MODULE_LICENSE("GPL");

