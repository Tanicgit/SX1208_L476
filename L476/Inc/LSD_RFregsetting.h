////////////////////////////////////////////////////////////////////////////////
// 版权:     利尔达科技集团股份有限公司
// 文件名:   LSD_RFregsetting.h
// 版本：    v1.0
// 工作环境: IAR  v5.30
// 作者:     于海波
// 生成日期: 2014.11
// 功能:     
// 相关文件: 
// 修改日志：
////////////////////////////////////////////////////////////////////////////////
#ifndef _LSD_RFregsetting_h_
#define _LSD_RFregsetting_h_

#include "LSD_RFreg.h"
#define  LSD4RF_2X717N10      1
#define  LSD4RF_2S313N10      2
typedef struct {
    unsigned char addr;
    unsigned char val;
}_SX12XX_REG;



//选择一个所用利尔达模块平台型号
#define VERSION        LSD4RF_2S313N10                   



//////////////////////////////////////////////////////////////////////////////////
//// 
////                   以下为LSD4RF_2X717N10和LSD4RF_2S313N10
////
//////////////////////////////////////////////////////////////////////////////////

///////////////////////////////LSD4RF_2X717N10平台///////////////////////////////
#if (VERSION==LSD4RF_2X717N10)
#define  HIGH_POWER    1   //HIGH_POWER 设置
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 寄存器组
//// 说明     : AGC=0，AFC=0，9600，200ohm ，20dbm
//////////////////////////////////////////////////////////////////////////////////
static const _SX12XX_REG LSD_RFregConfig[] = {         // 
     
    {REG_OPMODE,        0x04},           
    {REG_DATAMODUL,     0x00},           
    {REG_BITRATEMSB,    0X0D},//9600bps
    {REG_BITRATELSB,    0X05}, 
    {REG_FDEVMSB,       0x01},// 20KDEV
    {REG_FDEVLSB,       0x48},    
    {REG_FRFMSB,        0X76}, //472MHz
    {REG_FRFMID,        0X00},           
    {REG_FRFLSB,        0X00},           
    {REG_OSC1,          0X41},           
    {REG_AFCCTRL,       0x00},
    {REG_LOWBAT,        0x02},           
    {REG_LISTEN1,       0X92},           
    {REG_LISTEN2,       0XF5},           
    {REG_LISTEN3,       0X20},                      
    {REG_PALEVEL,       0x7F},           
    {REG_PARAMP ,       0X09},           
    {REG_OCP,           0X1B},           
    {REG_SERVED14,      0x40},
    {REG_SERVED15,      0xB0},
    {REG_SERVED16,      0x7B},
    {REG_SERVED17,      0x9B},      
    {REG_LNA ,          0X89},
    {REG_RXBW,          0xC4}, //   31K ,0.25
    {REG_AFCBW,         0X8B},           
    {REG_OOKPEAK,       0X40},           
    {REG_OOKAVG,        0X80},           
    {REG_OOKFIX,        0X06},           
    {REG_AFCFEI,        0X10},        
    {REG_DIOMAPPING1,   0X00},     
    {REG_DIOMAPPING2,   0X0F},     //修改时间----20150108，07->0F                 
    {REG_RSSITHRESH ,   0XFF},     //修改时间----20150108    
    {REG_RXTIMEOUT1 ,   0X00},           
    {REG_RXTIMEOUT2 ,   0X00},           
    {REG_PREAMBLEMSB,   0X00},           
    {REG_PREAMBLELSB,   0X04},            
    {REG_SYNCCONFIG,    0X9A},           
    {REG_SYNCVALUE1,    0XD3},
    {REG_SYNCVALUE2,    0X91},
    {REG_SYNCVALUE3,    0XD3},     
    {REG_SYNCVALUE4,    0X91},     
    {REG_SYNCVALUE5,    0X00},           
    {REG_SYNCVALUE6,    0X00},           
    {REG_SYNCVALUE7,    0X00},           
    {REG_SYNCVALUE8,    0X00},           
    {REG_PACKETCONFIG1, 0X90},
    {REG_PAYLOADLENGTH, 66},            // max to 66 bytes
    {REG_NODEADRS,      0X00},           
    {REG_BROADCASTADRS, 0X00},           
    {REG_AUTOMODES,     0X00},           
    {REG_FIFOTHRESH,    0XC2},           
    {REG_PACKETCONFIG2, 0X02},        
    {REG_AESKEY1,       0X00},                       
    {REG_AESKEY2,       0X00},                       
    {REG_AESKEY3,       0X00},                       
    {REG_AESKEY4,       0X00},                       
    {REG_AESKEY5,       0X00},                       
    {REG_AESKEY6,       0X00},                       
    {REG_AESKEY7,       0X00},                       
    {REG_AESKEY8,       0X00},                       
    {REG_AESKEY9,       0X00},                       
    {REG_AESKEY10,      0X00},                       
    {REG_AESKEY11,      0X00},                       
    {REG_AESKEY12,      0X00},                       
    {REG_AESKEY13,      0X00},                       
    {REG_AESKEY14,      0X00},                       
    {REG_AESKEY15,      0X00},                       
    {REG_AESKEY16,      0X00}, 
    {REG_PREAMBLE,      0XCA},          //修改时间----20150108，开启Premble
    {REG_TESTLNA,       0x2D},
    {REG_TESTPA1,       0x55},
    {REG_TESTPA2,       0x70},
    {REG_TESTDAGC,      0x30},
    {REG_TESTAFC,       0x00},  
};
//470-500Mhz频率表
static const unsigned char Freq_Cal_Tab[]=
{
      0x75,0x80,0x00,		//	470.0	MHZ
      0x75,0x8C,0xE0,		//	470.2	MHZ
      0x75,0x99,0xAD,		//	470.4	MHZ
      0x75,0xA6,0x7A,		//	470.6	MHZ
      0x75,0xB3,0x46,		//	470.8	MHZ
      0x75,0xC0,0x13,		//	471.0	MHZ
      0x75,0xCC,0xE0,		//	471.2	MHZ
      0x75,0xD9,0xAD,		//	471.4	MHZ
      0x75,0xE6,0x7A,		//	471.6	MHZ
      0x75,0xF3,0x46,		//	471.8	MHZ
      0x76,0x00,0x13,		//	472.0	MHZ
      0x76,0x0C,0xE0,		//	472.2	MHZ
      0x76,0x19,0xAD,		//	472.4	MHZ
      0x76,0x26,0x7A,		//	472.6	MHZ
      0x76,0x33,0x47,		//	472.8	MHZ
      0x76,0x40,0x13,		//	473.0	MHZ
      0x76,0x4C,0xE0,		//	473.2	MHZ
      0x76,0x59,0xAD,		//	473.4	MHZ
      0x76,0x66,0x7A,		//	473.6	MHZ
      0x76,0x73,0x47,		//	473.8	MHZ
      0x76,0x80,0x13,		//	474.0	MHZ
      0x76,0x8C,0xE0,		//	474.2	MHZ
      0x76,0x99,0xAD,		//	474.4	MHZ
      0x76,0xA6,0x7A,		//	474.6	MHZ
      0x76,0xB3,0x47,		//	474.8	MHZ
      0x76,0xC0,0x13,		//	475.0	MHZ
      0x76,0xCC,0xE0,		//	475.2	MHZ
      0x76,0xD9,0xAD,		//	475.4	MHZ
      0x76,0xE6,0x7A,		//	475.6	MHZ
      0x76,0xF3,0x47,		//	475.8	MHZ
      0x77,0x00,0x13,		//	476.0	MHZ
      0x77,0x0C,0xE0,		//	476.2	MHZ
      0x77,0x19,0xAD,		//	476.4	MHZ
      0x77,0x26,0x7A,		//	476.6	MHZ
      0x77,0x33,0x47,		//	476.8	MHZ
      0x77,0x40,0x14,		//	477.0	MHZ
      0x77,0x4C,0xE0,		//	477.2	MHZ
      0x77,0x59,0xAD,		//	477.4	MHZ
      0x77,0x66,0x7A,		//	477.6	MHZ
      0x77,0x73,0x47,		//	477.8	MHZ
      0x77,0x80,0x14,		//	478.0	MHZ
      0x77,0x8C,0xE0,		//	478.2	MHZ
      0x77,0x99,0xAD,		//	478.4	MHZ
      0x77,0xA6,0x7A,		//	478.6	MHZ
      0x77,0xB3,0x47,		//	478.8	MHZ
      0x77,0xC0,0x14,		//	479.0	MHZ
      0x77,0xCC,0xE0,		//	479.2	MHZ
      0x77,0xD9,0xAD,		//	479.4	MHZ
      0x77,0xE6,0x7A,		//	479.6	MHZ
      0x77,0xF3,0x47,		//	479.8	MHZ
      0x78,0x00,0x14,		//	480.0	MHZ
      0x78,0x0C,0xE0,		//	480.2	MHZ
      0x78,0x19,0xAD,		//	480.4	MHZ
      0x78,0x26,0x7A,		//	480.6	MHZ
      0x78,0x33,0x47,		//	480.8	MHZ
      0x78,0x40,0x14,		//	481.0	MHZ
      0x78,0x4C,0xE0,		//	481.2	MHZ
      0x78,0x59,0xAD,		//	481.4	MHZ
      0x78,0x66,0x7A,		//	481.6	MHZ
      0x78,0x73,0x47,		//	481.8	MHZ
      0x78,0x80,0x14,		//	482.0	MHZ
      0x78,0x8C,0xE1,		//	482.2	MHZ
      0x78,0x99,0xAD,		//	482.4	MHZ
      0x78,0xA6,0x7A,		//	482.6	MHZ
      0x78,0xB3,0x47,		//	482.8	MHZ
      0x78,0xC0,0x14,		//	483.0	MHZ
      0x78,0xCC,0xE1,		//	483.2	MHZ
      0x78,0xD9,0xAD,		//	483.4	MHZ
      0x78,0xE6,0x7A,		//	483.6	MHZ
      0x78,0xF3,0x47,		//	483.8	MHZ
      0x79,0x00,0x14,		//	484.0	MHZ
      0x79,0x0C,0xE1,		//	484.2	MHZ
      0x79,0x19,0xAD,		//	484.4	MHZ
      0x79,0x26,0x7A,		//	484.6	MHZ
      0x79,0x33,0x47,		//	484.8	MHZ
      0x79,0x40,0x14,		//	485.0	MHZ
      0x79,0x4C,0xE1,		//	485.2	MHZ
      0x79,0x59,0xAD,		//	485.4	MHZ
      0x79,0x66,0x7A,		//	485.6	MHZ
      0x79,0x73,0x47,		//	485.8	MHZ
      0x79,0x80,0x14,		//	486.0	MHZ
      0x79,0x8C,0xE1,		//	486.2	MHZ
      0x79,0x99,0xAE,		//	486.4	MHZ
      0x79,0xA6,0x7A,		//	486.6	MHZ
      0x79,0xB3,0x47,		//	486.8	MHZ
      0x79,0xC0,0x14,		//	487.0	MHZ
      0x79,0xCC,0xE1,		//	487.2	MHZ
      0x79,0xD9,0xAE,		//	487.4	MHZ
      0x79,0xE6,0x7A,		//	487.6	MHZ
      0x79,0xF3,0x47,		//	487.8	MHZ
      0x7A,0x00,0x14,		//	488.0	MHZ
      0x7A,0x0C,0xE1,		//	488.2	MHZ
      0x7A,0x19,0xAE,		//	488.4	MHZ
      0x7A,0x26,0x7A,		//	488.6	MHZ
      0x7A,0x33,0x47,		//	488.8	MHZ
      0x7A,0x40,0x14,		//	489.0	MHZ
      0x7A,0x4C,0xE1,		//	489.2	MHZ
      0x7A,0x59,0xAE,		//	489.4	MHZ
      0x7A,0x66,0x7A,		//	489.6	MHZ
      0x7A,0x73,0x47,		//	489.8	MHZ
      0x7A,0x80,0x14,		//	490.0	MHZ
      0x7A,0x8C,0xE1,		//	490.2	MHZ
      0x7A,0x99,0xAE,		//	490.4	MHZ
      0x7A,0xA6,0x7A,		//	490.6	MHZ
      0x7A,0xB3,0x47,		//	490.8	MHZ
      0x7A,0xC0,0x14,		//	491.0	MHZ
      0x7A,0xCC,0xE1,		//	491.2	MHZ
      0x7A,0xD9,0xAE,		//	491.4	MHZ
      0x7A,0xE6,0x7B,		//	491.6	MHZ
      0x7A,0xF3,0x47,		//	491.8	MHZ
      0x7B,0x00,0x14,		//	492.0	MHZ
      0x7B,0x0C,0xE1,		//	492.2	MHZ
      0x7B,0x19,0xAE,		//	492.4	MHZ
      0x7B,0x26,0x7B,		//	492.6	MHZ
      0x7B,0x33,0x47,		//	492.8	MHZ
      0x7B,0x40,0x14,		//	493.0	MHZ
      0x7B,0x4C,0xE1,		//	493.2	MHZ
      0x7B,0x59,0xAE,		//	493.4	MHZ
      0x7B,0x66,0x7B,		//	493.6	MHZ
      0x7B,0x73,0x47,		//	493.8	MHZ
      0x7B,0x80,0x14,		//	494.0	MHZ
      0x7B,0x8C,0xE1,		//	494.2	MHZ
      0x7B,0x99,0xAE,		//	494.4	MHZ
      0x7B,0xA6,0x7B,		//	494.6	MHZ
      0x7B,0xB3,0x47,		//	494.8	MHZ
      0x7B,0xC0,0x14,		//	495.0	MHZ
      0x7B,0xCC,0xE1,		//	495.2	MHZ
      0x7B,0xD9,0xAE,		//	495.4	MHZ
      0x7B,0xE6,0x7B,		//	495.6	MHZ
      0x7B,0xF3,0x47,		//	495.8	MHZ
      0x7C,0x00,0x14,		//	496.0	MHZ
      0x7C,0x0C,0xE1,		//	496.2	MHZ
      0x7C,0x19,0xAE,		//	496.4	MHZ
      0x7C,0x26,0x7B,		//	496.6	MHZ
      0x7C,0x33,0x48,		//	496.8	MHZ
      0x7C,0x40,0x14,		//	497.0	MHZ
      0x7C,0x4C,0xE1,		//	497.2	MHZ
      0x7C,0x59,0xAE,		//	497.4	MHZ
      0x7C,0x66,0x7B,		//	497.6	MHZ
      0x7C,0x73,0x48,		//	497.8	MHZ
      0x7C,0x80,0x14,		//	498.0	MHZ
      0x7C,0x8C,0xE1,		//	498.2	MHZ
      0x7C,0x99,0xAE,		//	498.4	MHZ
      0x7C,0xA6,0x7B,		//	498.6	MHZ
      0x7C,0xB3,0x48,		//	498.8	MHZ
      0x7C,0xC0,0x14,		//	499.0	MHZ
      0x7C,0xCC,0xE1,		//	499.2	MHZ
      0x7C,0xD9,0xAE,		//	499.4	MHZ
      0x7C,0xE6,0x7B,		//	499.6	MHZ
      0x7C,0xF3,0x48,		//	499.8	MHZ
      0x7D,0x00,0x14		//	500.0	MHZ
};

