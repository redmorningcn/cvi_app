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
#include 	"cvi_SpeedCali.h"
#include 	"includes.h"
#include  	"cvi_config.h"
#include 	"cvi_SpeedCaliType.h"
#include  	"setpara.h"    


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//面板变量
int 					gSpeedCali_panelHandle;
extern		int			gmainPanel;
strLineCali				lstrSpeedCali[SPEED_GROUP_NUM];				//速度信号校验参数
strLineCali				lstrSpeedCaliCtrlId[SPEED_GROUP_NUM];		//速度信号面板ID

/********************************************************************************************/
//local
/********************************************************************************************/

int CVICALLBACK SpeedCaliTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	static	u8	tmp = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(gSpeedCali_panelHandle)			//面板有效，则进行定时器操作
			{
				if(tmp == 0){
					SpeedInitCaliCtrlId();
					tmp++;
				}
				SpeedCaliCommcode();			//校准串口通讯
				
				Com_SetParaTask();				//串口参数设置
				
				Com_SetParaRecTask();			// 串口数据接收
				
				SpeedGetRecvCaliInfo();			//取串接收
				
				SpeedCaliDisplay();				//显示面板内容
			}
			break;
	}
	return 0;
}

/********************************************************************************************/
//载并显示面板。	redmoringcn 20180619
/********************************************************************************************/
void LoadSpeedCaliPanel(void)
{
	gSpeedCali_panelHandle = LoadPanel (0, "cvi_SpeedCali.uir", SPEEDCALI);
	/* 	Display the panel and run the UI */
	DisplayPanel (gSpeedCali_panelHandle);
}

/********************************************************************************************/
/*打开面板																	        */
/********************************************************************************************/
int CVICALLBACK OpenSpeedCaliCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadSpeedCaliPanel();

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
void	QuitSpeedCaliPanel(void)
{
	HidePanel (gSpeedCali_panelHandle);

	DisplayPanel (gmainPanel);

	gSpeedCali_panelHandle = 0;
}

int CVICALLBACK SpeedCaliPanelCB (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitSpeedCaliPanel();				//退出面板操作
			break;
	}
	return 0;
}




int CVICALLBACK G1_VccCaliCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[0].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G1_Speed1CaliCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[1].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G1_Speed2CaliCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[2].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G1_VccLowCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[0].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G1_Speed1LowCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[1].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G1_Speed2lowCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[2].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G1_Speed2HigCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[2].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G2_VccCaliCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[3].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G2_Speed1CaliCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[4].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G2_Speed2CaliCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[5].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G2_VccLowCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[3].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G2_Speed1LowCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[4].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G2_Speed2lowCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[5].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G1_VccHigCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[0].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G1_Speed1HigCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[1].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G2_VccHigCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[3].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G2_Speed1HigCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[4].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G2_Speed2HigCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[5].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G3_Speed1CaliCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[7].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G3_VccCaliCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[6].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G3_Speed2CaliCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[8].califlg = 1;
			SpeedCtrlDimmedSendControl(1);	//关闭所有发送
			SpeedGetCaliCtrlVal();			//取面板值
			break;
	}
	return 0;
}

int CVICALLBACK G3_VccLowCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[6].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G3_Speed1LowCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[7].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G3_Speed2lowCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[8].lowflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G3_VccHigCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[6].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G3_Speed1HigCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[7].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK G3_Speed2HigCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrSpeedCali[8].higflg = 1;	//读同步信号。同步的相应标识置位
			SpeedMeasureCtrlSetVal();
			break;
	}
	return 0;
}


