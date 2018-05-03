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
#ifndef	RECORDTABLE_H
#define	RECORDTABLE_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include 	"databaseoperate.h"
#include 	"includes.h"   

#include 	<utility.h>
#include 	<ansi_c.h>
#include 	<cvirte.h>		
#include 	<userint.h>
#include 	<formatio.h> 
#include 	"modedata.h"   

#include 	"oilmodel_db.h"
#include	"cvi_config.h"   
#include	"setpara.h"   

/*******************************************************************************
* MACROS
*/
#define		MODEL_TABLE_NAME			"oilmodeltest"

typedef struct	_stcModelOperateCtrl_  
{
	stcCalcModel	wrModel;			//读模型缓存
	stcCalcModel	rdModel;			//写模型缓存
	char			wrStartFlg;
	char			rdStartFlg;
	char			wrEndFlg;			//改写结构体表示（已完成）
	char			rdEndFlg;			//读结构体表示（将进行） 
	
	int				rdRecNum;			//读取的数据序号
	char			ModefyModelFlg;
}stcModelOperateCtrl;

typedef struct	_stcTableCtrl_
{
	int					*phdbc;				//数据库句柄
	char				tablename[24];		//数据表名称
	int					map;				//数据表映射
	int					sql;				//表和映射有效
	stcCalcModel		sMode;				//表要映射的结构体
	stcModelOperateCtrl Operate;
}stcModelTableCtrl;						//数据库表操作


//db控制
typedef struct _stcThreadModel_
{
	//stcModelTableCtrl	*ModelCtrl;
	int					ThreadID;						//该线ID
	int					ThreadExit;						//该线释放标识
} stcThreadModel;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	stcModelTableCtrl	gsSetModelTable;	//模型表
extern	stcOilPara			gsOilPara;			//油量运算参数	
extern	stcThreadModel		gsThreadModel;		//油箱模型线程 （191017）


/*******************************************************************************
* 功    能： 读取指定值得数据表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-06
* 修    改：
* 修改日期：
* 备    注： 从数据库中读取指定的数据，并返回 
*******************************************************************************/
int	ReadModelFromTable(int	keyval);

/*******************************************************************************
* 功    能： 初始化模型表控制表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
void	InitModelTableCtrl(void);

/*******************************************************************************
* 功    能： 创建数据表映射
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
int	CreateModelToTableMap(stcModelTableCtrl * stable);

//----------------------------------------------------------------------------
// 功    能： 初始化模型表数据库操作线程。为实现数据库操作必须开启此线程
// 参    数：
// 作    者： redmornigcn 20171027
//----------------------------------------------------------------------------
int	cvi_InitBspDB(stcThreadModel * T_Ctrl);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
