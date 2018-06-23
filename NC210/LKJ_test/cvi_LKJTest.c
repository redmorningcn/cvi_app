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

			if(gLKJTest_panelHandle)			// �����Ч������ж�ʱ������
			{
				if(tmp == 0){
					InitSpeedCtrlID();			// ��ʼ�����ID
					InitLocoCtrlID();			
					tmp++;
				}
				
				RecDetectInfoReadCode();		// ׼��������ݶ�ȡָ��
				
				Com_SetParaTask();				// ���ڲ�������
				
				Com_SetParaRecTask();			// �������ݽ���
				
				GetRecDetectInfo();				// ��ȡ��ȡ�ü������
				
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
		case EVENT_COMMIT:				//ϵͳ��λ
			l_eqiupmentcode = CMD_SYS_RST;
			break;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* �������ʾ�����������ؼ������޹�
/********************************************************************************************/

/*******************************************************************************
* Description  : ͨ��������ָ��
* Author       : 2018/6/24 ������, by redmorningcn
*******************************************************************************/
typedef	struct _stcSpeedDetect_
{
    /*******************************************************************************
    * Description  : ͨ������ָ��
    * Author       : 2018/6/24 ������, by redmorningcn
    *******************************************************************************/
    struct  {
        uint32              period;                         //���ڣ�  0.00-2000000.00us ��0.5Hz��
        uint32              freq;                           //Ƶ�ʣ�  0-100000hz              
        uint16              raise;                          //�����أ�0.00-50.00us
        uint16              fail;                           //�½��أ�0.00-50.00us
        uint16              ratio;                          //ռ�ձȣ�0.00-100.00%
        uint16              Vol;                            //�͵�ƽ��0.00-30.00V
        uint16              Voh;                            //�ߵ�ƽ��0.00-30.00V
        uint16				status;                         //ͨ��״̬
    }para[2];
    
    uint32  ch1_2phase;                                     //��λ�0.00-360.00��
    uint16  vcc_vol;                                        //�����ѹ
    uint16  stand_vol;                                      //�ο���ѹ
}stcSpeedDetect;

/*******************************************************************************
* Description  : �����ź�ͨ��������ݽṹ����
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
typedef	struct _strpara_ {          
    uint16              vcc;                           //Ԥ��
    uint16              qy;                             //ǣ��
    uint16              zd;                             //�ƶ�
    uint16              xq;                             //��ǰ
    uint16              xh;                             //���
    uint16              lw;                             //��λ
}strLocoDetect;

strLocoDetect		lsstLocoDetect;						//�����źŶ���
strLocoDetect		lsstLocoCtrlID;						//�����ź�ID�ռ춨��
stcSpeedDetect		lstcSpeedDetect[3];					//�ٶ��źż��ֵ
stcSpeedDetect		lsSpeedCrtID[3];					//�ٶȿؼ�IDֵ

/*******************************************************************************
* Description  : ��ʼ���ٶ�ͨ���ؼ�ID�������ؼ�������ϵ
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitSpeedCtrlID(void)
{
	//��һ��
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

	//�ڶ���
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

	//������
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
* Description  : ���ٶ��źż��ֵ�����ؼ���ʾ
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
* Description  : ��ʼ�������źſؼ�ID�������ؼ�������ϵ
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
* Description  : �������źż��ֵ�����ؼ���ʾ
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
* Description  : �����յ������ݼ�¼���������ʾ
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	RecordDisplay(void)  {
	if(gstrDtuData.recvrecflg == 1)	
	{
		gstrDtuData.recvrecflg = 0;		// 	
		
		u8	buf[1024];
		// 
		snprintf(buf,sizeof(buf)-2,"%2d-%2d-%2d %2d:%2d:%2d,����:%4d.%4d,��¼��:%8d,λ��:\r\n"
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
/* ������޹غ���
/********************************************************************************************/

/********************************************************************************************
author��redmorningcn 20180622 
�ٶ��źż�loco�ź��������׼������ֱ�Ӷ�ȡ ���ư�ctrl.recʵʱ���ݣ�ָ����ַ������
********************************************************************************************/
void	RecDetectInfoReadCode(void)
{
	u32	len;
	
	len = sizeof(Ctrl.Rec);
	l_eqiupmentcode = CMD_PARA_GET;		//ָ��������

	gstrDtuData.paraaddr = (u16)((u32)&Ctrl.Rec.speed[0] -  (u32)&Ctrl) ;					//��ָ����ַ
	gstrDtuData.paralen  = (u16)((u32)&Ctrl.Rec.Longitude -  (u32)&Ctrl.Rec.speed[0]) ;		//��ָ������
}

/********************************************************************************************
author��redmorningcn 20180622 
ȡ�ٶ��źż�loco�ź��������׼������ͨ�����ձ�ʶ���ж��ǽ��յ����ݣ�
********************************************************************************************/
void	GetRecDetectInfo(void)
{
	u32	len;
	
	if(gstrDtuData.dataokflg == 1)		//���յ�����
	{
		len =   (u16)((u32)&Ctrl.Rec.Longitude -  (u32)&Ctrl.Rec.speed[0]);					//detect ���ݣ��������ݣ� 
		if(gstrDtuData.recdatalen == len)
		{
			memcpy((u8 *)&Ctrl.Rec.speed[0],gstrDtuData.parabuf,len);						//��������
		}
	}
}
