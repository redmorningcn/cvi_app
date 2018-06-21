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
int					l_eqiupmentcode = 0;	//װ�������룬����������
StrProductInfo  	gstrProductInfo;		//��Ʒ����
StrTargetPara		gstrTargetPara;			//ָ����ַ����
Unnctrl     		Ctrl;					//ϵͳ���������⣩
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
	unsigned char  buf[256];
	unsigned int   datalen = 0;
	u32			   tmp8;
	
	if(l_eqiupmentcode != 0)					//������ָ��
	{
		datalen = 0;
		
		memcpy(&buf[datalen],(unsigned char *)&l_eqiupmentcode,sizeof(l_eqiupmentcode));
		datalen += sizeof(l_eqiupmentcode);
		
		switch (l_eqiupmentcode)				//����ָ����������ͳ��ģ��ͨѶЭ��
		{
			stcTime			sTime;  
			unsigned short 	locotype,loconum;

			case CMD_TIME_SET:   
	 						  ReadTime((stcTime *)&sTime);											//ȡʱ��   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);
							  break; 
							  
			case CMD_LOCO_SET:   
							  memcpy(&buf[datalen],(unsigned char *)&gstrProductInfo.LocoId,sizeof(gstrProductInfo.LocoId));
							  datalen += sizeof(gstrProductInfo.LocoId);
							  break; 
			case CMD_PARA_SET:   
							  tmp8 = sizeof(gstrTargetPara.paraaddr) + sizeof(gstrTargetPara.paralen) + gstrTargetPara.paralen;		//��ַ+���ݳ���+����
							  memcpy(&buf[datalen],(unsigned char *)&gstrTargetPara,tmp8);
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
	}
	
	l_eqiupmentcode = 0;
}


