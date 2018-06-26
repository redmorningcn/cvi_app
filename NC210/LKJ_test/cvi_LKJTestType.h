/**************************************************************************/
//author:redmorningcn 20180623
//LKJ测试面板
/**************************************************************************/
#ifndef		CVI_LKJTEST_TYPE_H_
#define		CVI_LKJTEST_TYPE_H_ 	1

#include 	<userint.h>
#include 	"includes.h"
#ifdef __cplusplus
    extern "C" {
#endif

		
		
/*******************************************************************************
* Description  : 通道具体检测指标
* Author       : 2018/6/24 星期三, by redmorningcn
*******************************************************************************/
typedef	struct _strSpeedDetect_
{
    /*******************************************************************************
    * Description  : 通道具体指标
    * Author       : 2018/6/24 星期三, by redmorningcn
    *******************************************************************************/
    struct  {
        uint32              period;                         //周期，  0.00-2000000.00us （0.5Hz）
        uint32              freq;                           //频率，  0-100000hz              
        uint16              raise;                          //上升沿，0.00-50.00us
        uint16              fail;                           //下降沿，0.00-50.00us
        uint16              ratio;                          //占空比，0.00-100.00%
        uint16              Vol;                            //低电平，0.00-30.00V
        uint16              Voh;                            //高电平，0.00-30.00V
        uint16				status;                         //通道状态
    }para[2];
    
    uint32  ch1_2phase;                                     //相位差，0.00-360.00°
    uint16  vcc_vol;                                        //供电电压
    uint16  stand_vol;                                      //参考电压
}strSpeedDetect;

/*******************************************************************************
* Description  : 工况信号通道检测数据结构定义
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
typedef	struct _strpara_ {          
    uint16              vcc;                           //预留
    uint16              qy;                             //牵引
    uint16              zd;                             //制动
    uint16              xq;                             //向前
    uint16              xh;                             //向后
    uint16              lw;                             //零位
}strLocoDetect;





extern	void	RecDetectInfoReadCode(void) ;
extern	void	GetRecDetectInfo(void);
extern	void	SpeedDetectDisplay(void);
extern	void	InitSpeedCtrlID(void);
extern	void	InitLocoCtrlID(void);
extern	void	LocoDetectDisplay(void);
extern	void	RecordDisplay(void);


#ifdef __cplusplus
    }
#endif
#endif
