#include <userint.h>
#include <rs232.h>
#include <ansi_c.h>

#include <comconfig.h>
#include <modbus_poll.h>
#include <MB_BSP.h>

#include <mb_poll.h>
#include <mb_salve.h>
#include <cvi_comm.h>



extern	stcUartConfig		mb_com1config;
extern	int					gCom1PanelHandle;
#define		UIR_COM1CONFIG_NAME		"comconfig.uir"


/********************************************************************************************/
/* PanelCB ():  Quits panel.														*/
/********************************************************************************************/
void	QuitCom1Panel(int	panel)
{
	GetCtrlVal (panel, COM1_PANEL_PORT, 	&mb_com1config.port);	//取端口
	GetCtrlVal (panel, COM1_PANEL_BAUT, 	&mb_com1config.baut);	//取波特率
	GetCtrlVal (panel, COM1_PANEL_BITS, 	&mb_com1config.bits);	//取数据长度
	GetCtrlVal (panel, COM1_PANEL_PARITY, 	&mb_com1config.parity);	//取校验
	GetCtrlVal (panel, COM1_PANEL_STOPS, 	&mb_com1config.stops);	//取停止位

	mb_com1config.config = 1;										//配置更改
	
	WriteMbComConfigToFile(&mb_com1config);							//将配置信息写入文件

	
	//if( mb_com1config.open == 0)									//未打开，直接打开
	{
		if(mb_com1config.stops == 0)
			mb_com1config.stops = 1;
		
		int	status = OpenComConfig (	mb_com1config.port,		//打开串口
								   	"",
									mb_com1config.baut,
									mb_com1config.parity,
									mb_com1config.bits,
									mb_com1config.stops,
									256,
									256
					  			);

		char	buf[128];
		if(status < 0 )										//端口打开错误
		{
			sprintf(buf,"串口不能打开，请确认!，状态字为%d",status);
			MessagePopup ("配置错误信息", buf);

			return ;
		}

		/* 	Make sure Serial buffers are empty */
		FlushInQ  (mb_com1config.port);
		FlushOutQ (mb_com1config.port);
		
		mb_com1config.open = 1;						//打开串口成功标识置位
	}
	
	HidePanel(gCom1PanelHandle);											//退出窗口
}

int CVICALLBACK OpenCom1Callback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2);
/********************************************************************************************/
/* PanelCB ():  Quits panel.														*/
/********************************************************************************************/
void	ConfigMbComWithFile(void)
{

	mb_com1config.config = 1;										//配置更改
	
	ReadMbComConfigFromFile(&mb_com1config);							//从文件中取出配置信息

	//if( mb_com1config.open == 0)									//未打开，直接打开
	{
		if(mb_com1config.stops == 0)
			mb_com1config.stops = 1;
		
		int	status = OpenComConfig (	mb_com1config.port,		//打开串口
								   	"",
									mb_com1config.baut,
									mb_com1config.parity,
									mb_com1config.bits,
									mb_com1config.stops,
									255,
									255
					  			);

		char	buf[128];
		if(status < 0 )										//端口打开错误
		{
			sprintf(buf,"串口不能打开，请确认!，状态字为%d",status);
			MessagePopup ("配置错误信息", buf);

			int	data;
			//访问回调函数
			OpenCom1Callback(MAIN,MAIN_COMCONFIG,EVENT_COMMIT,&data,data,data);
			
			return ;
		}

		/* 	Make sure Serial buffers are empty */
		FlushInQ  (mb_com1config.port);
		FlushOutQ (mb_com1config.port);
		
		mb_com1config.open = 1;						//打开串口成功标识置位
	}
}

/********************************************************************************************/
/* PanelCB ():  串口1配置													             	*/
/********************************************************************************************/
int CVICALLBACK Com1ConfigOkCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	//int status;
	switch (event)
	{
		case EVENT_COMMIT:

			QuitCom1Panel(panel);

			break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.														*/
/********************************************************************************************/
int CVICALLBACK Com1PanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			QuitCom1Panel(panel);

			break;
		}
	return 0;
}

int		gCom1PanelHandle;
/********************************************************************************************/
/* 在com1_panel面板上显示配置信息*/
/********************************************************************************************/
void	SetCviCtrlMbComConfig(stcUartConfig * sUartConfig)
{
	 if( gCom1PanelHandle )
	 {
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_PORT, sUartConfig->port);			//取端口
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_BAUT, sUartConfig->baut);			//取波特率
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_BITS, sUartConfig->bits);			//取数据长度
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_PARITY,sUartConfig->parity);		//取校验
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_STOPS, sUartConfig->stops);		//取停止位
	 }
}

int CVICALLBACK OpenCom1Callback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(mb_com1config.open  == 0)
			{
				gCom1PanelHandle	= LoadPanel (0,UIR_COM1CONFIG_NAME, COM1_PANEL);
				DisplayPanel (gCom1PanelHandle);								//显示设置面板

				ReadMbComConfigFromFile(&mb_com1config);							//从文件中取出配置信息
				
				SetCviCtrlMbComConfig(&mb_com1config);								//参数值面板显示
			}else{
				if( mb_com1config.open )											//串口为打开状态，关闭串口
				{
					mb_com1config.open = 0;										//置关闭标识
					CloseCom (mb_com1config.port);								//关闭串口
				}			
			}
			break;	
	}
	return 0;
}

extern	int	    	gPollPanelHandle ;
extern	int	    	gSlavePanelHandle ;

//在INFO窗口打印接收的内容
void	printrecinfo(char *string)
{
	if( gPollPanelHandle )				//poll面板有效，在poll面板显示
	{
	   SetCtrlVal(gPollPanelHandle,MB_POLL_INFO,string);

	}
		
	if( gSlavePanelHandle )				//poll面板有效，在poll面板显示
	{
	   SetCtrlVal(gSlavePanelHandle,MB_SLAVE_INFO,string);
	   //printf(string);
	}
}
