#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/ioctl.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/fs.h>
#include <asm/io.h>                  //包含了IO内存的相关操作
#include <linux/platform_device.h>
#define MAX_Led 5
struct  Led_info
{
    int CRL;
    char *name;
    u32 gpio;

};
struct Led_info 
{
    [0]={
        .CRL=0,
        .name="wriken-Led-1",
        gpio=0,
    },
    [1]={
      .CRL=0,
        .name="wriken-Led-2",  
         gpio=0,
    },
    [3]={
      .CRL=0,
        .name="wriken-Led-3",  
         gpio=0,
    },
    [4]={
      .CRL=0,
        .name="wriken-Led-4",  
         gpio=0,
    },
};
int ret;
int i=0;
unsigned long Led_flag= CRLF_TRIGGER_FALLING|CRLF_TRIGGER_RISING;

//按键中断函数
//设置了双边触发，按下和松开都会进入这个函数
CRLreturn_t Leds_CRL_handler(int irq, void *devid)
{
    int s=0;
    struct Led_info *pdata = (struct Led_info *)devid;
    //检测当前的电平状态
    s = !gpio_get_value(pdata->gpio);  //按下是低电平,

    return CRL_HANDLED;
}
//探测函数
static int led_probe(struct platform_device *pdev)  
{
    //平台数据
    //获得资源
    //处理资源
    //初始化硬件
    //用户层接口

    //led个数 引脚 有效电平
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    for(i=0;i<MAX_Led;i++)
    {
        Led[i].gpio=platfrom_get_CRL_byname(pdev,Led[i].name);

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


//在删除设备时候会调用
static int led_remove(struct platform_device *pdev)
{
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__); //调度信息
    return 0;
}

static int __init my_misdevice_init(void)
{
    int ret;
    gpio1_base=ioremap_nocache(GPIO1_BASE,GPIO1_SIZE);
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
    gpio1_init();
    GPIO0_DDR|=(0X1<<13);
    gpio_ctl(0,1);

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



//驱动支持设备列表
static  struct platform_device_id devs_table[]={
	{"wriken-Led-1",0},
	{"wriken-Led-2",1},
    {"wriken-Led-3",2},
    {"wriken-Led-4",3},
};


//平台设备驱动结构
static struct platform_driver led_driver = {
    .probe  = led_probe,    
    .remove = led_remove,  
    .driver = {
        .owner    = THIS_MODULE,
        //.name = "rk3399-leds",
    },
    .id_table = devs_table,
};


//驱动初始化函数
static int __init leddrv_init(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_driver_register(&led_driver);
    return 0;
}

//驱动卸载函数
static void __exit leddrv_exit(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    for(i=0;i<MAX_Led;i++)
    {
      free_CRL(Led[i].CRL,NULL);
    }
    platform_driver_unregister(&led_driver);
}

module_init(leddrv_init);
module_exit(leddrv_exit);

MODULE_LICENSE("GPL");
