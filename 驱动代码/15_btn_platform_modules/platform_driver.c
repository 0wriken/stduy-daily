
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
#define MAX_Btn 5
struct  key_info
{
    int irq;
    char *name;
    u32 gpio;

};
struct key_info 
[MAX_Btn]
{
    [0]={
        .irq=0,
        .name="wriken-Btn-1",
        gpio=0,
    },
    [1]={
      .irq=0,
        .name="wriken-Btn-2",  
         gpio=0,
    },
    [3]={
      .irq=0,
        .name="wriken-Btn-3",  
         gpio=0,
    },
    [4]={
      .irq=0,
        .name="wriken-Btn-4",  
         gpio=0,
    },
};
int ret;
int i=0;
unsigned long Btn_flag= IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING;

//�����жϺ���
//������˫�ߴ��������º��ɿ���������������
irqreturn_t btns_irq_handler(int irq, void *devid)
{
    int s=0;
    struct key_info *pdata = (struct key_info *)devid;
    //��⵱ǰ�ĵ�ƽ״̬
    s = !gpio_get_value(pdata->gpio);  //�����ǵ͵�ƽ,

    return IRQ_HANDLED;
}
//̽�⺯��
static int led_probe(struct platform_device *pdev)  
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    for(i=0;i<MAX_Btn;i++)
    {
        Btn[i].irq=platfrom_get_irq_byname(pdev,Btn[i].name);
        //�õ��жϱ�Ų������ж�
        ret=  request_irq(Btn[i].irq, btns_irq_handler, Btn_flag, Btn[i].name, NULL);
        if(ret < 0) {
            printk("error request_irq!\r\n");
            return -EFAULT;
        }   
    }
    //��λ�ø���id�µ�data

    
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


//����֧���豸�б�
static  struct platform_device_id devs_table[]={
	{"wriken-Btn-1",0},
	{"wriken-Btn-2",1},
    {"wriken-Btn-3",2},
    {"wriken-Btn-4",3},
};


//ƽ̨�豸�����ṹ
static struct platform_driver led_driver = {
    .probe  = led_probe,    
    .remove = led_remove,  
    .driver = {
        .owner    = THIS_MODULE,
        //.name = "rk3399-leds",
    },
    .id_table = devs_table,
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
    for(i=0;i<MAX_Btn;i++)
    {
      free_irq(Btn[i].irq,NULL);
    }
    platform_driver_unregister(&led_driver);
}

module_init(leddrv_init);
module_exit(leddrv_exit);

MODULE_LICENSE("GPL");
