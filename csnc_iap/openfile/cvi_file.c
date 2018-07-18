/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    
 *   Notes:
 *     				 E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/


/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "IAP.h"
#include "cvi_file.h"
#include "send_IAP.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/
#define		UIR_BINFILE_PANEL_NAME		"iap.uir"


/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
//������
int					l_binfilehandle = 0;		//�ļ��ؼ�
int					gBinFilePanelHandle = 0;
int 				g_sysIaptime = 0;

extern	int			gmainPanel;

/********************************************************************************************/
/* local Prototypes																				*/
/********************************************************************************************/

#define			SOTREFILE	"cvi_file_myinfo.ini"
stcIapCtrl		gsIapCtrl;
stcFileInfo		gsBinFileInfo;

/********************************************************************************************/
/* local Prototypes																			*/
/********************************************************************************************/


/********************************************************************************************/
/* PanelCB ():  Quits this application.														*/
/********************************************************************************************/
int CVICALLBACK BinFilePanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event) 
		{
		case EVENT_CLOSE:
			
			HidePanel (gBinFilePanelHandle);									//�˳�����
			
			gBinFilePanelHandle = 0;
			
			DisplayPanel (gmainPanel);											//��ʾ�������

			break;
		}
	return 0;
}


/********************************************************************************************/
//�ز���ʾ��塣	redmoringcn 20170930						            
/********************************************************************************************/
void LoadCsncIapPanel(void)
{
    gBinFilePanelHandle = LoadPanel (0, UIR_BINFILE_PANEL_NAME, IAP_PANEL);
	/* 	Display the panel and run the UI */
	DisplayPanel (gBinFilePanelHandle);
}

/********************************************************************************************/
/*�򿪲����������																	        */
/********************************************************************************************/
int CVICALLBACK 	 OpenIapPanelCallback(int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadCsncIapPanel();								//װ���������
			
			/* Schedule two thread functions */				//���̣߳��������̺߳���
			cvi_InitBspComm(&sCtrl.PC);						//����
			
			HidePanel(gmainPanel);							//���������
			
			break;
	}
	return 0;
}

/********************************************************************************************/
/* GetHexFileDir ȡ�ļ�·��,�����ļ���ȡ�ļ�����							                */
/********************************************************************************************/
int	GetHexFileDir(char * filedir)
{
	
	char 	curparhstring[512];
	int		status;
	
	GetProjectDir(curparhstring);
	
	status = FileSelectPopup ("curparhstring", "*.bin", "*.txt;*.doc;*.bin", "ѡ�������ļ�", VAL_OK_BUTTON, 0, 0, 1, 0, filedir); 
	
	if(status)
	{
		gsBinFileInfo.handle = OpenFile (filedir, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_BINARY); 
	
		GetFileInfo (filedir,&gsBinFileInfo.size );
		
		return 1;
	}
	return 0;
}

/********************************************************************************************/
/*���ļ�ѡ��																            */
/********************************************************************************************/
int CVICALLBACK OpenBinFileCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	char		binpathstring[512];
	int			len;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(GetHexFileDir(binpathstring))						//�ļ�ѡ����Ч
			{
				SetCtrlVal(panel,IAP_PANEL_BINPAHT,binpathstring);		
			
				GetCtrlAttribute (panel, IAP_PANEL_BINPAHT, ATTR_STRING_TEXT_LENGTH, &len);
				if(len)
				{
					SetCtrlAttribute (panel, IAP_PANEL_DOWNLOAD, ATTR_DIMMED, 0);
				}
			}else{
				MessagePopup ("��Ϣ����", "�ļ����쳣��������ѡ���ļ�");
			}

			break;
	}
	return 0;
}


/********************************************************************************************/
/* CloseBinFile�ر��ļ�						                								*/
/********************************************************************************************/
void	CloseBinFile(void)
{
	CloseFile (gsBinFileInfo.handle);
}

/********************************************************************************************/
/* ��bin�ļ���ȡ����						                								*/
/********************************************************************************************/
int	ReadFileData(int	addr,char *buf,int	reclen)
{
	int		len = 0;	
	
	if(gsBinFileInfo.handle == 0)
		return len;
	
	SetFilePtr (gsBinFileInfo.handle, addr, 0);
	
	len = ReadFile (gsBinFileInfo.handle, buf, reclen);
	
	//gsBinFileInfo.deallen += len;
	
	return len;
}

/********************************************************************************************/
/* �ļ��Ѵ�����ʼ��						                								*/
/********************************************************************************************/
void	StartFileFromHome(void)
{
	SetFilePtr (gsBinFileInfo.handle, 0, 0);
	gsBinFileInfo.deallen = 0;
}

/********************************************************************************************/
/* �����ļ�����ٷֱ�						                								*/
/********************************************************************************************/
char	SetFileDealPer(void)
{
	char	per = 0;
	
	if((gsBinFileInfo.size /100)&&gsBinFileInfo.deallen)
	{
		per	 =  (char)(gsBinFileInfo.deallen/(gsBinFileInfo.size /100));
	}	
	
	return per;
}

/********************************************************************************************/
/* �������ļ�д������					                							    	*/
/********************************************************************************************/
char	WriteData_File(int	addr,char	buf[],int  len)
{
	char	dirstring[512];
	char	filestring[512];
	int		filehandle;
	
	GetProjectDir (dirstring);
	MakePathname (dirstring, SOTREFILE, filestring);
	
	filehandle = OpenFile (filestring, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);					 
	SetFilePtr (filehandle, addr, 0);
	
	WriteFile(filehandle,buf,len);
	
	CloseFile(filehandle);
	
	return 1;
}

/********************************************************************************************/
/* �������ļ��ж�ȡ����					                								*/
/********************************************************************************************/
int	ReadData_File(int  addr,char	buf[],int  len)
{
	char	dirstring[512];
	char	filestring[512];
	int		filehandle;
	int	datalen = 0;
	
	GetProjectDir (dirstring);
	MakePathname (dirstring, SOTREFILE, filestring);
	
	filehandle = OpenFile (filestring, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);					 
	SetFilePtr (filehandle, addr, 0);
	datalen = ReadFile(filehandle,buf,len);
	
	CloseFile(filehandle);
	
	return datalen;
}

/********************************************************************************************/
/* �������ؿ�ʼ				                								*/
/********************************************************************************************/
int CVICALLBACK SetProgramFlgCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	static	status = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			if(status == 0)					//�����ļ����ر�ʾ
			{
				//InitCom1Contrl();			//��մ��ڻ�����
				gsIapCtrl.startflg = 1;
				gsIapCtrl.sendeable= 1; 
				
				SetCtrlAttribute (panel, IAP_PANEL_DOWNLOAD, ATTR_LABEL_TEXT, "ȡ������");
				status =1;
			}
			else							//ȡ���ļ����ر�ʾ�����������
			{			
				gsIapCtrl.sendeable= 0; 

				SetCtrlAttribute (panel, IAP_PANEL_DOWNLOAD, ATTR_LABEL_TEXT, "��ʼ����");
				
				//InitCom1Contrl();			//��մ��ڻ�����
				status = 0;
			}
			
			StartFileFromHome();
			break;
	}
	return 0;
}

int CVICALLBACK IaptimerCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			if(gBinFilePanelHandle)
			{
				g_sysIaptime++;
				SendIapTask();
				IapRecTask();
			}
			
			break;
	}
	return 0;
}
