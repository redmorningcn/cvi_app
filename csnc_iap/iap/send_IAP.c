/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/


/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "send_IAP.h"

stcIapStart gsIapStart;		//IAP下载


stcIAPPara	gsIapPara =
{
	0x10,
	0x20,
	0,
	0,
	0,
	0
};

/*******************************************************************************************
数据发送： 	SendCsnrIapDataDeal
将数据按照协议格式发送。
*******************************************************************************************/
void	SendCsnrIapDataDeal(char *buf,int len)
{
	memcpy(sCtrl.PC.wr,buf,len);							//数据拷贝到控制字符		
	sCtrl.PC.ConnCtrl.sendlen 		= len;					//发送数据区长度

	sCtrl.PC.ConnCtrl.sourceaddr	= 0xcA;					//源地址
	sCtrl.PC.ConnCtrl.DestAddr		= HOST_ADDR; 				//目的地址
	sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 				//序号
	sCtrl.PC.ConnCtrl.FrameCode		= IAP_FRAME_CODE;		//帧命令字	

	sCtrl.PC.ConnCtrl.SendFlg 		= 1;					//启动发送 （CVI_bsComm,多线程）
} 	

/*******************************************************************************************
初始化IAP结构体
*******************************************************************************************/
void InitIPACtrl(void)
{
	gsIapCtrl.echoflg 	= 0;
	gsIapCtrl.endflg 	= 0;
	gsIapCtrl.filesize 	= gsBinFileInfo.size;
	gsIapCtrl.recvnum	= 0;
	gsIapCtrl.resendflg = 0;
	gsIapCtrl.sendnum	= 0;
	gsIapCtrl.sendsize  = 0;
	gsIapCtrl.startflg 	= 0;
}


/*******************************************************************************************
数据发送： SendFileData()
*******************************************************************************************/
void	SendIapTask(void)
{
	static	char	buf[256]; 
	static	int		len = 0;
	static	int 	resendtimes = 0;
	int		per;
	short	tmp16;
	
	static	int	sendtime = 0;
	static	uint64_t     crc32   = 0x00000000FFFFFFFFL;


	if( gsIapCtrl.sendeable == 0)
		return;	
	
	if(			gsIapCtrl.startflg
			|| 	gsIapCtrl.echoflg
			|| 	gsIapCtrl.resendflg 
	  )	
	{//
		if(gsIapCtrl.startflg)						//开始下载，发送开始下载指令
		{
			//新增，计算文件crc32校验   180326
			crc32   = 0x00000000FFFFFFFFL; 			//初值
			gsBinFileInfo.deallen 	= 0;			//初值
			while(gsBinFileInfo.deallen < gsBinFileInfo.size)
			{
				int readlen = ReadFileData(gsBinFileInfo.deallen,&buf[0],128);//从文件中读取数据
				gsBinFileInfo.deallen += readlen;
				
				crc32   = GetCrc32Chk( crc32, buf, readlen);
			}
			//新增，180326 
			
			InitIPACtrl();							//初始化控制变量
			
			gsIapPara.softsize 		= gsBinFileInfo.size;
			gsBinFileInfo.deallen 	= 0;
			
			len = 0;

			tmp16 = 0x01;							//开始指令
			memcpy(&buf[len],(char *)&tmp16,sizeof(tmp16));
			len += sizeof(tmp16);
			
			memcpy(&buf[len],(char *)&gsIapPara,sizeof(gsIapPara));
			len +=sizeof(gsIapPara);
			
			//增加crc校验（全文件） 180316
			crc32   = crc32 ^ 0x00000000FFFFFFFFL;
    		crc32  &= 0x00000000FFFFFFFFL;				
			
			memcpy(&buf[len],(char *)&crc32,sizeof(uint32));
			len += sizeof(uint32);			
			//增加crc
			
			//SendCsnrIapDataDeal(buf,len);											//发送数据
			
			int i = 100000;
			while(i--);
			SendCsnrIapDataDeal(buf,len);											//发送数据

			sendtime = 	g_sysIaptime; ;
			
		}else if(gsIapCtrl.echoflg)												//收到正确的应答，继续数据发送
		{
			gsIapCtrl.echoflg 	= 0;

			len = 0;

			resendtimes = 10;		//重发控制
			sendtime = 	g_sysIaptime; ;
				
			printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"发送序号:%03d\r\n",gsIapCtrl.sendnum);	

			if(gsBinFileInfo.deallen <gsBinFileInfo.size)						//已出里文件长度小于文件长度
			{
				tmp16 = 0x02;
				memcpy(&buf[len],(char *)&tmp16,sizeof(tmp16));   				//指令
				len += sizeof(tmp16);
				
				memcpy(&buf[len],(char *)&gsIapCtrl.sendnum,sizeof(tmp16));   	//序号，在接收区累加
				len += sizeof(gsIapCtrl.sendnum);
					
				int readlen = ReadFileData(gsBinFileInfo.deallen,&buf[len],128);//从文件中读取数据
		 		len +=  readlen;
				
				per = SetFileDealPer();
				SetCtrlVal (gBinFilePanelHandle, IAP_PANEL_PRE, per);			//设置百分比(下载进度) 
				
				SendCsnrIapDataDeal(buf,len);									//发送数据
				
				gsBinFileInfo.deallen += readlen;								//已处理数据 长度累加len
				
				if(gsBinFileInfo.deallen >= gsBinFileInfo.size)					//数据发送完成
				{
					//i = 0;
				}
				
				gsIapPara.framenum 		= gsIapCtrl.sendnum;					//记录已发序号 

			}
			else	//数据发送完成，发送结束标示
			{
				tmp16 = 0x03;													//发送结束指令
				memcpy(&buf[len],(char *)&tmp16,sizeof(tmp16));   				//指令
				len += sizeof(tmp16); 
				resendtimes = 0;		//重发控制

				memcpy(&buf[len],(char *)&gsIapPara,sizeof(gsIapPara));
				len +=sizeof(gsIapPara);				
				gsIapPara.framenum  = 0;									
				
				//增加crc校验（全文件） 180316
				crc32   = crc32 ^ 0x00000000FFFFFFFFL;
        		crc32  &= 0x00000000FFFFFFFFL;				
				
				memcpy(&buf[len],(char *)&crc32,sizeof(uint32));
				len += sizeof(uint32);
				//增加crc
				printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"发送序号:%03d，数据发送完成\r\n",gsIapCtrl.sendnum);	

				SendCsnrIapDataDeal(buf,len);									//发送数据
				
			}
		}
		else if(gsIapCtrl.resendflg)											//未收到正确指令，重发
		{
			 gsIapCtrl.resendflg = 0;
			 SendCsnrIapDataDeal(buf,len);										//发送数据上次的数据
		}
	}
	
	//重发数据
	if(  	g_sysIaptime - sendtime > 100*10	//1s（重发时间控制）
		&&  resendtimes							//重发次数大于1
		)
	{
		sendtime =  g_sysIaptime;
		resendtimes--;
		
		printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"发送序号:%03dR\r\n",gsIapCtrl.sendnum);	

		SendCsnrIapDataDeal(buf,len);											//发送数据上次的数据       
	}     
																																											 
	return;
}

