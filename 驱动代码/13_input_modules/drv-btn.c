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
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/input.h>
#define LEDS_MINOR    255

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)		(sizeof(a) / sizeof(a[0]))
#endif

 struct input_dev *pdev;
//使用面向对象思想设计按键，把一个按键信息进行封装
struct key_info{
	int id;                  //按键编号
	int gpio;                //统一的gpio编号
	unsigned long flags	;    //触发方式
	char *name;              //按键名
	int  irq;                //中断编号	
	struct timer_list timer; //增加一个定时器作消抖
	struct tasklet_struct my_tasklet;
	int code;	 //子系统结构体建码
};


//实例化对象
static struct key_info keys[]={
	[0] ={
		.id    = 0,
		.gpio  = 5,
		.flags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
		.name  = "key-0",
		.code=KEY_L,
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
//定义队列标志位

//按键数量,在模块初始化函数中进行计算
static int  key_size;

//按键缓冲区，一个元素存放一个按键值，'1'表示按下，'0'表示松开 
//在模块的初始化函数中分配缓冲区空间

//按键中断函数
//设置了双边触发，按下和松开都会进入这个函数
irqreturn_t btns_irq_handler(int irq, void *devid)
{
	int s=0;
	struct key_info *pdata = (struct key_info *)devid;
	//检测当前的电平状态
	s = !gpio_get_value(pdata->gpio);  //按下是低电平,
	//子系统事件上报
	input_report_key(pdev,pdata->code,s);
	input_sync(pdev);
	return IRQ_HANDLED;
}

static int __init xyd_btn_init(void)
{
	int i,ret;
    printk("gpio is ok\n");
	//计算按键数量
	key_size = ARRAY_SIZE(keys);  
	//分配按键缓冲区
	for(i=0; i < key_size; i++)
	{
		//子系统
		/*分配空间*/
		pdev=input_allocate_device();
		if(pdev==NULL)
		{
			printk("input_allocate_device fail");
			return -ENOMEM;
		}
		pdev->name="wriken-Btn";
		//初始化
		input_set_capability(pdev,EV_KEY,keys[i].code);
	}
	/*注册子系统*/
	if(input_register_device(pdev)<0)
	{
		printk("regisetr \n");
		input_free_device(pdev);
		return -EFAULT;
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
		}  
		return 0;

	
error_request_irq:
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //注销中断
	}
                       
error_gpio_to_irq:		
	return ret;
}

static void __exit xyd_btn_exit(void)
{
	int i = key_size;     	     
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //注销中断
	}	
	input_unregister_device(pdev);
    input_free_device(pdev);                      
}

/*
hexdump 
struct input_event{
	struct timeval time; //时间戳
	_u16 type;   //事件类型            
	_u16 code;   //   
	_s32 value;
}

事件处理层：注册字符设备+文件操作方法，用户层交互
核心层：交互上下层
设备驱动层:直接与硬件交互
 struct input_dev
{
	char *name;
	char *phus;
	char *uniq;
	struct input_id id;
	evbit[];
}
//动态分配
struct input_dev *pdev=input_allocate_device(void)
void input_free

int input_register_device()

void input_unregister_device()

//set bit
1.set_bit(EV_KEY,pdev->evbit)
  set_bit(KEY_A,pdev->keybit)
  set_bit(KEY_ENETR,pdev->keybit)
2.input_set_cacpability()
  input_set_cacpability(pdev,EV_KEY,KEY_A)
  input_set_cacpability(pdev,EV_KEY,KEY_ENTER)
事件上报函数
单点触摸屏数据上报
input_report_Key(pdev,KEY_A,1)
input_report_abs(pdev,ABS_X,x0);
	input_report_Key(pdev,BTN_TOUCH,1)
	input_report_abs(pdev,ABS_Y,y0)
	input_report_abs(pdev,ABS_X,x0);
	input_sync(pdev);
多点触摸：
	input_report_Key(pdev,BTN_TOUCH,1)
	input_report_abs(pdev,ABS_MT_POSITION_X,x0)
	input_report_abs(pdev,ABS_MT_POSITION_Y,y0)
	input_sync(pdev);
多点触碰中使用
	input_report_Key(pdev,BTN_TOUCH,1)
	input_report_abs(pdev,ABS_MT_POSITION_X,x0)
	input_report_abs(pdev,ABS_MT_POSITION_Y,y0)
	input_mt_sync(pdev)
	input_report_abs(pdev,ABS_MT_POSITION_X,x1)
	input_report_abs(pdev,ABS_MT_POSITION_Y,y1)
	input_sync(pdev);
setABS事件子事件取值范围
	input_set_abs_params(pdev,code,min,max,0,0)

*/

module_init(xyd_btn_init);
module_exit(xyd_btn_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYD: fyyy4030@qq.com");
MODULE_DESCRIPTION("XYD RK3399 buttons driver test!");

