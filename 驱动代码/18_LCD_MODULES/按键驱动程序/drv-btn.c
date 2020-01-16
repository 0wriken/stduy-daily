//这一个版本增加了内核定时器功能

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
//使用面向对象思想设计按键，把一个按键信息进行封装
struct key_info{
	int id;                  //按键编号
	int gpio;                //统一的gpio编号
	unsigned long flags	;    //触发方式
	char *name;              //按键名
	int  irq;                //中断编号	
	struct timer_list timer; //增加一个定时器作消抖
	struct tasklet_struct my_tasklet;
};

//实例化对象
static struct key_info keys[]={
	[0] ={
		.id    = 0,
		.gpio  = 5,
		.flags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
		.name  = "key-0"
	},			
	//或：{0,5,IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,"key-0"}
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
	mod_timer(&pdata->timer,  jiffies  + msecs_to_jiffies(20));	//启动新一次定时,
}
//超时处理函数
void btns_timer(unsigned long data)
{	
	int s; 
	struct key_info *pdata = (struct key_info *)data;
	//检测当前的电平状态
	s = !gpio_get_value(pdata->gpio);  //按下是低电平,
	keys_buf[pdata->id]= '0' + s;      //保存状态
	Btn_flag=1;
}

//按键数量,在模块初始化函数中进行计算
static int  key_size;

//按键缓冲区，一个元素存放一个按键值，'1'表示按下，'0'表示松开 
//在模块的初始化函数中分配缓冲区空间

//按键中断函数
//设置了双边触发，按下和松开都会进入这个函数
irqreturn_t btns_irq_handler(int irq, void *devid)
{
	struct key_info *pdata = (struct key_info *)devid;
	tasklet_schedule(&pdata->my_tasklet);
	return IRQ_HANDLED;
}

static ssize_t xxxx_read (struct file *pfile, char __user *buf, size_t count, loff_t * off)
{
	int ret = 0;

	// 检测用户空间传递下来的参数是否合法,以及尝试对参数进行修正
	if(count > key_size){
		count = key_size;
	}
	if(count == 0) {
		return 0;
	}	

	//准备数据，但是按键数据在中断中实时更新，不需要在这里读取

	//复制数据到用户空间
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
	.minor = LEDS_MINOR, //次设备号
	.name  = DEVICE_NAME,//设备名
	.fops  = &dev_fops,  //文件操作方法
};


static int __init xyd_btn_init(void)
{
	int i,ret;
    printk("gpio is ok\n");
	//计算按键数量
	key_size = ARRAY_SIZE(keys);  

	//分配按键缓冲区
	keys_buf = kzalloc(key_size, GFP_KERNEL);
	if(keys_buf==NULL){
		return  -EFAULT;
	}	
    //循环注册中断	
	for(i=0; i < key_size; i++){
		keys[i].irq = gpio_to_irq(keys[i].gpio);
		if(keys[i].irq < 0){
			printk("error request_irq!\r\n");
			goto error_gpio_to_irq;
		}
		printk("irq:%d\r\n",keys[i].irq);
		
		//传递每个按键结构变量地址，发生中断时可以通过参数取得
		ret=  request_irq(keys[i].irq, btns_irq_handler, keys[i].flags, keys[i].name, (void *)&keys[i]);
		if(ret < 0) {
			printk("error request_irq!\r\n");
			goto error_request_irq;
		}

		//初始化按键的定时器,参数是按键自身的结构内存地址
		setup_timer(&keys[i].timer, btns_timer, (unsigned long)&keys[i]);
		
		//初始化微线程
		tasklet_init(&keys[i].my_tasklet,
			my_task_func, (unsigned long)&keys[i]);

	}  

	ret = misc_register(&xxx_device);             //注册杂项设备
	if(ret < 0) {
		printk("error misc_register!\r\n");
		goto error_misc_register;
	}

	return 0;

error_misc_register:
error_request_irq:
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //注销中断
	}

	kfree(keys_buf);                             //释放按键缓冲区空间
error_gpio_to_irq:		
	return ret;
}

static void __exit xyd_btn_exit(void)
{
	int i = key_size;          
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //注销中断
		tasklet_kill(&keys[i].my_tasklet);
	}	
	misc_deregister(&xxx_device);                 //注销杂项设备

	kfree(keys_buf);                              //释放按键缓冲区空间
}

module_init(xyd_btn_init);
module_exit(xyd_btn_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYD: fyyy4030@qq.com");
MODULE_DESCRIPTION("XYD RK3399 buttons driver test!");

