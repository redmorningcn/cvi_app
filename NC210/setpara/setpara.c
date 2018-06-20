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
int				l_eqiupmentcode = 0;	//װ�������룬����������
StrProductInfo  gstrProductInfo;		//��Ʒ����

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


stcCalcModel	gsCalcModel;	//����ģ�ͣ������ã�
extern	int   	g_com1systictimes;
/********************************************************************************************/
/* �������ò���      																		*/
//ͨ��l_eqiupmentcode�����������ù��̡�
//�˺�����Ҫѭ��ִ�У������ⲿ���� l_eqiupmentcode
/********************************************************************************************/
void Com_SetParaTask(void)		
{
	unsigned char  buf[256];
	//unsigned char  txdatabuf[256];
	unsigned int   datalen = 0;
	static   int   modelsendnum = 0;			//�������
	unsigned char  clearcode = 1;
	int  	i;
	uint8	*p;
	if(l_eqiupmentcode != 0)					//������ָ��
	{
		datalen = 0;
		
		memcpy(&buf[datalen],(unsigned char *)&l_eqiupmentcode,sizeof(l_eqiupmentcode));
		datalen += sizeof(l_eqiupmentcode);
		
		switch (l_eqiupmentcode)				//����ָ����������ͳ��ģ��ͨѶЭ��
		{
			short  			density; 
			stcTime			sTime;  
			short   		hig; 
			char			modelnum;
			unsigned short 	locotype,loconum;
			//unsigned short	crc;
			unsigned int	calcpara;
			//unsigned int 	recnum;  
			
   
			case TIME_CARD:   
	 						  ReadTime((stcTime *)&sTime);											// ����??   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);

							  break; 

			case COPY_FRAM_CARD:  
							  break; 
			case EXPAND_CARD:  	
							  break; 

			case CLEAR_ALL:  	
							  break;		
							  
			default:
				break;
		}

		memcpy(sCtrl.PC.wr,buf,datalen);			//���ݿ����������ַ�		
		sCtrl.PC.ConnCtrl.sendlen 		= datalen;	//��������������

		sCtrl.PC.ConnCtrl.sourceaddr	= 0xC2;		//Դ��ַ
		sCtrl.PC.ConnCtrl.DestAddr		= 0x82; 	//Ŀ�ĵ�ַ
		sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 	//���
		sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		//֡������	
	 
		sCtrl.PC.ConnCtrl.SendFlg 		= 1;		//�������� ��CVI_bsComm,���̣߳�
		
		if( clearcode )
			l_eqiupmentcode = 0;					//���������������
	}
}


