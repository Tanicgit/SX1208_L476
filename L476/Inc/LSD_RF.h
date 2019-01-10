////////////////////////////////////////////////////////////////////////////////
// 版权:     利尔达科技集团股份有限公司
// 文件名:   LSD_RF.h
// 版本：    v1.0
// 工作环境: IAR  v5.30
// 作者:     于海波
// 生成日期: 2014.11
// 功能:     
// 相关文件: 
// 修改日志：
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _LSD_RF_h_
#define _LSD_RF_h_
#include "spi.h"
#include "gpio.h"
////===================================RF硬件IO口定义（根据实际使用修改）===================================================

////SX1276 SPI I/O definitions
////SIMO
//#define  LSD_SPI_SIMO_PORT_SEL   P6SEL_bit.P2
//#define  LSD_SPI_SIMO_PORT_DIR   P6DIR_bit.P2
//#define  LSD_SPI_SIMO_PORT_OUT   P6OUT_bit.P2
//#define  LSD_SPI_SIMO_PORT_IN    P6IN_bit.P2
////SCK
//#define  LSD_SPI_SCK_PORT_SEL    P6SEL_bit.P4
//#define  LSD_SPI_SCK_PORT_DIR    P6DIR_bit.P4
//#define  LSD_SPI_SCK_PORT_OUT    P6OUT_bit.P4
//#define  LSD_SPI_SCK_PORT_IN     P6IN_bit.P4   
////SOMI
//#define  LSD_SPI_SOMI_PORT_SEL   P6SEL_bit.P1
//#define  LSD_SPI_SOMI_PORT_DIR   P6DIR_bit.P1
//#define  LSD_SPI_SOMI_PORT_OUT   P6OUT_bit.P1
//#define  LSD_SPI_SOMI_PORT_IN    P6IN_bit.P1
////NSS
//#define  LSD_SPI_NSS_PORT_SEL    P6SEL_bit.P3
//#define  LSD_SPI_NSS_PORT_DIR    P6DIR_bit.P3
//#define  LSD_SPI_NSS_PORT_OUT    P6OUT_bit.P3
//#define  LSD_SPI_NSS_PORT_IN     P6IN_bit.P3

//////SX1276 DIO pins  I/O definitions
//////DIO0
extern uint8_t GPIO_PIN_7_exit_tp;

#define LSD_RF_DIO0_SEL      _DEFINE          //DIO0 IO复用功能选择 
#define LSD_RF_DIO0_DIR      _DEFINE           //DIO0 方向寄存器   
#define LSD_RF_DIO0_IFG      GPIO_PIN_7_exit_tp          //DIO0 中断标志位寄存器
#define LSD_RF_DIO0_IES      _DEFINE           //DIO0 触发方式寄存器，上升沿或下降沿
#define LSD_RF_DIO0_IE       _DEFINE            //DIO0 中断使能寄存器
#define LSD_RF_DIO0_IN       _DEFINE            //DIO0 输入寄存器
//#define LSD_RF_DIO0_SEL            P1SEL_bit.P0     //DIO0 IO复用功能选择 
//#define LSD_RF_DIO0_DIR            P1DIR_bit.P0     //DIO0 方向寄存器   
//#define LSD_RF_DIO0_IFG            P1IFG_bit.P0     //DIO0 中断标志位寄存器
//#define LSD_RF_DIO0_IES            P1IES_bit.P0     //DIO0 触发方式寄存器，上升沿或下降沿
//#define LSD_RF_DIO0_IE             P1IE_bit.P0      //DIO0 中断使能寄存器
//#define LSD_RF_DIO0_IN             P1IN_bit.P0      //DIO0 输入寄存器
////DIO1（未使用）
//#define LSD_RF_DIO1_SEL            P5SEL_bit.P0     //DIO1 IO复用功能选择  
//#define LSD_RF_DIO1_DIR            P5DIR_bit.P0     //DIO1 方向寄存器   
//#define LSD_RF_DIO1_IFG            P5IFG_bit.P0     //DIO1 中断标志位寄存器
//#define LSD_RF_DIO1_IES            P5IES_bit.P0     //DIO1 触发方式寄存器，上升沿或下降沿
//#define LSD_RF_DIO1_IE             P5IE_bit.P0      //DIO1 中断使能寄存器
//#define LSD_RF_DIO1_IN             P5IN_bit.P0      //DIO1 输入寄存器
////DIO2
//#define LSD_RF_DIO2_SEL            P1SEL_bit.P1     //DIO2 IO复用功能选择  
//#define LSD_RF_DIO2_DIR            P1DIR_bit.P1     //DIO2 方向寄存器   
//#define LSD_RF_DIO2_IFG            P1IFG_bit.P1     //DIO2 中断标志位寄存器
//#define LSD_RF_DIO2_IES            P1IES_bit.P1     //DIO2 触发方式寄存器，上升沿或下降沿
//#define LSD_RF_DIO2_IE             P1IE_bit.P1      //DIO2 中断使能寄存器
//#define LSD_RF_DIO2_IN             P1IN_bit.P1      //DIO2 输入寄存器
////DIO3（未使用）
#define LSD_RF_DIO3_SEL            _DEFINE     //DIO3 IO复用功能选择  
#define LSD_RF_DIO3_DIR            _DEFINE     //DIO3 方向寄存器   
#define LSD_RF_DIO3_IFG            _DEFINE     //DIO3 中断标志位寄存器
#define LSD_RF_DIO3_IES            _DEFINE     //DIO3 触发方式寄存器，上升沿或下降沿
#define LSD_RF_DIO3_IE             _DEFINE      //DIO3 中断使能寄存器
#define LSD_RF_DIO3_IN             _DEFINE      //DIO3 输入寄存器
//#define LSD_RF_DIO3_SEL            P2SEL_bit.P0     //DIO3 IO复用功能选择  
//#define LSD_RF_DIO3_DIR            P2DIR_bit.P0     //DIO3 方向寄存器   
//#define LSD_RF_DIO3_IFG            P2IFG_bit.P0     //DIO3 中断标志位寄存器
//#define LSD_RF_DIO3_IES            P2IES_bit.P0     //DIO3 触发方式寄存器，上升沿或下降沿
//#define LSD_RF_DIO3_IE             P2IE_bit.P0      //DIO3 中断使能寄存器
//#define LSD_RF_DIO3_IN             P2IN_bit.P0      //DIO3 输入寄存器
////DIO4（未使用）
//#define LSD_RF_DIO4_SEL            P2SEL_bit.P1     //DIO4 IO复用功能选择  
//#define LSD_RF_DIO4_DIR            P2DIR_bit.P1     //DIO4 方向寄存器   
//#define LSD_RF_DIO4_IFG            P2IFG_bit.P1     //DIO4 中断标志位寄存器
//#define LSD_RF_DIO4_IES            P2IES_bit.P1     //DIO4 触发方式寄存器，上升沿或下降沿
//#define LSD_RF_DIO4_IE             P2IE_bit.P1      //DIO4 中断使能寄存器
//#define LSD_RF_DIO4_IN             P2IN_bit.P1      //DIO4 输入寄存器

