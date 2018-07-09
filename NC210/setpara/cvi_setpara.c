#include "cvi_LocoCali.h"
#include <userint.h>
#include "cvi_setpara.h"

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

#include "setpara.h"
#include "cvi_comm.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals																					
/********************************************************************************************/
//������
int 					gsetpara_panelHandle;
extern		int			gmainPanel;

/********************************************************************************************/
//local																					
/********************************************************************************************/
extern		void		WriteSetParaToFile(void);
extern		int			ReadSetPararomFile(void);

extern	void	GetSetParaRecvInfo(void);


/********************************************************************************************/
//�ز���ʾ��塣	redmoringcn 20170930						            
/********************************************************************************************/
void LoadCsncSetparaPanel(void)
{
    gsetpara_panelHandle = LoadPanel (0, UIR_SETPARA_NAME, SETP_PANEL);
	/* 	Display the panel and run the UI */
	DisplayPanel (gsetpara_panelHandle);
	
	ReadSetPararomFile();
}

/********************************************************************************************/
/*�򿪲����������																	        */
/********************************************************************************************/
int CVICALLBACK OpenSetParaPanelCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadCsncSetparaPanel();
			
			/* Schedule two thread functions */				//���̣߳��������̺߳���
			cvi_InitBspComm(&sCtrl.PC);						//����
			
			ReadSetPararomFile();													//������ǰ�洢�Ĳ���
			
			HidePanel(gmainPanel);												//���������
			break;
	}
	return 0;
}

/********************************************************************************************/
/*���������ʾʱ��																	        */
/********************************************************************************************/
void	DisplayTimeOnSetPanel(void)
{
	struct tm *ptr;
    time_t lt; 
	char  databuf[64];  
	
    lt=time(NULL);
    ptr=localtime((time_t*)&lt);
	
	sprintf(databuf,"%02d-%02d-%02d %02d:%02d:%02d",ptr->tm_year-100,
		ptr->tm_mon+1,ptr->tm_mday,ptr->tm_hour,ptr->tm_min,ptr->tm_sec);
		
	if(gsetpara_panelHandle)
		SetCtrlVal (gsetpara_panelHandle, SETP_PANEL_DATEANDTIME, databuf);  
}

/********************************************************************************************/
/*�˳����      																	        */
/********************************************************************************************/
void	QuitSetParaPanel(void)
{
	WriteSetParaToFile();			//�˳����������
	
	HidePanel (gsetpara_panelHandle);
	
	DisplayPanel (gmainPanel);

	gsetpara_panelHandle = 0;	
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitSetParaPanel();			//�˳�������
			break;
	}
	return 0;
}

int CVICALLBACK SetTimeCallBack (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   	l_eqiupmentcode = CMD_TIME_SET; 
			break;
	}
	return 0;
}

int CVICALLBACK SetLocoCallBack (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(panel,SETP_PANEL_LOCOTYPE,&gstrProductInfo.LocoId.Type);
			GetCtrlVal(panel,SETP_PANEL_LOCONUM, &gstrProductInfo.LocoId.Nbr);
			
			if(gstrProductInfo.LocoId.Nbr == 0|| gstrProductInfo.LocoId.Type==0)
			{
				MessagePopup ("ErrMessage", "��Ϣ���ݴ�������������");
			}
			
			l_eqiupmentcode = CMD_LOCO_SET;

			break;
	}
	return 0;
}

int CVICALLBACK SetProductCallBack (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			gstrSendDtuData.paraaddr = (u16)((u32)&Ctrl.sProductInfo -  (u32)&Ctrl) ;
			gstrSendDtuData.paralen  = sizeof(Ctrl.sProductInfo.Type) +  sizeof(Ctrl.sProductInfo.Id);
			gstrSendDtuData.node	 = 0;
			
			GetCtrlVal(panel,SETP_PANEL_PRO_TYPE,(u32*)&gstrSendDtuData.parabuf);
			GetCtrlVal(panel,SETP_PANEL_PRO_NUM, (u32*)&gstrSendDtuData.parabuf[2]);
			
			if(gstrProductInfo.LocoId.Nbr == 0|| gstrProductInfo.LocoId.Type==0)
			{
				MessagePopup ("ErrMessage", "��Ϣ���ݴ�������������");
			}
			
			l_eqiupmentcode = CMD_PARA_SET;				 

			break;
	}
	return 0;
}


