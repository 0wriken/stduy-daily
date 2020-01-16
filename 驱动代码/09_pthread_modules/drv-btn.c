//��һ���汾�������ں˶�ʱ������

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/delay.h>
#define LEDS_MINOR    255
#define DEVICE_NAME  "xyd-buttons"

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)		(sizeof(a) / sizeof(a[0]))
#endif
static char *keys_buf;
static int Btn_flag;
//ʹ���������˼����ư�������һ��������Ϣ���з�װ
struct key_info{
	int id;                  //�������
	int gpio;                //ͳһ��gpio���
	unsigned long flags	;    //������ʽ
	char *name;              //������
	int  irq;                //�жϱ��	
	struct timer_list timer; //����һ����ʱ��������
	struct tasklet_struct my_tasklet;
};

//ʵ��������
static struct key_info keys[]={
	[0] ={
		.id    = 0,
		.gpio  = 5,
		.flags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
		.name  = "key-0"
	},			
	//��{0,5,IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,"key-0"}
	[1]=
    {
	    .id=1,
	    .gpio=60,
	    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
	    .name="KEY1",
	    .irq=0
    },
    [2]=
    {
	    .id=2,
	    .gpio=64,
	    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
	    .name="KEY2",
	    .irq=0
    },
    [3]=
    {
	    .id=3,
	    .gpio=65,
	    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
	    .name="KEY3",
	    .irq=0
    },
    [4]=
    {
	    .id=4,
	    .gpio=66,
	    .flags=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
	    .name="KEY4",
	    .irq=0
    },
};
//container_of(ptr,type,member);
void my_task_func(unsigned long data)
{
	printk("%s\n",(char *)data); 
	struct key_info *pdata = (struct key_info *)data;
	mod_timer(&pdata->timer,  jiffies  + msecs_to_jiffies(20));	//������һ�ζ�ʱ,
}
//��ʱ������
void btns_timer(unsigned long data)
{	
	int s; 
	struct key_info *pdata = (struct key_info *)data;
	//��⵱ǰ�ĵ�ƽ״̬
	s = !gpio_get_value(pdata->gpio);  //�����ǵ͵�ƽ,
	keys_buf[pdata->id]= '0' + s;      //����״̬
	Btn_flag=1;
}

//��������,��ģ���ʼ�������н��м���
static int  key_size;

//������������һ��Ԫ�ش��һ������ֵ��'1'��ʾ���£�'0'��ʾ�ɿ� 
//��ģ��ĳ�ʼ�������з��仺�����ռ�

//�����жϺ���
//������˫�ߴ��������º��ɿ���������������
irqreturn_t btns_irq_handler(int irq, void *devid)
{
	struct key_info *pdata = (struct key_info *)devid;
	tasklet_schedule(&pdata->my_tasklet);
	return IRQ_HANDLED;
}

static ssize_t xxxx_read (struct file *pfile, char __user *buf, size_t count, loff_t * off)
{
	int ret = 0;

	// ����û��ռ䴫�������Ĳ����Ƿ�Ϸ�,�Լ����ԶԲ�����������
	if(count > key_size){
		count = key_size;
	}
	if(count == 0) {
		return 0;
	}	

	//׼�����ݣ����ǰ����������ж���ʵʱ���£�����Ҫ�������ȡ

	//�������ݵ��û��ռ�
	if(Btn_flag==1)
	{
		ret = copy_to_user(buf, keys_buf, count);
		if(ret)
		{
			printk("error copy_to_user!");
			ret = -EFAULT;
			goto error_copy_to_user;
		}
		Btn_flag=0;
	}

	return count;
	
error_copy_to_user:
	return ret;
}


static const struct file_operations dev_fops = {
	.read   =   xxxx_read,
	.owner  =   THIS_MODULE,
};

static struct miscdevice xxx_device = {
	.minor = LEDS_MINOR, //���豸��
	.name  = DEVICE_NAME,//�豸��
	.fops  = &dev_fops,  //�ļ���������
};


static int __init xyd_btn_init(void)
{
	int i,ret;
    printk("gpio is ok\n");
	//���㰴������
	key_size = ARRAY_SIZE(keys);  

	//���䰴��������
	keys_buf = kzalloc(key_size, GFP_KERNEL);
	if(keys_buf==NULL){
		return  -EFAULT;
	}	
    //ѭ��ע���ж�	
	for(i=0; i < key_size; i++){
		keys[i].irq = gpio_to_irq(keys[i].gpio);
		if(keys[i].irq < 0){
			printk("error request_irq!\r\n");
			goto error_gpio_to_irq;
		}
		printk("irq:%d\r\n",keys[i].irq);
		
		//����ÿ�������ṹ������ַ�������ж�ʱ����ͨ������ȡ��
		ret=  request_irq(keys[i].irq, btns_irq_handler, keys[i].flags, keys[i].name, (void *)&keys[i]);
		if(ret < 0) {
			printk("error request_irq!\r\n");
			goto error_request_irq;
		}

		//��ʼ�������Ķ�ʱ��,�����ǰ�������Ľṹ�ڴ��ַ
		setup_timer(&keys[i].timer, btns_timer, (unsigned long)&keys[i]);
		
		//��ʼ��΢�߳�
		tasklet_init(&keys[i].my_tasklet,
			my_task_func, (unsigned long)&keys[i]);

	}  

	ret = misc_register(&xxx_device);             //ע�������豸
	if(ret < 0) {
		printk("error misc_register!\r\n");
		goto error_misc_register;
	}

	return 0;

error_misc_register:
error_request_irq:
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //ע���ж�
	}

	kfree(keys_buf);                             //�ͷŰ����������ռ�
error_gpio_to_irq:		
	return ret;
}

static void __exit xyd_btn_exit(void)
{
	int i = key_size;          
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //ע���ж�
		tasklet_kill(&keys[i].my_tasklet);
	}	
	misc_deregister(&xxx_device);                 //ע�������豸

	kfree(keys_buf);                              //�ͷŰ����������ռ�
}

module_init(xyd_btn_init);
module_exit(xyd_btn_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYD: fyyy4030@qq.com");
MODULE_DESCRIPTION("XYD RK3399 buttons driver test!");

