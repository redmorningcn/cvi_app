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
//������
int 					gLKJTest_panelHandle;
extern		int			gmainPanel;
extern		int			l_eqiupmentcode;

/********************************************************************************************/
//local
/********************************************************************************************/


/********************************************************************************************/
//�ز���ʾ��塣	redmoringcn 20180619
/********************************************************************************************/
void LoadLKJTestPanel(void)
{
	gLKJTest_panelHandle = LoadPanel (0, "cvi_LKJTest.uir", LKJTEST);
	/* 	Display the panel and run the UI */
	DisplayPanel (gLKJTest_panelHandle);
}

/********************************************************************************************/
/*�����																	        */
/********************************************************************************************/
int CVICALLBACK OpenLKJTestCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{				
		case EVENT_COMMIT:

			LoadLKJTestPanel();

			/* Schedule two thread functions */				//���̣߳��������̺߳���
			cvi_InitBspComm(&sCtrl.PC);						//����
			
			HidePanel(gmainPanel);							//���������
			break;
	}
	return 0;
}

/********************************************************************************************/
/*�˳����      																	        */
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
			QuitLKJTestPanel();				//�˳�������
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

			if(gLKJTest_panelHandle)			// �����Ч������ж�ʱ������
			{
				if(tmp == 0){
					InitSpeedCtrlID();			// ��ʼ�����ID
					InitLocoCtrlID();			
					tmp++;
				}
				
				SetDetectReadCode();		// ׼��������ݶ�ȡָ��
				
				Com_SetParaTask();				// ���ڲ�������
				
				Com_SetParaRecTask();			// �������ݽ���
				
				GetDetectInfo();				// ��ȡ��ȡ�ü������
				
				SpeedDetectDisplay();			// �ٶȰ��ź�ֵ�������ʾ
				
				LocoDetectDisplay();			// �������ź�ֵ���������ʾ
				
				RecordDisplay();				// ���ݼ�¼���������ʾ
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
		case EVENT_COMMIT:				//ȡ���ݼ�¼
			//l_eqiupmentcode = CMD_RECORD_GET;
			if(gstrDtuData.recenableflg == 0){
				gstrDtuData.recenableflg = 1;
				SetCtrlAttribute (panel, LKJTEST_READREC, ATTR_LABEL_TEXT, "�������ݶ�ȡ"); 
			}else
			{
				gstrDtuData.recenableflg = 0;
				SetCtrlAttribute (panel, LKJTEST_READREC, ATTR_LABEL_TEXT, "��ʼ���ݶ�ȡ"); 	
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
		case EVENT_COMMIT:					//ϵͳ����
			l_eqiupmentcode = CMD_REC_CLR;
			
			break;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* �������ʾ�����������ؼ������޹�
/********************************************************************************************/

strLocoDetect		lstrLocoDetect;						//�����źŶ���
strLocoDetect		lstrLocoDetectId;					//�����ź�ID�ռ춨��
strSpeedDetect		lstrSpeedDetect[3];					//�ٶ��źż��ֵ
strSpeedDetect		lstrSpeedCrtID[3];					//�ٶȿؼ�IDֵ

/*******************************************************************************
* Description  : ��ʼ���ٶ�ͨ���ؼ�ID�������ؼ�������ϵ
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitSpeedCtrlID(void)
{
	//��һ��
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

	//�ڶ���
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

	//������
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
* Description  : ���ٶ��źż��ֵ�����ؼ���ʾ
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
* Description  : ��ʼ�������źſؼ�ID�������ؼ�������ϵ
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
* Description  : �������źż��ֵ�����ؼ���ʾ
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
* Description  : �����յ������ݼ�¼���������ʾ
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	RecordDisplay(void)  {
	if(gstrDtuData.recvrecflg == 1)	
	{
		gstrDtuData.recvrecflg = 0;		// 	
		
		u8	buf[512];
		//��ӡʱ�� 
			snprintf((char *)buf,sizeof(buf)-2,"%02d-%02d-%02d %02d:%02d:%02d"
										,gstrDtuData.Rec.Year
										,gstrDtuData.Rec.Mon 	
										,gstrDtuData.Rec.Day 
										,gstrDtuData.Rec.Hour
										,gstrDtuData.Rec.Min 	
										,gstrDtuData.Rec.Sec 
				);	
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf);
		
		//��ӡ��������¼�� 
		snprintf((char *)buf,sizeof(buf)-2,", ����:%3d-%4d, ��¼��:%6d"
										,gstrDtuData.Rec.LocoType
										,gstrDtuData.Rec.LocoNbr
										,gstrDtuData.Rec.RecordId
				);	
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf);		

		//��ӡ�н��� 
		snprintf((char *)buf,sizeof(buf)-2," \r\n" );	
		
		SetCtrlVal(gLKJTest_panelHandle,LKJTEST_INFOTEXTBOX	 ,buf);				
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* ������޹غ���
/********************************************************************************************/

u8		l_DetectGetNode = 1;
static	u32	lstestcode;     
/********************************************************************************************
author��redmorningcn 20180622 
�ٶ��źż�loco�ź��������׼������ֱ�Ӷ�ȡ ���ư�ctrl.recʵʱ���ݣ�ָ����ַ������
********************************************************************************************/
void	SetDetectReadCode(void)
{
	u32	len;
	static	u32	time;
	
	if(gstrDtuData.recenableflg == 1){						// Ӧ�����ݼ�¼������ѯ��������
		l_eqiupmentcode	=	0;
		lstestcode		=   0;
		return;
	}
	
	if(time <= GetAnsySysTime()){
		if(time + 1000 > GetAnsySysTime()  ) {				// ���ڷ��ͣ����Ʒ���Ƶ��
			return;
		} 
	}
	
	time = GetAnsySysTime();								// ʱ����Ϣ
	len	 = sizeof(Ctrl.Rec);

	if(l_DetectGetNode == 4){								// ȡLKJ�����ź�
		len = sizeof(strLocoDetect);	
		gstrDtuData.paraaddr =  ADDR_LOCO_DETECT;			// ��ָ����ַ
		gstrDtuData.paralen  =  (u8)len;					// ��ָ������
		gstrDtuData.node     =  l_DetectGetNode;
		
	}else if(l_DetectGetNode < 4){ 	// ȡ�ٶ��ź�
		len = sizeof(strSpeedDetect);
		gstrDtuData.paraaddr =  ADDR_SPEED_DETECT;			// ��ָ����ַ
		gstrDtuData.paralen  =  (u8)len;					// ��ָ������
		gstrDtuData.node     =  l_DetectGetNode;
		
		if(l_DetectGetNode == 0)
			l_DetectGetNode  = 1;							// Ĭ�Ͻڵ�1	
	}
	
	l_eqiupmentcode = CMD_DETECT_GET;						// ָ�������������壩
	lstestcode		= CMD_DETECT_GET;
}

/********************************************************************************************
author��redmorningcn 20180622 
ȡ�ٶ��źż�loco�ź��������׼������ͨ�����ձ�ʶ���ж��ǽ��յ����ݣ�
********************************************************************************************/
void	GetDetectInfo(void)
{
	u32		len;
	u8		reclen;
	u8		node;
   	static	u32	time;

	if(	   (gstrDtuData.dataokflg 	== 1 
		&&  gstrDtuData.code 		== lstestcode)
	  )															//	���յ�����
	{														
		gstrDtuData.dataokflg  = 0;
		
		reclen  = (u8)gstrDtuData.recdatalen ;					//	�������ݳ���
		node	= (u8)gstrDtuData.node;							//  
		
		if(node == 4){											// 	ȡLKJ�����ź�
		
			len =  sizeof(strLocoDetect);						//	detect ���ݣ��������ݣ�

			if(reclen == len){									// ���ݳ����������ֵ����
				memcpy((u8 *)&lstrLocoDetect,gstrDtuData.parabuf,len);	// ��������	
			}
		}else if(node < 4 && node > 0){ 						// ȡ�ٶ��ź�
			len =  sizeof(strSpeedDetect);						//	detect ���ݣ��������ݣ�
			 
			memcpy((u8 *)&lstrSpeedDetect[node - 1],gstrDtuData.parabuf,len);	// ��������
		}
		
		//l_DetectGetNode++;
		l_DetectGetNode = (l_DetectGetNode % 4) + 1;			// ������һ��ͨѶ�ڵ�
		
		time 			= GetAnsySysTime();						
	}else{				//��ʱ����
		if(sCtrl.PC.ConnCtrl.TimeoutFlg == 1 ||sCtrl.PC.ConnCtrl.DataErrFlg == 1) {
			l_DetectGetNode = (l_DetectGetNode % 4) + 1;		// ������һ��ͨѶ�ڵ�
			sCtrl.PC.ConnCtrl.TimeoutFlg	=	0;
			sCtrl.PC.ConnCtrl.DataErrFlg  	=   0;
		}
	}
}
