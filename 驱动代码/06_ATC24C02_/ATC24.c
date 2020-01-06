#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#define CRU_BASE 0XFF750000
/*时钟有误！！**/
#define CRU_T_BASE 0XFF760000
#define CRU_T_SIZE 0XFFFF
#define GPIO1_BASE 0XFF730000
#define GPIO0_BASE 0XFF720000

#define GPIO4_BASE  0XFF790000
#define GPIO4_SIZE 0XFFFF

#define PMUGRF_SIZE 0XFFFF
#define PMUGRF_BASE 0XFF320000

#define GRF4_SIZE 0XFFFF
#define GRF4_BASE 0XFF770000

#define GPIO0_SIZE 0XFFFF
#define GPIO1_SIZE 0XFFFF

#define CRU_SIZE 0XFFFF
#define LED_SIZE 5
//ÐéÄâÓ³Éä
void *va_base =NULL;
void *gpio0_base=NULL;
void *gpio1_base=NULL;
void *gpio4_base=NULL;
void  *pmugrf_base=NULL;
void  *pmugrf4_base=NULL;
void  *cru_base=NULL;

#define CRU_CLACK_COM1 *(volatile unsigned int *)(va_base+0x0104)
#define CRU_T_CLACK_COM31 *(volatile unsigned int *)(cru_base+0x037c)


#define GPIO1_DDR  *(volatile unsigned int *)(gpio1_base+0x0004) 
#define GPIO1_EXT  *(volatile unsigned int *)(gpio1_base+0x0050) 
#define GPIO1_DR  *(volatile unsigned int *)(gpio1_base+0x0000) 
#define GPIO1_PU_PD  *(volatile unsigned int *)(pmugrf_base+0x0058)

#define GPIO4_DDR  *(volatile unsigned int *)(gpio4_base+0x0004) 
#define GPIO4_EXT  *(volatile unsigned int *)(gpio4_base+0x0050) 
#define GPIO4_DR  *(volatile unsigned int *)(gpio4_base+0x0000) 
#define GPIO4_PU_PD  *(volatile unsigned int *)(pmugrf4_base+0xE068)



#define AT24C02ADDR    0x50//01010000
#define AT24C02ADDR_W  0xA0//10100000
#define AT24C02ADDR_R  0xA1//10100001


#define WRITE_ERR1 1
#define WRITE_ERR2 2
#define WRITE_ERR3 3
#define WRITE_ERR4 4
#define WRITE_ERR5 5
#define WRITE_ERR6 6
#define WRITE_ERR7 7
#define WRITE_ERR8 8

#define READ_ERR1 11
#define READ_ERR2 22
#define READ_ERR3 33
#define READ_ERR4 44
#define READ_ERR5 55

#define NOTSAMEPAGE 66


#define LED_ON_ALL _IO('L',0)
#define LED_OFF_ALL _IO('L',1)
#define LED_ON_X   _IOW('L',2,int)
#define LED_OFF_X   _IOW('L',3,int)
//ÒÔÏÂÊÇÎÄŒþ²Ù×÷·œ·šµÄŸßÌåÊµÏÖŽúÂë
static int xxx_open(struct inode *pinode, struct file *pfile )
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
//读取引脚电平


static int xxx_release (struct inode *pinode, struct file *pfile)
{
    printk("line:%d, %s is call\n", __LINE__, __FUNCTION__);
    return 0;
}
/*  IOCTL*/
static long xxx_unlocked_ioctl (struct file *pfile,unsigned int cmd, unsigned long args)
{
    printk("nothing in here\n");
    return 0;
}

