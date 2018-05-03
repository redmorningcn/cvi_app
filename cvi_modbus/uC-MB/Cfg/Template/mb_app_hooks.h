/*
************************************************************************************************************************
*                                                     uC/MB-III
*                                                The Real-Time Kernel
*
*                                  (c) Copyright 2009-2010; Micrium, Inc.; Weston, FL
*                          All rights reserved.  Protected by international copyright laws.
*
*                                                  APPLICATION HOOKS
*
* File    : MB_APP_HOOKS.H
* By      : JJL
* Version : V3.01.2
*
* LICENSING TERMS:
* ---------------
*               uC/MB-III is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
************************************************************************************************************************
*/

#ifndef  MB_APP_HOOKS_H
#define  MB_APP_HOOKS_H


#ifdef   MB_APP_HOOKS_H_GLOBALS
#define  MB_APP_HOOKS_H_EXT
#else
#define  MB_APP_HOOKS_H_EXT  extern
#endif

/*
************************************************************************************************************************
*                                                 INCLUDE HEADER FILES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*                                                 FUNCTION PROTOTYPES
************************************************************************************************************************
*/

void  App_MB_SetAllHooks            (void);
void  App_MB_ClrAllHooks            (void);



CPU_INT08U  App_MB_RdNRegsHook    ( CPU_INT16U  reg_base,
                                    CPU_INT16U *prx_data,
                                    CPU_INT16U  reg_nbr,
                                    CPU_INT16U *perr);

CPU_INT08U  App_MB_WrNRegsHook    ( CPU_INT16U  reg_base,
                                    CPU_INT16U *prx_data,
                                    CPU_INT16U  reg_nbr,
                                    CPU_INT16U *perr);

#endif
