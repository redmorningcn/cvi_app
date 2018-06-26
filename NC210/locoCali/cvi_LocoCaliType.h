/**************************************************************************/
//author:redmorningcn 20180621
//LKJ工况信号校准结构体定义
/**************************************************************************/
#ifndef		CVI_LOCOCALI_TYPE_H_
#define		CVI_LOCOCALI_TYPE_H_ 	1

#include <userint.h>
#include <includes.h>

#ifdef __cplusplus
    extern "C" {
#endif
		
#define		LOCO_GROUP_NUM  		(6)			/* 有效校准组			*/	
#define		LOCO_CALI_BASE_ADDR		(340)		/* 工况校准存储基地址	*/
		
//校准结构体		
typedef struct _strLocoCali_
{
	u16		lowstandard;
	u16		lowmeasure;
	u16		higstandard;
	u16		higmeasure;
	u16		send;
	u16		rec16;
	u32		ansyflg;				//同步标识
	
	u8		califlg :	1;			//开始校准标识
	u8		lowflg:		1;			//低位读标识
	u8		higflg:		1;			//高位读标识
	u8		calisend:	1;			//校准发送标识

	u8		tmpflg:		4;			//预留
	
	u8		tmp8[3];				//预留
	
	u16		line;				
	s16		zero;
}strLocoCali;


/**************************************************************
* Description  : 校准参数
* Author       : 2018/5/22 星期二, by redmorningcn
*/

typedef struct {
    u32     line;       //修正线性度  
    int16   Delta;      //修正偏差
    int16   tmp;        //预留

}strLocoCalibration;

/**************************************************************
* Description  : 修正参数表
* Author       : 2018/5/22 星期二, by redmorningcn
*/
typedef struct{
    union   {
        struct{
            strLocoCalibration  VccVol;         //电平
            strLocoCalibration  QY_Vol;         //
            strLocoCalibration  ZD_Vol;         //
            strLocoCalibration  XQ_Vol;         //
            strLocoCalibration  XH_Vol;         //
            strLocoCalibration  LW_Vol;         //
        };
        strLocoCalibration      CaliBuf[10];
    };
}strLocoCaliTable;


/**************************************************************
* Description  : 函数声明
* Author       : 2018/5/24 星期二, by redmorningcn
*/
extern	void	InitLocoCaliCtrlId(void);
extern	void	LocoCaliCommcode(void)	;
extern	void	LocoCaliDisplay(void)	;
extern	void	GetLocoCaliCtrlVal(void);   
extern	void	CtrlDimmedSendControl(u8	dimmed);  
extern	void	CtrlDimmedControl(u8 id);
extern	void	MeasureCtrlSetVal(void);  
extern	void	GetRecLocoCaliInfo(void);


#ifdef __cplusplus
    }
#endif

#endif
