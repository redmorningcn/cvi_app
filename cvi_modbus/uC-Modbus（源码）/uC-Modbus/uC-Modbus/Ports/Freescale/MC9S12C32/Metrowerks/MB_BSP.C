/*
*********************************************************************************************************
*                                             Micrium, Inc.
*                                         949 Crestview Circle
*                                        Weston,  FL 33327-1848
*
*                                      MODBUS BOARD SUPPORT PACKAGE
*                                          Freescale MC9S12C32
*
*                                   (c) Copyright 2004, Micrium, Inc.
*                                          All rights reserved.
*
* Filename    : MB_BSP.C
* Version     : V1.50
* Programmers : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*							            GLOBALS
*********************************************************************************************************
*/     


/*
*********************************************************************************************************
*                                             EXIT MODBUS
*
* Description : This function is called to terminate Modbus communications.  All Modbus channels are close.
*
* Argument(s) : none
*
* Return(s)   : none.
*********************************************************************************************************
*/

CPU_VOID  MB_CommExit (CPU_VOID)
{
    CPU_INT08U   ch;
    MODBUS_CH   *pch;   


    pch = &MB_ChTbl[0];
    for (ch = 0; ch < MODBUS_MAX_CH; ch++) {    
        MBS_CommTxIntDis(pch);
        MBS_CommRxIntDis(pch);
        pch++;
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                            CONFIGURE PORT
*
* Description : This function initializes the serial port to the desired baud rate and the UART will be
*               configured for N, 8, 1 (No parity, 8 bits, 1 stop).
*
* Arguments   : ch         is the Modbus channel number (0 ... MODBUS_MAX_CH - 1)
*               port_nbr   is the desired serial port number.  This argument allows you to assign a 
*                          specific serial port to a sepcific Modbus channel.
*               baud       is the desired baud rate for the serial port.
*               parity     is the desired parity and can be either:
*                          MODBUS_PARITY_NONE
*                          MODBUS_PARITY_ODD
*                          MODBUS_PARITY_EVEN
*               bits       8 or 9 data bits
*               stops      Only 1 stop bit supported in the MC9S12 family
*
* Returns     : None.
*********************************************************************************************************
*/

CPU_VOID  MB_CommPortCfg (CPU_INT08U  ch, 
                          CPU_INT08U  port_nbr, 
                          CPU_INT32U  baud, 
                          CPU_INT08U  bits, 
                          CPU_INT08U  parity, 
                          CPU_INT08U  stops)
{
    MODBUS_CH   *pch;
    CPU_INT32U   cnts;
    CPU_INT08U   reg_val;


    if (ch < MODBUS_MAX_CH) {
        pch           = &MB_ChTbl[ch];
        pch->PortNbr  = port_nbr;
        pch->BaudRate = baud;
        pch->Parity   = parity;
        pch->Bits     = bits;
        pch->Stops    = stops;

        SCI_RxDis();                                                  /* Disable the SCI Receiver to reprogram it                */
        SCI_TxDis();                                                  /* Disable the SCI Transmitter to reprogram it             */

        reg_val = SCISR1;                                             /* Clear pending interrupts                                */
        reg_val = SCIDRL;                                             /* Clear pending interrupts                                */        
        (void)reg_val;                                                /* Eliminate compiler warning: reg_val not used            */
        
        switch (baud) {                                               /* Setup Baud Rate                                         */
            case   9600: 
                  SCI_SetBaud(9600);                                  
                  break;

            case  19200: 
                  SCI_SetBaud(19200);                                  
                  break;

            case  38400: 
                  SCI_SetBaud(38400);                                  
                  break;

            case  57600: 
                  SCI_SetBaud(57600);                                  
                  break;

            case 115200: 
                  SCI_SetBaud(115200);                                  
                  break;
                  
            default:                                                  /* Assume 38,400 by default                                */
                  SCI_SetBaud(38400);                                  
                  break;
        }

        switch (bits) {
            case 8:
                 SCI_SetDataBits(8);                                 
                 break;

            case 9:
                 SCI_SetDataBits(9);                                 
            
            default:
                 SCI_SetDataBits(8);                                 
                 break;
        }

        switch (parity) {
            case MODBUS_PARITY_ODD:
                 SCI_SetParity(SCI_PARITY_ODD);
                 break;

            case MODBUS_PARITY_EVEN:
                 SCI_SetParity(SCI_PARITY_EVEN);
                 break;

            case MODBUS_PARITY_NONE:
                 SCI_SetParity(SCI_PARITY_NONE);
                 break;
                 
            default:
                 SCI_SetParity(SCI_PARITY_NONE);
                 break;
        }
                 
        SCI_RxIntEn();                                                /* Enable Rx interrupts ONLY                               */

        SCI_RxEn();                                                   /* Enable the SCI Receiver                                 */
        SCI_TxEn();                                                   /* Enable the SCI Transmitter                              */
        
#if MODBUS_RTU_EN > 0
        cnts = (CPU_INT32U)(MB_RTU_Freq * 5L * 10L) / baud;           /* Freq * 5 char * 10 bits/char * 1/BaudRate               */
        if (cnts <= 1) {
            cnts = 2;
        }
        pch->RTU_TimeoutCnts = cnts;
        pch->RTU_TimeoutCtr  = cnts;
#endif
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         DISABLE RX INTERRUPTS
*
* Description : This function disables Rx interrupts.
*********************************************************************************************************
*/

CPU_VOID  MBS_CommRxIntDis (MODBUS_CH  *pch)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;


    cpu_sr = 0;
#endif
    OS_ENTER_CRITICAL();
    switch (pch->PortNbr) {
        case 0:
             SCI_RxIntDis();
             break;
        
        default:
             break;
    }
    OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                          ENABLE RX INTERRUPTS
*
* Description : This function enables the Rx interrupt.
*********************************************************************************************************
*/

CPU_VOID  MBS_CommRxIntEn (MODBUS_CH  *pch)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;


    cpu_sr = 0;
#endif
    OS_ENTER_CRITICAL();
    switch (pch->PortNbr) {
        case 0:
             SCI_RxIntEn();
             break;
             
        default:
             break;
    }
    OS_EXIT_CRITICAL();
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                 UART Rx/Tx Communication handler for Modbus
*
* Description: This function is the ISR for either a received or transmitted character.
*
* Arguments  : none
*
* Pseudocode : if (Rx Byte has been received) {
*                  c = get byte from serial port;
*                  Clear receive interrupt;
*                  pch->RxCtr++;                      Increment the number of bytes received
*                  MBS_RxByte(pch, c);                Pass character to Modbus to process
*              }
*              if (Byte has been transmitted) {
*                  pch->TxCtr++;                      Increment the number of bytes transmitted
*                  MBS_TxByte(pch);                   Send next byte in response
*                  Clear transmit interrupt           Clear Transmit Interrupt flag
*              }
*********************************************************************************************************
*/

CPU_VOID  MBS_CommRxTxISR_Handler (CPU_INT08U  port_nbr)
{						 
    CPU_INT08U   c;
    CPU_INT08U   ch;
    MODBUS_CH   *pch;
    CPU_INT32U   mis;
    CPU_INT08U   SCI_Status;

    
    (CPU_VOID)port_nbr;
    (CPU_VOID)ch;
    (CPU_VOID)mis;
        
    SCI_Status     = SCISR1;

    pch = &MB_ChTbl[0];

    if (SCI_Status & SCI_RX_COMPLETE) {
        c          = (CPU_INT08U)(SCIDRL);             /* Read the character from the UART             */
        pch->RxCtr++;
        MBS_RxByte(pch, c);                            /* Pass character to Modbus to process          */
    }
    
    if (SCI_Status & SCI_TX_COMPLETE) {	        
        pch->TxCtr++;
        MBS_TxByte(pch);                               /* Send next byte in response                   */        
    }    
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                UART #0 Rx/Tx Communication handler for Modbus 
*                                        (THIS IS THE START OF THE ISR!)
*********************************************************************************************************
*/

interrupt CPU_VOID  MBS_CommRxTxISR_0_Handler (CPU_VOID)
{
    MBS_CommRxTxISR_Handler(0);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         GET NEXT BYTE TO SEND
*
* Description : This function is called to obtain the next byte to send from the transmit buffer.  When
*               all bytes in the reply have been sent, transmit interrupts are disabled and the receiver
*               is enabled to accept the next Modbus request.
*
* Argument(s) : c     is the byte to send to the serial port
*
* Return(s)   : none.
*********************************************************************************************************
*/

CPU_VOID  MBS_CommTx1 (MODBUS_CH  *pch, 
                   CPU_INT08U  c)
{
    switch (pch->PortNbr) {
        case 0:
             SCI_Tx1(c);
             break;
             
        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                       Disable Tx Interrupts
*********************************************************************************************************
*/

CPU_VOID  MBS_CommTxIntDis (MODBUS_CH  *pch)
{									  
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;


    cpu_sr = 0;
#endif

    (CPU_VOID)pch;
    
    OS_ENTER_CRITICAL();
    SCI_TxIntDis();                               /* Enable SCI Receive Interrupts                     */
    OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                       Enable Tx Interrupts
*********************************************************************************************************
*/

CPU_VOID  MBS_CommTxIntEn (MODBUS_CH  *pch)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;


    cpu_sr = 0;
#endif

    (CPU_VOID)pch;
    
    OS_ENTER_CRITICAL();
    SCI_TxIntEn();                                /* Enable SCI Rx Interrupts                          */
    OS_EXIT_CRITICAL();
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                  INITIALIZE THE RTU TIMEOUT TIMER
*
* Description : This function is called to initialize the RTU timeout timer.  
*
* Argument(s) : freq   Is the frequency of the modbus RTU timer interrupt.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if MODBUS_RTU_EN > 0
CPU_VOID  MB_RTU_TmrInit (CPU_INT32U  freq)
{						
    ECT_ChInt_Init(MB_ECT_CH, freq);                  /* Use ECT Channel selected in app.cfg at freq hz     */
                                                      /* for the RTU timer                                  */

    MB_RTU_Freq  = freq;                              /* Save the RTU frequency                             */

    MB_RTU_TmrResetAll();                             /* Reset all the RTU timers, we changed freq.         */
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                  DISABLE THE RTU TIMEOUT TIMER
*
* Description : This function is called to disable the RTU timeout timer.  
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if MODBUS_RTU_EN > 0
CPU_VOID  MB_RTU_TmrExit (CPU_VOID)
{    
    ECT_IntDis(MB_ECT_CH);                            /* Disable the MB ECT Timer Channel Interrupts        */                              
}
#endif

/*$PAGE*/
/*
*******************************************************************************
*                       Modbus RTU Timeout Timer ISR
*
* Description : This function handles the case when the RTU timeout timer expires.
*               OS Timers are assumed to be configured in the OS_CFG.H, OS Ver >= 2.81
*
* Arguments   : None.
*
* Returns     : None.
*******************************************************************************
*/

#if MODBUS_RTU_EN > 0
interrupt CPU_VOID  MB_RTU_Tmr_Timeout (CPU_VOID)
{
    TFLG1    |= (1 << MB_ECT_CH);                     /* Clear the ECT interrupt flag for the channel used  */
    MB_RTU_TmrCtr++;                                  /* Indicate that we had activities on this interrupt. */
    MB_RTU_TmrUpdate();                               /* Check for RTU timers that have expired             */
}
#endif
	 		  	 	  	 		 		   		  	  			 	  	 		 	 	 			 	 		 		 
