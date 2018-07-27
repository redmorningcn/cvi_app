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

strLineCaliTable		lstrSpeedCaliTable;							//速度信号校准表         

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
		
			for(u8 j = 0;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].califlg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}
			
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
			
			for(u8 j = 1;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].califlg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}		
			
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
			
			for(u8 j = 2;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].califlg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}				
			
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
			
			for(u8 j = 0;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].lowflg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}
			
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
			
			for(u8 j = 1;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].lowflg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}			
			
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

			for(u8 j = 2;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].lowflg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}
			
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
			
			for(u8 j = 2;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].higflg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}
			
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
			
			for(u8 j = 0;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].higflg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}
			
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

			for(u8 j = 1;j < SPEED_GROUP_NUM;)  {
				GetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].ansyflg	,&lstrSpeedCali[j].ansyflg);
				if(	lstrSpeedCali[j].ansyflg == 1 ){
					lstrSpeedCali[j].higflg = 1;	
				}
				
				j += SPEED_TYPE_NUM; 
			}
			
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
					lstrSpeedCali[i].ansyflg = 0;
					
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
	lstrSpeedCaliCtrlId[0].info			=	SPEEDCALI_G1VCC_CUR_INFO		;

	
	lstrSpeedCaliCtrlId[1].lowstandard	=	SPEEDCALI_G1SPEED1_LOW_STAND	;		
	lstrSpeedCaliCtrlId[1].lowmeasure	=	SPEEDCALI_G1SPEED1_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[1].higstandard	=	SPEEDCALI_G1SPEED1_HIG_STAND	;
	lstrSpeedCaliCtrlId[1].higmeasure	=	SPEEDCALI_G1SPEED1_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[1].ansyflg		=	SPEEDCALI_G1SPEED1_SYNC			;
	lstrSpeedCaliCtrlId[1].send			=	SPEEDCALI_G1SPEED1				;
	lstrSpeedCaliCtrlId[1].info			=	SPEEDCALI_G1SPEED1_CUR_INFO		;

	
	lstrSpeedCaliCtrlId[2].lowstandard	=	SPEEDCALI_G1SPEED2_LOW_STAND	;		
	lstrSpeedCaliCtrlId[2].lowmeasure	=	SPEEDCALI_G1SPEED2_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[2].higstandard	=	SPEEDCALI_G1SPEED2_HIG_STAND	;
	lstrSpeedCaliCtrlId[2].higmeasure	=	SPEEDCALI_G1SPEED2_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[2].ansyflg		=	SPEEDCALI_G1SPEED2_SYNC			;
	lstrSpeedCaliCtrlId[2].send			=	SPEEDCALI_G1SPEED2				;
	lstrSpeedCaliCtrlId[2].info			=	SPEEDCALI_G1SPEED2_CUR_INFO		;
	
	lstrSpeedCaliCtrlId[3].lowstandard	=	SPEEDCALI_G2VCC_LOW_STAND		;		
	lstrSpeedCaliCtrlId[3].lowmeasure	=	SPEEDCALI_G2VCC_LOW_MEASURE		;
	lstrSpeedCaliCtrlId[3].higstandard	=	SPEEDCALI_G2VCC_HIG_STAND		;
	lstrSpeedCaliCtrlId[3].higmeasure	=	SPEEDCALI_G2VCC_HIG_MEASURE		;
	lstrSpeedCaliCtrlId[3].ansyflg		=	SPEEDCALI_G2VCC_SYNC			;
	lstrSpeedCaliCtrlId[3].send			=	SPEEDCALI_G2VCC					;
	lstrSpeedCaliCtrlId[3].info			=	SPEEDCALI_G2VCC_CUR_INFO		;
	
	lstrSpeedCaliCtrlId[4].lowstandard	=	SPEEDCALI_G2SPEED1_LOW_STAND	;		
	lstrSpeedCaliCtrlId[4].lowmeasure	=	SPEEDCALI_G2SPEED1_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[4].higstandard	=	SPEEDCALI_G2SPEED1_HIG_STAND	;
	lstrSpeedCaliCtrlId[4].higmeasure	=	SPEEDCALI_G2SPEED1_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[4].ansyflg		=	SPEEDCALI_G2SPEED1_SYNC			;
	lstrSpeedCaliCtrlId[4].send			=	SPEEDCALI_G2SPEED1				;
	lstrSpeedCaliCtrlId[4].info			=	SPEEDCALI_G2SPEED1_CUR_INFO		;
	
	lstrSpeedCaliCtrlId[5].lowstandard	=	SPEEDCALI_G2SPEED2_LOW_STAND	;		
	lstrSpeedCaliCtrlId[5].lowmeasure	=	SPEEDCALI_G2SPEED2_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[5].higstandard	=	SPEEDCALI_G2SPEED2_HIG_STAND	;
	lstrSpeedCaliCtrlId[5].higmeasure	=	SPEEDCALI_G2SPEED2_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[5].ansyflg		=	SPEEDCALI_G2SPEED2_SYNC			;
	lstrSpeedCaliCtrlId[5].send			=	SPEEDCALI_G2SPEED2				;
	lstrSpeedCaliCtrlId[5].info			=	SPEEDCALI_G2SPEED2_CUR_INFO		;

	lstrSpeedCaliCtrlId[6].lowstandard	=	SPEEDCALI_G3VCC_LOW_STAND		;		
	lstrSpeedCaliCtrlId[6].lowmeasure	=	SPEEDCALI_G3VCC_LOW_MEASURE		;
	lstrSpeedCaliCtrlId[6].higstandard	=	SPEEDCALI_G3VCC_HIG_STAND		;
	lstrSpeedCaliCtrlId[6].higmeasure	=	SPEEDCALI_G3VCC_HIG_MEASURE		;
	lstrSpeedCaliCtrlId[6].ansyflg		=	SPEEDCALI_G3VCC_SYNC			;
	lstrSpeedCaliCtrlId[6].send			=	SPEEDCALI_G3VCC					;
	lstrSpeedCaliCtrlId[6].info			=	SPEEDCALI_G3VCC_CUR_INFO		;
	
	lstrSpeedCaliCtrlId[7].lowstandard	=	SPEEDCALI_G3SPEED1_LOW_STAND	;		
	lstrSpeedCaliCtrlId[7].lowmeasure	=	SPEEDCALI_G3SPEED1_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[7].higstandard	=	SPEEDCALI_G3SPEED1_HIG_STAND	;
	lstrSpeedCaliCtrlId[7].higmeasure	=	SPEEDCALI_G3SPEED1_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[7].ansyflg		=	SPEEDCALI_G3SPEED1_SYNC			;
	lstrSpeedCaliCtrlId[7].send			=	SPEEDCALI_G3SPEED1				;
	lstrSpeedCaliCtrlId[7].info			=	SPEEDCALI_G3SPEED1_CUR_INFO		;
	
	lstrSpeedCaliCtrlId[8].lowstandard	=	SPEEDCALI_G3SPEED2_LOW_STAND	;		
	lstrSpeedCaliCtrlId[8].lowmeasure	=	SPEEDCALI_G3SPEED2_LOW_MEASURE	;
	lstrSpeedCaliCtrlId[8].higstandard	=	SPEEDCALI_G3SPEED2_HIG_STAND	;
	lstrSpeedCaliCtrlId[8].higmeasure	=	SPEEDCALI_G3SPEED2_HIG_MEASURE	;
	lstrSpeedCaliCtrlId[8].ansyflg		=	SPEEDCALI_G3SPEED2_SYNC			;
	lstrSpeedCaliCtrlId[8].send			=	SPEEDCALI_G3SPEED2				;
	lstrSpeedCaliCtrlId[8].info			=	SPEEDCALI_G3SPEED2_CUR_INFO		;
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
	u16		lowstandard = 0,higstandard = 0;
	
	for(j = 0; j < SPEED_GROUP_NUM; j++){
		if(lstrSpeedCali[j].lowflg ){
			
			switch (j % SPEED_TYPE_NUM){
				case 0:		SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].lowmeasure,lstrSpeedDetect[j/SPEED_TYPE_NUM].vcc_vol);
							GetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[0].lowstandard,&lowstandard); 
					break;
				case 1: 	SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].lowmeasure,lstrSpeedDetect[j/SPEED_TYPE_NUM].para[0].Voh);
							GetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[1].lowstandard,&lowstandard); 

					break;
				case 2:		SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].lowmeasure,lstrSpeedDetect[j/SPEED_TYPE_NUM].para[1].Voh); 
							GetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[2].lowstandard,&lowstandard); 

					break;
			}
			
			if(j < SPEED_TYPE_NUM){
				u8	i = 0;
				for(i = j;i< SPEED_GROUP_NUM; ) {
					if(lstrSpeedCali[i].ansyflg == 1){ //同步校准
						SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].lowstandard,lowstandard);
					}
					
					i += SPEED_TYPE_NUM;
				}
			}
			
			lstrSpeedCali[j].lowflg = 0;
			
		}else if(lstrSpeedCali[j].higflg){
			switch (j % SPEED_TYPE_NUM){
				case 0:		SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].higmeasure,lstrSpeedDetect[j/SPEED_TYPE_NUM].vcc_vol);
							GetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[0].higstandard,&higstandard);   
					break;
				case 1: 	SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].higmeasure,lstrSpeedDetect[j/SPEED_TYPE_NUM].para[0].Voh);
							GetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[1].higstandard,&higstandard);
					break;
				case 2:		SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[j].higmeasure,lstrSpeedDetect[j/SPEED_TYPE_NUM].para[1].Voh); 
							GetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[2].higstandard,&higstandard);
					break;
			}
			
			if(j < SPEED_TYPE_NUM){
				u8	i = 0;
				for(i = j;i< SPEED_GROUP_NUM; ) {
					
					if(lstrSpeedCali[i].ansyflg == 1){ //同步校准
						SetCtrlVal (gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].higstandard,higstandard);
					}
					i += SPEED_TYPE_NUM;
				}
			}

			lstrSpeedCali[j].higflg = 0;
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
	u8		infobuf[256];

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
		
		u16	voltage = 0;
		switch (i % SPEED_TYPE_NUM){
			case 0:		
				voltage = lstrSpeedDetect[i/SPEED_TYPE_NUM].vcc_vol;
				break;
			case 1: 	
				voltage = lstrSpeedDetect[i/SPEED_TYPE_NUM].para[0].Voh;
				break;
			case 2:		
				voltage = lstrSpeedDetect[i/SPEED_TYPE_NUM].para[1].Voh;   	
				break;
		}
		snprintf((char *)infobuf,100," 电压：%-5d (10mV)\r\n 线性：%-5d (/10000)\r\n 偏移：%-5d (10mV)",
				 									voltage,lstrSpeedCaliTable.CaliBuf[i].line,lstrSpeedCaliTable.CaliBuf[i].Delta);
		
		SetCtrlVal(gSpeedCali_panelHandle,lstrSpeedCaliCtrlId[i].info,infobuf);
		
		lstrSpeedCali[i].line = (u16)lstrSpeedCaliTable.CaliBuf[i].line;
		lstrSpeedCali[i].zero = lstrSpeedCaliTable.CaliBuf[i].Delta;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/


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
	static	u8			sendflg = 0;
	static	u8			sendtimes;
	
	if(sendflg == 1) {					//限制发送频次
		if(sendtimes--)
			return;
		sendflg = 0;	
	}
	
	sendtimes = 2;

	
	//查询，是否有校准信号正在处理，有则直接退出。
	for(i =0;i < SPEED_GROUP_NUM;i++){
		if(lstrSpeedCali[i].calisend ){
			//超时判断
			if(time <= GetAnsySysTime()){
				if(time + 500 > GetAnsySysTime()  ) {	//发送超时（为接收到应答）
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
	for(i =0;i < SPEED_GROUP_NUM;i++){
		if(lstrSpeedCali[i].califlg){
			lstrSpeedCali[i].califlg 	= 0;
			lstrSpeedCali[i].calisend 	= 1;								//校准发送置位
			
			//计算线性度及零点
			CalcCaliVal(&lstrSpeedCali[i]);						
			
			lstrSpeedCaliTable.CaliBuf[i].line = lstrSpeedCali[i].line;		//赋值给calitable
			lstrSpeedCaliTable.CaliBuf[i].Delta= lstrSpeedCali[i].zero; 
			
			len = sizeof(strLineCalibration);	
			gstrSendDtuData.paraaddr =  SPEED_CALI_BASE_ADDR + sizeof(strLineCalibration)*(i % SPEED_TYPE_NUM) ;	//读指定地址

			gstrSendDtuData.paralen  =  (u8)len;						   //读指定数据 (len << 8 + l_DetectGetNode)  
			gstrSendDtuData.node	 =  (i / SPEED_TYPE_NUM) + 1;		   // node 地址1-3
			memcpy((u8 *)gstrSendDtuData.parabuf,(u8 *)&lstrSpeedCaliTable.CaliBuf[i],len);
			l_eqiupmentcode = CMD_DETECT_SET;								// 指定参数读（检测板）
			
			sendflg = 1;
			time = GetAnsySysTime();
			return;
		}
	}
	
	static	u8	readnode = 0;
	if(l_eqiupmentcode == 0)  {												//
											
		if((idletimes++ %2) == 0){  										//空闲时，读speed校准。    			 
		   	
			
			gstrSendDtuData.paraaddr 	= SPEED_CALI_BASE_ADDR ; 
			//gstrSendDtuData.paralen		= sizeof(lstrLocoCaliTable);
			len							= sizeof(lstrSpeedCaliTable.CaliBuf[0]) * SPEED_TYPE_NUM;	//3个点
			//gstrSendDtuData.paralen  	= (u16)((NODE_LOCO << 8) + (u8)len);	//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrSendDtuData.paralen  	= (u8)len;								//读指定数据 (len << 8 + l_DetectGetNode)  
			
			readnode++;
			gstrSendDtuData.node		= (readnode % SPEED_TYPE_NUM) + 1; 		// node 地址1-3
			
			l_eqiupmentcode 			= CMD_DETECT_GET; 
		}else{
			SetDetectReadCode();					//取速度检测信号
		}
		
		time = GetAnsySysTime();
		sendflg = 1;
	}
}

/********************************************************************************************
author：redmorningcn 20180629 
数据接收准备。（接收应答或数据）
********************************************************************************************/
void	SpeedGetRecvCaliInfo(void)
{
	u8	reclen;
	u8	node;
	
	if(gstrRecDtuData.dataokflg == 1)											//	接收到数据
	{														
		reclen  = gstrRecDtuData.recdatalen ;									//	接收数据长度 
		
		if(reclen == sizeof(lstrSpeedCaliTable.CaliBuf[0]) * SPEED_TYPE_NUM)	// 取校准值
		{
			node = gstrRecDtuData.node;	
			if(node < 4 && node > 0){
				memcpy((u8 *)&lstrSpeedCaliTable.CaliBuf[(node -1)*SPEED_TYPE_NUM],gstrRecDtuData.parabuf,reclen);
			}
		}
		
		GetDetectInfo();														// 取检测的电压值;
		
		gstrRecDtuData.dataokflg = 0;											// 标识清零
	}
}

