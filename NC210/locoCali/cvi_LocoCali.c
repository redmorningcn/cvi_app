#include <userint.h>

/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
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
#include 	"includes.h"
#include  	"cvi_config.h"
#include  	"cvi_LocoCaliType.h"


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//������
int 					gLocoCali_panelHandle;
extern		int			gmainPanel;
strLocoCali				gstrLocoCali[6];
/********************************************************************************************/
//local
/********************************************************************************************/


/********************************************************************************************/
//�ز���ʾ��塣	redmoringcn 20180620
/********************************************************************************************/
void LoadLocoCaliPanel(void)
{
	gLocoCali_panelHandle = LoadPanel (0, "cvi_LocoCali.uir", LOCOCALI);
	/* 	Display the panel and run the UI */
	DisplayPanel (gLocoCali_panelHandle);
}

/********************************************************************************************/
/*�����																	        */
/********************************************************************************************/
int CVICALLBACK OpenLocoCaliCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadLocoCaliPanel();

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
void	QuitLocoCaliPanel(void)
{
	HidePanel (gLocoCali_panelHandle);

	DisplayPanel (gmainPanel);

	gLocoCali_panelHandle = 0;
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
			QuitLocoCaliPanel();				//�˳�������
			break;
	}
	return 0;
}




int CVICALLBACK LocoCaliTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(gLocoCali_panelHandle)			//�����Ч������ж�ʱ������
			{
				//Com_SetParaTask();			//���ڲ�������
			}
			break;
	}
	return 0;
}

//��ȡ110v��λֵ�����ڴ�����ʾ��
int CVICALLBACK V110LowCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gstrLocoCali[0].lowflg = 1;
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
			gstrLocoCali[1].lowflg = 1; 
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
			gstrLocoCali[2].lowflg = 1;
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
			gstrLocoCali[3].lowflg = 1;
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
			gstrLocoCali[4].lowflg = 1;
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
			gstrLocoCali[5].lowflg = 1;
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
			gstrLocoCali[5].califlg = 1;
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
			gstrLocoCali[4].califlg = 1;
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
			gstrLocoCali[3].califlg = 1;
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
			gstrLocoCali[2].califlg = 1;
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
			gstrLocoCali[1].califlg = 1;
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
			gstrLocoCali[0].califlg = 1;
			break;
	}
	return 0;
}

int CVICALLBACK HelpCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				MessagePopup ("������Ϣ", "1��ѡ��ͬ��У׼��������110VУ׼ֵ��ͬ��\r\n2��У׼�ָߡ������㣬���������ֵ�󣬶�Ӧ����ֵ�Զ����루���ֶ�������");
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
			gstrLocoCali[0].higflg = 0;
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
			gstrLocoCali[1].higflg = 1;
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
			gstrLocoCali[2].higflg = 1;
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
			gstrLocoCali[3].higflg = 1;
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
			gstrLocoCali[4].higflg = 1;
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
			gstrLocoCali[5].higflg = 1;
			break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//author��redmorningcn   20180621
//
/////////////////////////////////////////////////////////////////////////////////////////////////

