#include <userint.h>

/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.  20180623
 *
 *   Description:
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/

#include 	"cvi_LocoCali.h"
#include  	"cvi_config.h"
#include  	"cvi_LocoCaliType.h"
#include  	"setpara.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//面板变量
int 					gLocoCali_panelHandle;
extern		int			gmainPanel;
strLineCali				lstrLocoCali[LOCO_GROUP_NUM];			//校验参数
strLineCali				lstrLocoCaliCtrlId[LOCO_GROUP_NUM];		//面板ID

strLineCaliTable		lstrLocoCaliTable;						//校准系数			


#define		CALI_LINE_MUTIPLY		(10000)
/********************************************************************************************/
//local
/********************************************************************************************/

int CVICALLBACK LocoCaliTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	static	u8	tmp = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(gLocoCali_panelHandle)			//面板有效，则进行定时器操作
			{
				if(tmp == 0){
					LocoInitCaliCtrlId();
					tmp++;
				}
				LocoCaliCommcode();				//校准串口通讯
				
				Com_SetParaTask();				//串口参数设置
				
				Com_SetParaRecTask();			// 串口数据接收
				
				LocoGetRecvCaliInfo();			//取串接收
				
				LocoCaliDisplay();				//显示面板内容
			}
			break;
	}
	return 0;
}


/********************************************************************************************/
//载并显示面板。	redmoringcn 20180620
/********************************************************************************************/
void LoadLocoCaliPanel(void)
{
	gLocoCali_panelHandle = LoadPanel (0, "cvi_LocoCali.uir", LOCOCALI);
	/* 	Display the panel and run the UI */
	DisplayPanel (gLocoCali_panelHandle);
}

/********************************************************************************************/
/*打开面板																	        */
/********************************************************************************************/
int CVICALLBACK OpenLocoCaliCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadLocoCaliPanel();

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
void	QuitLocoCaliPanel(void)
{
	HidePanel (gLocoCali_panelHandle);

	DisplayPanel (gmainPanel);

	gLocoCali_panelHandle = 0;
}

int CVICALLBACK V110SyncCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	u8	i,j;
	u16	*p;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,LOCOCALI_V110_SYNC,&lstrLocoCali[0].ansyflg);
			
			if(lstrLocoCali[0].ansyflg == 1) {
				for(i = 1;i < LOCO_GROUP_NUM;i++){
					p = (u16 *)&lstrLocoCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 1);
						p++;
					}
					
					SetCtrlVal (panel, lstrLocoCaliCtrlId[i].ansyflg,  1);
				}
			}else{
				for(i = 1;i < LOCO_GROUP_NUM;i++){
					p = (u16 *)&lstrLocoCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 0);
						p++;
					}
					
					SetCtrlVal (panel, lstrLocoCaliCtrlId[i].ansyflg,  0);
				}
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK QySyncCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LocoCtrlDimmedControl(1);

			break;
	}
	return 0;
}

int CVICALLBACK ZdSyncCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LocoCtrlDimmedControl(2);

			break;
	}
	return 0;
}

int CVICALLBACK XqSyncCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LocoCtrlDimmedControl(3);

			break;
	}
	return 0;
}

int CVICALLBACK XhSyncCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LocoCtrlDimmedControl(4);

			break;
	}
	return 0;
}

int CVICALLBACK LwSyncCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LocoCtrlDimmedControl(5);

			break;
	}
	return 0;
}

int CVICALLBACK LocoCaliPanelCB (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitLocoCaliPanel();				//退出面板操作
			break;
	}
	return 0;
}


//读取110v低位值，并在窗口显示。
int CVICALLBACK V110LowCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[0].lowflg = 1;
			//读同步信号。同步的相应标识置位
			
			for(u8 i = 1;i < LOCO_GROUP_NUM;i++)		//如果选择了同步信息，则校准值设为相同
			{
				GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].ansyflg	,&lstrLocoCali[i].ansyflg);
				if(	lstrLocoCali[i].ansyflg == 1 )
				{
					lstrLocoCali[i].lowflg = 1;	
				}
			}			
			
			LocoMeasureCtrlSetVal();
			//LocoStandCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK QYLowCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[1].lowflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK ZDLowCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[2].lowflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK XQLowCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[3].lowflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK XHLowCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[4].lowflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK LWLowCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[5].lowflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK LWCaliCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[5].califlg = 1;
			LocoCtrlDimmedSendControl(1);	//关闭所有发送
			LocoGetCaliCtrlVal();		//取面板值  
			break;
	}
	return 0;
}