/*
GPIO1 C6 SDA
GPIO1 C7 SCL
GPIO4 C0 SDA
GPIO4 C1 SCL
*/
static u8 iic_SDA_in(void)
{

    //输入上拉
    GPIO1_PU_PD|=(0x3<<28);
    /*配置上下拉*/
    GPIO4_PU_PD|=(0x3<<16);
    GPIO4_PU_PD|=(0X2<<0);
    //GPIO1_PU_PD|=(0x2<<12);
    GPIO1_PU_PD|=(0x1<<12);

    GPIO1_DDR&=~(0x1<<22);
    GPIO4_DDR&=~(0x1<<16);

    return  !!(GPIO4_EXT&(0x1<<16));
    //return  !!(GPIO1_EXT&(0x1<<22));
}
static void IIC_SCL(int i)
{
    GPIO1_DDR|=(0x1<<23);
    GPIO4_DDR|=(0X1<<17);
    if(i)
    {
        GPIO1_DR|=(0X1<<23);
        GPIO4_DR|=(0X1<<17);
    }
    else
    {
        GPIO1_DR&=~(0x1<<23);
        GPIO4_DR&=~(0X1<<17);
    }
}
static void IIC_SDA_OUT(int i)
{
    GPIO1_DDR|=(0x1<<22);
    GPIO4_DDR|=(0x1<<16);
    if(i)
    {
        GPIO1_DR|=(0X1<<22);
        GPIO4_DR|=(0X1<<16);
    }
    else
    {
        GPIO1_DR&=~(0x1<<22);
        GPIO4_DR&=~(0X1<<16);
    }
}

/*初始化时钟
SDA PC6
SCL PC7
*/
static void IICStart(void)
{
    IIC_SCL(1);
    IIC_SDA_OUT(1);
    udelay(2);//延时--起始条件建立时间
    IIC_SDA_OUT(0);
    udelay(1);//延时--起始条件保持时间
    IIC_SCL(0); //---一个完整的周期
    printk("IIC_START\n");
}
/*
停止条件
*/
static void IICStop(void)
{
    IIC_SCL(0);
    IIC_SDA_OUT(0);
    IIC_SCL(1);
    udelay(1);//延时--停止条件的建立时间
    IIC_SDA_OUT(1);
    udelay(2);//延时--本次停止到下一开始的时间
}

/*
函数功能：主机发送应答信号
参数说明：待发送的应答信号 0有应答 1非应答
*/
static void IICSendAck(u8 ack)
{
    IIC_SCL(0);
    if(ack)//主机准备数据
        IIC_SDA_OUT(0);
    else
        IIC_SDA_OUT(0);
    udelay(2);//延时（数据稳定在数据线上）
    IIC_SCL(1);//（从机在时钟线上升沿从SDA上采集数据）
    udelay(1);//延时（给时间从机读取数据）
}
 

/*
函数功能：主机读取从机的应答信号
返回值：读取到的应答信号  0有应答  1非应答
*/
static u8 IICReadAck(void)
{
    u8 ack=0;
    IIC_SCL(0);//（从机准备数据）
    IIC_SDA_OUT(1);//读模式，为了是IO口的输出电路给引脚断开！！！！！！！！！
    udelay(2);//延时（给时间从机准备数据并且数据稳定在数据线上）
    IIC_SCL(1);
    udelay(1);//延时 (给时间主机读取数据)
    if(iic_SDA_in())//主机读取SDA线上的数据
        ack=1;
    
    IIC_SCL(0);//为了方便后续操作，防止意外出现停止条件
    
    return ack;
}


/*
函数功能：主机给从机发送一个字节数据并且读取从机应答
参数说明：待发送的一个字节数据
返回值：应答信号
*/
static u8 IICSendByte(u8 data) 
{
    u8 i;
    
    for(i=0;i<8;i++)
    {
        IIC_SCL(0);
        if((data<<i)&0x80)//主机准备数据
            IIC_SDA_OUT(1);
        else
            IIC_SDA_OUT(0);
        udelay(2);//延时（数据稳定在数据线上）
        IIC_SCL(1);//（从机在时钟线上升沿从SDA上采集数据）
        udelay(1);//延时（给时间从机读取数据）
    }
    IIC_SCL(0);//为了方便后续操作，防止意外出现停止条件
    
    return IICReadAck( );
}

/*
函数功能：主机读取从机一个字节数据并且发送应答信号
参数说明：待发送的应答信号
返回值：读取到的一个字节数据
*/
static u8 IICReadByte(u8 ack) 
{
    u8 i;
    u8 data=0;
    
    for(i=0;i<8;i++)
    {
        IIC_SCL(0);//（从机准备数据）
        IIC_SDA_OUT(1);//读模式，为了是IO口的输出电路给引脚断开！！！！！！！！！
        udelay(2);//延时（给时间从iic_SDA_in机准备数据并且数据稳定在数据线上）
        IIC_SCL(1);
        udelay(1);//延时 (给时间主机读取数据)
        data<<=1;//空出最低位
        if(iic_SDA_in())//主机读取SDA线上的数据
            data |=1;
    }
    printk("iic receive is %d\n",data);
    IIC_SCL(0);//为了方便后续操作，防止意外出现停止条件
    
    IICSendAck(ack);
    
    return data;
}



