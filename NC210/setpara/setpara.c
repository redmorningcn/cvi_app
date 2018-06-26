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
strDtuRecData		gstrDtuData;				// DTUͨѶ����

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
		
		switch (l_eqiupmentcode)				//����ָ����������ͳ��ģ��ͨѶЭ��
		{
			stcTime			sTime;  

			case CMD_TIME_SET:   
	 						  ReadTime((stcTime *)&sTime);											//ȡʱ��   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);
							  break; 
							  
			case CMD_LOCO_SET:   
							  memcpy(&buf[datalen],(unsigned char *)&gstrProductInfo.LocoId,sizeof(gstrProductInfo.LocoId));
							  datalen += sizeof(gstrProductInfo.LocoId);
							  break; 
			case CMD_PARA_SET: 		// ָ����ַ���ò��� 
			case CMD_DETECT_SET:   	// д����ָ����ַ			
							  memcpy(&buf[datalen],(unsigned char *)&gstrDtuData.paraaddr,sizeof(gstrDtuData.paraaddr));  
							  datalen += sizeof(gstrDtuData.paraaddr);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrDtuData.paralen,sizeof(gstrDtuData.paralen));
							  datalen += sizeof(gstrDtuData.paralen);
							  
							  tmplen = (u8)gstrDtuData.paralen;	   	//ȡ���ݳ���
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrDtuData.parabuf[0],tmplen);
							  datalen += tmplen;
							  break;
							  
			case CMD_PARA_GET: 		// ָ����ַ��ȡ����
			case CMD_DETECT_GET:  	// ������ָ����ַ
							  memcpy(&buf[datalen],(unsigned char *)&gstrDtuData.paraaddr,sizeof(gstrDtuData.paraaddr));  
							  datalen += sizeof(gstrDtuData.paraaddr);
							  
							  memcpy(&buf[datalen],(unsigned char *)&gstrDtuData.paralen,sizeof(gstrDtuData.paralen));
							  datalen += sizeof(gstrDtuData.paralen);
							  break;
							  
			case  CMD_RECORD_GET:	// ��ָ����¼�ŵ����¼
							  tmp8 = sizeof(gstrDtuData.recordnum);
							  memcpy(&buf[datalen],(unsigned char *)&gstrDtuData.recordnum,tmp8);
						      datalen += tmp8;
							  break;	
			case CMD_REC_CLR:  	
			case CMD_SYS_RST:  	
							  break;		
							  
			default:
				break;
		}

		memcpy(sCtrl.PC.wr,buf,datalen);			//���ݿ����������ַ�	
		
		sCtrl.PC.ConnCtrl.sendlen 		= datalen;	//��������������
		sCtrl.PC.ConnCtrl.sourceaddr	= ADDR_SET;	//Դ��ַ
		
		sCtrl.PC.ConnCtrl.DestAddr		= ADDR_FIX; //Ŀ�ĵ�ַ
		sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 	//���
		sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		//֡������	
	 
		sCtrl.PC.ConnCtrl.SendFlg 		= 1;		//�������� ��CVI_bsComm,���̣߳�
		sCtrl.PC.ConnCtrl.SendTimeFlg 	= 1;		//�������ͼ�ʱ����ʱ�жϣ�
		
		l_sendcode = l_eqiupmentcode;				// Ӧ��ʱʹ�ã�ȷ�����ĸ�ָ������
		sendtime = GetAnsySysTime();				// ��ʼ����ʱ��
		
		l_eqiupmentcode = 0;

	} else{ 		//û����ͨѶʱ��ȷ���Ƿ��������ͨѶ��Ӧ�����ݣ�
	
		if(gstrDtuData.recechoflg == 1){
			gstrDtuData.recechoflg = 0;
			
			datalen = 0;
			sCtrl.PC.ConnCtrl.sendlen 		= datalen;	//��������������
			sCtrl.PC.ConnCtrl.sourceaddr	= ADDR_SET;	//Դ��ַ
		
			sCtrl.PC.ConnCtrl.DestAddr		= ADDR_FIX; //Ŀ�ĵ�ַ
			sCtrl.PC.ConnCtrl.SendFramNum 	= sCtrl.PC.RxCtrl.FramNum; 	//���(Ӧ����յ�֡���)
			sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		//֡������	
			
			sCtrl.PC.ConnCtrl.SendFlg 		= 1;		//�������� ��CVI_bsComm,���̣߳�
		}
	}
	
	//��ʱ�ж�
	if(sCtrl.PC.ConnCtrl.SendTimeFlg == 1  ) {
		if(sendtime <= GetAnsySysTime()){
			if(sendtime + 2000 < GetAnsySysTime()  ) {	//���ͳ�ʱ��Ϊ���յ�Ӧ��
				sCtrl.PC.ConnCtrl.SendTimeFlg 	= 0;
				sCtrl.PC.ConnCtrl.ErrFlg 		= 1;	//�ô����ʶ
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
		
		if(			reclen < sizeof(stcFlshRec) 
				||	l_sendcode ==  CMD_DETECT_GET
				||  l_sendcode ==  CMD_PARA_GET
				||  l_sendcode ==  CMD_RECORD_GET   
		  ){
			switch(l_sendcode){										// ���ݷ���������룬Ӧ�����ݣ�����ָ�ֻȷ��Ӧ��λ��
				case  CMD_TIME_SET:
				case  CMD_LOCO_SET:
				case  CMD_PARA_SET:
				case  CMD_DETECT_SET:
				case  CMD_REC_CLR:
				case  CMD_SYS_RST:
				
					if(sizeof(gstrDtuData) > reclen){				//
						memcpy((u8 *)&gstrDtuData,sCtrl.PC.rd,reclen); //���ݿ���
					
						if(gstrDtuData.reply.ack == 1)				// ���ճɹ�����ʶӦ��ɹ�
							gstrDtuData.setokflg = 1;
					}
					break;
				
				case CMD_PARA_GET: 									// ָ����ַ��ȡ����
				case CMD_DETECT_GET:  								// ������ָ����ַ
				//case CMD_RECORD_GET:  								// �����ݼ�¼
					if(sizeof(gstrDtuData) >= reclen){
						memcpy((u8 *)&gstrDtuData,sCtrl.PC.rd,reclen); //���ݸ���
						gstrDtuData.dataokflg 	= 1;					// ���ݽ������
						
						headlen	= sizeof(gstrDtuData.code) + sizeof(gstrDtuData.paraaddr) + sizeof(gstrDtuData.paralen);
						if(headlen > reclen){
							gstrDtuData.recdatalen = 0;	
							break;
						}
						gstrDtuData.recdatalen 	= ((u8)reclen - (u8)headlen);	// (��Ч)���ݳ���
					}
					break;				 
				default:
					break;			
			}
		
			l_sendcode = 0;											// ��������������
		}else if(reclen == sizeof(stcFlshRec)){
			if(gstrDtuData.recenableflg == 1)						// Ӧ������
			{
				gstrDtuData.recechoflg  = 1;						// ����Ӧ��	
			}
		}
	}
}






