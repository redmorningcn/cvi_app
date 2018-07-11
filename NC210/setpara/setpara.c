/*******************************************************************************
 *   Filename:       SetPara.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *					 ��������Ӧ�ã�����ƷͨѶЭ�顣 20180423
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
int					l_eqiupmentcode 	= 0;	// װ�������룬����������
int					l_sendcode			= 0;	// װ�÷��������룬Ӧ��ʱʹ��

StrProductInfo  	gstrProductInfo;			// ��Ʒ����
Unnctrl     		Ctrl;						// ϵͳ���������⣩
strDtuRecData		gstrSendDtuData;			// DTUͨѶ����
strDtuRecData		gstrRecDtuData;			// DTUͨѶ����


/********************************************************************************************/
/* local Prototypes																			*/
/********************************************************************************************/


/********************************************************************************************/
//��ϵͳʱ�䣬ת��ΪstcTime�ṹ
/********************************************************************************************/
void     ReadTime(stcTime * sTime)
{
	struct tm *ptr;
    time_t lt; 
	
    lt=time(NULL);
    ptr=localtime((time_t*)&lt);				//��ϵͳʱ��
	
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
/* �������ò���      																		*/
//ͨ��l_eqiupmentcode�����������ù��̡�
//�˺�����Ҫѭ��ִ�У������ⲿ���� l_eqiupmentcode
/********************************************************************************************/
void Com_SetParaTask(void)		
{
	unsigned char  	buf[256];
	unsigned int   	datalen = 0;
	u32			   	tmp8;
	static			u32		sendtime;
	u8				tmplen;
	
	if(		l_eqiupmentcode 				!= 0		// ������ָ�� 
		&&  sCtrl.PC.ConnCtrl.SendTimeFlg 	== 0		// ���������ڷ��ͣ���ͣ���ͣ�			
	  )					
	{
		datalen = 0;
		
		memcpy(&buf[datalen],(unsigned char *)&l_eqiupmentcode,sizeof(l_eqiupmentcode));
		datalen += sizeof(l_eqiupmentcode);
					
		switch (l_eqiupmentcode)						// ����ָ����������ͳ��ģ��ͨѶЭ��
		{
			stcTime			sTime;  

			case CMD_TIME_SET:   
	 						  ReadTime((stcTime *)&sTime);	//ȡʱ��   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);
							  break; 
							  
			case CMD_LOCO_SET:   
							  memcpy(&buf[datalen],(unsigned char *)&gstrProductInfo.LocoId,sizeof(gstrProductInfo.LocoId));
							  datalen += sizeof(gstrProductInfo.LocoId);
							  break; 
			case CMD_PARA_SET: 									// ָ����ַ���ò��� 
			case CMD_DETECT_SET:   								// д����ָ����ַ			
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paraaddr,sizeof(gstrSendDtuData.paraaddr));  
							  datalen += sizeof(gstrSendDtuData.paraaddr);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paralen,sizeof(gstrSendDtuData.paralen));
							  datalen += sizeof(gstrSendDtuData.paralen);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.node,sizeof(gstrSendDtuData.node));
							  datalen += sizeof(gstrSendDtuData.node);
							  
							  tmplen = (u8)gstrSendDtuData.paralen;// ȡ���ݳ���
							  									  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.parabuf[0],tmplen);
							  datalen += tmplen;
							  break;
							  
			case CMD_PARA_GET: 									// ָ����ַ��ȡ����
			case CMD_DETECT_GET:  								// ������ָ����ַ
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paraaddr,sizeof(gstrSendDtuData.paraaddr));  
							  datalen += sizeof(gstrSendDtuData.paraaddr);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.paralen,sizeof(gstrSendDtuData.paralen));
							  datalen += sizeof(gstrSendDtuData.paralen);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrSendDtuData.node,sizeof(gstrSendDtuData.node));
							  datalen += sizeof(gstrSendDtuData.node);
							  break;
							  
			case  CMD_RECORD_GET:								// ��ָ����¼�ŵ����¼
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

		memcpy(sCtrl.PC.wr,buf,datalen);						//���ݿ����������ַ�	
		
		sCtrl.PC.ConnCtrl.sendlen 		= datalen;				//��������������
		sCtrl.PC.ConnCtrl.sourceaddr	= ADDR_SET;				//Դ��ַ
		
		sCtrl.PC.ConnCtrl.DestAddr		= ADDR_FIX; 			//Ŀ�ĵ�ַ
		sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 				//���
		sCtrl.PC.ConnCtrl.FrameCode		= 0x00;					//֡������	
	 
		sCtrl.PC.ConnCtrl.SendFlg 		= 1;					//�������� ��CVI_bsComm,���̣߳�
		sCtrl.PC.ConnCtrl.SendTimeFlg 	= 1;					//�������ͼ�ʱ����ʱ�жϣ�
		
		l_sendcode = l_eqiupmentcode;							// Ӧ��ʱʹ�ã�ȷ�����ĸ�ָ������
		sendtime = GetAnsySysTime();							// ��ʼ����ʱ��
		
		l_eqiupmentcode = 0;

	} else{ 		//û����ͨѶʱ��ȷ���Ƿ��������ͨѶ��Ӧ�����ݣ�
	
		if(gstrRecDtuData.recechoflg == 1){
			gstrRecDtuData.recechoflg = 0;
			
			datalen = 0;
			sCtrl.PC.ConnCtrl.sendlen 		= datalen;	// ��������������
			sCtrl.PC.ConnCtrl.sourceaddr	= sCtrl.PC.RxCtrl.DestAddr;	// Դ��ַ
		
			sCtrl.PC.ConnCtrl.DestAddr		= sCtrl.PC.RxCtrl.SourceAddr; // Ŀ�ĵ�ַ
			sCtrl.PC.ConnCtrl.SendFramNum 	= sCtrl.PC.RxCtrl.FramNum; 	//���(Ӧ����յ�֡���)
			sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		// ֡������	
			
			sCtrl.PC.ConnCtrl.SendFlg 		= 1;		// �������� ��CVI_bsComm,���̣߳�
		}
	}
	
	//��ʱ�ж�
	if(sCtrl.PC.ConnCtrl.SendTimeFlg == 1  ) {
		if(sendtime <= GetAnsySysTime()){
			if(sendtime + 500 < GetAnsySysTime()  ) {	// ���ͳ�ʱ��Ϊ���յ�Ӧ��
				sCtrl.PC.ConnCtrl.SendTimeFlg 	= 0;
				sCtrl.PC.ConnCtrl.ErrFlg 		= 1;	// �ô����ʶ
				sCtrl.PC.ConnCtrl.TimeoutFlg	= 1;	// ��ʱ
				sendtime = GetAnsySysTime();  
			}
		} else{
			sendtime = GetAnsySysTime();
		}
	}
}


