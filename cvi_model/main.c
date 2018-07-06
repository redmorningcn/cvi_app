#include "cvi_db.h"  

#include "mian.h"
#include "modeltable.h"

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>

#include "cvi_config.h"   


/********************************************************************************************/
/* Constants										    */
/********************************************************************************************/



/********************************************************************************************/
/* Globals										    */
/********************************************************************************************/
//������
int			gmainPanel  = 0;						//ȫ��������

stcSysCtrl	sCtrl;		

/********************************************************************************************/
/* Application entry point.																	*/
/********************************************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)				/* Initialize CVI libraries */
		return -1;	/* out of memory */
	
	gmainPanel = LoadPanel (0, "mian.uir", MAINPANEL); //װ�������

	sCtrl.PC.sCom = cvi_initCom1Contrl();				//�ʹ���1������ϵ����ֲ��Ҫ�޸�
	cvi_InitBspComm(&sCtrl.PC);

	cvi_InitBspDB(&gsThreadModel);
	
	DisplayPanel (gmainPanel);

	RunUserInterface ();
				
	/*	Discard the loaded panels from memory */
	DiscardPanel (gmainPanel);

	return 0;
}


int CVICALLBACK mainPanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			
			//cvi_CloseBspComm(&sCtrl.PC);					//�߳��˳� 
			QuitUserInterface(0);
			break;
	}
	return 0;
}


/********************************************************************************************/
/*��弰�������¼�							            */
/********************************************************************************************/
void CVI_MainPanelHandle(int panel)
{
	//static	int	times = 0;

/////////////////////////////////////////////////ˢ��������Ϣ
	if(sCtrl.PC.sCom != NULL && sCtrl.PC.sCom->sConfig.open == 1)	  	//���ڴ�
	{				
		//SetCtrlAttribute (panel, MAINPANEL_OPEN_SETPARA, ATTR_DIMMED, 0);
		SetCtrlAttribute (panel, MAINPANEL_OPEN_COM, ATTR_LABEL_TEXT, "�رմ���");
	}

	if(sCtrl.PC.sCom != NULL && sCtrl.PC.sCom->sConfig.open == 0)	  	//���ڹر�
	{
		//SetCtrlAttribute (panel, MAINPANEL_OPEN_SETPARA, ATTR_DIMMED, 1);
		SetCtrlAttribute (panel, MAINPANEL_OPEN_COM, ATTR_LABEL_TEXT, "�򿪴���");
	}
}


extern	void Com_SetParaTask(void);		

int CVICALLBACK MainTimerCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_MainPanelHandle(panel);				//�����ư���
			
			Com_SetParaTask();						//���ڲ�������(----���ڲ�������)    
			
			break;
	}
	return 0;
}
