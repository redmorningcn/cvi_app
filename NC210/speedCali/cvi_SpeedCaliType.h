/**************************************************************************/
//author:redmorningcn 20180629
//LKJ速度信号校准结构体定义
/**************************************************************************/
#ifndef		CVI_SPEEDCALI_TYPE_H_
#define		CVI_SPEEDCALI_TYPE_H_ 		1

#include <userint.h>
#include <includes.h>
//线性定义
#include <cvi_LocoCaliType.h>   
#include <cvi_LKJTestType.h>   


#ifdef __cplusplus
    extern "C" {
#endif
		
#define		SPEED_GROUP_NUM  			(9)			/* 速度信号校准组数			*/
#define		SPEED_TYPE_NUM  			(3)			/* 每组信号校准类型			*/	

#define		SPEED_CALI_BASE_ADDR		(2800)		/* 速度信号校准存储基地址	*/
#define		SPEED_PARA_BASE_ADDR		(ADDR_SPEED_DETECT)		/* 速度信号参数存储基地址	*/

		

/**************************************************************
* Description  : 函数声明
* Author       : 2018/6/29  by redmorningcn
*/
extern	void	SpeedInitCaliCtrlId(void)	;
extern	void	SpeedCaliCommcode(void)		;
extern	void	SpeedCaliDisplay(void)		;
extern	void	SpeedGetCaliCtrlVal(void)	;   
extern	void	SpeedCtrlDimmedSendControl(u8	dimmed);  
extern	void	SpeedCtrlDimmedControl(u8 id);
extern	void	SpeedMeasureCtrlSetVal(void);  
extern	void	SpeedGetRecvCaliInfo(void);

#ifdef __cplusplus
    }
#endif

#endif
