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
extern		int			l_eqiupmentcode;

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
extern	void	SpeedDetectDisplay(void);
extern	void	InitSpeedCtrlID(void);
extern	void	InitLocoCtrlID(void);
extern	void	LocoDetectDisplay(void);
extern	void	RecordDisplay(void);
int CVICALLBACK LKJTestTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	static	u8  tmp = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(gLKJTest_panelHandle)			// 面板有效，则进行定时器操作
			{
				if(tmp == 0){
					InitSpeedCtrlID();			// 初始化面板ID
					InitLocoCtrlID();			
					tmp++;
				}
				
				RecDetectInfoReadCode();		// 准备检测数据读取指令
				
				Com_SetParaTask();				// 串口参数设置
				
				Com_SetParaRecTask();			// 串口数据接收
				
				GetRecDetectInfo();				// 获取读取得检测数据
				
				SpeedDetectDisplay();			// 速度板信号值在面板显示
				
				LocoDetectDisplay();			// 工况板信号值在面板上显示
				
				RecordDisplay();				// 数据记录在面板上显示
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
		case EVENT_COMMIT:				//取数据记录
			//l_eqiupmentcode = CMD_RECORD_GET;
			if(gstrDtuData.recenableflg == 0){
				gstrDtuData.recenableflg = 1;
				SetCtrlAttribute (panel, LKJTEST_READREC, ATTR_LABEL_TEXT, "结束数据读取"); 
			}else
			{
				gstrDtuData.recenableflg = 0;
				SetCtrlAttribute (panel, LKJTEST_READREC, ATTR_LABEL_TEXT, "开始数据读取"); 	
			}
			break;
	}
	return 0;
}

