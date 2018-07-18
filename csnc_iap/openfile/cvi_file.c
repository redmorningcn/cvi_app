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
//面板变量
int					l_binfilehandle = 0;		//文件控件
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
			
			HidePanel (gBinFilePanelHandle);									//退出窗口
			
			gBinFilePanelHandle = 0;
			
			DisplayPanel (gmainPanel);											//显示设置面板

			break;
		}
	return 0;
}


/********************************************************************************************/
//载并显示面板。	redmoringcn 20170930						            
/********************************************************************************************/
void LoadCsncIapPanel(void)
{
    gBinFilePanelHandle = LoadPanel (0, UIR_BINFILE_PANEL_NAME, IAP_PANEL);
	/* 	Display the panel and run the UI */
	DisplayPanel (gBinFilePanelHandle);
}

/********************************************************************************************/
/*打开参数设置面板																	        */
/********************************************************************************************/
int CVICALLBACK 	 OpenIapPanelCallback(int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadCsncIapPanel();								//装载下载面板
			
			/* Schedule two thread functions */				//多线程，创建新线程函数
			cvi_InitBspComm(&sCtrl.PC);						//串口
			
			HidePanel(gmainPanel);							//隐藏主面板
			
			break;
	}
	return 0;
}

/********************************************************************************************/
/* GetHexFileDir 取文件路径,并打开文件，取文件长度							                */
/********************************************************************************************/
int	GetHexFileDir(char * filedir)
{
	
	char 	curparhstring[512];
	int		status;
	
	GetProjectDir(curparhstring);
	
	status = FileSelectPopup ("curparhstring", "*.bin", "*.txt;*.doc;*.bin", "选择下载文件", VAL_OK_BUTTON, 0, 0, 1, 0, filedir); 
	
	if(status)
	{
		gsBinFileInfo.handle = OpenFile (filedir, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_BINARY); 
	
		GetFileInfo (filedir,&gsBinFileInfo.size );
		
		return 1;
	}
	return 0;
}

/********************************************************************************************/
/*打开文件选项																            */
/********************************************************************************************/
int CVICALLBACK OpenBinFileCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	char		binpathstring[512];
	int			len;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(GetHexFileDir(binpathstring))						//文件选择有效
			{
				SetCtrlVal(panel,IAP_PANEL_BINPAHT,binpathstring);		
			
				GetCtrlAttribute (panel, IAP_PANEL_BINPAHT, ATTR_STRING_TEXT_LENGTH, &len);
				if(len)
				{
					SetCtrlAttribute (panel, IAP_PANEL_DOWNLOAD, ATTR_DIMMED, 0);
				}
			}else{
				MessagePopup ("消息提醒", "文件打开异常，请重新选择文件");
			}

			break;
	}
	return 0;
}


/********************************************************************************************/
/* CloseBinFile关闭文件						                								*/
/********************************************************************************************/
void	CloseBinFile(void)
{
	CloseFile (gsBinFileInfo.handle);
}

/********************************************************************************************/
/* 从bin文件读取数据						                								*/
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
/* 文件已处理，初始化						                								*/
/********************************************************************************************/
void	StartFileFromHome(void)
{
	SetFilePtr (gsBinFileInfo.handle, 0, 0);
	gsBinFileInfo.deallen = 0;
}

/********************************************************************************************/
/* 设置文件处理百分比						                								*/
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
/* 向配置文件写入数据					                							    	*/
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
/* 从配置文件中读取数据					                								*/
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
/* 设置下载开始				                								*/
/********************************************************************************************/
int CVICALLBACK SetProgramFlgCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	static	status = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			if(status == 0)					//设置文件下载标示
			{
				//InitCom1Contrl();			//清空串口缓存区
				gsIapCtrl.startflg = 1;
				gsIapCtrl.sendeable= 1; 
				
				SetCtrlAttribute (panel, IAP_PANEL_DOWNLOAD, ATTR_LABEL_TEXT, "取消下载");
				status =1;
			}
			else							//取消文件下载标示，清空下载区
			{			
				gsIapCtrl.sendeable= 0; 

				SetCtrlAttribute (panel, IAP_PANEL_DOWNLOAD, ATTR_LABEL_TEXT, "开始下载");
				
				//InitCom1Contrl();			//清空串口缓存区
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