////SX1276 RESET I/O definitions
//#define  LSD_RF_SXRESET_DIR        P5DIR_bit.P1
//#define  LSD_RF_SXRESET_OUT        P5OUT_bit.P1

//////==========================================end======================================================



//////================================函数宏定义======================================================
//#define  LSD_RF_DELAY()            __no_operation()             //SPI延时
#define LSD_RF_SPIInit()
//#define LSD_RF_SPIInit()        do{         \
//                                        LSD_SPI_SIMO_PORT_SEL=0 ;\
//                                        LSD_SPI_SIMO_PORT_DIR=1 ;\
//                                        LSD_SPI_SIMO_PORT_OUT=1; \
//                                            \
//                                        LSD_SPI_SCK_PORT_SEL=0;  \
//                                        LSD_SPI_SCK_PORT_DIR=1;  \
//                                        LSD_SPI_SCK_PORT_OUT=0;  \
//                                           \
//                                        LSD_SPI_SOMI_PORT_SEL=0; \
//                                        LSD_SPI_SOMI_PORT_DIR=0; \
//                                        LSD_SPI_SOMI_PORT_OUT=0; \
//                                           \
//                                        LSD_SPI_NSS_PORT_SEL=0 ; \
//                                        LSD_SPI_NSS_PORT_DIR=1;  \
//                                        LSD_SPI_NSS_PORT_OUT=1;  \
//                                  }while(0)

//#define LSD_SPI_SIMO_OUT(x)   LSD_SPI_SIMO_PORT_OUT=x            //SIMO=X
//#define LSD_SPI_SCK_OUT(x)    LSD_SPI_SCK_PORT_OUT=x             //sck=x
//#define LSD_SPI_NSS_OUT(x)    LSD_SPI_NSS_PORT_OUT=x             //nss=x
//#define LSD_SPI_SOMI_IN()     LSD_SPI_SOMI_PORT_IN            

#define LSD_SPI_NSS_OUT(x)			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, x)


/////*********************************************************************
////**  function Declaration
////*********************************************************************/
void LSD_RF_StandbyMode(void);
void LSD_RF_SleepMode(void);
void LSD_RF_Config(void);
void LSD_RF_RestRF(void);
unsigned char LSD_RF_InitRF(void);
void LSD_RF_RXmode(void);
void LSD_RF_SendPacket(uint8_t *txBuffer, uint8_t size);
void LSD_RF_RxPacket(uint8_t *cRxBuf, uint8_t *cLength);
void LSD_RF_FreqSet(uint8_t ch);
void LSD_RF_WORInit(void);
void LSD_RF_WORexecute(uint8_t cLength);
void LSD_RF_WOR_Exit(void);
void LSD_RF_AwakePkt(void);
//void LSD_RF_RSSIInit(void);
void LSD_RF_TriggerRssi(void);
unsigned char LSD_RF_GetRSSI(void);
void LSD_RF_test(void);
#endif