int CVICALLBACK ParaReadCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(panel,SETP_PANEL_PARA_ADDR,&gstrSendDtuData.paraaddr); 		//��ַ
			GetCtrlVal(panel,SETP_PANEL_PARA_LEN, &gstrSendDtuData.paralen);  		//����
			gstrSendDtuData.node	 = 0;									

			l_eqiupmentcode = CMD_PARA_GET;				 
			break;
	}
	return 0;
}

int CVICALLBACK ParaWriteCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	u8	buf[512];
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(panel,SETP_PANEL_PARA_ADDR,&gstrSendDtuData.paraaddr); 				//��ַ
			//GetCtrlVal(panel,SETP_PANEL_PARA_LEN, &gstrSendDtuData.paralen);  			//����
			gstrSendDtuData.node	 = 0;									

			GetCtrlVal(panel,SETP_PANEL_PARA_BUF,buf); 										//������
			
			gstrSendDtuData.paralen = (u8)strtohex(buf,(uint8 *)gstrSendDtuData.parabuf);	//װ����HEX

			SetCtrlVal(panel,SETP_PANEL_PARA_LEN,gstrSendDtuData.paralen);					//���� ���ݳ���
			
			l_eqiupmentcode = CMD_PARA_SET;				 

			break;
	}
	return 0;
	
}

int CVICALLBACK DetectReadCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,SETP_PANEL_DETECT_ADDR, &gstrSendDtuData.paraaddr); 		//��ַ
			GetCtrlVal(panel,SETP_PANEL_DETECT_LEN,  &gstrSendDtuData.paralen);  		//����
			GetCtrlVal(panel,SETP_PANEL_DETECT_NODE, &gstrSendDtuData.node);  		//����

			l_eqiupmentcode = CMD_DETECT_GET;				
			break;
	}
	return 0;
}

int CVICALLBACK DetectWriteCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	u8	buf[512];
	
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(panel,SETP_PANEL_DETECT_ADDR,&gstrSendDtuData.paraaddr); 				//��ַ
			//GetCtrlVal(panel,SETP_PANEL_PARA_LEN, &gstrSendDtuData.paralen);  			//����
			gstrSendDtuData.node	 = 0;									

			GetCtrlVal(panel,SETP_PANEL_DETECT_BUF,buf); 										//������
			
			gstrSendDtuData.paralen = (u8)strtohex(buf,(uint8 *)gstrSendDtuData.parabuf);	//װ����HEX

			SetCtrlVal(panel,SETP_PANEL_DETECT_LEN,gstrSendDtuData.paralen);					//���� ���ݳ���
			
			l_eqiupmentcode = CMD_DETECT_SET;				
			
			break;
	}
	return 0;
}

/********************************************************************************************/
/* ��������帳ֵ
/********************************************************************************************/
void	SetSetParaPanelVal(void)
{
	SetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCOTYPE,gstrProductInfo.LocoId.Type);
	SetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCONUM, gstrProductInfo.LocoId.Nbr);	
}

/********************************************************************************************/
/* ȡ������帳ֵ
/********************************************************************************************/
void	GetSetParaPanelVal(void)
{
	GetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCOTYPE,&gstrProductInfo.LocoId.Type);
	GetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCONUM,&gstrProductInfo.LocoId.Nbr);	
}