int CVICALLBACK G1VCCSyncCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	u8	i,j;
	u8	id = 0;
	u16	*p;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,lstrSpeedCaliCtrlId[id].ansyflg,&lstrSpeedCali[id].ansyflg);
			
			if(lstrSpeedCali[id].ansyflg == 1) {
				for(i = id+SPEED_TYPE_NUM;i < SPEED_GROUP_NUM;){
					p = (u16 *)&lstrSpeedCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 1);
						p++;
					}
					
					SetCtrlVal (panel, lstrSpeedCaliCtrlId[i].ansyflg,  1);
					i += SPEED_TYPE_NUM;
				}
			}else{
				for(i = id+SPEED_TYPE_NUM;i < SPEED_GROUP_NUM;){
					p = (u16 *)&lstrSpeedCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 0);
						p++;
					}
					
					SetCtrlVal (panel, lstrSpeedCaliCtrlId[i].ansyflg,  0);
					
					i += SPEED_TYPE_NUM;  
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK G1Speed1SyncCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	u8	i,j;
	u8	id = 1;
	u16	*p;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,lstrSpeedCaliCtrlId[id].ansyflg,&lstrSpeedCali[id].ansyflg);
			
			if(lstrSpeedCali[id].ansyflg == 1) {
				for(i = id+SPEED_TYPE_NUM;i < SPEED_GROUP_NUM;){
					p = (u16 *)&lstrSpeedCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 1);
						p++;
					}
					
					SetCtrlVal (panel, lstrSpeedCaliCtrlId[i].ansyflg,  1);
					i += SPEED_TYPE_NUM;
				}
			}else{
				for(i = id+SPEED_TYPE_NUM;i < SPEED_GROUP_NUM;){
					p = (u16 *)&lstrSpeedCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 0);
						p++;
					}
					
					SetCtrlVal (panel, lstrSpeedCaliCtrlId[i].ansyflg,  0);
					
					i += SPEED_TYPE_NUM;  
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK G1Speed2SyncCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	u8	i,j;
	u8	id = 2;
	u16	*p;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,lstrSpeedCaliCtrlId[id].ansyflg,&lstrSpeedCali[id].ansyflg);
			
			if(lstrSpeedCali[id].ansyflg == 1) {
				for(i = id+SPEED_TYPE_NUM;i < SPEED_GROUP_NUM;){
					p = (u16 *)&lstrSpeedCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 1);
						p++;
					}
					
					SetCtrlVal (panel, lstrSpeedCaliCtrlId[i].ansyflg,  1);
					i += SPEED_TYPE_NUM;
				}
			}else{
				for(i = id+SPEED_TYPE_NUM;i < SPEED_GROUP_NUM;){
					p = (u16 *)&lstrSpeedCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 0);
						p++;
					}
					
					SetCtrlVal (panel, lstrSpeedCaliCtrlId[i].ansyflg,  0);
					
					i += SPEED_TYPE_NUM;  
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK G2VCCSyncCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SpeedCtrlDimmedControl(3);
			break;
	}
	return 0;
}

int CVICALLBACK G2Speed1SyncCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SpeedCtrlDimmedControl(4);
			break;
	}
	return 0;
}

int CVICALLBACK G2Speed2SyncCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SpeedCtrlDimmedControl(5);
			break;
	}
	return 0;
}

int CVICALLBACK G3VCCSyncCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SpeedCtrlDimmedControl(6);
			break;
	}
	return 0;
}

int CVICALLBACK G3Speed1SyncCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SpeedCtrlDimmedControl(7);
			break;
	}
	return 0;
}

int CVICALLBACK G3Speed2SyncCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SpeedCtrlDimmedControl(8);
			break;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/

