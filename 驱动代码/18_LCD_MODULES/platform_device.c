
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
 
struct pin_info
{
   int gpio;
   int value;
   char dri;
}; 

static struct pin_info pin_gpio={13,1,'O'};



static void led_release(struct device * dev)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    printk(KERN_EMERG"%s\r\n%d,%s is call\r\n", __FILE__, __LINE__, __FUNCTION__);
}


static struct platform_device led_dev = {
    .name = "rk3399-leds",
    .id   = -1,
    .dev = {
        .release = led_release,
        .platform_data=(void *)&pin_gpio,
    },
};


static int leddev_init(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_device_register(&led_dev);
    return 0;
}

static void leddev_exit(void)
{
    printk(KERN_EMERG"%s is call\r\n", __FUNCTION__);
    platform_device_unregister(&led_dev);
}

module_init(leddev_init);
module_exit(leddev_exit);

MODULE_LICENSE("GPL");

/*
ӳ��: void* mmap(void*addr,size_t lenth,int port,
    int flag,int fd,offset_set offset)
    port->�ļ�����Ȩ��
    flag-> MAP_SHARED����ӳ�� MAP_PRIVATE˽��ӳ��

    munmap(void *addr,size_t lenth)

    ��x,y��=fd_base+y*len+x*bpp/8;
LCD����ʾJPEG
    ��ֲJPEG�����  ��linux�½�ѹ ����./config --help
    ϵͳ���� --prefix=���·�� --bulid=BUILD ������Ĭ�ϲ������� --host=HOST Ŀ������������
    --targetĬ��������һ��   -enable-share -enable-static
    �������ã�CC ����������  CFLAGS ָ�������־�������Ŀ��Ż��ȵ�
            LDFLAGS -L��·��  LIBS -l���� ָ�������"-l -l" 
            CPPFLAGS -Iͷ�ļ�·��
            CPP ָ��Ԥ������ gcc -E   
            alisa sudo ="sudo env PATH=$PATH"

libjepgͼƬ���� 
ѹ����rgb -> jepg








*/

