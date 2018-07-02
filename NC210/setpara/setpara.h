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
#include "app_type.h"



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

#define		CMD_REC_START       	0x00000001			//记录马上启动发送
#define		CMD_TIME_SET        	0x00000100			//时间卡（IC/无线）
#define		CMD_LOCO_SET        	0x00002000			//装车卡（IC/无线）
#define		CMD_REC_CLR				0x00080000			//记录清零（无线）
#define		CMD_SYS_RST	        	0x00100000		    //系统复位（无线）
#define		CMD_PARA_SET        	0x00800000		    //写参数（无线）
#define		CMD_PARA_GET        	0x00800001		    //读参数（无线）
#define		CMD_RECORD_GET      	0x01000001		    //读数据记录（无线）
#define		CMD_DETECT_SET      	0x02000000		    //读检测板参数（无线）
#define		CMD_DETECT_GET      	0x02000001		    //写检测板参数（无线）





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
 
//产品信息:型号 + 编号
//12 bytes

typedef struct {
    u8      buf[8];
    u8      ack;
} stcParaReply;

/**************************************************************
* Description  : dtu操作命令
* Author       : 2018/5/25 星期五, by redmorningcn
*/
#pragma pack( 1 )
typedef struct{
    union{
        //strIapdata      iap;

        struct{
            u32     code;
            union{
                stcTime         time;
                stcLocoId       loco;
                stcParaReply    reply;
                u32             recordnum;      //记录号
                struct{                         //指定地址读取
                    u16         paraaddr;
					u8         	paralen;
					u8         	node;
                    u16         parabuf[64];       
                };
            };
        };
		
		stcFlshRec  		Rec;				//数据记录
    };
	
	
////操作标识。接收完后，根据数据置位	
	u8 		setokflg 	:1	;					//设置成功标识
	u8		dataokflg	:1	;					//数据接收完成标识
	u8		recechoflg	:1	;					//数据记录应答，接收数据记录使用（如果该标识置1，接收到数据，应答）
	u8		recenableflg:1	;					//数据记录应答允许
	u8		recvrecflg	:1	;					//数据记录接收成功（和app接口，提示可以对数据记录处理）
	u8		recflg		:3	;					//预留
	
	u8		recdatalen;							//接收数据长度
}strDtuRecData;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
//串口结构体及通讯
extern	int				l_eqiupmentcode;			//装置命令码，操作面板控制
extern	StrProductInfo  gstrProductInfo;			//产品参数
extern	strDtuRecData	gstrSendDtuData;			//发送
extern	strDtuRecData	gstrRecDtuData;				//接收



/********************************************************************************************/
/* Prototypes																				*/
/********************************************************************************************/

/********************************************************************************************/
/* 串口设置参数      																		*/
//通过l_eqiupmentcode变量控制设置过程。
//此函数需要循环执行，且能外部设置 l_eqiupmentcode
/********************************************************************************************/
void 	Com_SetParaTask(void);	

void	Com_SetParaRecTask(void);


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
