/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.		  180621
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
#include 	"cvi_LKJTestType.h"
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
				
				SetDetectReadCode();		// 准备检测数据读取指令
				
				Com_SetParaTask();				// 串口参数设置
				
				Com_SetParaRecTask();			// 串口数据接收
				
				GetDetectInfo();				// 获取读取得检测数据
				
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
		case EVENT_COMMIT:					//系统清零
			l_eqiupmentcode = CMD_REC_CLR;
			
			break;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板显示函数，和面板控件操作无关
/********************************************************************************************/

strLocoDetect		lstrLocoDetect;						//工况信号定义
strLocoDetect		lstrLocoDetectId;					//工况信号ID空检定义
strSpeedDetect		lstrSpeedDetect[3];					//速度信号检测值
strSpeedDetect		lstrSpeedCrtID[3];					//速度控件ID值

/*******************************************************************************
* Description  : 初始化速度通道控件ID，和面板控件建立联系
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitSpeedCtrlID(void)
{
	//第一组
	lstrSpeedCrtID[0].ch1_2phase	= LKJTEST_G0_PHASE;
	lstrSpeedCrtID[0].vcc_vol		= LKJTEST_G0_VCC;
	lstrSpeedCrtID[0].stand_vol  	= LKJTEST_G0_STANDARD;
		
	lstrSpeedCrtID[0].para[0].fail	= LKJTEST_CH1_FAIL;
	lstrSpeedCrtID[0].para[0].Voh	= LKJTEST_CH1_HIG;
	lstrSpeedCrtID[0].para[0].Vol	= LKJTEST_CH1_LOW;
	lstrSpeedCrtID[0].para[0].raise	= LKJTEST_CH1_RAISE;
	lstrSpeedCrtID[0].para[0].ratio	= LKJTEST_CH1_RATIO;
	lstrSpeedCrtID[0].para[0].freq	= LKJTEST_CH1_FREQ;
	lstrSpeedCrtID[0].para[0].status= LKJTEST_CH1_STATUS;	
	
	lstrSpeedCrtID[0].para[1].fail	= LKJTEST_CH2_FAIL;
	lstrSpeedCrtID[0].para[1].Voh	= LKJTEST_CH2_HIG;
	lstrSpeedCrtID[0].para[1].Vol	= LKJTEST_CH2_LOW;
	lstrSpeedCrtID[0].para[1].raise	= LKJTEST_CH2_RAISE;
	lstrSpeedCrtID[0].para[1].ratio	= LKJTEST_CH2_RATIO;
	lstrSpeedCrtID[0].para[1].freq	= LKJTEST_CH2_FREQ;
	lstrSpeedCrtID[0].para[1].status= LKJTEST_CH2_STATUS;	

	//第二组
	lstrSpeedCrtID[1].ch1_2phase	= LKJTEST_G1_PHASE;
	lstrSpeedCrtID[1].vcc_vol		= LKJTEST_G1_VCC;
	lstrSpeedCrtID[1].stand_vol  	= LKJTEST_G1_STANDARD;
		
	lstrSpeedCrtID[1].para[0].fail	= LKJTEST_CH3_FAIL;
	lstrSpeedCrtID[1].para[0].Voh	= LKJTEST_CH3_HIG;
	lstrSpeedCrtID[1].para[0].Vol	= LKJTEST_CH3_LOW;
	lstrSpeedCrtID[1].para[0].raise	= LKJTEST_CH3_RAISE;
	lstrSpeedCrtID[1].para[0].ratio	= LKJTEST_CH3_RATIO;
	lstrSpeedCrtID[1].para[0].freq	= LKJTEST_CH3_FREQ;
	lstrSpeedCrtID[1].para[0].status= LKJTEST_CH3_STATUS;	
	
	lstrSpeedCrtID[1].para[1].fail	= LKJTEST_CH4_FAIL;
	lstrSpeedCrtID[1].para[1].Voh	= LKJTEST_CH4_HIG;
	lstrSpeedCrtID[1].para[1].Vol	= LKJTEST_CH4_LOW;
	lstrSpeedCrtID[1].para[1].raise	= LKJTEST_CH4_RAISE;
	lstrSpeedCrtID[1].para[1].ratio	= LKJTEST_CH4_RATIO;
	lstrSpeedCrtID[1].para[1].freq	= LKJTEST_CH4_FREQ;
	lstrSpeedCrtID[1].para[1].status= LKJTEST_CH4_STATUS;	

	//第三组
	lstrSpeedCrtID[2].ch1_2phase	= LKJTEST_G2_PHASE;
	lstrSpeedCrtID[2].vcc_vol		= LKJTEST_G2_VCC;
	lstrSpeedCrtID[2].stand_vol  	= LKJTEST_G2_STANDARD;
		
	lstrSpeedCrtID[2].para[0].fail	= LKJTEST_CH5_FAIL;
	lstrSpeedCrtID[2].para[0].Voh	= LKJTEST_CH5_HIG;
	lstrSpeedCrtID[2].para[0].Vol	= LKJTEST_CH5_LOW;
	lstrSpeedCrtID[2].para[0].raise	= LKJTEST_CH5_RAISE;
	lstrSpeedCrtID[2].para[0].ratio	= LKJTEST_CH5_RATIO;
	lstrSpeedCrtID[2].para[0].freq	= LKJTEST_CH5_FREQ;
	lstrSpeedCrtID[2].para[0].status= LKJTEST_CH5_STATUS;	
	
	lstrSpeedCrtID[2].para[1].fail	= LKJTEST_CH6_FAIL;
	lstrSpeedCrtID[2].para[1].Voh	= LKJTEST_CH6_HIG;
	lstrSpeedCrtID[2].para[1].Vol	= LKJTEST_CH6_LOW;
	lstrSpeedCrtID[2].para[1].raise	= LKJTEST_CH6_RAISE;
	lstrSpeedCrtID[2].para[1].ratio	= LKJTEST_CH6_RATIO;
	lstrSpeedCrtID[2].para[1].freq	= LKJTEST_CH6_FREQ;
	lstrSpeedCrtID[2].para[1].status= LKJTEST_CH6_STATUS;
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
	   SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].ch1_2phase ,lstrSpeedDetect[i].ch1_2phase	);
	   SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].vcc_vol    ,lstrSpeedDetect[i].vcc_vol		);
	   SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].stand_vol  ,lstrSpeedDetect[i].stand_vol	);
				  
		for(j = 0; j < 2;j++  )
	   {
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].fail	  	,lstrSpeedDetect[i].para[j].fail	);
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].Voh		,lstrSpeedDetect[i].para[j].Voh		);
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].Vol		,lstrSpeedDetect[i].para[j].Vol		);
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].raise  	,lstrSpeedDetect[i].para[j].raise	);
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].ratio     ,lstrSpeedDetect[i].para[j].ratio	);
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].freq	  	,lstrSpeedDetect[i].para[j].freq	);
	   		SetCtrlVal(gLKJTest_panelHandle,lstrSpeedCrtID[i].para[j].status    ,lstrSpeedDetect[i].para[j].status	);
	   }
	}
}

/*******************************************************************************
* Description  : 初始化工况信号控件ID，和面板控件建立联系
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitLocoCtrlID(void)   
{
	lstrLocoDetectId.vcc	 = LKJTEST_V110;
	lstrLocoDetectId.qy	 = LKJTEST_QY  ;
	lstrLocoDetectId.zd	 = LKJTEST_ZD  ;
	lstrLocoDetectId.xq	 = LKJTEST_XQ  ;
	lstrLocoDetectId.xh	 = LKJTEST_XH  ;
	lstrLocoDetectId.lw	 = LKJTEST_LW  ;
}

/*******************************************************************************
* Description  : 将工况信号检测值在面板控件显示
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	LocoDetectDisplay(void)
{
   SetCtrlVal(gLKJTest_panelHandle,lstrLocoDetectId.vcc	 ,lstrLocoDetect.vcc	);
   SetCtrlVal(gLKJTest_panelHandle,lstrLocoDetectId.qy	 ,lstrLocoDetect.qy		);
   SetCtrlVal(gLKJTest_panelHandle,lstrLocoDetectId.zd	 ,lstrLocoDetect.zd		);
   SetCtrlVal(gLKJTest_panelHandle,lstrLocoDetectId.xq	 ,lstrLocoDetect.xq		);
   SetCtrlVal(gLKJTest_panelHandle,lstrLocoDetectId.xh	 ,lstrLocoDetect.xh		);
   SetCtrlVal(gLKJTest_panelHandle,lstrLocoDetectId.lw	 ,lstrLocoDetect.lw		);
}

/*******************************************************************************
* Description  : 将接收到的数据记录在面板上显示
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	RecordDisplay(void)  {
	if(gstrDtuData.recvrecflg == 1)	
	{
		gstrDtuData.recvrecflg = 0;		// 	
		
		u8	buf[512];
		//打印时间 
			snprintf((char *)buf,sizeof(buf)-2,"%02d-%02d-%02d %02d:%02d:%02d"
										,gstrDtuData.Rec.Year
										,gstrDtuData.Rec.Mon 	
										,gstrDtuData.Rec.Day 
										,gstrDtuData.Rec.Hour
										,gstrDtuData.Rec.Min 	
										,gstrDtuData.Rec.Sec 
				);	
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf);
		
		//打印机车、记录号 
		snprintf((char *)buf,sizeof(buf)-2,", 机车:%3d-%4d, 记录号:%6d"
										,gstrDtuData.Rec.LocoType
										,gstrDtuData.Rec.LocoNbr
										,gstrDtuData.Rec.RecordId
				);	
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf);		

		//打印行结束 
		snprintf((char *)buf,sizeof(buf)-2," \r\n" );	
		
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf);				
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* 和面板无关函数
/********************************************************************************************/

