#include "LSD_RFreg.h"
#include "LSD_RF.h"
#include "LSD_RFregsetting.h"
//extern uint8_t Sleep_RX;

uint8_t _DEFINE=0;

uint8_t RF_Version;

#define DelayMs HAL_Delay

//**********************************************************************************
// 功能描述 : spi发送or接收1字节
// 输入参数 : unsigned char mosi
// 返回参数 : unsigned char
// 说明     : 
//**********************************************************************************
static unsigned char LSD_RF_SpiInOut (unsigned char mosi) 
{ 
	uint8_t miso=0;
	HAL_SPI_TransmitReceive(&hspi1,&mosi,&miso,1,0xfff);
	return miso;
//    unsigned char i;
//    unsigned char onebyte;
//    onebyte = mosi;
//    for(i = 8; i > 0; i--) 
//    {
//        LSD_RF_DELAY();
//        if(onebyte & 0x80) 
//        {
//            LSD_SPI_SIMO_OUT(1);
//        }
//        else 
//        {
//            LSD_SPI_SIMO_OUT(0);
//        }

//        LSD_RF_DELAY();
//        LSD_SPI_SCK_OUT(1);
//        onebyte <<= 1;      // next bit
//        if(LSD_SPI_SOMI_IN()) 
//        {
//            onebyte++;      // 1 found on MISO
//        }
//        LSD_RF_DELAY();
//        LSD_SPI_SCK_OUT(0);
//    }
//    return onebyte;         // mosi now becomes the value of miso
}
//**********************************************************************************
// 功能描述 : spi读写寄存器
// 输入参数 : unsigned char addr地址 unsigned char val数据
// 返回参数 : 
// 说明     : Note: don't call it directely use macro SpiWriteReg and SpiWriteReg  to call this routine
//**********************************************************************************
unsigned char LSD_RF_SpiRW_Reg (unsigned char addr, unsigned char val) 
{
    unsigned char rc;
    LSD_RF_SPIInit();
    LSD_SPI_NSS_OUT(GPIO_PIN_RESET);
    LSD_RF_SpiInOut(addr);
    rc = LSD_RF_SpiInOut(val);
    LSD_SPI_NSS_OUT(GPIO_PIN_SET);
    return rc;
}
//**********************************************************************************
// 功能描述 : 写寄存器
// 输入参数 : addr地址 val数据
// 返回参数 : 无
// 说明     : 
//**********************************************************************************
#define LSD_RF_WriteReg(addr, val)         LSD_RF_SpiRW_Reg(addr|0x80,val)
//**********************************************************************************
// 功能描述 : 读寄存器
// 输入参数 : addr地址
// 返回参数 : 寄存器值
// 说明     : 
//**********************************************************************************
#define LSD_RF_ReadReg(addr)               LSD_RF_SpiRW_Reg(addr&0x7F, 0)
//**********************************************************************************
// 功能描述 : 清除FIFO以及溢出标志位
// 输入参数 : 
// 返回参数 : 
// 说明     : 
//**********************************************************************************
#define LSD_RF_ClearFIFO()                    LSD_RF_WriteReg(REG_IRQFLAGS2, 0x10)
//**********************************************************************************
// 功能描述 : 确保进入standby
// 输入参数 : 
// 返回参数 : 
// 说明     : 注意：此函数将listen功能关闭,TS_OSC>500us
//**********************************************************************************
void LSD_RF_StandbyMode(void)
{
    unsigned long int i=600000;
    LSD_RF_WriteReg(REG_OPMODE, (RF_OPMODE_SEQUENCER_ON|RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY));
    while (((LSD_RF_ReadReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00)&&i)i--; // Wait for ModeReady
}
//**********************************************************************************
// 功能描述 : 确保进入sleep
// 输入参数 : 
// 返回参数 : 
// 说明     : 注意：此函数将listen功能关闭
//**********************************************************************************
void LSD_RF_SleepMode(void)
{
    unsigned long int i=600000;
    LSD_RF_StandbyMode();       //先切换到standby模式再切到sleep模式
    LSD_RF_WriteReg(REG_OPMODE, (RF_OPMODE_SEQUENCER_ON|RF_OPMODE_LISTEN_OFF | RF_OPMODE_SLEEP));
    while (((LSD_RF_ReadReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00)&&i)i--; // Wait for ModeReady
//    LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO0_00+RF_DIOMAPPING1_DIO1_11+RF_DIOMAPPING1_DIO2_01+RF_DIOMAPPING1_DIO3_01); // DIO0 = packet sent
//    LSD_RF_WriteReg(REG_DIOMAPPING2, RF_DIOMAPPING2_DIO4_00+RF_DIOMAPPING2_DIO5_00); // DIO0 = packet sent
    LSD_SPI_NSS_OUT(GPIO_PIN_RESET);  //进入低功耗，要将NSS拉低，防止漏电流，这个很重要
}
//**********************************************************************************
// 功能描述 : 确保进入RX模式
// 输入参数 : 
// 返回参数 : 
// 说明     : 注意：此函数将listen功能关闭  ，DIO3=Premble   DIO0=PLD
//**********************************************************************************
void LSD_RF_RXmode(void)
{
    unsigned char nTimes,cData;
    LSD_RF_DIO0_IFG=0;          //清除MCU标志位
    LSD_RF_DIO3_IFG=0;          //清除MCU标志位
    LSD_RF_DIO0_IE=0;           //进入接收前关闭中断
    LSD_RF_DIO3_IE=0;           //关中断
    LSD_RF_StandbyMode();       //先切换到standby模式
    if(RF_Version==RF_SX1208)
       LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAP1_DIO0_PLD_RDY|RF_DIOMAPPING1_DIO3_01); // DIO0 = PLD_RDY
    else 
       LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAP1_DIO0_PLD_RDY|RF_DIOMAPPING1_DIO3_10); // DIO0 = PLD_RDY
    LSD_RF_ClearFIFO();         //清FIFO  
    while(1)    //防止外部因素导致SPI切换到RX模式失败，此代码为做保护用。
    {
         nTimes=100;
         LSD_RF_WriteReg(REG_OPMODE, (RF_OPMODE_SEQUENCER_ON|RF_OPMODE_LISTEN_OFF | RF_OPMODE_RECEIVER));
         //等待进入接收状态
         do
         {
             cData=LSD_RF_ReadReg(REG_OPMODE) & 0x1c;
             nTimes--;
         }
         while((cData!=RF_OPMODE_RECEIVER)&&nTimes);
         if(!nTimes)
              continue;
         LSD_RF_DIO0_IFG=0;          //清除MCU标志位
         LSD_RF_DIO3_IFG=0;          //清除MCU标志位
         LSD_RF_DIO0_IE=1;           //开始中断
         LSD_RF_DIO3_IE=1;           //开始中断
         return;
     } 
}
////**********************************************************************************
//// 功能描述 : 写配置表
//// 输入参数 : 无
//// 返回参数 : 无
//// 说明     : 
////**********************************************************************************
void LSD_RF_Config(void)
{
    _SX12XX_REG const *p;
    unsigned char i;
    p = LSD_RFregConfig;
    for(i=sizeof(LSD_RFregConfig)/2; i>0; i--) 
    {
        LSD_RF_WriteReg(p->addr, p->val);
        p++;
    }
}
////**********************************************************************************
//// 功能描述 : 复位无线模块
//// 输入参数 : 无
//// 返回参数 : 无
//// 说明     : 
////**********************************************************************************
void LSD_RF_RestRF(void)
{
//   LSD_RF_SXRESET_DIR =1;  //复位引脚做输出
//   LSD_RF_SXRESET_OUT =1;  //复位引脚输出高电平复位
//   DelayMs(20);
//   LSD_RF_SXRESET_OUT=0;   //复位引脚输出低电平
//   DelayMs(20);
}
////**********************************************************************************
//// 功能描述 : RF初始化
//// 输入参数 : 无
//// 返回参数 : 无
//// 说明     : 
////**********************************************************************************
unsigned char LSD_RF_InitRF(void) 
{
    LSD_RF_RestRF();                    //复位RF
    LSD_RF_SPIInit();                   //RF初始化 
    LSD_RF_StandbyMode();               //进入standby模式
    LSD_RF_Config();                    //写RF配置表，最好在standby模式或sleep模式下修改
    RF_Version = LSD_RF_ReadReg(REG_VERSION);
    // to test SPI
    LSD_RF_WriteReg(REG_SYNCVALUE8, 0x55);
    if(LSD_RF_ReadReg(REG_SYNCVALUE8) != 0x55) 
    {
        return 1;// something wrong with SPI
    }
    LSD_RF_WriteReg(REG_SYNCVALUE8, 0xD3);
    if(LSD_RF_ReadReg(REG_SYNCVALUE8) != 0xD3) 
    {
        return 1;// something wrong with SPI
    }
   return 0;           
}