/*******************************************************************************
* Description  : 初始化速度校准控件ID，和面板控件建立联系
* Author       : 2018/6/29  by redmorningcn
*******************************************************************************/
void	SpeedInitCaliCtrlId(void)   
{
	lstrSpeedCaliCtrlId[0].lowstandard	=	SPEEDCALI_G1VCC_LOW_STAND		;		
	lstrSpeedCaliCtrlId[0].lowmeasure	=	SPEEDCALI_G1VCC_LOW_MEASURE		;
	lstrSpeedCaliCtrlId[0].higstandard	=	SPEEDCALI_G1VCC_HIG_STAND		;
	lstrSpeedCaliCtrlId[0].higmeasure	=	SPEEDCALI_G1VCC_HIG_MEASURE		;
	lstrSpeedCaliCtrlId[0].ansyflg		=	SPEEDCALI_G1VCC_SYNC			;
	lstrSpeedCaliCtrlId[0].send			=	SPEEDCALI_G1VCC					;
	
	lstrSpeedCaliCtrlId[1].lowstandard	=	SPEEDCALI_G1SPEED1_LOW_STAND	;		
	lstrSpeedCaliCtrlId[1].lowmeasure	=	SPEEDCALI_G1SPEED1_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[1].higstandard	=	SPEEDCALI_G1SPEED1_HIG_STAND	;
	lstrSpeedCaliCtrlId[1].higmeasure	=	SPEEDCALI_G1SPEED1_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[1].ansyflg		=	SPEEDCALI_G1SPEED1_SYNC			;
	lstrSpeedCaliCtrlId[1].send			=	SPEEDCALI_G1SPEED1				;	
	
	lstrSpeedCaliCtrlId[2].lowstandard	=	SPEEDCALI_G1SPEED2_LOW_STAND	;		
	lstrSpeedCaliCtrlId[2].lowmeasure	=	SPEEDCALI_G1SPEED2_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[2].higstandard	=	SPEEDCALI_G1SPEED2_HIG_STAND	;
	lstrSpeedCaliCtrlId[2].higmeasure	=	SPEEDCALI_G1SPEED2_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[2].ansyflg		=	SPEEDCALI_G1SPEED2_SYNC			;
	lstrSpeedCaliCtrlId[2].send			=	SPEEDCALI_G1SPEED2				;		
	
	lstrSpeedCaliCtrlId[3].lowstandard	=	SPEEDCALI_G2VCC_LOW_STAND		;		
	lstrSpeedCaliCtrlId[3].lowmeasure	=	SPEEDCALI_G2VCC_LOW_MEASURE		;
	lstrSpeedCaliCtrlId[3].higstandard	=	SPEEDCALI_G2VCC_HIG_STAND		;
	lstrSpeedCaliCtrlId[3].higmeasure	=	SPEEDCALI_G2VCC_HIG_MEASURE		;
	lstrSpeedCaliCtrlId[3].ansyflg		=	SPEEDCALI_G2VCC_SYNC			;
	lstrSpeedCaliCtrlId[3].send			=	SPEEDCALI_G2VCC					;
	
	lstrSpeedCaliCtrlId[4].lowstandard	=	SPEEDCALI_G2SPEED1_LOW_STAND	;		
	lstrSpeedCaliCtrlId[4].lowmeasure	=	SPEEDCALI_G2SPEED1_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[4].higstandard	=	SPEEDCALI_G2SPEED1_HIG_STAND	;
	lstrSpeedCaliCtrlId[4].higmeasure	=	SPEEDCALI_G2SPEED1_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[4].ansyflg		=	SPEEDCALI_G2SPEED1_SYNC			;
	lstrSpeedCaliCtrlId[4].send			=	SPEEDCALI_G2SPEED1				;	
	
	lstrSpeedCaliCtrlId[5].lowstandard	=	SPEEDCALI_G2SPEED2_LOW_STAND	;		
	lstrSpeedCaliCtrlId[5].lowmeasure	=	SPEEDCALI_G2SPEED2_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[5].higstandard	=	SPEEDCALI_G2SPEED2_HIG_STAND	;
	lstrSpeedCaliCtrlId[5].higmeasure	=	SPEEDCALI_G2SPEED2_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[5].ansyflg		=	SPEEDCALI_G2SPEED2_SYNC			;
	lstrSpeedCaliCtrlId[5].send			=	SPEEDCALI_G2SPEED2				;	

	lstrSpeedCaliCtrlId[6].lowstandard	=	SPEEDCALI_G3VCC_LOW_STAND		;		
	lstrSpeedCaliCtrlId[6].lowmeasure	=	SPEEDCALI_G3VCC_LOW_MEASURE		;
	lstrSpeedCaliCtrlId[6].higstandard	=	SPEEDCALI_G3VCC_HIG_STAND		;
	lstrSpeedCaliCtrlId[6].higmeasure	=	SPEEDCALI_G3VCC_HIG_MEASURE		;
	lstrSpeedCaliCtrlId[6].ansyflg		=	SPEEDCALI_G3VCC_SYNC			;
	lstrSpeedCaliCtrlId[6].send			=	SPEEDCALI_G3VCC					;
	
	lstrSpeedCaliCtrlId[7].lowstandard	=	SPEEDCALI_G3SPEED1_LOW_STAND	;		
	lstrSpeedCaliCtrlId[7].lowmeasure	=	SPEEDCALI_G3SPEED1_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[7].higstandard	=	SPEEDCALI_G3SPEED1_HIG_STAND	;
	lstrSpeedCaliCtrlId[7].higmeasure	=	SPEEDCALI_G3SPEED1_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[7].ansyflg		=	SPEEDCALI_G3SPEED1_SYNC			;
	lstrSpeedCaliCtrlId[7].send			=	SPEEDCALI_G3SPEED1				;	
	
	lstrSpeedCaliCtrlId[8].lowstandard	=	SPEEDCALI_G3SPEED2_LOW_STAND	;		
	lstrSpeedCaliCtrlId[8].lowmeasure	=	SPEEDCALI_G3SPEED2_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[8].higstandard	=	SPEEDCALI_G3SPEED2_HIG_STAND	;
	lstrSpeedCaliCtrlId[8].higmeasure	=	SPEEDCALI_G3SPEED2_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[8].ansyflg		=	SPEEDCALI_G3SPEED2_SYNC			;
	lstrSpeedCaliCtrlId[8].send			=	SPEEDCALI_G3SPEED2				;
}