int CVICALLBACK XHCaliCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[4].califlg = 1;
			LocoCtrlDimmedSendControl(1);	//关闭所有发送
			LocoGetCaliCtrlVal();		//取面板值  
			break;
	}
	return 0;
}

int CVICALLBACK XQCaliCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[3].califlg = 1;
			LocoCtrlDimmedSendControl(1);	//关闭所有发送
			LocoGetCaliCtrlVal();		//取面板值  
			break;
	}
	return 0;
}

int CVICALLBACK ZDCaliCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[2].califlg = 1;
			LocoCtrlDimmedSendControl(1);	//关闭所有发送
			LocoGetCaliCtrlVal();		//取面板值  
			break;
	}
	return 0;
}

int CVICALLBACK QYCaliCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[1].califlg = 1;
			LocoCtrlDimmedSendControl(1);	//关闭所有发送
			LocoGetCaliCtrlVal();		//取面板值

			break;
	}
	return 0;
}

int CVICALLBACK V110CaliCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[0].califlg = 1;
			
			for(u8 i = 1;i < LOCO_GROUP_NUM;i++)		//如果选择了同步信息，则校准值设为相同
			{
				GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].ansyflg	,&lstrLocoCali[i].ansyflg);
				if(	lstrLocoCali[i].ansyflg == 1 )
				{
					lstrLocoCali[i].califlg = 1;	
				}
			}
			
			LocoCtrlDimmedSendControl(1);	//关闭所有发送
			LocoGetCaliCtrlVal();			//取面板值
			
			break;
	}
	return 0;
}

int CVICALLBACK HelpCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	char 	*fileName;									//文件指针
	char 	projectDir[MAX_PATHNAME_LEN];				//工程路径
	char 	fullPath[MAX_PATHNAME_LEN];					//文件全路径
	int		filecom1hand;								//文件句柄
	char	infobuf[1024*8];							
	
	fileName = "calihelp.txt";							//校准帮助文件
	
	GetProjectDir (projectDir) ;						//取项目路径

	MakePathname (projectDir, fileName, fullPath);		//文件路劲 where fullPath has the following format: c:\myproject\myfile.dat
	
	filecom1hand = OpenFile (fullPath, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);		//打开文件
		
	SetFilePtr (filecom1hand, 0, 0);								//文件从头开始
	
	ReadFile (filecom1hand, infobuf, sizeof(infobuf)-10);			//读帮助信息			
	
	CloseFile(filecom1hand);															//关闭文件     				
	
	switch (event)
	{
		case EVENT_COMMIT:
				//MessagePopup ("帮助信息", "1、选择“同步校准”，将和110V校准值相同！\r\n2、校准分高、低两点，在输入测量值后，对应测量值自动输入（可手动调整）");
				MessagePopup ("帮助信息",infobuf);
			break;
	}
	

	return 0;
}


int CVICALLBACK V110HigCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[0].higflg = 1;
			
			for(u8 i = 1;i < LOCO_GROUP_NUM;i++)		//如果选择了同步信息，则校准值设为相同
			{
				GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].ansyflg	,&lstrLocoCali[i].ansyflg);
				if(	lstrLocoCali[i].ansyflg == 1 )
				{
					lstrLocoCali[i].higflg = 1;	
				}
			}		
			
			LocoMeasureCtrlSetVal();
			//LocoStandCtrlSetVal(); 
			break;
	}
	return 0;
}

int CVICALLBACK QYHigCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[1].higflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK ZDHigCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[2].higflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK XQHigCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[3].higflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK XHHigCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[4].higflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

int CVICALLBACK LWHigCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			lstrLocoCali[5].higflg = 1;
			LocoMeasureCtrlSetVal();
			break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//author：redmorningcn   20180621
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板显示函数，和面板控件操作无关
/********************************************************************************************/


