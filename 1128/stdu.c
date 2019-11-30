void set_task_point(int x,int y,u8 *buf)
{
	if(x>240||y>430)
	{
		printf("设置位置有误\n");
		return ;		
	}
	if(t_para.sx>x&&t_para.sx<(x+80)&&t_para.sy<(y+50)&&t_para.sy>y)
		{
			//strcpy((char *)send_buf,"LED1_ON");
			printf("准确按下%s\n"buf);
			 OSMboxPost (QSM,
                   (void*)"LED1_ON");	
			 retr
		}
}
 OS_STK sun_task_stk[SUN_TASK_STK_SIZE];
 OS_STK water_task_stk[WATER_TASK_STK_SIZE];
void send_wait(u32 id,u8 * buf,len)
{
	 u8 re_buf[100={0};
	 u8 getid=0;
		while(1)
		{
			can1_send_msg(id,buf,len);
			printf("%s",buf);
			can1_receive_msg(re_buf,&gid);
			printf("应答：%s\n",re_buf);
			if(strcmp((char *)re_buf,"OK")==0)
			{	
				printf("接收到应答\n");
				break;
			}
			//OSTimeDly(200);
		}
}	

can1_receive_msg(r_buf,&gid)
play_Square(40,100)
play_Square(80,200)
play_Square(40,200)  雨水
play_Square(80,100)
play_Square(200,400);退出