/*******************************************************************************************
初始化IAP接收任务
*******************************************************************************************/
void	IapRecTask(void)
{
	unsigned char	tmp16;
	
	if(	sCtrl.PC.RxCtrl.recvflg 			&&		//有数据接收
		sCtrl.PC.RxCtrl.DestAddr == MY_ADDR &&		//地址有效
		sCtrl.PC.RxCtrl.FrameCode== IAP_FRAME_CODE	//IAP帧指令
	  )   			//接收到数据
	{
		sCtrl.PC.RxCtrl.recvflg = 0;				//接收完成标识
		
		memcpy((uint8 *)&tmp16,sCtrl.PC.rd,sizeof(tmp16));	//命令	

		gsIapCtrl.endflg  	= 0;
		gsIapCtrl.resendflg	= 0;
		gsIapCtrl.echoflg   = 0;
		
		if(tmp16 == 1 || tmp16 == 2) 					//继续下载
		{
			if(tmp16 == 1)								//开始发送，启动发送
			{
				gsIapCtrl.echoflg = 1;	
				
				memcpy((uint8 *)&gsIapStart,&sCtrl.PC.rd[2],sizeof(gsIapStart));	//接收应答	
				
				//printf("\r\n启动命令，收到的序号: %d",gsIapStart.CurNum);
																			//断点续传
				if(
							gsIapStart.CurNum   							//应答帧序号不为零，开始断点续传
						&&	gsIapStart.SoftSize == gsBinFileInfo.size		//文件大小相同
				  )				
				{
					gsIapCtrl.sendnum  		= gsIapStart.CurNum;			//发送序号			
					gsIapCtrl.sendsize 		= gsIapStart.CurNum * 128;		//已发长度
					gsBinFileInfo.deallen  	= gsIapStart.CurNum * 128;  	//文件已处理长度
				}
			}
			else
			{
				memcpy((uint8 *)&gsIapCtrl.recvnum,&sCtrl.PC.rd[2],sizeof(gsIapCtrl.recvnum));	   //取接收序号
				if(gsIapCtrl.recvnum == gsIapCtrl.sendnum)  
				{
					gsIapCtrl.sendnum++;
					gsIapCtrl.echoflg 	= 1;			  //数据下载正确，应答标示置1
				}else{
					gsIapCtrl.resendflg	= 1;			  //数据下载错误，重发标示置1
				}
			}
		} else if(tmp16 == 3 || tmp16 == 4)
		{
			gsIapCtrl.endflg = 1;
		}
		
		if(sCtrl.PC.rd[1])
			printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"\r\n通讯异常，代码：%0x\r\n",sCtrl.PC.rd[1]);	

			//printf("\r\n通讯异常，代码：%0x ",sCtrl.PC.rd[1]);
	}
}