/*******************************************************************************
* Description  : 初始化工况校准控件ID，和面板控件建立联系
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	LocoInitCaliCtrlId(void)   
{
	lstrLocoCaliCtrlId[0].lowstandard	=	LOCOCALI_V110_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[0].lowmeasure	=	LOCOCALI_V110_LOW_MEASURE	;
	lstrLocoCaliCtrlId[0].higstandard	=	LOCOCALI_V110_HIG_STANDARD	;
	lstrLocoCaliCtrlId[0].higmeasure	=	LOCOCALI_V110_HIG_MEASURE	;
	lstrLocoCaliCtrlId[0].ansyflg		=	LOCOCALI_V110_SYNC			;
	lstrLocoCaliCtrlId[0].send			=	LOCOCALI_V110				;
	lstrLocoCaliCtrlId[0].info			=	LOCOCALI_V110_CUR_INFO		;

	lstrLocoCaliCtrlId[1].lowstandard	=	LOCOCALI_QY_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[1].lowmeasure	=	LOCOCALI_QY_LOW_MEASURE		;
	lstrLocoCaliCtrlId[1].higstandard	=	LOCOCALI_QY_HIG_STANDARD	;
	lstrLocoCaliCtrlId[1].higmeasure	=	LOCOCALI_QY_HIG_MEASURE		;
	lstrLocoCaliCtrlId[1].ansyflg		=	LOCOCALI_QY_SYNC			;
	lstrLocoCaliCtrlId[1].send			=	LOCOCALI_QY					;  
	lstrLocoCaliCtrlId[1].info			=	LOCOCALI_QY_CUR_INFO		;

	lstrLocoCaliCtrlId[2].lowstandard	=	LOCOCALI_ZD_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[2].lowmeasure	=	LOCOCALI_ZD_LOW_MEASURE		;
	lstrLocoCaliCtrlId[2].higstandard	=	LOCOCALI_ZD_HIG_STANDARD	;
	lstrLocoCaliCtrlId[2].higmeasure	=	LOCOCALI_ZD_HIG_MEASURE		;
	lstrLocoCaliCtrlId[2].ansyflg		=	LOCOCALI_ZD_SYNC			;
	lstrLocoCaliCtrlId[2].send			=	LOCOCALI_ZD					; 
	lstrLocoCaliCtrlId[2].info			=	LOCOCALI_ZD_CUR_INFO		;
	
	lstrLocoCaliCtrlId[3].lowstandard	=	LOCOCALI_XQ_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[3].lowmeasure	=	LOCOCALI_XQ_LOW_MEASURE		;
	lstrLocoCaliCtrlId[3].higstandard	=	LOCOCALI_XQ_HIG_STANDARD	;
	lstrLocoCaliCtrlId[3].higmeasure	=	LOCOCALI_XQ_HIG_MEASURE		;
	lstrLocoCaliCtrlId[3].ansyflg		=	LOCOCALI_XQ_SYNC			;
	lstrLocoCaliCtrlId[3].send			=	LOCOCALI_XQ					;
	lstrLocoCaliCtrlId[3].info			=	LOCOCALI_XQ_CUR_INFO		;

	lstrLocoCaliCtrlId[4].lowstandard	=	LOCOCALI_XH_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[4].lowmeasure	=	LOCOCALI_XH_LOW_MEASURE		;
	lstrLocoCaliCtrlId[4].higstandard	=	LOCOCALI_XH_HIG_STANDARD	;
	lstrLocoCaliCtrlId[4].higmeasure	=	LOCOCALI_XH_HIG_MEASURE		;
	lstrLocoCaliCtrlId[4].ansyflg		=	LOCOCALI_XH_SYNC			;
	lstrLocoCaliCtrlId[4].send			=	LOCOCALI_XH					;
	lstrLocoCaliCtrlId[4].info			=	LOCOCALI_XH_CUR_INFO		;

	lstrLocoCaliCtrlId[5].lowstandard	=	LOCOCALI_LW_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[5].lowmeasure	=	LOCOCALI_LW_LOW_MEASURE		;
	lstrLocoCaliCtrlId[5].higstandard	=	LOCOCALI_LW_HIG_STANDARD	;
	lstrLocoCaliCtrlId[5].higmeasure	=	LOCOCALI_LW_HIG_MEASURE		;  
	lstrLocoCaliCtrlId[5].ansyflg		=	LOCOCALI_LW_SYNC			;
	lstrLocoCaliCtrlId[5].send			=	LOCOCALI_LW					; 
	lstrLocoCaliCtrlId[5].info			=	LOCOCALI_LW_CUR_INFO		;
}

/*******************************************************************************
* Description  : 获取面板控件值
* Author       : 2018/6/24  by redmorningcn
*******************************************************************************/
void	LocoGetCaliCtrlVal(void)   
{
	u8	i;
	
	for(i = 0; i < LOCO_GROUP_NUM;i++)
	{
		GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].lowstandard	,&lstrLocoCali[i].lowstandard	);  
		GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].lowmeasure	,&lstrLocoCali[i].lowmeasure	); 
		GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].higstandard	,&lstrLocoCali[i].higstandard	); 
		GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].higmeasure	,&lstrLocoCali[i].higmeasure	); 
	}
}

