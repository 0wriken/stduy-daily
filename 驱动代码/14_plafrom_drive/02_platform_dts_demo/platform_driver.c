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
struct resource *res;
//̽�⺯��
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
    
    platform_set_drvdata(pdev,�Զ���ṹ��)
    
    �ṹ��=devm_kmalloc(dev,sizeof,GPL)
    �����ӿڶ������ã��Զ���Ľṹ�� 
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


//��ɾ���豸ʱ������
static int led_remove(struct platform_device *pdev)
{
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__); //������Ϣ
    return 0;
}

#if  0
//����֧���豸�б�
static  struct platform_device_id devs_table[]={
	{"rk3399-leds-1",0},
	{"rk3399-leds-2",1},
};
#endif

//�������豸���ļ��ж����豸�ڵ��γɵ�ƽ̨�豸ƥ��
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

//ƽ̨�豸�����ṹ
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


/*
struct platform_dri
ver led_driver
{
    .probe
    .remove
    .shutdown
    .suspend������
    .resume(����)
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

��Դ��ͻ
struct resource_p platfrom_get_resource(pdev,flag,�ظ�����)
*/