/*
函数功能：字节写
参数说明：addr待写入的地址  data待写入的数据
返回值：0写入成功  其他：错误码
*/
/*static u8 At24c02WriteByte(u8 addr,u8 data)
{
    IICStart( );//起始条件
    
    
    if( IICSendByte(AT24C02ADDR_W) )//发送器件地址+写方向
    {
        IICStop( );
        return WRITE_ERR1;
    }
    
    if( IICSendByte(addr) )//发送内部地址
    {
        IICStop( );
        return WRITE_ERR2;
    }
    
    if( IICSendByte(data) )//发送数据
    {
        IICStop( );
        return WRITE_ERR3;
    }
    
    IICStop( );//停止条件
    
    
    mdelay(5);//写周期
    
    return 0;
}
*/

/*
函数功能：页写
参数说明：addr待写入的地址  num待写入的数据个数   p待指向待写入的数据换从前
返回值：0写入成功  其他：错误码
注意事项：起始地址和结束地址要在一样
*/
static u8 At24c02PageWrite(u8 addr,u8 num,u8* p)
{
    //起始写入地址：addr         所在页：addr/8
    //结束写入地址：addr+num-1   所在页：（addr+num-1）/8
    
    if( addr/8 != (addr+num-1)/16 )
            return NOTSAMEPAGE;
    
    IICStart( );//起始条件
    
    
    if( IICSendByte(AT24C02ADDR_W) )//发送器件地址+写方向
    {
        IICStop( );
        return WRITE_ERR4;
    }
    
    if( IICSendByte(addr) )//发送内部地址
    {
        IICStop( );
        return WRITE_ERR5;
    }
    
    while(num--)
    {
        if( IICSendByte(*p++) )//发送数据
        {
            IICStop( );
            return WRITE_ERR6;
        }
    }
    
    
    IICStop( );//停止条件
    
    
    mdelay(5);//写周期
    
    return 0;
}


/*
函数功能：随机写
参数说明：addr内部地址   num待写入的数据个数1~256  p指向数据缓冲区
返回值：0写入成功  其他：错误码
*/
//u8 At24c02WriteBytes(u8 addr,u16 num,u8* p)
//{
//  u8 ret=0;
//      u8 less_addr=0;//当前页还剩多少个字节空间
//  
//  while(1)
//  {
//      less_addr=8-addr%8;
//      if(less_addr>=num){//当前页能全部写完
//          ret=At24c02PageWrite(addr,num,p);
//          return ret;
//      }
//      else{//当前页写不完num个，先写完当前页less_addr个
//          ret=At24c02PageWrite(addr,less_addr,p);
//          if(ret)//写入失败
//              return ret;
//      }
//      
//      addr=addr+less_addr;
//      num=num-less_addr;
//      p=p+less_addr;
//  }
//  
//}
static u8 At24c02WriteBytes(u8 addr,u16 num,u8* p)
{
    u8 ret=0;
        u8 less_addr=0;//当前页还剩多少个字节空间
    
    while(1)
    {
        less_addr=16-addr%8;
        if(less_addr>=num){//当前页能全部写完
            less_addr=num;
        }
        ret=At24c02PageWrite(addr,less_addr,p);
        if(ret)//写入失败
            return ret;
        
        if(less_addr==num)
            return 0;
        
        
        addr=addr+less_addr;
        num=num-less_addr;
        p=p+less_addr;
    }
}

