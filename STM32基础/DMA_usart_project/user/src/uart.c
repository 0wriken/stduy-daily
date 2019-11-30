#include "uart.h"
u8 res=0;
static u8 recieve_buf[20]={0};
u8 *buf;
u8 buf1[20]={0};
static u32 n=0;
/*
***********************************************************************************************
* �������ܣ���ʼ������
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-08
* �޸�����: None
* �޸�ʱ��: None
***********/
void uart_init(u32 B)
{
	float USARTDIV_1=0;
	u16 DIV_MAN=0;
	u16 DIV_FRA=0;
	RCC->AHB1ENR|=(0x1<<0);    //ʱ��ʹ��
	GPIOA->MODER&=~(0xf<<2*9);	
	GPIOA->MODER|=(0xA<<2*9);  // ģʽ����
	GPIOA->AFR[1]&=(0xff<<4*(9-8));
	GPIOA->AFR[1]|=(0x77<<4*(9-8)); //���ù���ΪUART
	GPIOA->OTYPER&=~(0x1<<9);       //PA9����
	GPIOA->PUPDR&=~(0xf<<2*9);      //PA9PA10������
	GPIOA->OSPEEDR&=~(0x3<<2*9);    //PA9�ٶ�
	
	
	RCC->APB2ENR|=(0x1<<4);    //ʱ��ʹ��
	USART1->CR1&=(0x3<<2);		
	USART1->CR1|=(0x3<<2);    //�շ�ʹ��
	USART1->CR1 |= (0X1 << 13);//ʹ��USART1
	USART1->CR2&=~(0x3<<12);//���÷��ͽ���ʹ�ܣ�ֹͣλ0.5
	
	USARTDIV_1=(float)84000000ul/(16*B);//������
	DIV_MAN=(u16)USARTDIV_1;     //��������
	DIV_FRA=(USARTDIV_1-DIV_MAN)*16+(float)0.5; //С������4��5��
	USART1->BRR=(DIV_MAN<<4)|DIV_FRA;  //������д��Ĵ���
//	u32 i=0;
//	NVIC_SetPriorityGrouping(7-2);//��ռλ
//	i= NVIC_EncodePriority(7 - 2, 2, 2);//��ռ����Ӧ���ȼ�
//	NVIC_SetPriority(USART1_IRQn, i);//�ж�����
//	//����Ĵ���

//	//NVIC�ж�ʹ��*/
//	NVIC_EnableIRQ(USART1_IRQn);
//	USART1->CR1|=(0X1<<5);//�����ж�ʹ�ܱ�־λ
}

///*
//***********************************************************************************************
//* �������ܣ����ڽ����ַ���
//* �����β�: None
//* ��������ֵ: None
//* ��ע: None
//* ����: wriken
//* ʱ��: 2019-08-06
//* �޸�����: None
//* �޸�ʱ��: None
//***********/
//u8 *uart_recive(void)//����
//{
//	u16 i=0;
//	
//	 do
//	{
//		while(!(USART1->SR&(0x1<<5)));//ʱ������
//		recieve_buf[i++]=USART1->DR;
//		
//	}while(USART1->DR!='\n');
//	return recieve_buf;
//	//return USART1->DR;
//}
///***********************************************************************************************
//* �������ܣ����ڽ����ַ�
//* �����β�: None
//* ��������ֵ: None
//* ��ע: None
//* ����: wriken
//* ʱ��: 2019-08-06
//* �޸�����: None
//* �޸�ʱ��: None
//***********/
//u8 uart_recive_data(void)//����
//{
//	
//		while(!(USART1->SR&(0x1<<5)));//ʱ������	
//		return USART1->DR;
//}
///*
//***********************************************************************************************
//* �������ܣ����ڷ����ַ�
//* �����β�: None
//* ��������ֵ: None
//* ��ע: None
//* ����: wriken
//* ʱ��: 2019-08-08
//* �޸�����: None
//* �޸�ʱ��: None
//***********/
//void uart_send_data(u8 send_data)
//{	
//		while(!(USART1->SR&(0x1<<6)));//ʱ������
//		USART1->DR=send_data;

//}
///*
/***********************************************************************************************
* �������ܣ����ڷ����ַ���
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-08
* �޸�����: None
* �޸�ʱ��: None
***********/
void uart_send(u8 *send_buf)//����
{
	
	
	do
		{	
		while(!(USART1->SR&(0x1<<6)));//ʱ������
		USART1->DR=*send_buf;

		send_buf++;
	}while((char)*send_buf!='\0');
}
/***********************************************************************************************
* ��������:�жϷ�����
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-10
* �޸�����: None
* �޸�ʱ��: None
***********/
void USART1_IRQHandler(void)
{
			recieve_buf[n]=USART1->DR;
			n++;
		if(recieve_buf[n-1]=='\n')
		{
		uart_send(recieve_buf);
		recieve_buf[n-2]='\0';
			n=0;
		}
		USART1->SR&=~(0x1<<5);
}

