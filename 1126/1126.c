STM32模块：主界面 触摸屏 
STM8模块 ：窗帘 光照   led  温湿度 
			有毒气体 雨水 震动

起始主界面: 智能家局系统+组员  OK按键
	界面：温度：   湿度：
		  光照：   震动：
		  雨水：   空气质量：

	控制区域： 窗帘  ON/OFF
				灯光
3个优先级： 
			用户界面
			检测CAN+发送CAN
			检测到的CAN控制显示 
//CAN通信：
u8 can1_tx_msg(u32 id,u8 ide,u8 rtr,u8 len, u8 *p_dat)
{	   
	u8 mbox;
	
	if (CAN1->TSR & (1<<26))
	{
		mbox=0;			//邮箱0为空
	}
	else if (CAN1->TSR & (1<<27))
	{
		mbox=1;			//邮箱1为空
	}
	else if (CAN1->TSR & (1<<28))
	{
		mbox=2;			//邮箱2为空
	}
	else 
	{
		return 0XFF;	//无空邮箱,无法发送 
	}
	
	CAN1->sTxMailBox[mbox].TIR = 0;		//清除之前的设置
	if (ide == 0)	//标准帧
	{
		id &= 0x7ff;//取低11位stdid
		id <<= 21;		  
	}
	else		//扩展帧
	{
		id &= 0X1FFFFFFF;//取低32位extid
		id <<= 3;									   
	}
	CAN1->sTxMailBox[mbox].TIR |= id;		 
	CAN1->sTxMailBox[mbox].TIR |= ide << 2;	  
	CAN1->sTxMailBox[mbox].TIR |= rtr << 1;
	
	len &= 0X0F;//得到低四位
	CAN1->sTxMailBox[mbox].TDTR &= ~(0XF);
	CAN1->sTxMailBox[mbox].TDTR |= len;	   //设置DLC.
		
	CAN1->sTxMailBox[mbox].TDLR = 0;
	CAN1->sTxMailBox[mbox].TDHR = 0;
	//待发送数据存入邮箱.
    switch(len)
    {
        case 8:CAN1->sTxMailBox[mbox].TDHR |= (p_dat[7] << 24);
        case 7:CAN1->sTxMailBox[mbox].TDHR |= (p_dat[6] << 16);
        case 6:CAN1->sTxMailBox[mbox].TDHR |= (p_dat[5] <<  8);
        case 5:CAN1->sTxMailBox[mbox].TDHR |= (p_dat[4] <<  0);
        case 4:CAN1->sTxMailBox[mbox].TDLR |= (p_dat[3] << 24);
        case 3:CAN1->sTxMailBox[mbox].TDLR |= (p_dat[2] << 16);
        case 2:CAN1->sTxMailBox[mbox].TDLR |= (p_dat[1] <<  8);
        case 1:CAN1->sTxMailBox[mbox].TDLR |= (p_dat[0] <<  0);break;
        default: break;
    }
    
	CAN1->sTxMailBox[mbox].TIR |= 1; //请求发送邮箱数据  TXRQ
	
	return mbox;
}
u8 can1_send_msg( u32 id,u8* msg, u8 len)
{	
	u8 mbox;
	u16 i=0;	 
	
    mbox = can1_tx_msg(id,0,0,len,msg);
	
	while ((can1_tx_status(mbox) != 0X07))//等待发送结束
	{
		if(++i >= 0XFFF)
		{
			return 1;//发送失败?
		}
	}
	return 0;	//发送成功;
}
u8 can1_receive_msg(u8 *buf,u8 *id)
{		   		   
	u32 id;
	u8 ide,rtr = 0,len=0; 
	
	if(can1_fifo_status(0) == 0)
	{
		return 0;	//没有接收到数据,直接退出 	 
	}
  	can1_rx_msg(&id,&ide,&rtr,&len,buf, 0); 	//读取数据

    if (rtr == 1)
    {
        len = 1;
    }
	return len;	
}


unsigned char CAN_Receive_Buffer(unsigned char *CAN_RX_Buf)
{
	unsigned char i=0,len=0,temp=0;

	temp = MCP2515_ReadByte(CANINTF);
	if(temp & 0x01)
	{
		len=MCP2515_ReadByte(RXB0DLC);//读取接收缓冲器0接收到的数据长度(0~8个字节)
		while(i<len)
		{	
			CAN_RX_Buf[i]=MCP2515_ReadByte(RXB0D0+i);//把CAN接收到的数据放入指定缓冲区
			i++;
		}
	}
	MCP2515_WriteByte(CANINTF,0);//清除中断标志位(中断标志寄存器必须由MCU清零)
	return len;
}
/*******************************************************************************
**功能描述：定时器4参数初始化
**入口参数：无
**输出：无
*******************************************************************************/
void Timer4Init()
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_16, 1000);
  TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);        // 禁止中断
