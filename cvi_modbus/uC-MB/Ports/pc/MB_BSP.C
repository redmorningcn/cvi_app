/*
*********************************************************************************************************
*                                              uC/Modbus
*                                       The Embedded Modbus Stack
*
*                          (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL               
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            uC/Modbus
*
*                                      MODBUS BOARD SUPPORT PACKAGE
*                                         Philips LPC2000 (ARM7)
*
* Filename    : mb_bsp.c
* Version     : V2.12
* Programmers : JJL
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include <utility.h>
#include "asynctmr.h"
#include <rs232.h>
#include <ansi_c.h>
#include <userint.h>
#include  <global.h>
#include  <mb.h>
#include <utility.h>
#include "includes.h"
#include "MB_BSP.h"
#include "formatio.h"

//串口允许标识
typedef	struct	_strUartEnable_
{
	char	send;
	char	rec;
}strUardEnable;
strUardEnable	sEnableFlg;

/*
*********************************************************************************************************
*                                             LOCAL VARIABLES
*********************************************************************************************************
*/

#define UARAT_CFG_MAX_PORT          5           // 定义最大串口数量
MODBUS_CH  			*MB_ChPortMap[UARAT_CFG_MAX_PORT] = {NULL,NULL,NULL,NULL,NULL};

#define	MB_CONFIG_NAME	"mb_uartconfig"

stcUartConfig		mb_com1config;


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MB_CommExit()
*
* Description : This function is called to terminate Modbus communications.  All Modbus channels are close.
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
void  MB_CommExit (void)
{
    CPU_INT08U   ch;
    MODBUS_CH   *pch;


    pch = &MB_ChTbl[0];
    for (ch = 0; ch < MODBUS_CFG_MAX_CH; ch++) {
        MB_CommTxIntDis(pch);
        MB_CommRxIntDis(pch);
        pch++;
    }
}

void CVICALLBACK mb_Com1RecvAndSend (int portNo,int eventMask,void *callbackData) ;

