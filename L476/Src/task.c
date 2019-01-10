#include "LSD_RF.h"

#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/*上行方向*/
uint8_t pData[100];
uint8_t pLen=0;


/**/
#define RX_STA	0
#define TX_STA	1
uint8_t RF_RxTx_sta=RX_STA;
uint8_t GPIO_PIN_7_exit_tp=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_7)
	{
		if(RF_RxTx_sta==RX_STA)
		{
			LSD_RF_RxPacket(pData,&pLen);
			//立刻转发
			if(pLen)
			{
				HAL_UART_Transmit(&huart2,pData,pLen,0xfff);
				LSD_RF_RXmode();
			}
		}
		else{
			GPIO_PIN_7_exit_tp = 1;
		}
	}
}
/*下行方向*/
#define FIFO_SIZE 1200
static uint8_t PAfifo[FIFO_SIZE];
static uint32_t tail=0;
static uint32_t head=FIFO_SIZE-1;
uint8_t pBuf[64];
int8_t in(uint8_t a)
{
	uint32_t p;
	p=tail;
	if(p==head)return -1;
	else
	{
		PAfifo[p] = a;
		tail = p<FIFO_SIZE-1 ? p+1 : 0;
		return 0;
	}
}
int8_t Fifoout(uint8_t *a)
{
	uint32_t p;
	p= head;
	p= p<FIFO_SIZE-1 ? p+1:0;
	if(p==tail)
	{
		return -1;
	}
	else
	{
		*a = PAfifo[p];
		head = p;
		return 0;
	}
}
void UART2_Callback(uint8_t a)
{
	in(a);
}
#include "string.h"
void task()
{
	int8_t re=0;
	uint8_t da=0,n=0;
	memset(pData,0,100);
	memset(pBuf,0,64);
	LSD_RF_RXmode();
	for(;;)
	{
		HAL_Delay(50);
		n=0;	
		do
		{
			re = Fifoout(&da);
			if(re==0)pBuf[n++]=da;
		}while(re==0&&n<64);	
		if(n)
		{
			RF_RxTx_sta = TX_STA;
			GPIO_PIN_7_exit_tp=0;
			LSD_RF_SendPacket(pBuf,n);
			RF_RxTx_sta = RX_STA;
			LSD_RF_RXmode();
		}
	}
}
