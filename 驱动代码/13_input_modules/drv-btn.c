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
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/input.h>
#define LEDS_MINOR    255

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)		(sizeof(a) / sizeof(a[0]))
#endif

 struct input_dev *pdev;
//ʹ���������˼����ư�������һ��������Ϣ���з�װ
struct key_info{
	int id;                  //�������
	int gpio;                //ͳһ��gpio���
	unsigned long flags	;    //������ʽ
	char *name;              //������
	int  irq;                //�жϱ��	
	struct timer_list timer; //����һ����ʱ��������
	struct tasklet_struct my_tasklet;
	int code;	 //��ϵͳ�ṹ�彨��
};


//ʵ��������
static struct key_info keys[]={
	[0] ={
		.id    = 0,
		.gpio  = 5,
		.flags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
		.name  = "key-0",
		.code=KEY_L,
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
//������б�־λ

//��������,��ģ���ʼ�������н��м���
static int  key_size;

//������������һ��Ԫ�ش��һ������ֵ��'1'��ʾ���£�'0'��ʾ�ɿ� 
//��ģ��ĳ�ʼ�������з��仺�����ռ�

//�����жϺ���
//������˫�ߴ��������º��ɿ���������������
irqreturn_t btns_irq_handler(int irq, void *devid)
{
	int s=0;
	struct key_info *pdata = (struct key_info *)devid;
	//��⵱ǰ�ĵ�ƽ״̬
	s = !gpio_get_value(pdata->gpio);  //�����ǵ͵�ƽ,
	//��ϵͳ�¼��ϱ�
	input_report_key(pdev,pdata->code,s);
	input_sync(pdev);
	return IRQ_HANDLED;
}

static int __init xyd_btn_init(void)
{
	int i,ret;
    printk("gpio is ok\n");
	//���㰴������
	key_size = ARRAY_SIZE(keys);  
	//���䰴��������
	for(i=0; i < key_size; i++)
	{
		//��ϵͳ
		/*����ռ�*/
		pdev=input_allocate_device();
		if(pdev==NULL)
		{
			printk("input_allocate_device fail");
			return -ENOMEM;
		}
		pdev->name="wriken-Btn";
		//��ʼ��
		input_set_capability(pdev,EV_KEY,keys[i].code);
	}
	/*ע����ϵͳ*/
	if(input_register_device(pdev)<0)
	{
		printk("regisetr \n");
		input_free_device(pdev);
		return -EFAULT;
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
		}  
		return 0;

	
error_request_irq:
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //ע���ж�
	}
                       
error_gpio_to_irq:		
	return ret;
}

static void __exit xyd_btn_exit(void)
{
	int i = key_size;     	     
	while(--i >= 0){
		free_irq(keys[i].irq,(void *)&keys[i]);  //ע���ж�
	}	
	input_unregister_device(pdev);
    input_free_device(pdev);                      
}

/*
hexdump 
struct input_event{
	struct timeval time; //ʱ���
	_u16 type;   //�¼�����            
	_u16 code;   //   
	_s32 value;
}

�¼�����㣺ע���ַ��豸+�ļ������������û��㽻��
���Ĳ㣺�������²�
�豸������:ֱ����Ӳ������
 struct input_dev
{
	char *name;
	char *phus;
	char *uniq;
	struct input_id id;
	evbit[];
}
//��̬����
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
�¼��ϱ�����
���㴥���������ϱ�
input_report_Key(pdev,KEY_A,1)
input_report_abs(pdev,ABS_X,x0);
	input_report_Key(pdev,BTN_TOUCH,1)
	input_report_abs(pdev,ABS_Y,y0)
	input_report_abs(pdev,ABS_X,x0);
	input_sync(pdev);
��㴥����
	input_report_Key(pdev,BTN_TOUCH,1)
	input_report_abs(pdev,ABS_MT_POSITION_X,x0)
	input_report_abs(pdev,ABS_MT_POSITION_Y,y0)
	input_sync(pdev);
��㴥����ʹ��
	input_report_Key(pdev,BTN_TOUCH,1)
	input_report_abs(pdev,ABS_MT_POSITION_X,x0)
	input_report_abs(pdev,ABS_MT_POSITION_Y,y0)
	input_mt_sync(pdev)
	input_report_abs(pdev,ABS_MT_POSITION_X,x1)
	input_report_abs(pdev,ABS_MT_POSITION_Y,y1)
	input_sync(pdev);
setABS�¼����¼�ȡֵ��Χ
	input_set_abs_params(pdev,code,min,max,0,0)

*/

module_init(xyd_btn_init);
module_exit(xyd_btn_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYD: fyyy4030@qq.com");
MODULE_DESCRIPTION("XYD RK3399 buttons driver test!");