u8		l_DetectGetNode = 1;
static	u32	lstestcode;     
/********************************************************************************************
author：redmorningcn 20180622 
速度信号及loco信号命令，数据准备。（直接读取 控制板ctrl.rec实时数据（指定地址读））
********************************************************************************************/
void	SetDetectReadCode(void)
{
	u32	len;
	static	u32	time;
	
	if(gstrDtuData.recenableflg == 1){						// 应答数据记录，不查询其他数据
		l_eqiupmentcode	=	0;
		lstestcode		=   0;
		return;
	}
	
	if(time <= GetAnsySysTime()){
		if(time + 1000 > GetAnsySysTime()  ) {				// 周期发送，控制发送频率
			return;
		} 
	}
	
	time = GetAnsySysTime();								// 时间信息
	len	 = sizeof(Ctrl.Rec);

	if(l_DetectGetNode == 4){								// 取LKJ工况信号
		len = sizeof(strLocoDetect);	
		gstrDtuData.paraaddr =  ADDR_LOCO_DETECT;			// 读指定地址
		gstrDtuData.paralen  =  (u8)len;					// 读指定数据
		gstrDtuData.node     =  l_DetectGetNode;
		
	}else if(l_DetectGetNode < 4){ 	// 取速度信号
		len = sizeof(strSpeedDetect);
		gstrDtuData.paraaddr =  ADDR_SPEED_DETECT;			// 读指定地址
		gstrDtuData.paralen  =  (u8)len;					// 读指定数据
		gstrDtuData.node     =  l_DetectGetNode;
		
		if(l_DetectGetNode == 0)
			l_DetectGetNode  = 1;							// 默认节点1	
	}
	
	l_eqiupmentcode = CMD_DETECT_GET;						// 指定参数读（检测板）
	lstestcode		= CMD_DETECT_GET;
}

