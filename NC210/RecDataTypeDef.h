/*******************************************************************************
* Description  :  定义存储记录的数据结构
* Author       : 2018/5/15 星期二, by redmorningcn
*******************************************************************************/

#ifndef  _RecDataTypeDef_h_
#define  _RecDataTypeDef_h_

#include <includes.h>
#define	 __packed   /* */	

/**************************************************************
* Description  : tax箱通讯-时间格式定义
* Author       : 2018/6/4 星期一, by redmorningcn
*/
typedef struct {
    u32      Sec                 : 6;        // D05~D00：秒
    u32      Min                 : 6;        // D11~D06：分
    u32      Hour                : 5;        // D16~D12：时
    u32      Day                 : 5;        // D21~D17：日
    u32      Mon                 : 4;        // D25~D22：月
    u32      Year                : 6;        // D31~D26：年
} StrLkjTime;                                       // 04 LKJ时间
    
/*******************************************************************************
* Description  : 速度通道存储数据结构
* Author       : 2018/5/15 星期二, by redmorningcn
*******************************************************************************/
typedef struct _stcSpeed
{
    union{
        struct{
            u8  Freq1Lose   :1 ;   //丢脉冲；
            u8  Freq1None   :1 ;   //无信号；
            u8  rec         :4 ;   //预留
            u8  FreqLess    :1 ;   //频率少
            u8  FreqMore    :1 ;   //频率多 
        }Err[2];
        u8 flgs[2];
    }sta;
    u16     phase;
    u16     vcc;
    u16     freq;
    struct _stcCH
    {
        u16     raise;
        u16     fail;
        u16     ratio;    
        u16     hig;
        u16     low;    
    }ch[2];
}sSpeed;

typedef union _strDevicErr
{
    struct{
        u16                  Speed1Comm     : 1;    //D0=1：速度检测板1通讯故障
        u16                  Speed2Comm     : 1;    //D1=1：速度检测板2通讯故障
        u16                  Speed3Comm     : 1;    //D2=1：速度检测板3通讯故障
        u16                  Speed1Lose     : 1;    //D3=1：速度检测板1丢脉冲故障（详见各通道sta）
        u16                  Speed2Lose     : 1;    //D4=1：速度检测板2丢脉冲故障（详见各通道sta）
        u16                  Speed3Lose     : 1;    //D5=1：速度检测板3丢脉冲故障（祥见各通道sta）
        u16                  LocoComm       : 1;    //D6=1：工况信号检测板通讯故障
        u16                  Disp1CommErr   : 1;    //D7=1：一端显示模块通讯故障
        u16                  Disp2CommErr   : 1;    //D8=1：二端显示模块通讯故障
        u16                  TaxCommErr     : 1;    //D9=1：TAX通讯故障
        u16                  FlashErr       : 1;    //D10=1：存储器故障
        u16                  FramErr        : 1;    //D11=1：铁电故障
        u16                  TimeErr        : 1;    //D12=1：时间故障
        u16                  RsvErr         : 3;   //     ：预留
    };
    u32                 Flags;
}strDeviceErr;

/*******************************************************************************
* Description  : 定义空检的flash存储的数据结构（128字节）
* Author       : 2018/5/15 星期二, by redmorningcn
*******************************************************************************/
__packed
typedef  struct _stcFlshRec                 //定义空检记录数据结构
{
    u8   				CmdTpye		        ;//命令类型       1
    u8   				EvtType             ;//事件类型       1
    u16   				LocoType            ;//机车型号       2
    u16   				LocoNbr             ;//机 车 号       2
    u32   				RecordId            ;//记录流水号     4
    
    struct {                                //记录时间        4
        u32      Sec                 : 6    ;// D05~D00：秒
        u32      Min                 : 6    ;// D11~D06：分
        u32      Hour                : 5    ;// D16~D12：时
        u32      Day                 : 5    ;// D21~D17：日
        u32      Mon                 : 4    ;// D25~D22：月
        u32      Year                : 6    ;// D31~D26：年
    };                                                  // 
    
    sSpeed      speed[3]                    ;//速度通道信号   3*24
    
    struct {  
        u16     vcc                         ;//110V电压
        u16     qy                          ;//牵引电压
        u16     xq                          ;//向前电压
        u16     xh                          ;//向后电压
        u16     lw                          ;//零位电压
    }Vol;                                    //工况电压
    
    u32  				Longitude           ;//经度           4
    u32     			Latitude	        ;//纬度           4
    
    u16   				GpsSpeed       :10  ;//GPS速度         2
    u16   				GpsPos         : 3  ;//东西南北半球   2  1东北；2东南；3西北；4西南；其他未知
    u16                 OffHightFlag   : 1  ;//高度调整标志
    u16   				Rsv            : 2  ;//保留           2
    u8                  Rssi                ;//信号强度       1
    u8                  rsvbyte[3]          ;//预留字节
    
    strDeviceErr        Err                 ;//错误标识         4            

    u16   				CrcCheck            ;//校验   2                 
} stcFlshRec;


#endif