/********************************************************************************************/
/* 根据面板勾选，显示或关闭对应组控件      																	        */
/********************************************************************************************/
void	LocoCtrlDimmedControl(u8 id)
{
	u8	j;
	u16	*p;
	
	if(id > LOCO_GROUP_NUM)
		return;
	
	GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[id].ansyflg,&lstrLocoCali[id].ansyflg);
	
	if(lstrLocoCali[id].ansyflg == 1) {
		p = (u16 *)&lstrLocoCaliCtrlId[id];
		for(j = 0; j < 5; j++){
			SetCtrlAttribute (gLocoCali_panelHandle, *p,  ATTR_DIMMED, 1);
			p++;
		}	
	}else{
		p = (u16 *)&lstrLocoCaliCtrlId[id];
		for(j = 0; j < 5; j++){
			SetCtrlAttribute (gLocoCali_panelHandle, *p,  ATTR_DIMMED, 0);
			p++;
		}
	}
}

/********************************************************************************************/
/* 根据面板勾选，显示或关闭对应组控件      																	        */
/********************************************************************************************/
void	LocoCtrlDimmedSendControl(u8	dimmed)
{
	u8	j;

	if(dimmed)
		dimmed = 1;
	
	for(j = 0; j < LOCO_GROUP_NUM; j++){
		SetCtrlAttribute (gLocoCali_panelHandle,lstrLocoCaliCtrlId[j].send,  ATTR_DIMMED, dimmed);
	}	
}

/********************************************************************************************/
/* 测量控件置值    																	        */
/********************************************************************************************/
void	LocoMeasureCtrlSetVal(void)
{
	u8		j;
	//u16		*p = (u16 *)&gstrDtuData.Rec.Vol;
	u16		*p = (u16 *)&Ctrl.Rec.Vol;
	u16		lowstandard,higstandard;
	
	GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[0].lowstandard,&lowstandard);
	GetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[0].higstandard,&higstandard);
	

	for(j = 0; j < LOCO_GROUP_NUM; j++){
		if(lstrLocoCali[j].lowflg ){
			SetCtrlVal (gLocoCali_panelHandle,lstrLocoCaliCtrlId[j].lowmeasure,*(p+j));
			
			if(lstrLocoCali[j].ansyflg == 1) //同步校准
				SetCtrlVal (gLocoCali_panelHandle,lstrLocoCaliCtrlId[j].lowstandard,lowstandard);
			
			lstrLocoCali[j].lowflg = 0;
		}else if(lstrLocoCali[j].higflg){
			SetCtrlVal (gLocoCali_panelHandle,lstrLocoCaliCtrlId[j].higmeasure,*(p+j));
			
			if(lstrLocoCali[j].ansyflg == 1)//同步校准
				SetCtrlVal (gLocoCali_panelHandle,lstrLocoCaliCtrlId[j].higstandard,higstandard);
			
			lstrLocoCali[j].higflg = 0;    
		}
	}	
}


