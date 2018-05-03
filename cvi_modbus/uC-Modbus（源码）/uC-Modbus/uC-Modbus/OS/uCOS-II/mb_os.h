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
*                                     MODBUS uC/OS-II LAYER INTERFACE
* 
* Filename      : mb_os.h
* Version       : V2.12
* Programmer(s) : JJL
*********************************************************************************************************
* Note(s)       :
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  MB_OS_MODULE_PRESENT
#define  MB_OS_MODULE_PRESENT

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
*********************************************************************************************************
*/

#include <mb_cfg.h>
#include <mb.h>
#include <ucos_ii.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   MB_OS_MODULE
#define  MB_OS_EXT
#else
#define  MB_OS_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if      (OS_Q_EN == 0)
#error  "MODBUS Slave requires uC/OS-II Message Queue Services."
#endif

#ifndef  MB_OS_CFG_RX_TASK_ID
#error  "MODBUS Missing Rx Task's MB_OS_CFG_RX_TASK_ID."
#endif


#ifndef  MB_OS_CFG_RX_TASK_PRIO
#error  "MODBUS Missing Rx Task's MB_OS_CFG_RX_TASK_PRIO."
#endif


#ifndef  MB_OS_CFG_RX_TASK_STK_SIZE
#error  "MODBUS Missing Rx Task's MB_OS_CFG_RX_TASK_STK_SIZE."
#endif

#if      (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
#if      (OS_SEM_EN            == 0          )
#error  "MODBUS Master requires uC/OS-II Semaphore Services."
#error  "... It needs MODBUS_CFG_MAX_CH semaphores."
#endif
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of MB_OS module                                */

