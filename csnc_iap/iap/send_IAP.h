/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	SNED_IAP_H
#define	SNED_IAP_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include <IAP.h>

#include "cvi_config.h"  
#include "cvi_file.h"  
#include "cvi_comm.h"  

/********************************************************************************************/
/* Constants																					*/
/********************************************************************************************/
#define     IAP_FRAME_CODE      10 
#define		MY_ADDR				ADDR_PC

#define		COM_START_CODE		0x55
#define		PC_ADDR				0xaa
//#define		HOST_ADDR			0x82
#define		HOST_ADDR			ADDR_FIX
#define		SLAVE_ADDR			0xA1

/*******************************************************************************************
/结构体																				 
*******************************************************************************************/
typedef  struct   _stcIAPPara_
{
    short  	hardver;        //硬件版本
    short  	softver;        //软件版本
    int  	softsize;       //软件大小
    int  	addr;           //当前地址
    int  	framenum;       //帧序号
    short  	code;           //指令码 01，标示有正确的可用
    short  	crc16;
}stcIAPPara;					

//typedef  struct   _stcIAPPara_
//{
//    uint16          HwVer;          //硬件版本
//    uint16          SwVer;          //软件版本
//    uint32          Size;           //软件大小
//    uint32          Addr;           //当前地址
//    uint32          Idx;            //帧序号
//    uint16          Cmd;            //指令码 01，标示有正确的可用
//    uint16          Chk;            //校验
//    uint32          Crc32;          //程序校验码
//    uint16          IdxNbr;         //帧数
//}stcIAPPara;

typedef	struct	_stcIapCtrl_
{
	int		filesize;		//???t′óD?
	int		sendsize;		//ò?·￠?í???t′óD?
	short	sendnum;		//μ±?°Dòo?
	short	recvnum;		//?óê?Dòo?
	char	endflg;			//?áê?±êê?
	char	echoflg;		//ó|′e±êê?
	char	resendflg;		//??·￠±êê?
	char	startflg;
	char	sendeable;	
}stcIapCtrl;

typedef struct  _stcIAPStart_
{
    uint16  HardVer;        //硬件版本
    uint16  SoftVer;        //软件版本
    uint32  SoftSize;       //软件大小
    uint32  Addr;           //当前地址
    uint16  CurNum;         //当前序号
}stcIapStart;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	stcIapCtrl		gsIapCtrl;
extern	stcFileInfo		gsBinFileInfo;

/*******************************************************************************************
数据发送： SendFileData()
*******************************************************************************************/
void	SendIapTask(void);

/*******************************************************************************************
初始化IAP接收任务
*******************************************************************************************/
void	IapRecTask(void);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