////////////////////////////////////////////////////////////////////////////
// 功能描述 : 发送数据
// 输入参数 : uint8_t *txBuffer:发送数据存储数组首地址,
//            uint8_t size：发送数据长度
// 返回参数 : 无
// 说明     : 
//////////////////////////////////////////////////////////////////////////////
void LSD_RF_SendPacket(uint8_t *txBuffer, uint8_t size)
{
    uint8_t i;
    unsigned long int j=600000;   //发送超时退出，根据实际应用请做调整
    LSD_RF_DIO0_IFG=0; //清除MCU标志位
    LSD_RF_DIO3_IFG=0; //清除MCU标志位
    LSD_RF_DIO0_IE=0;   //发送前关闭中断
    LSD_RF_DIO3_IE=0;   //发送前关闭中断
    LSD_RF_StandbyMode();               //进入standby模式
    LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAP1_DIO0_PKT_SENT); // DIO0 = packet sent
    #if (HIGH_POWER==1)   //如果High Power 设置enable（+20dbm capability on PA_BOOST）
    {
        LSD_RF_WriteReg(REG_OCP,0x0F);   
        LSD_RF_WriteReg(REG_TESTPA1,0x5D);   
        LSD_RF_WriteReg(REG_TESTPA2,0x7C);
    }
		#endif
    LSD_RF_ClearFIFO();    //清除FIFO
    LSD_RF_WriteReg(REG_FIFO, size);
    for(i=0;i<size;i++)
    {
        LSD_RF_WriteReg(REG_FIFO, txBuffer[i]);
    }
    LSD_RF_WriteReg(REG_OPMODE, (RF_OPMODE_SEQUENCER_ON|RF_OPMODE_LISTEN_OFF | RF_OPMODE_TRANSMITTER));  //切换到发送
    while((!LSD_RF_DIO0_IFG)&&j)j--;         // packet sent
    LSD_RF_StandbyMode();               //进入standby模式
    #if (HIGH_POWER==1)                //退出发送后，注意一定要将Hing Power Disable。
    {
        LSD_RF_WriteReg(REG_OCP,0x1B);   
        LSD_RF_WriteReg(REG_TESTPA1,0x55);   
        LSD_RF_WriteReg(REG_TESTPA2,0x70); 
    }
    #endif
}