/*******************************************************************************************
�������ݽ��շ���
*******************************************************************************************/
void	Com_SetParaRecTask(void)
{
	u16	reclen 	=  sCtrl.PC.RxCtrl.Len; //
	u16	headlen = 0;
	u32	code;
	
	if(		sCtrl.PC.RxCtrl.recvflg 	== 1		&&			// �����ݽ���
		   (sCtrl.PC.RxCtrl.DestAddr 	== ADDR_PC 	||
			sCtrl.PC.RxCtrl.DestAddr 	== ADDR_SET)
													&&			// ��ַ��Ч
			reclen						!= 0		&&			// ���ݳ�����Ч
			
		(	sCtrl.PC.RxCtrl.FrameCode	== SET_FRAME_CODE ||
		 	sCtrl.PC.RxCtrl.FrameCode	== RECORD_FRAME_CODE
		)														// ��������ָ�� 
	  )   														// ���յ�����
	{
		sCtrl.PC.RxCtrl.recvflg 		= 0;					// ������ɱ�ʶ
		sCtrl.PC.ConnCtrl.SendTimeFlg	= 0;					// ���ݽ��ճɹ���ȡ�����ͼ�ʱ
		sCtrl.PC.ConnCtrl.ErrFlg 		= 0;					// �������
		
		memcpy((u32 *)&code,sCtrl.PC.rd,sizeof(code));
		
		if(	   (	l_sendcode ==  CMD_DETECT_GET
				||  l_sendcode ==  CMD_PARA_GET
				||  l_sendcode ==  CMD_RECORD_GET  
			   )&&	(l_sendcode ==  code) 
		  ){
			switch(l_sendcode){										// ���ݷ���������룬Ӧ�����ݣ�����ָ�ֻȷ��Ӧ��λ��
				case  CMD_TIME_SET:
				case  CMD_LOCO_SET:
				case  CMD_PARA_SET:
				case  CMD_DETECT_SET:
				case  CMD_REC_CLR:
				case  CMD_SYS_RST:
				
					if(sizeof(gstrRecDtuData) > reclen){				//
						memcpy((u8 *)&gstrRecDtuData,sCtrl.PC.rd,reclen); //���ݿ���
					
						if(gstrRecDtuData.code != l_sendcode)			//���յ�ָ��Ͱl�Ͳ�ͬ
							break;
						
						if(gstrRecDtuData.reply.ack == 1)				// ���ճɹ�����ʶӦ��ɹ�
							gstrRecDtuData.setokflg = 1;
					}
					break;
				
				case CMD_PARA_GET: 										// ָ����ַ��ȡ����
				case CMD_DETECT_GET:  									// ������ָ����ַ
					if(sizeof(gstrRecDtuData) >= reclen){
						memcpy((u8 *)&gstrRecDtuData,sCtrl.PC.rd,reclen); 	//���ݸ���
						
						headlen	= sizeof(gstrRecDtuData.code) + sizeof(gstrRecDtuData.paraaddr) + sizeof(gstrRecDtuData.paralen)+sizeof(gstrRecDtuData.node);
						if(headlen >= reclen){
							gstrRecDtuData.recdatalen 			= 0;
							sCtrl.PC.ConnCtrl.DataErrFlg	= 1;
							break;
						}
						gstrRecDtuData.recdatalen 	= ((u8)reclen - (u8)headlen);	// (��Ч)���ݳ���
						gstrRecDtuData.dataokflg 	= 1;			// ���ݽ������
					}
					break;	
					
				//case CMD_RECORD_GET:  								// �����ݼ�¼

				default:
					break;			
			}
		
			l_sendcode = 0;											// ��������������
		}else if(reclen == sizeof(stcFlshRec)){
			if(gstrSendDtuData.recenableflg == 1)					// Ӧ������
			{
				memcpy((u8 *)&gstrRecDtuData,sCtrl.PC.rd,reclen); 	//���ݸ���
				gstrRecDtuData.recechoflg  = 1;						// ����Ӧ��	
				gstrRecDtuData.recvrecflg  = 1;
			}
		}
	}
}