///*
//�������ܣ�printf
//�����βΣ���
//����ֵ����
//��ע����
//*/
//#pragma import(__use_no_semihosting_swi) //ȡ��������״̬

//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;

//int fputc(int ch, FILE *f) 
//{
//	while((USART1->SR &(0X01<<7))==0)
//	{
//		;  //�ȴ�֮ǰ�����ݷ������
//	}
//		USART1->DR=ch;
//  return (ch);
//}

//int ferror(FILE *f) {
//  /* Your implementation of ferror */
//  return EOF;
//}


//void _ttywrch(int ch) {
//  while((USART1->SR &(0X01<<7))==0);
//		USART1->DR=ch;
//}


//void _sys_exit(int return_code) {
//label:  goto label;  /* endless loop */
//}
///***********************************************************************************************
//* �������ܣ����ڽ����ַ����ж�
//* �����β�: None
//* ��������ֵ: None
//* ��ע: None
//* ����: wriken
//* ʱ��: 2019-08-08
//* �޸�����: None
//* �޸�ʱ��: None
//***********/

//void usart_string()
//{	while(1)
//	{
//		u32 i=0;
//		buf = uart_recive();
//		printf("**********%s",buf);
//		while(*buf!='\r')
//		{
//			buf++;
//			i++;
//		}
//		*buf=0;
//		buf-=i;
//		uart_send(buf);
//		if(strcmp((char *)buf,"open_led1")==0)   //�ȽϽ��յ�������
//		{
//			GPIOA->BSRRH|=0x1<<6;
//		}
//		if(strcmp((char *)buf,"open_led2")==0)
//		{
//				GPIOC->BSRRH|=0x1<<4;	
//		}
//		if(strcmp((char *)buf,"open_led3")==0)
//		{
//			GPIOC->BSRRH|=0x1<<5;
//		}
//		if(strcmp((char *)buf,"open_led4")==0)
//		{
//			GPIOA->BSRRH|=0x1<<7;
//		}
//		if(strcmp((char *)buf,"open_led")==0)
//		{
//			GPIOA->BSRRH|=0x3<<6;
//			GPIOC->BSRRH|=0X3<<4;
//		}
//		else if(strcmp((char *)buf,"close_led")==0)
//		{
//			GPIOA->BSRRL|=0x3<<6;
//			GPIOC->BSRRL|=0x3<<4;
//		}
//	}

//}
///***********************************************************************************************
//* �������ܣ����ڽ����ַ��ж�
//* �����β�: None
//* ��������ֵ: None
//* ��ע: None
//* ����: wriken
//* ʱ��: 2019-08-08
//* �޸�����: None
//* �޸�ʱ��: None
//***********/
//void uart_char()
//{
//	while(1)
//	{
//		u32 i=0;
//	memset((char *)buf1,0,strlen((char *)buf1));
//	do
//	{
//		buf1[i]=uart_recive_data();
//		uart_send_data(buf1[i]);
//		i++;
//	}while(buf1[i-1]!='\n');    //�����շ�����
//		buf1[i-2] = 0;
//		printf("**********%s",buf1);
//		if(strcmp((char *)buf1,"open_led1")==0)   //�ȽϽ��յ�������
//		{
//			GPIOA->BSRRH|=0x1<<6;
//		}
//		else if(strcmp((char *)buf1,"close_led1")==0)
//		{
//			GPIOA->BSRRL|=0x1<<6;
//		}
//		if(strcmp((char *)buf1,"open_led2")==0)
//		{
//				GPIOC->BSRRH|=0x1<<4;	
//		}
//		else if(strcmp((char *)buf1,"close_led2")==0)
//		{
//			GPIOC->BSRRL|=0x1<<4;
//		}
//		if(strcmp((char *)buf1,"open_led3")==0)
//		{
//			GPIOC->BSRRH|=0x1<<5;
//		}
//		else if(strcmp((char *)buf1,"close_led1")==0)
//		{
//			GPIOC->BSRRL|=0x1<<5;
//		}
//		if(strcmp((char *)buf1,"open_led4")==0)
//		{
//			GPIOA->BSRRH|=0x1<<7;
//		}
//		else if(strcmp((char *)buf1,"close_led1")==0)
//		{
//			GPIOA->BSRRL|=0x1<<7;
//		}
//		if(strcmp((char *)buf1,"open_led")==0)
//		{
//			GPIOA->BSRRH|=0x3<<6;
//			GPIOC->BSRRH|=0X3<<4;
//		}
//		else if(strcmp((char *)buf1,"close_led")==0)
//		{
//			GPIOA->BSRRL|=0x3<<6;
//			GPIOC->BSRRL|=0x3<<4;
//		}
//	}

//}