//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 接收数据包
//// 输入参数 : uint8_t *cRxBuf,返回数据存储首地址。 uint8_t cLength 读的数据长度
//// 返回参数 : 无
//// 说明     : 
//////////////////////////////////////////////////////////////////////////////////
void LSD_RF_RxPacket(uint8_t *cRxBuf, uint8_t *cLength)
{
    uint8_t i;
    LSD_RF_StandbyMode();               //进入standby模式
    *cLength = LSD_RF_ReadReg(REG_FIFO);
    for(i=0;i<*cLength;i++)
      cRxBuf[i]=LSD_RF_ReadReg(REG_FIFO);
    LSD_RF_ClearFIFO();    //清除FIFO
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : FreqCalSet
//// 输入参数 : ch   建议ch=0~75
//// 返回参数 : 无
//// 说明     : 
//////////////////////////////////////////////////////////////////////////////////
void LSD_RF_FreqSet(uint8_t ch)
{
    LSD_RF_StandbyMode();               //进入standby模式
    LSD_RF_WriteReg(REG_FRFMSB,Freq_Cal_Tab[ch*3]);
    LSD_RF_WriteReg(REG_FRFMID,Freq_Cal_Tab[ch*3+1]);
    LSD_RF_WriteReg(REG_FRFLSB,Freq_Cal_Tab[ch*3+2]);
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : WOR初始化
// 输入参数 : 无
//            
// 返回参数 : 无
// 说明     : 前导（2）+同步(2)         
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_WORInit(void)
{
    LSD_RF_StandbyMode();                //进入standby模式
    LSD_RF_DIO0_IFG=0;                   //清除MCU标志位
    LSD_RF_DIO0_IE=0;                    //关闭中断
    //配置参数
    LSD_RF_WriteReg(REG_PREAMBLELSB,0x02);   //设置2个前导码
    LSD_RF_WriteReg(REG_SYNCCONFIG,0x88);   //设置2个同步字
    LSD_RF_WriteReg(REG_SYNCVALUE1,0x55);   //设置同步字内容 
    LSD_RF_WriteReg(REG_SYNCVALUE2,0x55);   //设置同步字内容 
//    LSD_RF_WriteReg(REG_PACKETCONFIG1,0x80);   //关闭CRC  
    LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO3_10); // 映射DIO3 = SYNC_ADDR（也可以用DIO0，这里用DIO3为例子）    
    //初始化映射中断口
    LSD_RF_DIO3_IFG=0;   //清除中断标志位
    LSD_RF_DIO3_SEL=0;   //不选择第二功能（MSP430默认为第一功能）
    LSD_RF_DIO3_DIR=0;   //中断做输入
    LSD_RF_DIO3_IES=0;   //上升沿中断        
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 执行WOR操作
// 输入参数 : uint8_t cLength  0 进入睡眠模式。  1 进入接收模式。
//            
// 返回参数 : 无
// 说明     :  DIO3做WOR唤醒中断
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_WORexecute(uint8_t cLength)
{
    unsigned long int i=600000; 
    switch(cLength)
    {
        case 0://进入睡眠模式
                LSD_RF_DIO3_IE =0;      //关闭中断
//                Sleep_RX=0;             //指示睡眠
                LSD_RF_SleepMode();     //进入睡眠
          //      LSD_Sleep_Timerout();   //开启睡眠定时器
                break;
        case 1://进入接收模式
               LSD_RF_DIO3_IE =0;          //关闭中断
//               Sleep_RX=1;                 //指示接收
               LSD_RF_SleepMode();         //进入睡眠 
               LSD_RF_ClearFIFO();         //清FIFO 
               LSD_RF_WriteReg(REG_OPMODE, (RF_OPMODE_SEQUENCER_ON|RF_OPMODE_LISTEN_OFF | RF_OPMODE_RECEIVER));//进入接收
               while (((LSD_RF_ReadReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00)&&i)i--; // Wait for ModeReady
               LSD_RF_DIO3_IFG=0;          //清除中断标志位
               LSD_RF_DIO3_IE =1;          //开启中断
             //  LSD_RX_Timerout();          //开启接收定时器
               break;
        default:break;
    }

}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 退出WOR,滞留在sdandby模拟式
// 输入参数 : 无
// 返回参数 : 无
// 说明     : 退出WOR,将改变过的寄存器恢复到寄存器数组中的值
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_WOR_Exit(void)
{
   //关闭中断
    LSD_RF_DIO3_IFG=0;   //清除中断标志位
    LSD_RF_DIO3_IE =0;  //关闭中断
  //  TimerA_Init();      //重新初始化定时器，关闭定时器
    //恢复寄存器
    LSD_RF_StandbyMode();                //进入standby模式
    LSD_RF_WriteReg(REG_DIOMAPPING1, 0x00); // 恢复原值
    LSD_RF_WriteReg(REG_PREAMBLELSB,0x04);   //恢复原值
    LSD_RF_WriteReg(REG_SYNCCONFIG,0x9A);   //恢复原值
    LSD_RF_WriteReg(REG_SYNCVALUE1,0xD3);    //恢复原值
    LSD_RF_WriteReg(REG_SYNCVALUE2,0x91);    //恢复原值
//    LSD_RF_WriteReg(REG_PACKETCONFIG1,0x90);   //恢复原值   
}

////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 唤醒函数
// 输入参数 : 无
//            
// 返回参数 : 无
// 说明     : 前导唤醒方式
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_AwakePkt(void)
{
    LSD_RF_DIO0_IFG=0;                   //清除MCU标志位
    LSD_RF_DIO0_IE=0;                    //关闭中断
    LSD_RF_StandbyMode();               //进入standby模式
    if(HIGH_POWER==1)   //如果High Power 设置enable（+20dbm capability on PA_BOOST）
    {
        LSD_RF_WriteReg(REG_OCP,0x0F);   
        LSD_RF_WriteReg(REG_TESTPA1,0x5D);   
        LSD_RF_WriteReg(REG_TESTPA2,0x7C);
    }
    LSD_RF_ClearFIFO();    //清除FIFO
//     P6OUT |= BIT5;     //测试探针
    LSD_RF_WriteReg(REG_OPMODE, (RF_OPMODE_SEQUENCER_ON|RF_OPMODE_LISTEN_OFF | RF_OPMODE_TRANSMITTER));  //切换到发送
    DelayMs(4400);    //实际示波器测试发送时间为4.2s
//     P6OUT &=~ BIT5;    //测试探针
    LSD_RF_StandbyMode();               //进入standby模式
    if(HIGH_POWER==1)                 //退出发送后，注意一定要将Hing Power Disable。
    {
        LSD_RF_WriteReg(REG_OCP,0x1B);   
        LSD_RF_WriteReg(REG_TESTPA1,0x55);   
        LSD_RF_WriteReg(REG_TESTPA2,0x70); 
    }
}

////////////////////////////////////////////////////////////////////////////////////
////// 功能描述 : RSSI功能初始化
////// 输入参数 : 无
//////            
////// 返回参数 : 无
////// 说明     : 
////////////////////////////////////////////////////////////////////////////////////
//void LSD_RF_RSSIInit(void)
//{
////     //初始化映射中断口
//    LSD_RF_DIO3_IFG=0;   //清除中断标志位
//    LSD_RF_DIO3_SEL=0;   //不选择第二功能（MSP430默认为第一功能）
//    LSD_RF_DIO3_DIR=0;   //中断做输入
//    LSD_RF_DIO3_IES=0;   //上升沿中断        
//    LSD_RF_DIO3_IE =0;  //关闭中断
//    LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO3_10|RF_DIOMAP1_DIO0_PLD_RDY); // 映射DIO3 = SYNC_ADDR（也可以用DIO0，这里用DIO3为例子）
//    LSD_RF_DIO3_IFG=0;          //清除中断标志位
//    LSD_RF_DIO3_IE =1;          //开启中断   
//}

//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : Trigger a RSSI Measurement 触发一次RSSI测量
//// 输入参数 : 无         
//// 返回参数 : 无
//// 说明     : 
//////////////////////////////////////////////////////////////////////////////////
void LSD_RF_TriggerRssi(void)
{
    LSD_RF_WriteReg(REG_RSSICONFIG,0x01);   
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 计算RSSI值
//// 输入参数 : 无
////            
//// 返回参数 : 无
//// 说明     : 
//////////////////////////////////////////////////////////////////////////////////
unsigned char LSD_RF_GetRSSI(void)
{
    unsigned char cRssi;
    cRssi = LSD_RF_ReadReg(REG_RSSIVALUE);
    cRssi = cRssi/2;
    return cRssi;
}
////////////////////////////////////////////////////////////////////////////////////
////// 功能描述 : PreambleDetectorON
////// 输入参数 : 无
//////            
////// 返回参数 : 无
////// 说明     : 启动Preamble检测功能
////////////////////////////////////////////////////////////////////////////////////
//void LSD_RF_PreambleDetectorON(void)
//{  
//    //配置参数
//    LSD_RF_WriteReg(REG_DIOMAPPING2, 0x0F);
//    LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO3_01|RF_DIOMAP1_DIO0_PLD_RDY); 
//    LSD_RF_WriteReg(REG_PREAMBLE, 0xCA); // 
//
//    
//}
////////////////////////////////////////////////////////////////////////////////////
////// 功能描述 : test
////// 输入参数 : 无
//////            
////// 返回参数 : 无
////// 说明     : 
////////////////////////////////////////////////////////////////////////////////////
//unsigned char cfei,cfei2;
//void LSD_RF_test(void)
//{
//    
//    cfei = LSD_RF_ReadReg(REG_AFCMSB);
//    cfei2 = LSD_RF_ReadReg(REG_AFCLSB);
//}






















































//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : wor初始化
//// 输入参数 : 无
////            
//// 返回参数 : 无
//// 说明     : 前导（2）+同步(1)         
//////////////////////////////////////////////////////////////////////////////////
//void LSD_RF_WORInit(void)
//{
//    LSD_RF_StandbyMode();                //进入standby模式
//    LSD_RF_DIO0_IFG=0;                   //清除MCU标志位
//    LSD_RF_DIO0_IE=0;                    //关闭中断
//    //设置WOR周期
//    LSD_RF_WriteReg(REG_LISTEN1,0xDA);   //设置ListenResolldle =262ms，ListenResolRX =64us，RSSI&SyncAddress
//    LSD_RF_WriteReg(REG_LISTEN3,0x4E);   //设置接收时间，T_rx=ListenCoefRX*ListenResolRX=0X4E x 64us=4.992ms
//    LSD_RF_WriteReg(REG_LISTEN2,0x0F);   //设置发送时间，T_idle=ListenCoefIdle*ListenResolldle=0X0f x 262ms=3.930s
//    //
//    LSD_RF_WriteReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO3_10); // 映射DIO3 = SYNC_ADDR（也可以用DIO0，这里用DIO3为例子）
//    LSD_RF_WriteReg(REG_RSSITHRESH,0xFA);   //设置RSSI阀值为-125dbm 
//    LSD_RF_WriteReg(REG_PREAMBLELSB,0x02);   //设置2个前导码
//    LSD_RF_WriteReg(REG_SYNCCONFIG,0x82);   //设置1个同步字
////    LSD_RF_WriteReg(REG_SYNCVALUE1,0x55);   //设置1个同步字
//    
//    LSD_RF_WriteReg(REG_PACKETCONFIG1,0x80);   //关闭CRC 
//      
//}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 执行WOR操作
//// 输入参数 : void
////            
//// 返回参数 : 无
//// 说明     :  DIO3做WOR唤醒中断
//////////////////////////////////////////////////////////////////////////////////
//void LSD_RF_WORexecute(void)
//{
//    LSD_RF_StandbyMode();                //进入standby模式
//   //清除标志位
//    LSD_RF_DIO3_IFG=0;   //清除中断标志位
//    LSD_RF_DIO3_SEL=0;   //不选择第二功能（MSP430默认为第一功能）
//    LSD_RF_DIO3_DIR=0;   //中断做输入
//    LSD_RF_DIO3_IES=0;   //上升沿中断 
//    LSD_RF_DIO3_IE =1;  //开启中断 
//    LSD_RF_DIO3_IFG=0;   //清除中断标志位 
//    LSD_RF_WriteReg(REG_OPMODE,0x44);   //启动LISTEN(WOR)
//}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 退出WOR,滞留在sdandby模拟式
//// 输入参数 : 无
//// 返回参数 : 无
//// 说明     : 退出WOR,将改变过的寄存器恢复到寄存器数组中的值
//////////////////////////////////////////////////////////////////////////////////
//void LSD_RF_WOR_Exit(void)
//{
//   //关闭中断
//    LSD_RF_DIO3_IFG=0;   //清除中断标志位
//    LSD_RF_DIO3_IE =0;  //关闭中断
//    //恢复寄存器
//    LSD_RF_StandbyMode();                //进入standby模式
//    LSD_RF_WriteReg(REG_OPMODE,0x04);   //恢复原值
//    LSD_RF_WriteReg(REG_LISTEN1,0x92);   //恢复原值
//    LSD_RF_WriteReg(REG_LISTEN3,0x20);   //恢复原值
//    LSD_RF_WriteReg(REG_LISTEN2,0xF5);   //恢复原值
//    //
//    LSD_RF_WriteReg(REG_DIOMAPPING1, 0x00); // 恢复原值
//    LSD_RF_WriteReg(REG_RSSITHRESH,0xE8);   //恢复原值 
//    LSD_RF_WriteReg(REG_PREAMBLELSB,0x04);   //恢复原值
//    LSD_RF_WriteReg(REG_SYNCCONFIG,0x9A);   //恢复原值
//    LSD_RF_WriteReg(REG_SYNCVALUE1,0xD3);    //恢复原值
//    LSD_RF_WriteReg(REG_PACKETCONFIG1,0x90);   //恢复原值   
//}