static const _SX12XX_REG DateRate[]={
    //9.6Kbps
    {REG_BITRATEMSB,    0X0D},//9600bps
    {REG_BITRATELSB,    0X05},
    {REG_FDEVMSB,       0x01},// 19KDEV
    {REG_FDEVLSB,       0x48},
    {REG_RXBW,          0xC4}, //   31K ,0.25  
    //4.8kbps
    {REG_BITRATEMSB,    0X1A},//4800bps
    {REG_BITRATELSB,    0X0B},
    {REG_FDEVMSB,       0x01},// 16KDEV
    {REG_FDEVLSB,       0x06},
    {REG_RXBW,          0x44}, //   31.3K ,4   
    //20kbps
    {REG_BITRATEMSB,    0X06},//20kbps
    {REG_BITRATELSB,    0X40},
    {REG_FDEVMSB,       0x01},// 30KDEV
    {REG_FDEVLSB,       0xEC},
    {REG_RXBW,          0x4B}, // 50K ,4
    //40kbps
    {REG_BITRATEMSB,    0X03},//40kbps
    {REG_BITRATELSB,    0X20},
    {REG_FDEVMSB,       0x02},// 40KDEV
    {REG_FDEVLSB,       0x8F},
    {REG_RXBW,          0x43}, //62.5K ,4
};
///////////////////////////////LSD4RF_2S313N10平台///////////////////////////////

