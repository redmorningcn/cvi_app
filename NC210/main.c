#include "f:\cvi\project\CSNC\csnc_setpara\mian.h"

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>

#include "cvi_com1.h"  
#include "cvi_config.h"   
#include "cvi_setpara.h"   
#include "setpara.h"   

/********************************************************************************************/
/* Constants										    */
/********************************************************************************************/
//uir�ļ���
#define		UIR_MAIN_NAME			"csnc_debug.uir"

/********************************************************************************************/
/* Globals										    */
/********************************************************************************************/
//������
stcSysCtrl	sCtrl;		
int			gmainPanel  = 0;							//ȫ��������

/********************************************************************************************/
/* Application entry point.																	*/
/********************************************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)					/* Initialize CVI libraries */
		return -1;	/* out of memory */
	
	gmainPanel = LoadPanel (0, "mian.uir", MAINPANEL); 	//װ�������

	sCtrl.PC.sCom = cvi_initCom1Contrl();				//����1������������ֲ���޸ģ�

	cvi_InitBspComm(&sCtrl.PC);

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
			
			cvi_CloseBspComm(&sCtrl.PC);					//�߳��˳� 
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
		SetCtrlAttribute (panel, MAINPANEL_OPEN_SETPARA, ATTR_DIMMED, 0);
		SetCtrlAttribute (panel, MAINPANEL_OPEN_COM, ATTR_LABEL_TEXT, "�رմ���");
	}

	if(sCtrl.PC.sCom != NULL && sCtrl.PC.sCom->sConfig.open == 0)	  	//���ڹر�
	{
		SetCtrlAttribute (panel, MAINPANEL_OPEN_SETPARA, ATTR_DIMMED, 1);
		SetCtrlAttribute (panel, MAINPANEL_OPEN_COM, ATTR_LABEL_TEXT, "�򿪴���");
	}
}

int CVICALLBACK MainTimerCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_MainPanelHandle(panel);
			break;
	}
	return 0;
}
