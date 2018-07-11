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
int					l_eqiupmentcode 	= 0;	// 装置命令码，操作面板控制
int					l_sendcode			= 0;	// 装置发送命令码，应答时使用

StrProductInfo  	gstrProductInfo;			// 产品参数
Unnctrl     		Ctrl;						// 系统参数（虚拟）
strDtuRecData		gstrSendDtuData;			// DTU通讯数据
strDtuRecData		gstrRecDtuData;			// DTU通讯数据


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
	unsigned char  	buf[256];
	unsigned int   	datalen = 0;
	u32			   	tmp8;
	static			u32		sendtime;
	u8				tmplen;
	
	if(		l_eqiupmentcode 				!= 0		// 有设置指令 
		&&  sCtrl.PC.ConnCtrl.SendTimeFlg 	== 0		// 有数据正在发送（暂停发送）			
	  )					
	{
		datalen = 0;
		
		memcpy(&buf[datalen],(unsigned char *)&l_eqiupmentcode,sizeof(l_eqiupmentcode));
		datalen += sizeof(l_eqiupmentcode);
					
		switch (l_eqiupmentcode)						// 根据指令操作，祥见统计模块通讯协议
		{
			stcTime			sTime;  

			case CMD_TIME_SET:   
	 						  ReadTime((stcTime *)&sTime);	//取时钟   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);
							  break; 
							  
			case CMD_LOCO_SET:   
							  memcpy(&buf[datalen],(unsigned char *)&gstrProductInfo.LocoId,sizeof(gstrProductInfo.LocoId));
							  datalen += sizeof(gstrProductInfo.LocoId);
							  break; 
			case CMD_PARA_SET: 									// 指定地址设置参数 
			case CMD_DETECT_SET:   								// 写检测板指定地址			
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paraaddr,sizeof(gstrSendDtuData.paraaddr));  
							  datalen += sizeof(gstrSendDtuData.paraaddr);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paralen,sizeof(gstrSendDtuData.paralen));
							  datalen += sizeof(gstrSendDtuData.paralen);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.node,sizeof(gstrSendDtuData.node));
							  datalen += sizeof(gstrSendDtuData.node);
							  
							  tmplen = (u8)gstrSendDtuData.paralen;// 取数据长度
							  									  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.parabuf[0],tmplen);
							  datalen += tmplen;
							  break;
							  
			case CMD_PARA_GET: 									// 指定地址读取参数
			case CMD_DETECT_GET:  								// 读检测板指定地址
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paraaddr,sizeof(gstrSendDtuData.paraaddr));  
							  datalen += sizeof(gstrSendDtuData.paraaddr);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paralen,sizeof(gstrSendDtuData.paralen));
							  datalen += sizeof(gstrSendDtuData.paralen);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.node,sizeof(gstrSendDtuData.node));
							  datalen += sizeof(gstrSendDtuData.node);
							  break;
							  
			case  CMD_RECORD_GET:								// 读指定记录号的书记录
							  	tmp8 = sizeof(gstrSendDtuData.recordnum);
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.recordnum,tmp8);
						      datalen += tmp8;
							  break;	
			case CMD_REC_CLR:  	
			case CMD_SYS_RST:
			case CMD_REC_START:
							  	break;		
							  
			default:
				break;
		}

		memcpy(sCtrl.PC.wr,buf,datalen);						//数据拷贝到控制字符	
		
		sCtrl.PC.ConnCtrl.sendlen 		= datalen;				//发送数据区长度
		sCtrl.PC.ConnCtrl.sourceaddr	= ADDR_SET;				//源地址
		
		sCtrl.PC.ConnCtrl.DestAddr		= ADDR_FIX; 			//目的地址
		sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 				//序号
		sCtrl.PC.ConnCtrl.FrameCode		= 0x00;					//帧命令字	
	 
		sCtrl.PC.ConnCtrl.SendFlg 		= 1;					//启动发送 （CVI_bsComm,多线程）
		sCtrl.PC.ConnCtrl.SendTimeFlg 	= 1;					//启动发送计时（超时判断）
		
		l_sendcode = l_eqiupmentcode;							// 应答时使用（确认是哪个指令的命令）
		sendtime = GetAnsySysTime();							// 开始发送时间
		
		l_eqiupmentcode = 0;

	} else{ 		//没功能通讯时，确认是否进行数据通讯（应答数据）
	
		if(gstrRecDtuData.recechoflg == 1){
			gstrRecDtuData.recechoflg = 0;
			
			datalen = 0;
			sCtrl.PC.ConnCtrl.sendlen 		= datalen;	// 发送数据区长度
			sCtrl.PC.ConnCtrl.sourceaddr	= sCtrl.PC.RxCtrl.DestAddr;	// 源地址
		
			sCtrl.PC.ConnCtrl.DestAddr		= sCtrl.PC.RxCtrl.SourceAddr; // 目的地址
			sCtrl.PC.ConnCtrl.SendFramNum 	= sCtrl.PC.RxCtrl.FramNum; 	//序号(应答接收的帧序号)
			sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		// 帧命令字	
			
			sCtrl.PC.ConnCtrl.SendFlg 		= 1;		// 启动发送 （CVI_bsComm,多线程）
		}
	}
	
	//超时判断
	if(sCtrl.PC.ConnCtrl.SendTimeFlg == 1  ) {
		if(sendtime <= GetAnsySysTime()){
			if(sendtime + 500 < GetAnsySysTime()  ) {	// 发送超时（为接收到应答）
				sCtrl.PC.ConnCtrl.SendTimeFlg 	= 0;
				sCtrl.PC.ConnCtrl.ErrFlg 		= 1;	// 置错误标识
				sCtrl.PC.ConnCtrl.TimeoutFlg	= 1;	// 超时
				sendtime = GetAnsySysTime();  
			}
		} else{
			sendtime = GetAnsySysTime();
		}
	}
}