/********************************************************************************************/
/* ReadSetParaConfigFromFile  		�������ļ��ж������ڵ������ļ���������������ļ����ã�
������ʾĬ��ֵ	*/
/********************************************************************************************/
int	ReadSetPararomFile(void)
{
	char 	*fileName;									//�ļ�ָ��
	char 	projectDir[MAX_PATHNAME_LEN];				//����·��
	char 	fullPath[MAX_PATHNAME_LEN];					//�ļ�ȫ·��
	ssize_t size;										//�ļ���С
	int		filecom1hand;								//�ļ����
	int		flg = 0;
	
	fileName = SETPRAR_FILE_NAME;
	
	GetProjectDir (projectDir) ;					//ȡ��Ŀ·��
//
	MakePathname (projectDir, fileName, fullPath);	//�ļ�·�� where fullPath has the following format: c:\myproject\myfile.dat
	
	if(GetFileInfo (fullPath, &size) == 0)			//�ļ�������
	{
		return 0;
	}else{
		filecom1hand = OpenFile (fullPath, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);	//���ļ�
		SetFilePtr (filecom1hand, 0, 0);												//�ļ���ͷ��ʼ
		
		ReadFile (filecom1hand, (char *)&gstrProductInfo, sizeof(gstrProductInfo));		//�����ļ���ȡ 
		
		SetSetParaPanelVal();						//���ò������ֵ
	}
	
	CloseFile(filecom1hand);						//�ر��ļ�
	
	return	flg;
}


/********************************************************************************************/
/* WriteCom1ConfigToFile  		д�������ݵ��ļ�
/********************************************************************************************/
void	WriteSetParaToFile(void)
{
	char 	*fileName;									//�ļ�ָ��
	char 	projectDir[MAX_PATHNAME_LEN];				//����·��
	char 	fullPath[MAX_PATHNAME_LEN];					//�ļ�ȫ·��
	int		filecom1hand;								//�ļ����
	
	fileName = SETPRAR_FILE_NAME;
	
	GetProjectDir (projectDir) ;					//ȡ��Ŀ·��

	MakePathname (projectDir, fileName, fullPath);	//�ļ�·�� where fullPath has the following format: c:\myproject\myfile.dat
	
	filecom1hand = OpenFile (fullPath, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);		//���ļ�
		
	SetFilePtr (filecom1hand, 0, 0);													//�ļ���ͷ��ʼ

	GetSetParaPanelVal();																//ȡ���ֵ
	
	WriteFile (filecom1hand, (char *)&gstrProductInfo, sizeof(gstrProductInfo));		//���Ʒ��Ϣ			
	
	CloseFile(filecom1hand);															//�ر��ļ�     				
}

int CVICALLBACK SetParaPanelCB (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
				QuitSetParaPanel();				//�˳�������
			break;
	}
	return 0;
}


int CVICALLBACK SetParaTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
		
			if(gsetpara_panelHandle)			//�����Ч������ж�ʱ������
			{
				DisplayTimeOnSetPanel();	  	//�����ʾ
			
				Com_SetParaTask();				//���ڲ�������
				
				Com_SetParaRecTask();			//������
				
				GetSetParaRecvInfo();			//����Ӧ������
			}
			break;
	}
	return 0;
}

/********************************************************************************************
author��redmorningcn 20180706
���ݽ���׼����������Ӧ������ݣ�
********************************************************************************************/
void	GetSetParaRecvInfo(void)
{
	u8	reclen;
	u8	buf[1024];
	u8	stringtmp[10];
	u8	i;
	u8  *p = (u8 *)gstrRecDtuData.parabuf;
	
	if(gstrRecDtuData.dataokflg == 1)								//	���յ�����
	{														
		gstrRecDtuData.dataokflg	= 0;		
		
		reclen  = gstrRecDtuData.recdatalen ;						//	�������ݳ���  
		
		for(i = 0; i < reclen;i++){
			snprintf((char *)&stringtmp,5,"%02x ",*(p+i));
			strcat(buf,stringtmp);
		}
		
		if(gstrRecDtuData.code == CMD_PARA_GET)
			SetCtrlVal(gsetpara_panelHandle,SETP_PANEL_PARA_BUF,buf);
		
		if(gstrRecDtuData.code == CMD_DETECT_GET)
			SetCtrlVal(gsetpara_panelHandle,SETP_PANEL_DETECT_BUF,buf);
	}
}
