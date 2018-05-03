/*
*********************************************************************************************************
*                                            uC/Modbus
*
*                         (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL
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
*                                      MODBUS CONFIGURATION
*
* Filename      : mb_cfg.h
* Version       : V2.12
* Programmer(s) : JJL
*********************************************************************************************************
* Note(s)       : (1) This file contains configuration constants for uC/Modbus
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  MODBUS MODULES CONFIGURATION
*********************************************************************************************************
*/

#define  MODBUS_CFG_SLAVE_EN              DEF_ENABLED           /* Enable or Disable  Modbus Slave                    */
#define  MODBUS_CFG_MASTER_EN             DEF_DISABLED          /* Enable or Disable  Modbus Master                   */

/*
*********************************************************************************************************
*                                  MODBUS MODES CONFIGURATION
*********************************************************************************************************
*/

#define  MODBUS_CFG_ASCII_EN               DEF_ENABLED          /* Modbus ASCII is supported when DEF_ENABLED         */
#define  MODBUS_CFG_RTU_EN                 DEF_ENABLED          /* Modbus RTU   is supported when DEF_ENABLED         */

/*
*********************************************************************************************************
*                               MODBUS COMMUNICATION CONFIGURATION
*********************************************************************************************************
*/

#define  MODBUS_CFG_MAX_CH                          10           /* Maximum number of Modbus channels.                 */

#define  MODBUS_CFG_BUF_SIZE                       255           /* Maximum outgoing message size.                     */

/*
*********************************************************************************************************
*                                  MODBUS FLOATING POINT SUPPORT
*********************************************************************************************************
*/

#define  MODBUS_CFG_FP_EN                  DEF_ENABLED          /* Enable Floating-Point support.                     */

#if     (MODBUS_CFG_FP_EN == DEF_ENABLED)
#define  MODBUS_CFG_FP_START_IX                  5000           /* Start address of Floating-Point registers          */
#else
#define  MODBUS_CFG_FP_START_IX                 65500           /* Floating point is disabled, set start of ...       */
                                                                /*   ...FP very high                                  */
#endif


/*
*********************************************************************************************************
*                                   MODBUS FUNCTIONS CONFIGURATION
*********************************************************************************************************
*/

#define  MODBUS_CFG_FC01_EN                DEF_ENABLED          /* Enable or Disable support for Modbus functions     */
#define  MODBUS_CFG_FC02_EN                DEF_ENABLED
#define  MODBUS_CFG_FC03_EN                DEF_ENABLED
#define  MODBUS_CFG_FC04_EN                DEF_ENABLED
#define  MODBUS_CFG_FC05_EN                DEF_ENABLED
#define  MODBUS_CFG_FC06_EN                DEF_ENABLED
#define  MODBUS_CFG_FC08_EN                DEF_ENABLED
#define  MODBUS_CFG_FC15_EN                DEF_ENABLED
#define  MODBUS_CFG_FC16_EN                DEF_ENABLED
#define  MODBUS_CFG_FC20_EN                DEF_DISABLED
#define  MODBUS_CFG_FC21_EN                DEF_DISABLED