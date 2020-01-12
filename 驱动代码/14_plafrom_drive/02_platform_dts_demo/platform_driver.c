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
struct resource *res;
//探测函数
static int led_probe(struct platform_device *pdev)  
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"pdev->name:%s\r\n", pdev->name);
    /* 
    res=platfrom_get_resource(pdev,IORESOURCE_MEM,0);
    if(res==NULL)
    {
        printk("get resource\n");
        return -EFAULT;
    }
    platfrom_get_irq(pdev,0);
    platfrom_get_resource_byname(pdev,IORESOURCE_MEM,"");
    platfrom_get_irq_byname(pdev,"name");
    
    platform_set_drvdata(pdev,自定义结构体)
    
    结构体=devm_kmalloc(dev,sizeof,GPL)
    其他接口都可以用：自定义的结构体 
        platform_get_drvdata(pdev)
    devm_ioremap_nocache(statr,end,end-start+1);


    */


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

#if  0
//驱动支持设备列表
static  struct platform_device_id devs_table[]={
	{"rk3399-leds-1",0},
	{"rk3399-leds-2",1},
};
#endif

//用来和设备树文件中定义设备节点形成的平台设备匹配
static const struct of_device_id of_devs_table[]={
	[0]={
		.compatible = "xyd-rk3399-leds",  
		.data       = (void*)1,
	},
	
	[1]={
		.compatible = "haha-rk3399-leds",  
		.data       = (void*)2,
	},

};

//平台设备驱动结构
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
    platform_driver_unregister(&led_driver);
}

module_init(leddrv_init);
module_exit(leddrv_exit);

MODULE_LICENSE("GPL");


/*
struct platform_dri
ver led_driver
{
    .probe
    .remove
    .shutdown
    .suspend（挂起）
    .resume(唤醒)
    struct device_driver
    {
        .name
    }
    of_match_table
    {
        .compatible
    }
    id_table
}

资源冲突
struct resource_p platfrom_get_resource(pdev,flag,重复个数)
*/