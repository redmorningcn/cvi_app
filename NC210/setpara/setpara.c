/*******************************************************************************
 *   Filename:       SetPara.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *					 参数设置应用，见产品通讯协议。 20180423
 *   Description:    
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "setpara.h"

#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include <formatio.h> 


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
int					l_eqiupmentcode = 0;	//装置命令码，操作面板控制
StrProductInfo  	gstrProductInfo;		//产品参数
StrTargetPara		gstrTargetPara;			//指定地址参数
Unnctrl     		Ctrl;					//系统参数（虚拟）
/********************************************************************************************/
/* local Prototypes																			*/
/********************************************************************************************/


/********************************************************************************************/
//读系统时间，转换为stcTime结构
/********************************************************************************************/
void     ReadTime(stcTime * sTime)
{
	struct tm *ptr;
    time_t lt; 
	
    lt=time(NULL);
    ptr=localtime((time_t*)&lt);				//读系统时间
	
	sTime->Sec 		= (unsigned char)ptr->tm_sec;
	sTime->Min 		= (unsigned char)ptr->tm_min;
	sTime->Hour 	= (unsigned char)ptr->tm_hour;	
	sTime->Date 	= (unsigned char)ptr->tm_mday;	  	
	sTime->Month 	= (unsigned char)ptr->tm_mon+1;
	sTime->Year 	= (unsigned char)ptr->tm_year-100;	
//	printf("%d-%d-%d %d:%d:%d\r\n",sTime->Year ,sTime->Month,sTime->Date,sTime->Hour,sTime->Min,sTime->Sec);
}


extern	int   	g_com1systictimes;
/********************************************************************************************/
/* 串口设置参数      																		*/
//通过l_eqiupmentcode变量控制设置过程。
//此函数需要循环执行，且能外部设置 l_eqiupmentcode
/********************************************************************************************/
void Com_SetParaTask(void)		
{
	unsigned char  buf[256];
	unsigned int   datalen = 0;
	u32			   tmp8;
	
	if(l_eqiupmentcode != 0)					//有设置指令
	{
		datalen = 0;
		
		memcpy(&buf[datalen],(unsigned char *)&l_eqiupmentcode,sizeof(l_eqiupmentcode));
		datalen += sizeof(l_eqiupmentcode);
		
		switch (l_eqiupmentcode)				//根据指令操作，祥见统计模块通讯协议
		{
			stcTime			sTime;  
			unsigned short 	locotype,loconum;

			case CMD_TIME_SET:   
	 						  ReadTime((stcTime *)&sTime);											//取时钟   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);
							  break; 
							  
			case CMD_LOCO_SET:   
							  memcpy(&buf[datalen],(unsigned char *)&gstrProductInfo.LocoId,sizeof(gstrProductInfo.LocoId));
							  datalen += sizeof(gstrProductInfo.LocoId);
							  break; 
			case CMD_PARA_SET:   
							  tmp8 = sizeof(gstrTargetPara.paraaddr) + sizeof(gstrTargetPara.paralen) + gstrTargetPara.paralen;		//地址+数据长度+数据
							  memcpy(&buf[datalen],(unsigned char *)&gstrTargetPara,tmp8);
							  datalen += tmp8;
							  break; 
			case CMD_REC_CLR:  	
			case CMD_SYS_RST:  	
							  break;		
							  
			default:
				break;
		}

		
		memcpy(sCtrl.PC.wr,buf,datalen);			//数据拷贝到控制字符	
		
		sCtrl.PC.ConnCtrl.sendlen 		= datalen;	//发送数据区长度
		sCtrl.PC.ConnCtrl.sourceaddr	= ADDR_SET;	//源地址
		
		sCtrl.PC.ConnCtrl.DestAddr		= ADDR_FIX; //目的地址
		sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 	//序号
		sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		//帧命令字	
	 
		sCtrl.PC.ConnCtrl.SendFlg 		= 1;		//启动发送 （CVI_bsComm,多线程）
	}
	
	l_eqiupmentcode = 0;
}


