Joker。 17:34:31
#include "hongwai.h"

/*
函数功能：红外的管脚初始化
函数形参：无
返回值：无
备注：PA8浮空输入
日期：2019-09-02
*/
void Infrared_Pin_Init(void)
{
    RCC->AHB1ENR |= (0x1 << 0);
    
    GPIOA->MODER &= ~(0x3 << 16);
    GPIOA->PUPDR &= ~(0X3 << 16);
}


/*
函数功能：TIM2_CH2初始化
函数形参：无
返回值：无
备注：APB1 - 72MHZ
日期：2019-09-02    
*/
void Tim2_Ch2_input_Infrared(void)
{
    Infrared_Pin_Init( );//GPIO初始化
    
    //打开TIM2时钟
    RCC->APB1ENR |= (0x1 << 0);
    
    //选择时钟源
    TIM2->SMCR &= ~(0x7 << 0);//内部时钟源  84M
    
    //配置CR1寄存器
    TIM2->CR1 = 0;
    TIM2->CR1 |= (0x1 << 8);//fdts = fpclk/2 = 18M
    TIM2->CR1 |= (0x1 << 2);//只有计数器上溢才能才生UIF
    /*
    没有影子寄存器
    递增模式
    连续模式
    */
    
    //时钟单元
    TIM2->PSC = 84 - 1;//计一次的时间1us
    TIM2->ARR = 10000 - 1;//产生一次更新事件的周期10ms
    TIM2->EGR |= (0x1 << 0);//产生一次更新事件
    
    //配置捕获通道
    TIM2->CCMR1 &= ~(0x3 << 8);
    TIM2->CCMR1 |= (0x1 << 8);//CC2通道被配置为输入， IC2映射在TI2上
    
    TIM2->CCMR1 |= (0xf << 12);//滤波频率18M/32/8 = 70k
    
    TIM2->CCER &= ~(0x1 << 5);//上升沿触发
    
    TIM2->CCMR1 &= ~(0x3 << 10);//不分频
    
    TIM2->CCER |= (0x1 << 4);//使能捕获
    
    //使能捕获2中断和更新中断
    TIM2->DIER |= (0x1 << 0);//更新中断
    TIM2->DIER |= (0x1 << 2);//捕获2中断
    
    //设置优先级
    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(7-2, 1, 2));
    
    //使能NVIC响应
    NVIC_EnableIRQ(TIM2_IRQn);
    
    TIM2->CR1 |= (0x1 << 0);//使能定时器
}

u8 start_flag;//开始接收标志
u32 key_value;//保存得到的键值
u8 rev_ok;//接收完成标志
//TIM2中断服务函数
void TIM2_IRQHandler(void)
{
    u32 ccr2_value = 0;
    if(TIM2->SR & (0x1 << 2))//捕获2中断标志
    {
        TIM2->SR &= ~(0x1 << 2);//清标志
        while( TIM2->SR & (0x1 << 2) );//等待标志清除完毕
        
        if( GPIOA->IDR & (0x1 << 1) )//上升沿
        {
            TIM2->CNT = 0;//清计数器值
            TIM2->CCER |= (0x1 << 5);//切换为下降沿触发
        }else//下降沿
        {
            ccr2_value = TIM2->CCR2;//读取捕获2寄存器的值
            TIM2->CCER &= ~(0x1 << 5);//上升沿触发
            
            if(ccr2_value > 4400 && ccr2_value < 4600)
            {
                //收到了同步码头
                start_flag = 1;
            }else if(start_flag == 1)
            {
                if(ccr2_value > 460 && ccr2_value < 660)//逻辑0  560us
                {
                    key_value >>= 1;//空出最高位
                }
                else if(ccr2_value > 1580 && ccr2_value < 1780)//逻辑1 1680us
                {
                    key_value >>= 1;//空出最高位
                    key_value |= 0x80000000;
                }
            }
        }
    }
    
    if(TIM2->SR & (0x1 << 0))//更新中断标志
    {
        TIM2->SR &= ~(0x1 << 0);//清标志
        while( TIM2->SR & (0x1 << 0) );//等待标志清除完毕
        
        if(start_flag == 1)
        {
            start_flag = 0;
            rev_ok = 1;//表示接受完成
        }
    }
}



/*
函数功能：处理得到红外遥控器键值
函数形参：无
函数返回值：键值(控制码)
备注：无
2019-09-02
*/
u8 Get_Key_Value_Scan(void)
{
    u8 addr_z = 0, addr_f = 0;
    u8 key_z = 0, key_f = 0;
    
    if(rev_ok == 1)
    {
        rev_ok = 0;
        addr_z = (key_value & (0x000000ff));//得到地址码
        addr_f = (key_value & (0x0000ff00)) >> 8;//得到地址反码
        
        if(addr_z == (u8)(~addr_f))//如果地址码和地址反码相等
        {
            key_z = (key_value & (0x00ff0000)) >> 16;//得到控制码
            key_f = (key_value & (0xff000000)) >> 24;//得到控制反码
            
            if(key_z == (u8)(~key_f))
            {
                return key_z;//将控制码返回出去
            }
        }
    }

    return 0xff;
}


