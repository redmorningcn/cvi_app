/*
*********************************************************************************************************
*                                               uC/MODBUS
*                                         Embedded Modbus Stack
*
*                          (c) Copyright 2004-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/Modbus is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/Modbus in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/Modbus.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                     MODBUS uC/OS-II LAYER INTERFACE
*
* Filename      : mb_os.c
* Version       : V2.12
* Programmer(s) : JJL
*********************************************************************************************************
* Note(s)       :
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <utility.h>
#include "includes.h"
#include "mb_poll.h"
#include "uirbsp_config.h"


/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
static  void                 MB_OS_InitMaster  (void);
static  void                 MB_OS_ExitMaster  (void);
#endif

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
static  void                 MB_OS_InitSlave   (void);
static  void                 MB_OS_ExitSlave   (void);
static  void                 MB_OS_RxTask      (void *p_arg);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MB_OS_Init()
*
* Description : This function initializes the RTOS interface.  This function creates the following:
*
*               1) A message queue to signal the reception of a packet.
*
*               2) A task that waits for packets to be received.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_OS_Init (void)
{
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
    MB_OS_InitMaster();
#endif

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
    MB_OS_InitSlave();
#endif
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          MB_OS_InitMaster()
*
* Description : This function initializes and creates the kernel objectes needed for Modbus Master
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
static  void  MB_OS_InitMaster (void)
{

}
#endif

static int CVICALLBACK Thread_CommRecvAndSendCtrl (void *functionData);
int		mb_SlaveThreadID = 0;
int		RxSignalFlg = 0;
int		PollRxSignalFlg =0;
/*$PAGE*/
/*
*********************************************************************************************************
*                                          MB_OS_InitSlave()
*
* Description : This function initializes and creates the kernel objectes needed for Modbus Salve
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
static  void  MB_OS_InitSlave (void)
{
	
	CmtScheduleThreadPoolFunction (	DEFAULT_THREAD_POOL_HANDLE,
					   			Thread_CommRecvAndSendCtrl,		//该线程处理函数,创建一个线程函数
					   			NULL,
					   			&mb_SlaveThreadID
							  );

}
#endif

/*
*********************************************************************************************************
*                                             MB_OS_Exit()
*
* Description : This function is called to terminate the RTOS interface for Modbus channels.  We delete
*               the following uC/OS-II objects:
*
*               1) An event flag group to signal the reception of a packet.
*               2) A task that waits for packets to be received.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_OS_Exit (void)
{

}

/*
*********************************************************************************************************
*                                          MB_OS_ExitMaster()
*
* Description : This function is called to terminate the RTOS interface for Modbus Master channels.  The
*               Following objects are deleted.
*
*               (1) An event flag group to signal the reception of a packet.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
static  void  MB_OS_ExitMaster (void)
{

}
#endif

/*
*********************************************************************************************************
*                                          MB_OS_ExitSlave()
*
* Description : This function is called to terminate the RTOS interface for Modbus Salve channels.
*               The following objects are deleted.
*
*               (1) A task that waits for packets to be received.
*               (2) A message queue to signal the reception of a packet.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_OS_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
void  MB_OS_ExitSlave (void)
{

}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MB_OS_RxSignal()
*
* Description : This function signals the reception of a packet either from the Rx ISR(s) or the RTU timeout
*               timer(s) to indicate that a received packet needs to be processed.
*
* Argument(s) : pch     specifies the Modbus channel data structure in which a packet was received.
*
* Return(s)   : none.
*
* Caller(s)   : MB_ASCII_RxByte()
*               MB_RTU_TmrUpdate()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_OS_RxSignal (MODBUS_CH *pch)
{
	if(PollRxSignalFlg == 0)				//从机应答
	{
		RxSignalFlg  = 1;
	}
	else									//主机应答
	{
		PollRxSignalFlg  = 0;
	}
	
	//在窗口显示字符,接收结束
	printrecinfo("\r\n");
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              MB_OS_RxWait()
*
* Description : This function waits for a response from a slave.
*
* Argument(s) : pch     specifies the Modbus channel data structure to wait on.
*
*               perr    is a pointer to a variable that will receive an error code.  Possible errors are:
*
*                       MODBUS_ERR_NONE        the call was successful and a packet was received
*                       MODBUS_ERR_TIMED_OUT   a packet was not received within the specified timeout
*                       MODBUS_ERR_NOT_MASTER  the channel is not a Master
*                       MODBUS_ERR_INVALID     an invalid error was detected
*
* Caller(s)    : MBM_FCxx()  Modbus Master Functions
*
* Return(s)   : none
*********************************************************************************************************
*/

extern	void CVI_MBPollPanelHandle(int panel) ;
extern	int	    	gPollPanelHandle ;

void  MB_OS_RxWait (MODBUS_CH   *pch,
                    CPU_INT16U  *perr)
{
	uint32	i = 10000000;
	
	PollRxSignalFlg = 1;							//置主机应答，应答完成后，清零。
	while(i-- && (PollRxSignalFlg == 1)) 			//数据接收完成，退出
	{
		ProcessSystemEvents();						 //执行面板操作  
   		ProcessDrawEvents ();
	}
	PollRxSignalFlg = 0;							 //置为从机应答。

	*perr = MODBUS_ERR_NONE;
}

void  MB_OS_TxWait (MODBUS_CH   *pch,
                    CPU_INT16U  *perr)
{
	uint32	i = 10000000;
	
	while(i-- && MB_ChTbl[0].TxBufByteCtr) 			//无数据发送，退出
	{
		//CVI_MBPollPanelHandle(gPollPanelHandle); 					//执行面板操作 
		ProcessSystemEvents();
   		ProcessDrawEvents ();
	}
	*perr = MODBUS_ERR_NONE;
}

void  MB_OS_TxOver (MODBUS_CH   *pch )
{
	PollRxSignalFlg = 0;				//置从机接收模式，从机能正常接收数据
	

}
/*$PAGE*/
/*
*********************************************************************************************************
*                                            MB_OS_RxTask()
*
* Description : This task is created by MB_OS_Init() and waits for signals from either the Rx ISR(s) or
*               the RTU timeout timer(s) to indicate that a packet needs to be processed.
*
* Argument(s) : p_arg       is a pointer to an optional argument that is passed by uC/OS-II to the task.
*                           This argument is not used.
*
* Caller(s)   : This is a Task.
*
* Return(s)   : none.
*********************************************************************************************************
*/
#define UARAT_CFG_MAX_PORT          5           // 定义最大串口数量

extern	  MODBUS_CH  *MB_ChPortMap[UARAT_CFG_MAX_PORT] ;

#if (MODBUS_CFG_SLAVE_EN == DEF_ENABLED)
static  void  MB_OS_RxTask (void *p_arg)
{
	 if(RxSignalFlg == 1)
	 {
		RxSignalFlg = 0;
		int i = 1000;
		while(i--);
 	 	MB_RxTask(MB_ChPortMap[0]); 
	 }
}

int	FC03SendFlg = 0;
static int CVICALLBACK Thread_CommRecvAndSendCtrl (void *functionData)
{

	while(1)
	{
		MB_OS_RxTask(0);
	}
	
	return 1;
}

#endif