/*******************************************************************************
* Description  : 面板显示
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	LocoCaliDisplay(void)
{
	u8			i;
	static	u8 	sta = 0;
	u8		infobuf[256];
	u16		*p = (u16 *)&Ctrl.Rec.Vol;

	
	//判断校准是否发送完成
	for(i = 0;i < LOCO_GROUP_NUM;i++){
		if(lstrLocoCali[i].calisend) {
			sta = 1;
			break;
		}
		
		if(i == LOCO_GROUP_NUM - 1 && sta){
			sta = 0;
		 	LocoCtrlDimmedSendControl(0);   //打开所有发送控件开关
		}
		
		snprintf((char *)infobuf,100," 电压：%-5d (10mV)\r\n 线性：%-5d (/10000)\r\n 偏移：%-5d (mV)",
				 									*(p+i),lstrLocoCaliTable.CaliBuf[i].line,lstrLocoCaliTable.CaliBuf[i].Delta);
		
		SetCtrlVal(gLocoCali_panelHandle,lstrLocoCaliCtrlId[i].info,infobuf);
		
		lstrLocoCali[i].line = lstrLocoCaliTable.CaliBuf[i].line;
		lstrLocoCali[i].zero = lstrLocoCaliTable.CaliBuf[i].Delta;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/

/*******************************************************************************************
计算校准。根据测量点（measure）和目标点（standard），计算出修正线性（*10000）和偏移。
*******************************************************************************************/
void	CalcCaliVal(strLineCali *cali){
	
	double	linemeasure,linecali;
	double	zeromeasure,zerocali;

	double	lstline,lstzero;

//	cali->line 	= CALI_LINE_MUTIPLY;		//默认值
//	cali->zero	= 0;

	// 计算值异常判断
	if(		cali->higmeasure  < cali->lowmeasure  
		||	cali->higstandard < cali->lowstandard
		|| 	cali->higmeasure  == 0
		||  cali->higstandard == 0
		||  cali->higmeasure  == cali->lowmeasure
		||	cali->higstandard == cali->lowstandard
	 )	{
		  // 异常退出
		cali->caliErr  = 1;
		return;
	 }
  
	 // 计算线性和斜率
	linemeasure = (double)(cali->higmeasure - cali->lowmeasure)/(double)(cali->higstandard - cali->lowstandard);
	zeromeasure = (double)cali->higmeasure  - (double)linemeasure *  (double)cali->higstandard;
 
	 // 线性度判断
	if(linemeasure > 2 || linemeasure < 0.5) {
		cali->caliErr  = 1;
		return;
	}
 
	 // 斜率判断
	if(zeromeasure > 500 || zeromeasure <-500){
		cali->caliErr  = 1; 
		return;
	}
 
	linecali = 1/linemeasure;
	zerocali = -zeromeasure;
 
	 //校准前的值
	lstline = cali->line;
	lstzero = cali->zero;
	  //赋值 
	if(	(lstline/CALI_LINE_MUTIPLY > 2 || lstline/CALI_LINE_MUTIPLY < 0.5)  						//原值超限，直接赋值
	 || (lstline*linecali / CALI_LINE_MUTIPLY >2 || lstline*linecali / CALI_LINE_MUTIPLY < 0.5  )	//累计后超限，直接赋值   		  
	){
		cali->line =  linecali * CALI_LINE_MUTIPLY; 
		cali->caliErr  = 1; 

	}else{
		cali->line =  lstline * linecali;															//原值和计算值相乘（累计效应）												
	}
		  
	if(		(lstzero > 500 || lstzero <-500)	 													//原值超限
		||	((lstzero + zerocali)>500 || (lstzero + zerocali)< -500)){								//计算后超限
		cali->zero =  (short)zerocali;
		cali->caliErr  = 1; 
	}else{
		cali->zero = (short)(lstzero + zerocali);													//原值和计算值累计
	}
}