Joker。 17:34:38
#ifndef _HONGWAI_H_
#define _HONGWAI_H_

#include "stm32f4xx.h"

void Tim2_Ch2_input_Infrared(void);
u8 Get_Key_Value_Scan(void);

extern u8 start_flag;//开始接收标志
extern u32 key_value;//保存得到的键值
extern u8 rev_ok;//接收完成标志


#endif

//STM8 CAN通
/*******************************************************************************
* 函数名  : spi_init
* 描述    : SPI总线初始化
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void spi_init()
{
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT);


    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);


    SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_8, SPI_MODE_MASTER, 
        SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, 
        SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00);


    SPI_Cmd(ENABLE);//启用SPI
}
void Spi_send(u8 data)
{

    while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
    SPI_SendData(data);//发送数据

}

u8 Spi_rev()
{
        u8 u8_data;
        while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
        u8_data = SPI_ReceiveData();//接收数据
        return u8_data;
}
#define CS (GPIOA->ODR&(0X1<<3))
void can_reset()
{
    CS=0;
    SPI_SendData(0x0C);
    CS=1;
}
/*******************************************************************************
* 函数名  : can_init
* 描述    : CAN总线初始化
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void can_init()
{
    spi_init();
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);
    delay_ms(200);
    can_reset();
    delay_ms(2);
    Can_write(0X0F,0x84);//初始化模式 1000 0100
    while(Can_read(0x0E)==0x80);//等待进入初始化模式
    //位时间配置
    Can_write(0x2A,0x41);//2SJW 1TQ
    Can_write(0x29,0x9e);//位时间 1001 1110
    Can_write(0x28,0X03);
    delay_ms(2);
    //发送ID配置
    Can_write_id(0x31,0xAF);//如何转换
    Can_write(0x65,8);//数据长度为8个字节
    //接收ID配置
    Can_write_id(0x00,0xaf);
    //清空中断标志
    Can_write(0x2c,0x00);
    delay_ms(2);
    Can_write(0x2B,0x01);//使能接收中断
    delay_ms(2);
    Can_write(0x0f,0x04) ;//进入正常工作模式
    delay_ms(2);
    while(Can_read(0x0E)==0x00);//等待进入正常模式
}

u8 Can_read(u8 addr)
{
    u8 read_data;
    SPI_SendData(0x03);
    SPI_SendData(addr);
    read_data=SPI_ReceiveData();
    return read_data;
}

void Can_write(u8 addr,u8 data)
{
    CS=0;
    SPI_SendData(0x02);
    SPI_SendData(addr);
    SPI_SendData(data);
    CS=1;
}

/*******************************************************************************
* 函数名  : Can_write_id
* 描述    : CAN转化ID到标准寄存器
* 输入    : addr（写入ID的寄存器地址），id(8位id号)
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void Can_write_id(u8 addr，u8 id)
{
    int i=0;
    u8 buf_id[2]={0};
    buf_id[1]=(id&(0X07))<<5;
    buf_id[0]=(id&(0xF8));
   while(*buf_id!=0)
    {
        Can_write(addr+i,*buf_id);
        delay_ms(2);
        data++;
        i++;
    }

}
/*******************************************************************************
* 函数名  : CAN_send_buf
* 描述    : CAN发送指定长度的数据
* 输入    : *buf(待发送数据缓冲区指针),len(待发送数据长度)
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void CAN_send_buf(u8 * buf,u8 len)
{
    while(Can_read(0x30)&0x08);//缓冲区空
    for(int i=0;i<len;i++)
    {
        Can_write(0x36+i,*buf);
        buf++;
    }
    Can_write(0x35,len);//写入数据长度
    delay_ms(2);
    CS=0;
    Can_write(0x30,0x08);//请求写入数据
    CS=1;
    delay_ms(2);
    //???????
    CAN_TX_Buf[0] ^= CAN_TX_Buf[1];
    CAN_TX_Buf[1] ^= CAN_TX_Buf[0];
    CAN_TX_Buf[0] ^= CAN_TX_Buf[1];


}
/*******************************************************************************
* 函数名  : CAN_receive_buf
* 描述    : CAN接收一帧数据
* 输入    : *buf(待接收数据缓冲区指针)
* 输出    : 无
* 返回值  : len(接收到数据的长度,0~8字节)
* 说明    : 无
*******************************************************************************/
u8 CAN_receive_buf(u8 *buf) //中断服务函数中
{
    int i=0;
    if(!Can_read(0x2c)&0x01)//有报文数据时候
    {
        int len=Can_read(0x65);//读取数据长度
        while(len--)
        {
            *buf=Can_read(0x66+i);
            i++;
            buf++;
        }
        Can_write(0x2c,0x00);//清除标志位
    }
    return len;
}