/********************************************************************************************
author：redmorningcn 20180622 
取速度信号及loco信号命令，数据准备。（通过接收标识，判断是接收到数据）
********************************************************************************************/
void	GetDetectInfo(void)
{
	u32		len;
	u8		reclen;
	u8		node;
   	static	u32	time;

	if(	   (gstrDtuData.dataokflg 	== 1 
		&&  gstrDtuData.code 		== lstestcode)
	  )															//	接收到数据
	{														
		gstrDtuData.dataokflg  = 0;
		
		reclen  = (u8)gstrDtuData.recdatalen ;					//	接收数据长度
		node	= (u8)gstrDtuData.node;							//  
		
		if(node == 4){											// 	取LKJ工况信号
		
			len =  sizeof(strLocoDetect);						//	detect 数据（检测板数据）

			if(reclen == len){									// 数据长度相符，幅值数据
				memcpy((u8 *)&lstrLocoDetect,gstrDtuData.parabuf,len);	// 复制数据	
			}
		}else if(node < 4 && node > 0){ 						// 取速度信号
			len =  sizeof(strSpeedDetect);						//	detect 数据（检测板数据）
			 
			memcpy((u8 *)&lstrSpeedDetect[node - 1],gstrDtuData.parabuf,len);	// 复制数据
		}
		
		//l_DetectGetNode++;
		l_DetectGetNode = (l_DetectGetNode % 4) + 1;			// 计算下一个通讯节点
		
		time 			= GetAnsySysTime();						
	}else{				//超时处理
		if(sCtrl.PC.ConnCtrl.TimeoutFlg == 1 ||sCtrl.PC.ConnCtrl.DataErrFlg == 1) {
			l_DetectGetNode = (l_DetectGetNode % 4) + 1;		// 计算下一个通讯节点
			sCtrl.PC.ConnCtrl.TimeoutFlg	=	0;
			sCtrl.PC.ConnCtrl.DataErrFlg  	=   0;
		}
	}
}