/*
函数功能：随机读
参数说明：addr内部地址   num待读取的数据个数1~256  p指向接收数据缓冲区
返回值：0读取成功  其他：错误码
*/
static u8 At24c02ReadBytes(u8 addr,u16 num,u8* p)
{
    
    IICStart( );//起始条件
    
    printk("iic_in :%d\n",iic_SDA_in());
    if( IICSendByte(AT24C02ADDR_W) )//发送器件地址+写方向
    {
        IICStop( );
        printk("write addr is error\n");
        return WRITE_ERR1;
    }
    
    if( IICSendByte(addr) )//发送内部地址
    {
        IICStop( );
        printk("send addr is error\n");
        return WRITE_ERR2;
    }
    
    IICStart( );//重复起始条件
    
    if( IICSendByte(AT24C02ADDR_R) )//发送器件地址+读方向
    {
        IICStop( );
        printk("send_write is error\n");
        return WRITE_ERR3;
    }
    
    //连续读取
    while(num) 
    {
        num--;//读完这次还剩多少个数据
        if(0==num)
        {
            *p= IICReadByte(1) ;
            break;
        }
            
        *p++= IICReadByte(0) ;
    }
    
    IICStop( );//停止条件
    
    return 0;
}
static ssize_t xxx_read(struct file *pfile,char __user *buf, size_t count, loff_t *poff)
{

    char *kdata=kzalloc(count+1,GFP_KERNEL);
    loff_t cur_fpos=pfile->f_pos;
    printk("addr is %lld\n",cur_fpos);
    At24c02ReadBytes((u8 )cur_fpos,count,kdata);

    if(copy_to_user((char *)buf,kdata,count))
    {
        printk("error copy_to_user\n");
        kfree(kdata);
        return -EFAULT;
    }
    pfile->f_pos+=count;
    kfree(kdata);
    return count;

}
static ssize_t xxx_write(struct file *pfile, const char __user *buf, size_t count, loff_t *poff)
{
        char *kbuf=NULL;
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
    kbuf=kzalloc(count+1,GFP_KERNEL);
    if(copy_from_user(kbuf,buf,count))
    {
        printk("file write is error\n");
        goto error1;
    }
    At24c02WriteBytes((u8 )cur_fpos,count,(u8*) kbuf);
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
    if((tmp<0)|| tmp>256)
    {
        printk("llseek error \n");
        return -EINVAL;
    }
    pfile->f_pos=tmp;
    return off;
}

static void gpio1_init(void)
{
    CRU_CLACK_COM1|=(0X1<<20);
    CRU_CLACK_COM1&=~(0x1<<4);
    CRU_T_CLACK_COM31|=(0X1<<21);
    CRU_T_CLACK_COM31&=~(0X1<<5);

    GPIO1_DDR|=(0X1<<1);
    GPIO1_DDR|=(0X1<<3);
    GPIO1_DDR|=(0X1<<4);
    GPIO1_DDR|=(0X1<<18);
    GPIO1_DDR|=(0X1<<22);
    GPIO1_DDR|=(0X1<<23);
     
    GPIO4_DDR|=(0x3<<16);
     

    printk("atc  is ok\n");
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

#define  DEV_NAME    "atc24_misc"
//¶šÒåºËÐÄœá¹¹ 
static struct miscdevice  misc = {
    .minor = 255,
    .name  = DEV_NAME,     //devÄ¿ÂŒÏÂµÄÉè±žÃû
    .fops  = &xxx_fops,
};

static int __init my_misdevice_init(void)
{
    int ret;
    gpio1_base=ioremap_nocache(GPIO1_BASE,GPIO1_SIZE);
    gpio4_base=ioremap_nocache(GPIO4_BASE,GPIO4_SIZE);
    va_base= ioremap_nocache(CRU_BASE,CRU_SIZE);
    cru_base= ioremap_nocache(CRU_T_BASE,CRU_T_SIZE);
    if(va_base==NULL)
    {
        goto error_base0;
        ret=-EFAULT;
    }
    pmugrf_base=ioremap_nocache(PMUGRF_BASE,PMUGRF_SIZE);
    pmugrf4_base=ioremap_nocache(GRF4_BASE,GRF4_SIZE);
    gpio0_base= ioremap_nocache(GPIO0_BASE,GPIO0_SIZE);
    if(gpio0_base==NULL)
    {
        goto error_base1;
        ret=-EFAULT;
    }
    CRU_CLACK_COM1|=(0X1<<19);
    CRU_CLACK_COM1&=~(0X1<<3);
    gpio1_init();
    while(1)
    {
        mdelay(1000);
        GPIO4_DR&=~(0X3<<16);
    }
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
    
    misc_deregister(&misc);
    
    //灭灯并恢复默认输入
    iounmap(gpio0_base);
    iounmap(va_base);
    printk("misc_deregister ok\n");
}

module_init(my_misdevice_init);
module_exit(my_misdevice_exit);
MODULE_LICENSE("GPL");

