/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    统计模块油箱模型设置
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	MODEL_DATA_H
#define	MODEL_DATA_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <formatio.h> 
#include "includes.h"   


/*******************************************************************************************
/结构体																				 
*******************************************************************************************/
typedef struct _stcModPot_						//IC 卡cd参数
{
	unsigned short	HigVal;								//压力值
	unsigned short	DipVal;								//油量值
}stcModPot;

typedef struct _stcCalcModel_					
{
	stcModPot			sModPot[100];					// 4*100 	内容
	unsigned short		PotNum;							// 2 		模型有效点数 
	unsigned short		StartOil;                       // 2    	模型初始油量   	
	unsigned short		ModelNum;						// 1		模型编号
//	uint8		valid;									// 1        使用
	unsigned short		CrcCheck;						// 2 		CrcCheck;
}stcCalcModel;

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