/*******************************************************************************
* Description  : 获取面板控件值
* Author       : 2018/6/24  by redmorningcn
*******************************************************************************/
void	SpeedGetCaliCtrlVal(void)   
{
	u8	i;
	
	for(i = 0; i < SPEED_GROUP_NUM;i++)
	{
		GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].lowstandard	,&lstrSpeedCali[i].lowstandard	);  
		GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].lowmeasure		,&lstrSpeedCali[i].lowmeasure	); 
		GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].higstandard	,&lstrSpeedCali[i].higstandard	); 
		GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].higmeasure		,&lstrSpeedCali[i].higmeasure	); 
	}
}

/********************************************************************************************/
/* 根据面板勾选，显示或关闭对应组控件      																	        */
/********************************************************************************************/
void	SpeedCtrlDimmedControl(u8 id)
{
	u8	j;
	u16	*p;
	
	if(id > SPEED_GROUP_NUM)
		return;
	
	GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[id].ansyflg,&lstrSpeedCali[id].ansyflg);
	
	if(lstrSpeedCali[id].ansyflg == 1) {
		p = (u16 *)&lstrSpeedCaliCtrlId[id];
		for(j = 0; j < 5; j++){
			SetCtrlAttribute (gSpeedCali_panelHandle, *p,  ATTR_DIMMED, 1);
			p++;
		}	
	}else{
		p = (u16 *)&lstrSpeedCaliCtrlId[id];
		for(j = 0; j < 5; j++){
			SetCtrlAttribute (gSpeedCali_panelHandle, *p,  ATTR_DIMMED, 0);
			p++;
		}
	}
}

/********************************************************************************************/
/* 根据面板勾选，显示或关闭对应组控件      																	        */
/********************************************************************************************/
void	SpeedCtrlDimmedSendControl(u8	dimmed)
{
	u8	j;

	if(dimmed)
		dimmed = 1;
	
	for(j = 0; j < SPEED_GROUP_NUM; j++){
		SetCtrlAttribute (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].send,  ATTR_DIMMED, dimmed);
	}	
}

/********************************************************************************************/
/* 测量控件置值    																	        */
/********************************************************************************************/
void	SpeedMeasureCtrlSetVal(void)
{
	u8		j;
	//u16		*p = (u16 *)&gstrDtuData.Rec.Vol;
	u16		*p = (u16 *)&Ctrl.Rec.Vol;

	for(j = 0; j < SPEED_GROUP_NUM; j++){
		if(lstrSpeedCali[j].lowflg ){
			SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].lowmeasure,*(p+j));
		}else if(lstrSpeedCali[j].higflg){
			SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].higmeasure,*(p+j));	
		}
	}	
}