/*******************************************************************************************
串口数据接收服务
*******************************************************************************************/
void	Com_SetParaRecTask(void)
{
	u16	reclen 	=  sCtrl.PC.RxCtrl.Len; //
	u16	headlen = 0;
	u32	code;
	
	if(		sCtrl.PC.RxCtrl.recvflg 	== 1		&&			// 有数据接收
		   (sCtrl.PC.RxCtrl.DestAddr 	== ADDR_PC 	||
			sCtrl.PC.RxCtrl.DestAddr 	== ADDR_SET)
													&&			// 地址有效
			reclen						!= 0		&&			// 数据长度有效
			
		(	sCtrl.PC.RxCtrl.FrameCode	== SET_FRAME_CODE ||
		 	sCtrl.PC.RxCtrl.FrameCode	== RECORD_FRAME_CODE
		)														// 参数设置指令 
	  )   														// 接收到数据
	{
		sCtrl.PC.RxCtrl.recvflg 		= 0;					// 接收完成标识
		sCtrl.PC.ConnCtrl.SendTimeFlg	= 0;					// 数据接收成功，取消发送计时
		sCtrl.PC.ConnCtrl.ErrFlg 		= 0;					// 错误清除
		
		memcpy((u32 *)&code,sCtrl.PC.rd,sizeof(code));
		
		if(	   (	l_sendcode ==  CMD_DETECT_GET
				||  l_sendcode ==  CMD_PARA_GET
				||  l_sendcode ==  CMD_RECORD_GET  
			   )&&	(l_sendcode ==  code) 
		  ){
			switch(l_sendcode){										// 根据发送命令代码，应答数据（设置指令，只确认应答位）
				case  CMD_TIME_SET:
				case  CMD_LOCO_SET:
				case  CMD_PARA_SET:
				case  CMD_DETECT_SET:
				case  CMD_REC_CLR:
				case  CMD_SYS_RST:
				
					if(sizeof(gstrRecDtuData) > reclen){				//
						memcpy((u8 *)&gstrRecDtuData,sCtrl.PC.rd,reclen); //数据拷贝
					
						if(gstrRecDtuData.code != l_sendcode)			//接收的指令和發送不同
							break;
						
						if(gstrRecDtuData.reply.ack == 1)				// 接收成功，标识应答成功
							gstrRecDtuData.setokflg = 1;
					}
					break;
				
				case CMD_PARA_GET: 										// 指定地址读取参数
				case CMD_DETECT_GET:  									// 读检测板指定地址
					if(sizeof(gstrRecDtuData) >= reclen){
						memcpy((u8 *)&gstrRecDtuData,sCtrl.PC.rd,reclen); 	//数据复制
						
						headlen	= sizeof(gstrRecDtuData.code) + sizeof(gstrRecDtuData.paraaddr) + sizeof(gstrRecDtuData.paralen)+sizeof(gstrRecDtuData.node);
						if(headlen >= reclen){
							gstrRecDtuData.recdatalen 			= 0;
							sCtrl.PC.ConnCtrl.DataErrFlg	= 1;
							break;
						}
						gstrRecDtuData.recdatalen 	= ((u8)reclen - (u8)headlen);	// (有效)数据长度
						gstrRecDtuData.dataokflg 	= 1;			// 数据接收完成
					}
					break;	
					
				//case CMD_RECORD_GET:  								// 读数据记录

				default:
					break;			
			}
		
			l_sendcode = 0;											// 发送命令字清零
		}else if(reclen == sizeof(stcFlshRec)){
			if(gstrSendDtuData.recenableflg == 1)					// 应答允许
			{
				memcpy((u8 *)&gstrRecDtuData,sCtrl.PC.rd,reclen); 	//数据复制
				gstrRecDtuData.recechoflg  = 1;						// 数据应答	
				gstrRecDtuData.recvrecflg  = 1;
			}
		}
	}
}