#elif (VERSION==LSD4RF_2S313N10)
#define  HIGH_POWER    0        //注意LSD4RF_2S313N10平台的HIGH_POWER一定要设置成0，不能改成1
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 寄存器组
//// 说明     : AGC=0，AFC=0，9600bps，200ohm ，13dbm
//////////////////////////////////////////////////////////////////////////////////
static const _SX12XX_REG LSD_RFregConfig[] = {         // 
     
    {REG_OPMODE,        0x04},           
    {REG_DATAMODUL,     0x00},           
    {REG_BITRATEMSB,    0X0D},//9600bps
    {REG_BITRATELSB,    0X05},        
    {REG_FDEVMSB,       0x01},// 40KDEV
    {REG_FDEVLSB,       0x48},             
    {REG_FRFMSB,        0X6C}, //433.2MHz
    {REG_FRFMID,        0X4C},           
    {REG_FRFLSB,        0XCD},           
    {REG_OSC1,          0X41},           
    {REG_AFCCTRL,       0x00},
    {REG_LOWBAT,        0x02},           
    {REG_LISTEN1,       0X92},           
    {REG_LISTEN2,       0XF5},           
    {REG_LISTEN3,       0X20},                      
    {REG_PALEVEL,       0x9F},   //13dbm           
    {REG_PARAMP ,       0X09},           
    {REG_OCP,           0X1B},           
    {REG_SERVED14,      0x40},
    {REG_SERVED15,      0xB0},
    {REG_SERVED16,      0x7B},
    {REG_SERVED17,      0x9B},
    {REG_LNA ,          0X89},           
    {REG_RXBW,          0xC4}, //   31K   0.25  
    {REG_AFCBW,         0X8B},           
    {REG_OOKPEAK,       0X40},           
    {REG_OOKAVG,        0X80},           
    {REG_OOKFIX,        0X06},           
    {REG_AFCFEI,        0X10},           
    {REG_DIOMAPPING1,   0X00},     
    {REG_DIOMAPPING2,   0X07},                      
    {REG_RSSITHRESH ,   0XE8},           
    {REG_RXTIMEOUT1 ,   0X00},           
    {REG_RXTIMEOUT2 ,   0X00},           
    {REG_PREAMBLEMSB,   0X00},           
    {REG_PREAMBLELSB,   0X04},            
    {REG_SYNCCONFIG,    0X9A},           
    {REG_SYNCVALUE1,    0XD3},
    {REG_SYNCVALUE2,    0X91},
    {REG_SYNCVALUE3,    0XD3},     
    {REG_SYNCVALUE4,    0X91},     
    {REG_SYNCVALUE5,    0X00},           
    {REG_SYNCVALUE6,    0X00},           
    {REG_SYNCVALUE7,    0X00},           
    {REG_SYNCVALUE8,    0X00},           
    {REG_PACKETCONFIG1, 0X90},
    {REG_PAYLOADLENGTH, 66},            // max to 66 bytes
    {REG_NODEADRS,      0X00},           
    {REG_BROADCASTADRS, 0X00},           
    {REG_AUTOMODES,     0X00},           
    {REG_FIFOTHRESH,    0XC2},           
    {REG_PACKETCONFIG2, 0X02},     
    {REG_AESKEY1,       0X00},                       
    {REG_AESKEY2,       0X00},                       
    {REG_AESKEY3,       0X00},                       
    {REG_AESKEY4,       0X00},                       
    {REG_AESKEY5,       0X00},                       
    {REG_AESKEY6,       0X00},                       
    {REG_AESKEY7,       0X00},                       
    {REG_AESKEY8,       0X00},                       
    {REG_AESKEY9,       0X00},                       
    {REG_AESKEY10,      0X00},                       
    {REG_AESKEY11,      0X00},                       
    {REG_AESKEY12,      0X00},                       
    {REG_AESKEY13,      0X00},                       
    {REG_AESKEY14,      0X00},                       
    {REG_AESKEY15,      0X00},                       
    {REG_AESKEY16,      0X00},                                  
    {REG_TESTLNA,       0x2D},
    {REG_TESTPA1,       0x55},
    {REG_TESTPA2,       0x70},
    {REG_TESTDAGC,      0x30},
    {REG_TESTAFC,       0x00},
    
};
//433M频点
static const unsigned char Freq_Cal_Tab[]=
{
      0x6C,0x40,0x00,		//	433.0	MHZ
      0x6C,0x4C,0xCD,		//	433.2	MHZ
      0x6C,0x59,0x9A,		//	433.4	MHZ
      0x6C,0x66,0x67,		//	433.6	MHZ
      0x6C,0x73,0x34,		//	433.8	MHZ
      0x6C,0x80,0x01,		//	434.0	MHZ
      0x6C,0x8C,0xCE,		//	434.2	MHZ
      0x6C,0x99,0x9B,		//	434.4	MHZ
      0x6C,0xA6,0x68,		//	434.6	MHZ
      0x6C,0xB3,0x35,		//	434.8	MHZ
      0x6C,0xC0,0x02,		//	435.0	MHZ
};
#endif


#endif
