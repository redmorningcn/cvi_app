/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    设置统计模块参数。 
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	SET_PARA_H
#define	SET_PARA_H


/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "cvi_setpara.h"

#include "includes.h"



#include "modedata.h"   
#include "cvi_config.h"


/********************************************************************************************/
/* Constants																					*/
/********************************************************************************************/
//uir文件名
//uir文件名
#define		UIR_SETPARA_NAME		"cvi_setpara.uir"
//参数配置文件名																																									                             
#define		MAX_PATHNAME_LEN		512
#define		SETPRAR_FILE_NAME		"cvi_setpara.ini"


#define		DATA_CARD			0x0001			//数据卡
#define		DENSITY_CARD		0x0020			//密度卡
#define		MODEL_CARD			0x0040			//参数模型卡
#define		TIME_CARD			0x0100			//时间卡
#define		HIGHT_CARD			0x0200			//高度调整卡
#define		COPY_CARD			0x0400			//FLASH复制卡
#define		MODEL_SELECT_CARD	0x1000			//模型选择卡
#define		FIX_CARD			0x2000			//装车卡
#define		COPY_FRAM_CARD		0x4000			//铁电拷贝卡

#define		SET_DATA_CARD		0x0080			//置数卡
#define		DEBUG_CARD			0x0800			//调试复制卡
#define		DATA_CARD_DIS		0x10000			//数据卡
#define		DATA_CARD_FIN		0x20000			//数据卡

#define		EXPAND_CARD			0x8000			//扩展卡
#define		SYS_RUN_PARA		0x40000	
#define		CLEAR_ALL			0x80000			//设置运行参数

#define		RST_SYS				0x100000		//系统复位
#define		CALC_PARA           0x200000		//
#define		RUN_MODEL_PARA      0x400000		//运算模型卡




//定义打开配置串口空间名称


/********************************************************************************************/
//结构体																				    */
/********************************************************************************************/

//时间----------------------------------------
typedef		struct	_stcTime_
{
	uint8_t	Sec;
	uint8_t	Min;
	uint8_t	Hour;
	uint8_t	Date;
	uint8_t	Month;
	uint8_t	Year;
	uint16_t	CrcCheck;
}stcTime;
 
//机车信息   车型+车号
//4 bytes
typedef struct {     
 	uint16	Type;				//机车类型	2	参见机车类型代码表
 	uint16	Num;				//机车号		2	
} stcLocoId;

//产品信息:型号 + 编号
//12 bytes
typedef struct _StrProductInfo {
	u32   		        Type;			            //产品类别
	u32   		        Id;				            //产品编号	16110002
	stcLocoId		    LocoId;		                //机车信息	104(DF4B) - 1000
    u16                 HwVer;                      //硬件版本
    u16                 SwVer;                      //软件版本
    u16                 LoadingTime;                //装车时间
    u16                 LoadingStaff;               //装车人员
    u16                 RepairTime;                 //维修时间
    u16                 RepairStaff;                //维修人员
    u8                  Rsv[12];                    //预留12个
}StrProductInfo;


/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
//串口结构体及通讯
extern	int				l_eqiupmentcode;		//装置命令码，操作面板控制
extern	StrProductInfo  gstrProductInfo;		//产品参数


/********************************************************************************************/
/* Prototypes																				*/
/********************************************************************************************/

/********************************************************************************************/
/* 串口设置参数      																		*/
//通过l_eqiupmentcode变量控制设置过程。
//此函数需要循环执行，且能外部设置 l_eqiupmentcode
/********************************************************************************************/
void 	Com_SetParaTask(void);		

/********************************************************************************************/
//载并显示面板。	redmoringcn 20170930						            
/********************************************************************************************/
void 	LoadCsncSetparaPanel(void);

/********************************************************************************************/
//读系统时间，转换为stcTime结构
/********************************************************************************************/
void     ReadTime(stcTime * sTime);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
