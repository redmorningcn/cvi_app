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

		
//校准结构体		
typedef struct _strLocoCali_
{
	u16		line;				
	u16		zero;
	u16		lowstandard;
	u16		lowmeasure;
	u16		higstandard;
	u16		higmeasure;
	
	u8		califlg :	1;			//开始校准标识
	u8		lowflg:		1;			//低位读标识
	u8		higflg:		1;			//高位读标识
	u8		tmpflg:		5;			//预留
	
	u8		tmp8[3];				//预留
}strLocoCali;


#ifdef __cplusplus
    }
#endif

#endif