int CVICALLBACK ClearRecordCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{								
		case EVENT_COMMIT:				//系统复位
			l_eqiupmentcode = CMD_SYS_RST;
			break;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板显示函数，和面板控件操作无关
/********************************************************************************************/

/*******************************************************************************
* Description  : 通道具体检测指标
* Author       : 2018/6/24 星期三, by redmorningcn
*******************************************************************************/
typedef	struct _stcSpeedDetect_
{
    /*******************************************************************************
    * Description  : 通道具体指标
    * Author       : 2018/6/24 星期三, by redmorningcn
    *******************************************************************************/
    struct  {
        uint32              period;                         //周期，  0.00-2000000.00us （0.5Hz）
        uint32              freq;                           //频率，  0-100000hz              
        uint16              raise;                          //上升沿，0.00-50.00us
        uint16              fail;                           //下降沿，0.00-50.00us
        uint16              ratio;                          //占空比，0.00-100.00%
        uint16              Vol;                            //低电平，0.00-30.00V
        uint16              Voh;                            //高电平，0.00-30.00V
        uint16				status;                         //通道状态
    }para[2];
    
    uint32  ch1_2phase;                                     //相位差，0.00-360.00°
    uint16  vcc_vol;                                        //供电电压
    uint16  stand_vol;                                      //参考电压
}stcSpeedDetect;

/*******************************************************************************
* Description  : 工况信号通道检测数据结构定义
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
typedef	struct _strpara_ {          
    uint16              vcc;                           //预留
    uint16              qy;                             //牵引
    uint16              zd;                             //制动
    uint16              xq;                             //向前
    uint16              xh;                             //向后
    uint16              lw;                             //零位
}strLocoDetect;

strLocoDetect		lsstLocoDetect;						//工况信号定义
strLocoDetect		lsstLocoCtrlID;						//工况信号ID空检定义
stcSpeedDetect		lstcSpeedDetect[3];					//速度信号检测值
stcSpeedDetect		lsSpeedCrtID[3];					//速度控件ID值

/*******************************************************************************
* Description  : 初始化速度通道控件ID，和面板控件建立联系
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitSpeedCtrlID(void)
{
	//第一组
	lsSpeedCrtID[0].ch1_2phase		= LKJTEST_G0_PHASE;
	lsSpeedCrtID[0].vcc_vol			= LKJTEST_G0_VCC;
	lsSpeedCrtID[0].stand_vol  		= LKJTEST_G0_STANDARD;
		
	lsSpeedCrtID[0].para[0].fail	= LKJTEST_CH1_FAIL;
	lsSpeedCrtID[0].para[0].Voh		= LKJTEST_CH1_HIG;
	lsSpeedCrtID[0].para[0].Vol		= LKJTEST_CH1_LOW;
	lsSpeedCrtID[0].para[0].raise	= LKJTEST_CH1_RAISE;
	lsSpeedCrtID[0].para[0].ratio	= LKJTEST_CH1_RATIO;
	lsSpeedCrtID[0].para[0].freq	= LKJTEST_CH1_FREQ;
	lsSpeedCrtID[0].para[0].status  = LKJTEST_CH1_STATUS;	
	
	lsSpeedCrtID[0].para[1].fail	= LKJTEST_CH2_FAIL;
	lsSpeedCrtID[0].para[1].Voh		= LKJTEST_CH2_HIG;
	lsSpeedCrtID[0].para[1].Vol		= LKJTEST_CH2_LOW;
	lsSpeedCrtID[0].para[1].raise	= LKJTEST_CH2_RAISE;
	lsSpeedCrtID[0].para[1].ratio	= LKJTEST_CH2_RATIO;
	lsSpeedCrtID[0].para[1].freq	= LKJTEST_CH2_FREQ;
	lsSpeedCrtID[0].para[1].status  = LKJTEST_CH2_STATUS;	

	//第二组
	lsSpeedCrtID[1].ch1_2phase		= LKJTEST_G1_PHASE;
	lsSpeedCrtID[1].vcc_vol			= LKJTEST_G1_VCC;
	lsSpeedCrtID[1].stand_vol  		= LKJTEST_G1_STANDARD;
		
	lsSpeedCrtID[1].para[0].fail	= LKJTEST_CH3_FAIL;
	lsSpeedCrtID[1].para[0].Voh		= LKJTEST_CH3_HIG;
	lsSpeedCrtID[1].para[0].Vol		= LKJTEST_CH3_LOW;
	lsSpeedCrtID[1].para[0].raise	= LKJTEST_CH3_RAISE;
	lsSpeedCrtID[1].para[0].ratio	= LKJTEST_CH3_RATIO;
	lsSpeedCrtID[1].para[0].freq	= LKJTEST_CH3_FREQ;
	lsSpeedCrtID[1].para[0].status  = LKJTEST_CH3_STATUS;	
	
	lsSpeedCrtID[1].para[1].fail	= LKJTEST_CH4_FAIL;
	lsSpeedCrtID[1].para[1].Voh		= LKJTEST_CH4_HIG;
	lsSpeedCrtID[1].para[1].Vol		= LKJTEST_CH4_LOW;
	lsSpeedCrtID[1].para[1].raise	= LKJTEST_CH4_RAISE;
	lsSpeedCrtID[1].para[1].ratio	= LKJTEST_CH4_RATIO;
	lsSpeedCrtID[1].para[1].freq	= LKJTEST_CH4_FREQ;
	lsSpeedCrtID[1].para[1].status  = LKJTEST_CH4_STATUS;	

	//第三组
	lsSpeedCrtID[2].ch1_2phase		= LKJTEST_G2_PHASE;
	lsSpeedCrtID[2].vcc_vol			= LKJTEST_G2_VCC;
	lsSpeedCrtID[2].stand_vol  		= LKJTEST_G2_STANDARD;
		
	lsSpeedCrtID[2].para[0].fail	= LKJTEST_CH5_FAIL;
	lsSpeedCrtID[2].para[0].Voh		= LKJTEST_CH5_HIG;
	lsSpeedCrtID[2].para[0].Vol		= LKJTEST_CH5_LOW;
	lsSpeedCrtID[2].para[0].raise	= LKJTEST_CH5_RAISE;
	lsSpeedCrtID[2].para[0].ratio	= LKJTEST_CH5_RATIO;
	lsSpeedCrtID[2].para[0].freq	= LKJTEST_CH5_FREQ;
	lsSpeedCrtID[2].para[0].status  = LKJTEST_CH5_STATUS;	
	
	lsSpeedCrtID[2].para[1].fail	= LKJTEST_CH6_FAIL;
	lsSpeedCrtID[2].para[1].Voh		= LKJTEST_CH6_HIG;
	lsSpeedCrtID[2].para[1].Vol		= LKJTEST_CH6_LOW;
	lsSpeedCrtID[2].para[1].raise	= LKJTEST_CH6_RAISE;
	lsSpeedCrtID[2].para[1].ratio	= LKJTEST_CH6_RATIO;
	lsSpeedCrtID[2].para[1].freq	= LKJTEST_CH6_FREQ;
	lsSpeedCrtID[2].para[1].status  = LKJTEST_CH6_STATUS;
}

/*******************************************************************************
* Description  : 将速度信号检测值在面板控件显示
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	SpeedDetectDisplay(void)
{
	u16	i,j;

	for(i = 0;i< 3;i++ )
	{
	   SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].ch1_2phase ,lstcSpeedDetect[i].ch1_2phase);
	   SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].vcc_vol    ,lstcSpeedDetect[i].vcc_vol);
	   SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].stand_vol  ,lstcSpeedDetect[i].stand_vol);
				  
		for(j = 0; j < 2;j++  )
	   {
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].fail	  ,lstcSpeedDetect[i].para[j].fail		);
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].Voh		  ,lstcSpeedDetect[i].para[j].Voh		);
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].Vol		  ,lstcSpeedDetect[i].para[j].Vol		);
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].raise  	  ,lstcSpeedDetect[i].para[j].raise		);
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].ratio     ,lstcSpeedDetect[i].para[j].ratio		);
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].freq	  ,lstcSpeedDetect[i].para[j].freq		);
	   		SetCtrlVal(gLKJTest_panelHandle,lsSpeedCrtID[i].para[j].status    ,lstcSpeedDetect[i].para[j].status	);
	   }
	}
}

/*******************************************************************************
* Description  : 初始化工况信号控件ID，和面板控件建立联系
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitLocoCtrlID(void)   
{
	lsstLocoCtrlID.vcc	 = LKJTEST_V110;
	lsstLocoCtrlID.qy	 = LKJTEST_QY  ;
	lsstLocoCtrlID.zd	 = LKJTEST_ZD  ;
	lsstLocoCtrlID.xq	 = LKJTEST_XQ  ;
	lsstLocoCtrlID.xh	 = LKJTEST_XH  ;
	lsstLocoCtrlID.lw	 = LKJTEST_LW  ;
}

/*******************************************************************************
* Description  : 将工况信号检测值在面板控件显示
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	LocoDetectDisplay(void)
{
   SetCtrlVal(gLKJTest_panelHandle,lsstLocoCtrlID.vcc	 ,lsstLocoDetect.vcc	);
   SetCtrlVal(gLKJTest_panelHandle,lsstLocoCtrlID.qy	 ,lsstLocoDetect.qy		);
   SetCtrlVal(gLKJTest_panelHandle,lsstLocoCtrlID.zd	 ,lsstLocoDetect.zd		);
   SetCtrlVal(gLKJTest_panelHandle,lsstLocoCtrlID.xq	 ,lsstLocoDetect.xq		);
   SetCtrlVal(gLKJTest_panelHandle,lsstLocoCtrlID.xh	 ,lsstLocoDetect.xh		);
   SetCtrlVal(gLKJTest_panelHandle,lsstLocoCtrlID.lw	 ,lsstLocoDetect.lw		);
}

/*******************************************************************************
* Description  : 将接收到的数据记录在面板上显示
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	RecordDisplay(void)  {
	if(gstrDtuData.recvrecflg == 1)	
	{
		gstrDtuData.recvrecflg = 0;		// 	
		
		u8	buf[1024];
		// 
		snprintf(buf,sizeof(buf)-2,"%2d-%2d-%2d %2d:%2d:%2d,机车:%4d.%4d,记录号:%8d,位置:\r\n"
										,gstrDtuData.Rec.Year
										,gstrDtuData.Rec.Mon 	
										,gstrDtuData.Rec.Day 
										,gstrDtuData.Rec.Hour
										,gstrDtuData.Rec.Min 	
										,gstrDtuData.Rec.Sec 
										,gstrDtuData.Rec.LocoType
										,gstrDtuData.Rec.LocoNbr
										,gstrDtuData.Rec.RecordId
										
				);	
		
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf		); 
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/

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
