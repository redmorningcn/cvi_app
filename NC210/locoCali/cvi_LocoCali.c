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


/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
//  Globals
/********************************************************************************************/
//������
int 					gLocoCali_panelHandle;
extern		int			gmainPanel;
strLocoCali				lstrLocoCali[6];			//У�����
strLocoCali				lstrLocoCaliCtrlId[6];		//���ID
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

			if(gLocoCali_panelHandle)			//�����Ч������ж�ʱ������
			{
				if(tmp == 0){
					InitLocoCaliCtrlId();
					tmp++;
				}

				//Com_SetParaTask();			//���ڲ�������
			}
			break;
	}
	return 0;
}


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

/********************************************************************************************/
/*������年ѡ����ʾ��رն�Ӧ��ؼ�      																	        */
/********************************************************************************************/
void	CtrlDimmedControl(u8 id)
{
	u8	j;
	u16	*p;
	
	if(id > 6)
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
				for(i = 1;i < 6;i++){
					p = (u16 *)&lstrLocoCaliCtrlId[i];
					for(j = 0;j<5;j++){
						SetCtrlAttribute (panel, *p,  ATTR_DIMMED, 1);
						p++;
					}
					
					SetCtrlVal (panel, lstrLocoCaliCtrlId[i].ansyflg,  1);
				}
			}else{
				for(i = 1;i < 6;i++){
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
			CtrlDimmedControl(1);

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
			CtrlDimmedControl(2);

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
			CtrlDimmedControl(3);

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
			CtrlDimmedControl(4);

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
			CtrlDimmedControl(5);

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
			QuitLocoCaliPanel();				//�˳�������
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
			lstrLocoCali[0].lowflg = 1;
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
			lstrLocoCali[0].higflg = 0;
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
			break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//author��redmorningcn   20180621
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************/
/* �������ʾ�����������ؼ������޹�
/********************************************************************************************/


/*******************************************************************************
* Description  : ��ʼ������У׼�ؼ�ID�������ؼ�������ϵ
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
void	InitLocoCaliCtrlId(void)   
{
	lstrLocoCaliCtrlId[0].lowstandard	=	LOCOCALI_V110_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[0].lowmeasure	=	LOCOCALI_V110_LOW_MEASURE	;
	lstrLocoCaliCtrlId[0].higstandard	=	LOCOCALI_V110_HIG_STANDARD	;
	lstrLocoCaliCtrlId[0].higmeasure	=	LOCOCALI_V110_HIG_MEASURE	;
	lstrLocoCaliCtrlId[0].ansyflg		=	LOCOCALI_V110_SYNC			;
	lstrLocoCaliCtrlId[0].send			=	LOCOCALI_V110				;


	lstrLocoCaliCtrlId[1].lowstandard	=	LOCOCALI_QY_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[1].lowmeasure	=	LOCOCALI_QY_LOW_MEASURE		;
	lstrLocoCaliCtrlId[1].higstandard	=	LOCOCALI_QY_HIG_STANDARD	;
	lstrLocoCaliCtrlId[1].higmeasure	=	LOCOCALI_QY_HIG_MEASURE		;
	lstrLocoCaliCtrlId[1].ansyflg		=	LOCOCALI_QY_SYNC			;
	lstrLocoCaliCtrlId[1].send			=	LOCOCALI_QY					;  

	lstrLocoCaliCtrlId[2].lowstandard	=	LOCOCALI_ZD_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[2].lowmeasure	=	LOCOCALI_ZD_LOW_MEASURE		;
	lstrLocoCaliCtrlId[2].higstandard	=	LOCOCALI_ZD_HIG_STANDARD	;
	lstrLocoCaliCtrlId[2].higmeasure	=	LOCOCALI_ZD_HIG_MEASURE		;
	lstrLocoCaliCtrlId[2].ansyflg		=	LOCOCALI_ZD_SYNC			;
	lstrLocoCaliCtrlId[2].send			=	LOCOCALI_ZD					;  	
	
	lstrLocoCaliCtrlId[3].lowstandard	=	LOCOCALI_XQ_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[3].lowmeasure	=	LOCOCALI_XQ_LOW_MEASURE		;
	lstrLocoCaliCtrlId[3].higstandard	=	LOCOCALI_XQ_HIG_STANDARD	;
	lstrLocoCaliCtrlId[3].higmeasure	=	LOCOCALI_XQ_HIG_MEASURE		;
	lstrLocoCaliCtrlId[3].ansyflg		=	LOCOCALI_XQ_SYNC			;
	lstrLocoCaliCtrlId[3].send			=	LOCOCALI_XQ					;  	

	lstrLocoCaliCtrlId[4].lowstandard	=	LOCOCALI_XH_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[4].lowmeasure	=	LOCOCALI_XH_LOW_MEASURE		;
	lstrLocoCaliCtrlId[4].higstandard	=	LOCOCALI_XH_HIG_STANDARD	;
	lstrLocoCaliCtrlId[4].higmeasure	=	LOCOCALI_XH_HIG_MEASURE		;
	lstrLocoCaliCtrlId[4].ansyflg		=	LOCOCALI_XH_SYNC			;
	lstrLocoCaliCtrlId[4].send			=	LOCOCALI_XH					;  	

	lstrLocoCaliCtrlId[5].lowstandard	=	LOCOCALI_LW_LOW_STANDARD	;		
	lstrLocoCaliCtrlId[5].lowmeasure	=	LOCOCALI_LW_LOW_MEASURE		;
	lstrLocoCaliCtrlId[5].higstandard	=	LOCOCALI_LW_HIG_STANDARD	;
	lstrLocoCaliCtrlId[5].higmeasure	=	LOCOCALI_LW_HIG_MEASURE		;  
	lstrLocoCaliCtrlId[5].ansyflg		=	LOCOCALI_LW_SYNC			;
	lstrLocoCaliCtrlId[5].send			=	LOCOCALI_LW					;  	
}