int	mb_ThreadID = 0;
static int CVICALLBACK Thread_CommCallback (void *functionData)
{

	char	rx_data;	
	while(1)
	{
		if(mb_com1config.open == 1)										//串口打开
		{
			if(GetOutQLen(mb_com1config.port)==0 && sEnableFlg.send)						//发送数据(数据空，调用发送函数)
			{
				MB_ChPortMap[0]->TxCtr++;
			    MB_TxByte(MB_ChPortMap[0]);                          	/* Send next byte                                       */
			}


			while(GetInQLen(mb_com1config.port) && sEnableFlg.rec)						//有数据未取（有数据，取数）
			{
				rx_data = (char)ComRdByte (mb_com1config.port);
				MB_ChPortMap[0]->RxCtr++;
				MB_RxByte(MB_ChPortMap[0], rx_data);                   /* Pass character to Modbus to process                  */
			}
		}
	}
	return 1;
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MB_CommPortCfg()
*
* Description : This function initializes the serial port to the desired baud rate and the UART will be
*               configured for N, 8, 1 (No parity, 8 bits, 1 stop).
*
* Argument(s) : pch        is a pointer to the Modbus channel
*               port_nbr   is the desired serial port number.  This argument allows you to assign a
*                          specific serial port to a sepcific Modbus channel.
*               baud       is the desired baud rate for the serial port.
*               parity     is the desired parity and can be either:
*
*                          MODBUS_PARITY_NONE
*                          MODBUS_PARITY_ODD
*                          MODBUS_PARITY_EVEN
*
*               bits       specifies the number of bit and can be either 7 or 8.
*               stops      specifies the number of stop bits and can either be 1 or 2
*
* Return(s)   : none.
*
* Caller(s)   : MB_CfgCh()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  MB_CommPortCfg (MODBUS_CH  *pch,
                      CPU_INT08U  port_nbr,
                      CPU_INT32U  baud,
                      CPU_INT08U  bits,
                      CPU_INT08U  parity,
                      CPU_INT08U  stops)
{

	CmtScheduleThreadPoolFunction (	DEFAULT_THREAD_POOL_HANDLE,
						   			Thread_CommCallback,		//该线程处理函数,创建一个线程函数
						   			NULL,
						   			&mb_ThreadID
									);
									
    if (pch != (MODBUS_CH *)0) {
        pch->PortNbr            = port_nbr;                   		/* Store configuration in channel             */
        pch->BaudRate           = mb_com1config.baut;
        pch->Parity             = mb_com1config.parity;
        pch->Bits               = mb_com1config.bits;
        pch->Stops              = mb_com1config.stops;
        MB_ChPortMap[port_nbr]  = pch;
    }
	
	MB_CommRxIntEn(pch);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                         MB_CommRxIntDis()
*
* Description : This function disables Rx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_CommExit()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  MB_CommRxIntDis (MODBUS_CH  *pch)
{

    switch (pch->PortNbr) {
    case 0:

		sEnableFlg.rec 	= 0;
		break;
        
    case 1:

        break;
        
    case 2:

        break;
        
    case 3:

        break;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          MB_CommRxIntEn()
*
* Description : This function enables Rx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_TxByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  MB_CommRxIntEn (MODBUS_CH  *pch)
{

    switch (pch->PortNbr) {
    case 0:
		
        sEnableFlg.rec = 1;
		
        break;
        
    case 1:

        break;
        
    case 2:

        break;
        
    case 3:

        break;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                       MB_CommRxTxISR_Handler()
*
* Description : This function is the ISR for either a received or transmitted character.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is a ISR
*
* Note(s)     : (1) The pseudo-code for this function should be:  
*
*               if (Rx Byte has been received) {
*                  c = get byte from serial port;
*                  Clear receive interrupt;
*                  pch->RxCtr++;                      Increment the number of bytes received
*                  MB_RxByte(pch, c);                 Pass character to Modbus to process
*              }
*
*              if (Byte has been transmitted) {
*                  pch->TxCtr++;                      Increment the number of bytes transmitted
*                  MB_TxByte(pch);                    Send next byte in response
*                  Clear transmit interrupt           Clear Transmit Interrupt flag
*              }
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                UART #0 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             MB_CommTx1()
*
* Description : This function is called to obtain the next byte to send from the transmit buffer.  When
*               all bytes in the reply have been sent, transmit interrupts are disabled and the receiver
*               is enabled to accept the next Modbus request.
*
* Argument(s) : c     is the byte to send to the serial port
*
* Return(s)   : none.
*
* Caller(s)   : MB_TxByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommTx1 (MODBUS_CH  *pch,
                  CPU_INT08U  c)
{
    switch (pch->PortNbr) {
    case 0:
        /* Transmit Data */
		ComWrtByte(mb_com1config.port,c);
        break;
        
    case 1:
        /* Transmit Data */

		break;
        
    case 2:
        /* Transmit Data */

		break;
        
    case 3:
        /* Transmit Data */

		break;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                         MB_CommTxIntDis()
*
* Description : This function disables Tx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_CommExit()
*               MB_TxByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommTxIntDis (MODBUS_CH  *pch)
{

    switch (pch->PortNbr) {                       /* Just enable the receiver interrupt                */
    case 0:
		sEnableFlg.send = 0;
        break;
        
    case 1:

        break;
        
    case 2:

        break;
        
    case 3:

        break;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                         MB_CommTxIntEn()
*
* Description : This function enables Tx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_Tx()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  MB_CommTxIntEn (MODBUS_CH  *pch)
{

    switch (pch->PortNbr) {                       /* Just enable the receiver interrupt                */
    case 0:
		sEnableFlg.send = 1;
        break;
        
    case 1:

        break;
        
    case 2:

        break;
        
    case 3:

        break;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////定时器
//modbus异步定时器
int	 md_ansytimerid = 0;
/*$PAGE*/
/*
*********************************************************************************************************
*                                           MB_RTU_TmrExit()
*
* Description : This function is called to disable the RTU timeout timer.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : MB_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
void  MB_RTU_TmrExit (void)
{
	DiscardAsyncTimer(md_ansytimerid);					//关闭异步定时器
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                       MB_RTU_TmrISR_Handler()
*
* Description : This function handles the case when the RTU timeout timer expires.
*
* Arguments   : none.
*
* Returns     : none.
*
* Caller(s)   : This is a ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
void  MB_RTU_TmrISR_Handler (void)
{
      MB_RTU_TmrCtr++;                              /* Indicate that we had activities on this interrupt. */
      MB_RTU_TmrUpdate();                           /* Check for RTU timers that have expired             */
}
#endif
                      


//modbus的异步定时器的回调函数
int  CVICALLBACK mb_AnsyTimerCallback (	int reserved, int theTimerId, int event,
                       		void *callbackData, int eventData1,
                         	int eventData2)
{
	MB_RTU_TmrISR_Handler();
	return 1;
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MB_RTU_TmrInit()
*
* Description : This function is called to initialize the RTU timeout timer.
*
* Argument(s) : freq          Is the frequency of the modbus RTU timer interrupt.
*
* Return(s)   : none.
*
* Caller(s)   : MB_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
void  MB_RTU_TmrInit (void)
{

   	md_ansytimerid	= NewAsyncTimer ( 0.005 , -1,	//开异步定时器，5个波特率时间。( 0.001 = 1ms )
	   									1, mb_AnsyTimerCallback, NULL); 
}
#endif

CPU_INT16U   MB_getPseudo               ( void )
{
	return	0;
}



/********************************************************************************************/
/* ReadCom1ConfigFromFile  		从配置文件中读出串口的配置文件，如果有则按配置文件配置；
否则，显示默认值	*/
/********************************************************************************************/
int	ReadMbComConfigFromFile(stcUartConfig * sUartConfig)
{
	char 	fileName[64];									//文件指针
	char 	projectDir[MAX_PATHNAME_LEN];				//工程路径
	char 	fullPath[MAX_PATHNAME_LEN];					//文件全路径
	ssize_t size;										//文件大小
	int		filecom1hand;								//文件句柄
	stcUartConfig   comconfig;
	int		readsize;
	int		flg = 0;

	strcpy(fileName,MB_CONFIG_NAME);	
	strcat(fileName,".ini");	

	GetProjectDir (projectDir) ;						//取项目路径
//
	MakePathname (projectDir, fileName, fullPath);		//文件路劲 where fullPath has the following format: c:\myproject\myfile.dat

	if(GetFileInfo (fullPath, &size) == 0)				//文件不存在
	{
		filecom1hand = OpenFile (fullPath, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);   	//打开文件
		comconfig.baut = 57600;
		comconfig.port = 1;
		memcpy((char *)sUartConfig,(char *)&comconfig,sizeof(stcUartConfig));
	}else{
		filecom1hand = OpenFile (fullPath, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);		//打开文件

		SetFilePtr (filecom1hand, 0, 0);													//文件从头开始

		readsize = ReadFile (filecom1hand, (char *)&comconfig, sizeof(stcUartConfig));		//配置文件读取

		if(readsize)																		//数据大于零
		{
			if(0 < comconfig.port && comconfig.port < 11)									//端口号正常
				if(comconfig.stops == 1  || comconfig.stops == 2)							//停止位1、2
					 if(5<comconfig.bits && comconfig.bits < 9)								//数据位5-8
					 {
						memcpy((char *)sUartConfig,(char *)&comconfig,sizeof(stcUartConfig));
						flg = 1;
					 }
		}
		else
		{
			comconfig.baut 		= 57600;
			comconfig.port 		= 1;
			comconfig.stops 	= 1;
			comconfig.bits  	= 8; 
			comconfig.parity  	= 0;  

			memcpy((char *)sUartConfig,(char *)&comconfig,sizeof(stcUartConfig));
		}
	}

	CloseFile(filecom1hand);							//关闭文件

	return	flg;
}

/********************************************************************************************/
/* WriteCom1ConfigToFile  		写配置数据到文件
/********************************************************************************************/
void	WriteMbComConfigToFile(stcUartConfig * sUartConfig)
{
	char 	fileName[64];								//文件指针
	char 	projectDir[MAX_PATHNAME_LEN];				//工程路径
	char 	fullPath[MAX_PATHNAME_LEN];					//文件全路径
	int		filecom1hand;								//文件句柄

	strcpy(fileName,MB_CONFIG_NAME);	
	strcat(fileName,".ini");	

	GetProjectDir (projectDir) ;					//取项目路径

	MakePathname (projectDir, fileName, fullPath);	//文件路劲 where fullPath has the following format: c:\myproject\myfile.dat

	filecom1hand = OpenFile (fullPath, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);		//打开文件

	SetFilePtr (filecom1hand, 0, 0);													//文件从头开始

	WriteFile (filecom1hand, (char *)sUartConfig, sizeof(stcUartConfig));

	CloseFile(filecom1hand);															//关闭文件
}