/********************************************************************************************
author：redmorningcn 20180622 
loco校准通讯信号命令准备。（有校准信号，发送校准指令；否则，读取sctrl.rec的值）
********************************************************************************************/
void	LocoCaliCommcode(void)
{
	u8					i;
	u32					len;
	static	u32			time;
	static	u8			idletimes;
	
	if(time <= GetAnsySysTime()){
		if(time + 200 > GetAnsySysTime()  ) {				// 周期发送，控制发送频率
			return;
		} 
	}
	
	//查询，是否有校准信号正在处理，有则直接退出。
	for(i =0;i < LOCO_GROUP_NUM;i++){
		if(lstrLocoCali[i].calisend ){
			//超时判断
			if(time <= GetAnsySysTime()){
				if(time + 500 > GetAnsySysTime()  ) {	//发送超时（为接收到应答）
					return;
				}
			}else{
				time = GetAnsySysTime();				//重新计时
				return;
			}
			lstrLocoCali[i].calisend = 0;
		}
	}
	
	//查询，是否有校准信号需要发送，有则发送校准信号
	for(i =0;i < LOCO_GROUP_NUM;i++){
		if(lstrLocoCali[i].califlg){
			lstrLocoCali[i].califlg 	= 0;
			lstrLocoCali[i].calisend 	= 1;								//校准发送置位
			
			//计算线性度及零点
			CalcCaliVal(&lstrLocoCali[i]);						
			
			lstrLocoCaliTable.CaliBuf[i].line = lstrLocoCali[i].line;		//赋值给calitable
			lstrLocoCaliTable.CaliBuf[i].Delta= lstrLocoCali[i].zero; 
			
			len = sizeof(strLineCalibration);	
			gstrSendDtuData.paraaddr =  LOCO_CALI_BASE_ADDR + sizeof(strLineCalibration)*i;	//读指定地址

			//gstrSendDtuData.paralen  =  (u16)((len <<8) + NODE_LOCO);			//读指定数据 (len << 8 + l_DetectGetNode)
			gstrSendDtuData.paralen  =  (u8)len;								//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrSendDtuData.node	 =  NODE_LOCO;
			memcpy((u8 *)gstrSendDtuData.parabuf,(u8 *)&lstrLocoCaliTable.CaliBuf[i],len);
			l_eqiupmentcode = CMD_DETECT_SET;								// 指定参数读（检测板）
			
			time = GetAnsySysTime();
			return;
		}
	}
	
	if(l_eqiupmentcode == 0)  {												//
											
		if((idletimes++ %3) == 0){  										//空闲时，读Loco校准。    			 
		   	
			gstrSendDtuData.paraaddr 	= LOCO_CALI_BASE_ADDR ; 
			//gstrDtuData.paralen		= sizeof(lstrLocoCaliTable);
			len							= sizeof(lstrLocoCaliTable);
			//gstrDtuData.paralen  	= (u16)((NODE_LOCO << 8) + (u8)len);	//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrSendDtuData.paralen  	= (u8)len;								//读指定数据 (len << 8 + l_DetectGetNode)  
			gstrSendDtuData.node		= NODE_LOCO;
			l_eqiupmentcode 			= CMD_DETECT_GET; 
		}else{
			gstrSendDtuData.paraaddr 	= (u16)((u32)&Ctrl.Rec - (u32)&Ctrl) ;	//空闲时，读sctrl.rec记录。

			len  						= sizeof(stcFlshRec);
			gstrSendDtuData.paralen		= (u8)len;
			gstrSendDtuData.node		= 0;
			l_eqiupmentcode				= CMD_PARA_GET;	
		}
		
		time = GetAnsySysTime();
	}
}

/********************************************************************************************
author：redmorningcn 20180625 
数据接收准备。（接收应答或数据）
********************************************************************************************/
void	LocoGetRecvCaliInfo(void)
{
	u8	reclen;
	
	if(gstrRecDtuData.dataokflg == 1)								//	接收到数据
	{														
		gstrRecDtuData.dataokflg	= 0;		
		//reclen  = gstrRecDtuData.recdatalen >> 8;				//	接收数据长度
		reclen  = gstrRecDtuData.recdatalen ;						//	接收数据长度  
		
		if(reclen == sizeof(stcFlshRec)){						//接收到数据记录
			memcpy((u8 *)&Ctrl.Rec,(u8 *)&gstrRecDtuData.parabuf[0],reclen);	
		}else if(reclen == sizeof(lstrLocoCaliTable)){ 
			memcpy((u8 *)&lstrLocoCaliTable,(u8 *)&gstrRecDtuData.parabuf[0],reclen);
		}
	}
}
