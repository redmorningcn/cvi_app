/*******************************************************************************
 *   Filename:       main.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:
					 1�������ļ�
/////////////////////////////////////////////////////////////////////////////
					 ˫��ѡ�� otr �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Otr �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� OTR �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_COMM_PRIO     ��
 *                                            �� �����ջ�� APP_TASK_COMM_STK_SIZE ����С
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include <rs232.h>
#include "asynctmr.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "includes.h"

#include "modbus_poll.h"
#include "MB_BSP.h"
#include "comconfig.h"
#include "uirbsp_config.h"
#include "main.h"



int gmainPanel;




strCtrl		sCtrl;

int CVICALLBACK mb_mainPanelCB (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			
			QuitUserInterface(0);
			break;
	}
	return 0;
}



extern	stcUartConfig		mb_com1config;

/********************************************************************************************/
/* Application entry point.																	*/
/********************************************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)					/* Initialize CVI libraries */
		return -1;	/* out of memory */

	if ((gmainPanel = LoadPanel (0, "modbus_poll.uir", MAIN)) < 0)
		return -1;
	DisplayPanel (gmainPanel);
	
	ConfigMbComWithFile();						//ͨ���ļ����ô���
	
	MB_Init(1000);								//��ʼ��modbusƵ��					

    sCtrl.pch         = MB_CfgCh( ModbusNode,        	// ... Modbus Node # for this slave channel
                        MODBUS_SLAVE,           // ... This is a MASTER
                        500,                    // ... 0 when a slave
                        MODBUS_MODE_RTU,        // ... Modbus Mode (_ASCII or _RTU)
                        0,                      // ... Specify UART #2
                        mb_com1config.baut,                  // ... Baud Rate
                        mb_com1config.bits,         				// ... Number of data bits 7 or 8
                        mb_com1config.parity,       				// ... Parity: _NONE, _ODD or _EVEN
                        mb_com1config.stops,         				// ... Number of stop bits 1 or 2
                        MODBUS_WR_EN);          // ... Enable (_EN) or disable (_DIS) writes
	
	sCtrl.com1	= &mb_com1config;				//ָ������

	RunUserInterface ();								//����

	return 0;
}


/********************************************************************************************/
/*??��??��?��?��D?��??t							            */
/********************************************************************************************/
void CVI_MainPanelHandle(int panel)
{
	//static	int	times = 0;

/////////////////////////////////////////////////?��D?????D??��
	if(sCtrl.com1 != NULL && sCtrl.com1->open == 1)	  	//��??���䨰?a
	{				
		SetCtrlAttribute (panel, MAIN_POLL, ATTR_DIMMED, 0);
		SetCtrlAttribute (panel, MAIN_SLAVE, ATTR_DIMMED, 0);

		SetCtrlAttribute (panel, MAIN_COMCONFIG, ATTR_LABEL_TEXT, "�رմ���");
	}

	if(sCtrl.com1 != NULL && sCtrl.com1->open == 0)	  	//��??��1?��?
	{
		SetCtrlAttribute (panel, MAIN_POLL, ATTR_DIMMED, 1);
		SetCtrlAttribute (panel, MAIN_SLAVE, ATTR_DIMMED, 1);
		SetCtrlAttribute (panel, MAIN_COMCONFIG, ATTR_LABEL_TEXT, "���ô���");
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



