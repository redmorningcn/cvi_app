/*******************************************************************************
 *   Filename:       main.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:
					 1、测试文件
/////////////////////////////////////////////////////////////////////////////
					 双击选中 otr 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 Otr 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 OTR 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   在 app_cfg.h 中指定本任务的 优先级  （ APP_TASK_COMM_PRIO     ）
 *                                            和 任务堆栈（ APP_TASK_COMM_STK_SIZE ）大小
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
	
	ConfigMbComWithFile();						//通过文件配置串口
	
	MB_Init(1000);								//初始化modbus频率					

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
	
	sCtrl.com1	= &mb_com1config;				//指定串口

	RunUserInterface ();								//运行

	return 0;
}


/********************************************************************************************/
/*??°??°?ü?úD?ê??t							            */
/********************************************************************************************/
void CVI_MainPanelHandle(int panel)
{
	//static	int	times = 0;

/////////////////////////////////////////////////?￠D?????D??￠
	if(sCtrl.com1 != NULL && sCtrl.com1->open == 1)	  	//′??ú′ò?a
	{				
		SetCtrlAttribute (panel, MAIN_POLL, ATTR_DIMMED, 0);
		SetCtrlAttribute (panel, MAIN_SLAVE, ATTR_DIMMED, 0);

		SetCtrlAttribute (panel, MAIN_COMCONFIG, ATTR_LABEL_TEXT, "关闭串口");
	}

	if(sCtrl.com1 != NULL && sCtrl.com1->open == 0)	  	//′??ú1?±?
	{
		SetCtrlAttribute (panel, MAIN_POLL, ATTR_DIMMED, 1);
		SetCtrlAttribute (panel, MAIN_SLAVE, ATTR_DIMMED, 1);
		SetCtrlAttribute (panel, MAIN_COMCONFIG, ATTR_LABEL_TEXT, "配置串口");
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



