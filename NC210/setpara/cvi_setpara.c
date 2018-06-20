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
extern	void	WriteSetParaToFile(void);
extern	int		ReadSetPararomFile(void);


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
		   	l_eqiupmentcode = TIME_CARD; 
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
	SetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCONUM,gstrProductInfo.LocoId.Num);	
}

/********************************************************************************************/
/* ȡ������帳ֵ
/********************************************************************************************/
void	GetSetParaPanelVal(void)
{
	GetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCOTYPE,&gstrProductInfo.LocoId.Type);
	GetCtrlVal(gsetpara_panelHandle,SETP_PANEL_LOCONUM,&gstrProductInfo.LocoId.Num);	
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
			}
			break;
	}
	return 0;
}