TIM4_UpdateDisableConfig(ENABLE);      // 允许产生更新事件
TIM4_SetCounter(0x00);              // 设定计数器的初值
}
/*******************************************************************************
**函数名称：void TIM4Delayms(unsigned int ms)
**功能描述：定时器4参进行精确延时，最小为1毫秒，最大65535
**入口参数：unsigned int ms     1=< ms <= 65535
**输出：无
*******************************************************************************/
void Delay_Nms(unsigned int ms)
{
TIM4_SetCounter(0x00);                // 设定计数器的初值
TIM4_Cmd(ENABLE);           //启动定时器4开始计数
while(ms--)
{
	TIM4_Cmd(ENABLE);
  while(TIM4_GetFlagStatus(TIM4_FLAG_UPDATE)==RESET); //等待计数是否达到1毫秒
  printf("计数开启\n");
}
TIM4_ClearFlag(TIM4_FLAG_UPDATE);         //计数完成1毫秒，清除相应的标志
TIM4_Cmd(DISABLE); //延时全部结束，关闭定时器4
}

/*
函数功能：显示文字
函数形参：x,y,t_color,b_color,* txt_buf
函数返回值：无
备注：单独显示一个文字
*/
void lcd_dis_txt(u16 x, u16 y, u16 t_color, u16 b_color, u8 *txt_buf)
{
	u8 txt_line = 0, txt_column = 0;
	u16 txt_data = 0;
	
	for(txt_line = 0; txt_line < 16; txt_line++)
	{
		//txt_data：表示当前行的那些点需要显示字体颜色或背景颜色；当前行的所有数据
		txt_data = (txt_buf[2 * txt_line] << 8) + txt_buf[2 * txt_line + 1];
		
		for(txt_column = 0; txt_column < 16; txt_column++)
		{
			if(txt_data & (0x8000 >> txt_column))//字体颜色
			{
				lcd_draw_point(x + txt_column,y + txt_line,t_color);
			}
			else//背景颜色
			{
				lcd_draw_point(x + txt_column,y + txt_line,b_color);
			}
		}
	}
}


/*
函数功能：显示英文
函数形参：x,y,t_color,b_color,* ch_buf
函数返回值：无
备注：单独显示一个英文字母
*/
void lcd_dis_ch(u16 x, u16 y, u16 t_color, u16 b_color, u8 *ch_buf)
{
	u8 ch_line = 0, ch_column = 0;
	
	for(ch_line = 0; ch_line < 16; ch_line++)
	{	
		for(ch_column = 0; ch_column < 8; ch_column++)
		{
			if(ch_buf[ch_line] & (0x80 >> ch_column))//字体颜色
			{
				lcd_draw_point(x + ch_column,y + ch_line,t_color);
			}
			else//背景颜色
			{
				lcd_draw_point(x + ch_column,y + ch_line,b_color);
			}
		}
	}
}


/*
函数功能：显示一串字符
函数形参：x,y,t_color,b_color,*data_buff
函数返回值：无
备注：不需要管是中文还是英文
*/
void lcd_dis_str(u16 x, u16 y, u16 t_color, u16 b_color, u8 *data_buff)
{
	u16 var_num = 0;//是第几个字
	
	while(*data_buff != '\0')
	{
		if(*data_buff > 0xa0)//中文
		{
			var_num = 0;
			while(1)//查找是第几个字
			{
				if((*data_buff == data_txt[2 * var_num]) && (*(data_buff + 1) == data_txt[2 * var_num + 1]))
				{
					break;
				}
				var_num++;
				if(data_txt[2 * var_num] == '\0')
				{
					break;
				}
			}
			if(data_txt[2 * var_num] != '\0')//有这个字才显示
			{
				if((320 - x) < 16)//自动换行
				{
					x = 0; 
					y += 16;
				}
				lcd_dis_txt(x,y,t_color,b_color,(u8 *)&txt_buff[var_num * 32]);
				x += 16;
				data_buff += 2;
			}
		}
		else//英文
		{
			if((320 - x) < 8)//自动换行
			{
				x = 0; 
				y += 16;
			}
			var_num = *data_buff - ' ';
			
			lcd_dis_ch(x,y,t_color,b_color,(u8 *)&ch_buff[var_num * 16]);
			
			x += 8;
			data_buff += 1;
		}
	}
}












