/*******************************************************************************
 *   Filename:       setmodel.h
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    统计模块油箱模型设置

					 双击选中 otr 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 Otr 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 OTR 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   在 app_cfg.h 中指定本任务的 优先级  （ APP_TASK_COMM_PRIO     ）
 *                                            和 任务堆栈（ APP_TASK_COMM_STK_SIZE ）大小
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	SET_MODEL_H
#define	SET_MODEL_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "asynctmr.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <formatio.h> 
#include <comconfig.h>         
#include "pc_csnr.h"
#include "includes.h"

/*******************************************************************************
* MACROS
*/
//ODBC 数据源(32 位),DSN
#define		ODBC_DNS	"MySql32"


/*******************************************************************************************
/结构体																				 
*******************************************************************************************/
typedef struct _stcModPot_						//IC 卡cd参数
{
	uint16_t	HigVal;								//压力值
	uint16_t	DipVal;								//油量值
}stcModPot;

//油箱模型点，高度，油量
// 4 bytes
//typedef struct _stcModPot_					//
//{
//	uint16	Hig;								// 2 		高度
//	uint16	Oil;								// 2 		油量
//}stcModPot;
//运算用油箱模型
//408 bytes
typedef struct _stcCalcModel_					
{
	stcModPot	sModPot[100];					// 4*100 	内容
	uint16		PotNum;							// 2 		模型有效点数 
	uint16		StartOil;                       // 2    	模型初始油量   	
	uint16		ModelNum;						// 1		模型编号
//	uint8		valid;							// 1        使用
	uint16		CrcCheck;						// 2 		CrcCheck;
}stcCalcModel;



/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	stcCalcModel	gsCalcModel;
extern	int cvi_hdbc_mysql_handle;			//数据库连接句柄
extern	int globalvalue;
extern	int db_panelHandle;

/*******************************************************************************
* 名    称： ReadRecFromDB
* 功    能： 从数据库表中，读取数据记录
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-06
* 修    改：
* 修改日期：
* 备    注： 从数据库中读取指定的数据，并返回 
*******************************************************************************/
extern int	ReadRecFromDB(char *tabelname,int	keyval);

/*******************************************************************************
* 名    称： CreateDBTable
* 功    能： 创建数据表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注：DBBindColInt 
*******************************************************************************/
extern int	CreateDBTable(char *tabelname);

/*******************************************************************************
* 名    称： InsertRecToDB
* 功    能： 插入数据记录
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 由于数据库操作，现建立映射，在赋值改写数据，再数据入库。 
*******************************************************************************/
extern int CVICALLBACK InsertRecToDB (char *tabelname,stcCalcModel *sCalcModel);


/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
