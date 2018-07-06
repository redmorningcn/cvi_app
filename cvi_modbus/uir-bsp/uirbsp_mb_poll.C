#include <ansi_c.h>
#include <userint.h>
#include	"uirbsp_mb_poll.h"
#include 	"mb_poll.h"
#include 	"stringstr.h"
#include 	"main.h"
#include 	"mb.h"



#define		UIR_POLL_NAME	"mb_poll.uir"

//全局变量
int	    	gPollPanelHandle = 0;
extern	 	int gmainPanel;							//主面板

//定义从机控制字。
strMBPoll	gsMBPoll;								//主机控制字
extern		strCtrl		sCtrl;


//打开salve面板，关闭主面板。
int CVICALLBACK OpenPollCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gPollPanelHandle	= LoadPanel (0,UIR_POLL_NAME, MB_POLL);
				DisplayPanel (gPollPanelHandle);						//显示主机面板	
				HidePanel (gmainPanel);								//隐藏设置面板			
		break;
	}
	return 0;
}


/********************************************************************************************/
/* PanelCB ():  Quits this application.关闭salve面板，显示主面板。						    */
/********************************************************************************************/
int CVICALLBACK mb_PollPanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gPollPanelHandle);								//退出窗口
			gPollPanelHandle = 0;										//
			
			DisplayPanel(gmainPanel);

			break;
		}
	return 0;
}


//在时间回调函数中调用，进行常规任务查询、执行处理。
void CVI_MBPollPanelHandle(int panel)
{
	char	string[512];
	int		buflen;
	int		tmp;
	
	if(gPollPanelHandle == 0)												//面板打开状态下，才执行函数处理
		return;
	
	if(gsMBPoll.writeflg)
	{
		GetCtrlVal(panel,MB_POLL_BUF,string);										//取数据区
		buflen = stringtobuf(string,&gsMBPoll.buf[gsMBPoll.addr],gsMBPoll.format);	//将字符串改为数组	
	}
	else																			//读取数据接收到的数据
	{
		int	i;
		char	word[16];
		
		gsMBPoll.len  = (char)MB_ChTbl[0].RxFrameData[2]/2;							//接收数据长度
		
		string[0] = '\0'; 
		for(i = 0; i<gsMBPoll.len;i++ )
		{
			word[0] = '\0';
			switch(gsMBPoll.format)
			{
				case 0:
					sprintf(word,"%d,",gsMBPoll.buf[i]);
					break;
				case 1:
					sprintf(word,"%x,",gsMBPoll.buf[i]);
					break;		
				case 2:
					sprintf(word,"%0,",gsMBPoll.buf[i]);
					break;
				case 3:
					sprintf(word,"%b,",gsMBPoll.buf[i]);
					break;						
				default:
					sprintf(word,"%d,",gsMBPoll.buf[i]);
			}
			strcat(string,word);
		}
		if(strlen(string))
		{
			string[strlen(string) - 1]  =  '\0' ;
			ResetTextBox(panel, MB_POLL_BUF,"");
			SetCtrlVal (panel, MB_POLL_BUF,  string);					//接收到的数据打印出来
		}
	}
	
	GetCtrlVal(panel,MB_POLL_ID,		&gsMBPoll.node) ;				//取设备ID
	GetCtrlVal(panel,MB_POLL_ADDR,		&gsMBPoll.addr) ;				//取数据地址
	GetCtrlVal(panel,MB_POLL_FORMAT,	&gsMBPoll.format) ;				//取数据格式
	GetCtrlVal(panel,MB_POLL_NUM,		&gsMBPoll.len) ;				//取数据长度
	
	GetCtrlVal(panel,MB_POLL_DOFLG,&tmp);									//读写标识
	if(tmp == 1)
	{
		gsMBPoll.writeflg = 1;
		gsMBPoll.readflg  = 0;	
	}
	else
	{
		gsMBPoll.readflg  = 1;
		gsMBPoll.writeflg = 0;
	}
	
	GetCtrlVal(panel,MB_POLL_AUTOFLG,&tmp);									//自动操作标识。为1自动操作，为0手动操作。
	if(tmp == 1)
	{
		gsMBPoll.autoflg = 1;
	}
	else
	{
		gsMBPoll.autoflg  = 0;
	}
}

//poll操作，根据读写状态，是否进行操作（FC03和FC16操作）。
void	MB_PollOperate(void)
{
	if(gsMBPoll.writeflg)
	{
		MBM_FC16_HoldingRegWrN(	   sCtrl.pch,
								   gsMBPoll.node,
								   gsMBPoll.addr,
								   gsMBPoll.buf,
								   gsMBPoll.len
							  );
	}
	else
	{
		MBM_FC03_HoldingRegRd(	   sCtrl.pch,
								   gsMBPoll.node,
								   gsMBPoll.addr,
								   gsMBPoll.buf,
								   gsMBPoll.len
							 );
	}
	
}

//poll 面板时钟回调函数
int CVICALLBACK MBPollTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_MBPollPanelHandle(panel); 
			break;
	}
	return 0;
}

//手动操作回调函数
int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			MB_PollOperate();						//master 处理
			break;
	}
	return 0;
}

//自动操作回调函数
int CVICALLBACK AutoRunTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(gsMBPoll.autoflg)						//自动运行
			{
				MB_PollOperate();						//master 处理
			}
			break;
	}
	return 0;
}
