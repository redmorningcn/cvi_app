#include "cvi_LocoCali.h"
#include <userint.h>

/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.		  180619
 *
 *   Description:
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/

#include 	"cvi_LKJTest.h"
#include 	"includes.h"
#include  	"cvi_config.h"
#include  	"setpara.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//面板变量
int 					gLKJTest_panelHandle;
extern		int			gmainPanel;

/********************************************************************************************/
//local
/********************************************************************************************/


/********************************************************************************************/
//载并显示面板。	redmoringcn 20180619
/********************************************************************************************/
void LoadLKJTestPanel(void)
{
	gLKJTest_panelHandle = LoadPanel (0, "cvi_LKJTest.uir", LKJTEST);
	/* 	Display the panel and run the UI */
	DisplayPanel (gLKJTest_panelHandle);
}

/********************************************************************************************/
/*打开面板																	        */
/********************************************************************************************/
int CVICALLBACK OpenLKJTestCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadLKJTestPanel();

			/* Schedule two thread functions */				//多线程，创建新线程函数
			cvi_InitBspComm(&sCtrl.PC);						//串口
			
			HidePanel(gmainPanel);							//隐藏主面板
			break;
	}
	return 0;
}

/********************************************************************************************/
/*退出面板      																	        */
/********************************************************************************************/
void	QuitLKJTestPanel(void)
{
	HidePanel (gLKJTest_panelHandle);

	DisplayPanel (gmainPanel);

	gLKJTest_panelHandle = 0;
}

int CVICALLBACK LKJTestPanelCB (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitLKJTestPanel();				//退出面板操作
			break;
	}
	return 0;
}

extern	void	RecDetectInfoReadCode(void) ;
extern	void	GetRecDetectInfo(void);
int CVICALLBACK LKJTestTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(gLKJTest_panelHandle)			// 面板有效，则进行定时器操作
			{
				RecDetectInfoReadCode();		// 准备检测数据读取指令
				
				Com_SetParaTask();				// 串口参数设置
				
				Com_SetParaRecTask();			// 串口数据接收
				
				GetRecDetectInfo();				// 获取读取得检测数据

			}
			break;
	}
	return 0;
}



int CVICALLBACK ReadRecordCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK ClearRecordCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/
extern	int	l_eqiupmentcode;
/********************************************************************************************
author：redmorningcn 20180622 
速度信号及loco信号命令，数据准备。（直接读取 控制板ctrl.rec实时数据（指定地址读））
********************************************************************************************/
void	RecDetectInfoReadCode(void)
{
	u32	len;
	
	len = sizeof(Ctrl.Rec);
	l_eqiupmentcode = CMD_PARA_GET;		//指定参数读

	gstrDtuData.paraaddr = (u16)((u32)&Ctrl.Rec.speed[0] -  (u32)&Ctrl) ;					//读指定地址
	gstrDtuData.paralen  = (u16)((u32)&Ctrl.Rec.Longitude -  (u32)&Ctrl.Rec.speed[0]) ;		//读指定数据
}

/********************************************************************************************
author：redmorningcn 20180622 
取速度信号及loco信号命令，数据准备。（通过接收标识，判断是接收到数据）
********************************************************************************************/
void	GetRecDetectInfo(void)
{
	u32	len;
	
	if(gstrDtuData.dataokflg == 1)		//接收到数据
	{
		len =   (u16)((u32)&Ctrl.Rec.Longitude -  (u32)&Ctrl.Rec.speed[0]);					//detect 数据（检测板数据） 
		if(gstrDtuData.recdatalen == len)
		{
			memcpy((u8 *)&Ctrl.Rec.speed[0],gstrDtuData.parabuf,len);						//复制数据
		}
	}
}