/*******************************************************************************
* Description  : 面板显示
* Author       : 2018/6/29  by redmorningcn
*******************************************************************************/
void	SpeedCaliDisplay(void)
{
	u8			i;
	static	u8 	sta = 0;
	
	//判断校准是否发送完成
	for(i = 0;i < SPEED_GROUP_NUM;i++){
		if(lstrSpeedCali[i].calisend) {
			sta = 1;
			break;
		}
		
		if(i == SPEED_GROUP_NUM - 1 && sta){
			sta = 0;
		 	SpeedCtrlDimmedSendControl(0);   	//打开所有发送控件开关
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/
strLineCaliTable	lstrSpeedCaliTable;

/********************************************************************************************
author：redmorningcn 20180622 
Speed校准通讯信号命令准备。（有校准信号，发送校准指令；否则，读取sctrl.rec的值）
********************************************************************************************/
void	SpeedCaliCommcode(void)
{
	u8					i;
	u32					len;
	static	u32			time;
	static	u8			idletimes;
	
	//查询，是否有校准信号正在处理，有则直接退出。
	for(i =0;i < SPEED_GROUP_NUM;i++){
		if(lstrSpeedCali[i].calisend ){
			//超时判断
			if(time <= GetAnsySysTime()){
				if(time + 1000 > GetAnsySysTime()  ) {	//发送超时（为接收到应答）
					return;
				}
			}else{
				time = GetAnsySysTime();				//重新计时
				return;
			}
			lstrSpeedCali[i].calisend = 0;
		}
	}
	
	//查询，是否有校准信号需要发送，有则发送校准信号
	for(i =0;i < LOCO_GROUP_NUM;i++){
		if(lstrSpeedCali[i].califlg){
			lstrSpeedCali[i].califlg 	= 0;
			lstrSpeedCali[i].calisend 	= 1;								//校准发送置位
			
			//计算线性度及零点
			CalcCaliVal(&lstrSpeedCali[i]);						
			
			lstrSpeedCaliTable.CaliBuf[i].line = lstrSpeedCali[i].line;		//赋值给calitable
			lstrSpeedCaliTable.CaliBuf[i].Delta= lstrSpeedCali[i].zero; 
			
			len = sizeof(strLineCalibration);	
			gstrDtuData.paraaddr =  SPEED_CALI_BASE_ADDR + sizeof(strLineCalibration)*i;	//读指定地址

			//gstrDtuData.paralen  =  (u16)((len <<8) + NODE_LOCO);			//读指定数据 (len << 8 + l_DetectGetNode)
			gstrDtuData.paralen  =  (u8)len;								//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrDtuData.node	 =  NODE_LOCO;
			memcpy((u8 *)gstrDtuData.parabuf,(u8 *)&lstrSpeedCaliTable.CaliBuf[i],len);
			l_eqiupmentcode = CMD_DETECT_SET;								// 指定参数读（检测板）
			
			time = GetAnsySysTime();
			return;
		}
	}
	
	if(l_eqiupmentcode == 0)  {												//
											
		if((idletimes++ %3) == 0){  										//空闲时，读Loco校准。    			 
		   	
			gstrDtuData.paraaddr 	= SPEED_CALI_BASE_ADDR ; 
			//gstrDtuData.paralen		= sizeof(lstrLocoCaliTable);
			len						= sizeof(lstrSpeedCaliTable);
			//gstrDtuData.paralen  	= (u16)((NODE_LOCO << 8) + (u8)len);	//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrDtuData.paralen  	= (u8)len;								//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrDtuData.node		= NODE_LOCO;
			l_eqiupmentcode 		= CMD_DETECT_GET; 
		}else{
			gstrDtuData.paraaddr 	= (u16)((u32)&Ctrl.Rec - (u32)&Ctrl) ;	//空闲时，读sctrl.rec记录。

			len  					= sizeof(stcFlshRec);
			gstrDtuData.paralen		= (u8)len;
			gstrDtuData.node		= 0;
			l_eqiupmentcode			= CMD_PARA_GET;	
		}
	}
}

/********************************************************************************************
author：redmorningcn 20180629 
数据接收准备。（接收应答或数据）
********************************************************************************************/
void	SpeedGetRecvCaliInfo(void)
{
	u8	reclen;
	
	if(gstrDtuData.dataokflg == 1)								//	接收到数据
	{														
		gstrDtuData.dataokflg	= 0;		
		//reclen  = gstrDtuData.recdatalen >> 8;				//	接收数据长度
		reclen  = gstrDtuData.recdatalen ;						//	接收数据长度  
		
		if(reclen == sizeof(stcFlshRec)){						//接收到数据记录
			memcpy((u8 *)&Ctrl.Rec,(u8 *)&gstrDtuData.parabuf[0],reclen);	
		}else if(reclen == sizeof(lstrSpeedCaliTable)){ 
			memcpy((u8 *)&lstrSpeedCaliTable,(u8 *)&gstrDtuData.parabuf[0],reclen);
		}
	}
}

