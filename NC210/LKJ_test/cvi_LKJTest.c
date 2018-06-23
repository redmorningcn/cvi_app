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
int CVICALLBACK LKJTestTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(gLKJTest_panelHandle)			// �����Ч������ж�ʱ������
			{
				RecDetectInfoReadCode();		// ׼��������ݶ�ȡָ��
				
				Com_SetParaTask();				// ���ڲ�������
				
				Com_SetParaRecTask();			// �������ݽ���
				
				GetRecDetectInfo();				// ��ȡ��ȡ�ü������

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
/* ������޹غ���
/********************************************************************************************/
extern	int	l_eqiupmentcode;
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
