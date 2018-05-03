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
#include <global.h>
#include <includes.h>
#include <lpc17xx_uart.h>
#include <lpc17xx_gpio.h>
#include <GPIO_APP.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES 
*********************************************************************************************************
*/

#define  BIT0               0x01
#define  BIT1               0x02
#define  BIT2               0x04
#define  BIT3               0x08
#define  BIT4               0x10
#define  BIT5               0x20
#define  BIT6               0x40
#define  BIT7               0x80


#define UARAT_CFG_MAX_PORT  5       // 定义最大串口数量

/***********************************************
* 描述： 
*/
#define  BSP_COM0_REN       DEF_ENABLED
#define  BSP_COM1_REN       DEF_ENABLED
#define  BSP_COM2_REN       DEF_ENABLED
#define  BSP_COM3_REN       DEF_ENABLED


//0号串口引脚配置
#define     TXD0	        2
#define     RXD0	        3
//#define     EN_485_0		27
#define     EN_485_0		428

//1号串口引脚配置
#define		TXD1            15
#define		RXD1            16
#define		EN_485_1        122

//2号串口引脚配置
#define		TXD2            10
#define		RXD2            11
#define		EN_485_2        128

//3号串口引脚配置
#define		TXD3			0
#define		RXD3			1
#define		EN_485_3		129




/*
*********************************************************************************************************
*                                             LOCAL VARIABLES
*********************************************************************************************************
*/

static  CPU_INT32U  MB_Tmr_ReloadCnts;
static  MODBUS_CH  *MB_ChPortMap[UARAT_CFG_MAX_PORT] = {NULL,NULL,NULL,NULL,NULL};


void    USARTx_RxTxISRHandler   (MODBUS_CH *pch);

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

/*
*********************************************************************************************************
*                                            WriteEN_485()
*
* Description : 485  收发控制.
*
* Argument(s) : pornum：串口号
                ctl：  0，接收；1发送
*
* Return(s)   : none.
*
* Caller(s)   : MB_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void    WriteEN_485(CPU_INT08U port_nbr,CPU_INT08U ctl)
{
    CPU_INT08U  en485_pins[5] = {EN_485_0,EN_485_1,EN_485_2,EN_485_3};

    if(ctl)		
	{
		GPIO_SetOrClearValue(en485_pins[port_nbr],1);
	}
	else
	{
		GPIO_SetOrClearValue(en485_pins[port_nbr],0);		
	}	
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
    UART_CFG_Type		    UART_ConfigStruct_Test;
    UART_FIFO_CFG_Type 	    FIFOCfg_Test;
    UART_INT_Type 		    UARTIntCfg_Test;
    LPC_UART_TypeDef*       USARTx;
    IRQn_Type               UARTx_IRQn;
    LPC_UART_TypeDef*       USARTs[4]   = {
        (LPC_UART_TypeDef *)LPC_UART0,
        (LPC_UART_TypeDef *)LPC_UART1,
        (LPC_UART_TypeDef *)LPC_UART2,
        (LPC_UART_TypeDef *)LPC_UART3
    };
    
    /***********************************************
    * 描述： 
    */
    switch ( port_nbr ) {
    case 0:  
        USARTx      = (LPC_UART_TypeDef *)LPC_UART0;
        UARTx_IRQn  = UART0_IRQn;
        
        //配置端口为UART和收发控制端口为GPIO
        GPIO_PinselConfig(RXD0,1);
        GPIO_PinselConfig(TXD0,1);	
        GPIO_PinselConfig(EN_485_0,0);
        
        /***********************************************
        * 描述： 接收发送使能信号
        */
#if (BSP_COM0_REN == DEF_ENABLED)
        WriteEN_485(port_nbr,0);  // 低电平接收使能 
#endif
        break;
        
    case 1:
        USARTx      = (LPC_UART_TypeDef *)LPC_UART1;
        UARTx_IRQn  = UART1_IRQn;
        
        //配置端口为UART和收发控制端口为GPIO
        GPIO_PinselConfig(RXD1,1);
        GPIO_PinselConfig(TXD1,1);	
        GPIO_PinselConfig(EN_485_1,0);
        
        /***********************************************
        * 描述： 接收发送使能信号
        */
#if (BSP_COM1_REN == DEF_ENABLED)
        
        WriteEN_485(port_nbr,0);                                   // 低电平接收使能 
#endif
        break;
        
    case 2:
        USARTx      = (LPC_UART_TypeDef *)LPC_UART2;        
        UARTx_IRQn  = UART2_IRQn;
        
        //配置端口为UART和收发控制端口为GPIO
        GPIO_PinselConfig(RXD2,1);
        GPIO_PinselConfig(TXD2,1);	
        GPIO_PinselConfig(EN_485_2,0);	
        
        /***********************************************
        * 描述： 接收发送使能信号
        */
#if (BSP_COM2_REN == DEF_ENABLED)
        WriteEN_485(port_nbr,0);                                   // 低电平接收使能 
#endif
        break;
        
    case 3:
        USARTx      = (LPC_UART_TypeDef *)LPC_UART3;
        UARTx_IRQn  = UART3_IRQn;
        
        //配置端口为UART和收发控制端口为GPIO
        GPIO_PinselConfig(RXD3,2);
        GPIO_PinselConfig(TXD3,2);	
        GPIO_PinselConfig(EN_485_3,0);
        
        /***********************************************
        * 描述： 接收发送使能信号
        */
#if (BSP_COM3_REN == DEF_ENABLED)
        WriteEN_485(port_nbr,0);                                   // 低电平接收使能 
#endif
        break;
    default:
    }
    
    
    //串口格式配置
    UART_ConfigStruct_Test.Baud_rate  = baud;
    UART_ConfigStruct_Test.Databits   = (UART_DATABIT_Type)bits;
    UART_ConfigStruct_Test.Parity     = (UART_PARITY_Type)parity;
    UART_ConfigStruct_Test.Stopbits   = (UART_STOPBIT_Type)stops;  
    
    UART_Init((LPC_UART_TypeDef *)USARTs[port_nbr],(UART_CFG_Type *)&UART_ConfigStruct_Test);
    UART_TxCmd((LPC_UART_TypeDef *)USARTs[port_nbr],ENABLE);
    
    //收发缓存配置
    FIFOCfg_Test.FIFO_DMAMode         = DISABLE;
    FIFOCfg_Test.FIFO_Level           = UART_FIFO_TRGLEV0;     //fifo len 1
    FIFOCfg_Test.FIFO_ResetRxBuf      = DISABLE;
    FIFOCfg_Test.FIFO_ResetTxBuf      = DISABLE;	 
    
    UART_FIFOConfig((LPC_UART_TypeDef *)USARTs[port_nbr], (UART_FIFO_CFG_Type *)&FIFOCfg_Test);
    
    //中断类型配置
    UARTIntCfg_Test = UART_INTCFG_RBR;	
    UART_IntConfig((LPC_UART_TypeDef *)USARTs[port_nbr], UARTIntCfg_Test,ENABLE);   
    //UARTIntCfg_Test = UART_INTCFG_THRE;	
    //UART_IntConfig((LPC_UART_TypeDef *)USARTs[port_nbr], UARTIntCfg_Test,DISABLE);    
    
    if (pch != (MODBUS_CH *)0) {
        pch->PortNbr            = port_nbr;                                 /* Store configuration in channel             */
        pch->BaudRate           = baud;
        pch->Parity             = parity;
        pch->Bits               = bits;
        pch->Stops              = stops;
        pch->USARTx             = USARTx;                
        MB_ChPortMap[port_nbr]  = pch;
    }
        
    //配置中断向量
    NVIC_SetPriority(UARTx_IRQn, UARTx_IRQn);
    NVIC_EnableIRQ(UARTx_IRQn);
    return;
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
    CPU_SR  cpu_sr = 0;

    CPU_CRITICAL_ENTER();
    switch (pch->PortNbr) {
    case 0:
        /***********************************************
        * 描述： 收发送使能控制信号
        */
#if (BSP_COM0_REN == DEF_ENABLED)
        //GPIO_SetBits(MBREN1_GPIO_PORT, MBREN1_GPIO_PIN);        // 高电平发送使能 
        WriteEN_485(pch->PortNbr,1);
#endif
        //USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
        UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,DISABLE);
        break;
        
    case 1:
        /***********************************************
        * 描述： 收发送使能控制信号
        */
#if (BSP_COM1_REN == DEF_ENABLED)
        //GPIO_SetBits(MBREN2_GPIO_PORT, MBREN2_GPIO_PIN);        // 高电平发送使能 
        WriteEN_485(pch->PortNbr,1);

#endif
        //USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
        UART_IntConfig((LPC_UART_TypeDef *) LPC_UART1,UART_INTCFG_RBR,DISABLE);
        break;
        
    case 2:
        /***********************************************
        * 描述： 收发送使能控制信号
        */
#if (BSP_COM2_REN == DEF_ENABLED)
        //GPIO_SetBits(MBREN3_GPIO_PORT, MBREN3_GPIO_PIN);        // 高电平发送使能 
        WriteEN_485(pch->PortNbr,1);
#endif
        //USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
        UART_IntConfig(LPC_UART2,UART_INTCFG_RBR,DISABLE);
        break;
        
    case 3:
        /***********************************************
        * 描述： 收发送使能控制信号
        */
#if (BSP_COM3_REN == DEF_ENABLED)
        //GPIO_SetBits(MBREN4_GPIO_PORT, MBREN4_GPIO_PIN);        // 高电平发送使能 
        WriteEN_485(pch->PortNbr,1);

#endif
        //USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
        UART_IntConfig(LPC_UART3,UART_INTCFG_RBR,DISABLE);
        break;
    }
    CPU_CRITICAL_EXIT();
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
    CPU_SR  cpu_sr = 0;

    CPU_CRITICAL_ENTER();
    switch (pch->PortNbr) {
    case 0:
#if (BSP_COM0_REN == DEF_ENABLED)
        //GPIO_ResetBits(MBREN1_GPIO_PORT, MBREN1_GPIO_PIN);  // 低电平接收使能 
      WriteEN_485(pch->PortNbr,0);

#endif
        //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);     
        UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);
        break;
        
    case 1:
#if (BSP_COM1_REN == DEF_ENABLED)
        //GPIO_ResetBits(MBREN2_GPIO_PORT, MBREN2_GPIO_PIN);  // 低电平接收使能 
      WriteEN_485(pch->PortNbr,0);

#endif
        //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
        UART_IntConfig((LPC_UART_TypeDef *) LPC_UART1,UART_INTCFG_RBR,ENABLE);
        break;
        
    case 2:
#if (BSP_COM2_REN == DEF_ENABLED)
        //GPIO_ResetBits(MBREN3_GPIO_PORT, MBREN3_GPIO_PIN);  // 低电平接收使能 
      WriteEN_485(pch->PortNbr,0);

#endif
        //USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
      UART_IntConfig(LPC_UART2,UART_INTCFG_RBR,ENABLE);

        break;
        
    case 3:
#if (BSP_COM3_REN == DEF_ENABLED)
        //GPIO_ResetBits(MBREN4_GPIO_PORT, MBREN4_GPIO_PIN);  // 低电平接收使能 
      WriteEN_485(pch->PortNbr,0);

#endif
        //USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
      UART_IntConfig(LPC_UART3,UART_INTCFG_RBR,ENABLE);

        break;
    }
    CPU_CRITICAL_EXIT();
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
void  USARTx_RxTxISRHandler (MODBUS_CH *pch)
{
    volatile            CPU_INT08U    rx_data;
    volatile            CPU_INT08U    RecNumCom;
    
    USART_TypeDef*       USARTx  = pch->USARTx;
    
   // while ((USARTx->IIR & 0x01) == 0)
    {                                                            /* 是否有中断       */
        
        switch (USARTx->IIR & 0x0E){                            /*                */
            /***********************************************
            * 描述：接收中断
            */ 
        case 0x04:       //接收中断 
            //while ((USARTx->LSR & 0x01) == 0x01){               /*  判断数据是否接收完毕        */ 
                rx_data = USARTx->RBR;  
                pch->RxCtr++;
                MB_RxByte(pch, rx_data);                          /* Pass character to Modbus to process                  */
            //}
            break;
        case 0x0C:       //超时中断
            while ((USARTx->LSR & 0x01) == 0x01){               /*  判断数据是否接收完毕        */ 
                rx_data = USARTx->RBR;  
                pch->RxCtr++;
                MB_RxByte(pch, rx_data);                          /* Pass character to Modbus to process                  */
            }
            
            rx_data = USARTx->RBR;                      //清中断,初次有效，mcubug
            break;
            
            /***********************************************
            * 描述：发送中断
            */
        case 0x02:	                                    // 发送中断
            pch->TxCtr++;                           //?计数器加
            MB_TxByte(pch);                         //
            break;
        default:
            break;
        } 
    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                UART #0 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

/***********************************************
* 描述： UART0中断服务程序
*/
void UART0_IRQHandler (void)
{
  USARTx_RxTxISRHandler(MB_ChPortMap[0]);
}

/***********************************************
* 描述： UART1中断服务程序
*/
void UART1_IRQHandler (void)
{
  USARTx_RxTxISRHandler(MB_ChPortMap[1]);
}
/***********************************************
* 描述： UART2中断服务程序
*/
void UART2_IRQHandler (void)
{
  USARTx_RxTxISRHandler(MB_ChPortMap[2]);
}
/***********************************************
* 描述： UART3中断服务程序
*/
void UART3_IRQHandler (void)
{  
  USARTx_RxTxISRHandler(MB_ChPortMap[3]);
}
 

/*$PAGE*/
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
    
    UART_SendByte(pch->USARTx,c);
    return;
    
    switch (pch->PortNbr) {
    case 0:
        /* Transmit Data */
        //USART1->DR = (c & (u16)0x01FF);
        UART_SendByte(LPC_UART0,c);         
        break;
        
    case 1:
        /* Transmit Data */
        //USART2->DR = (c & (u16)0x01FF);
        UART_SendByte((LPC_UART_TypeDef*) LPC_UART1,c);         

        break;
        
    case 2:
        /* Transmit Data */
        //USART3->DR = (c & (u16)0x01FF);
        UART_SendByte(LPC_UART2,c);         

        break;
        
    case 3:
        /* Transmit Data */
        //UART4->DR = (c & (u16)0x01FF);
        UART_SendByte(LPC_UART3,c);         

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
    CPU_SR  cpu_sr = 0;

    CPU_CRITICAL_ENTER();
    
    UART_IntConfig(pch->USARTx,UART_INTCFG_THRE,DISABLE);
        
    CPU_CRITICAL_EXIT();
    return;
    
    switch (pch->PortNbr) {                       /* Just enable the receiver interrupt                */
    case 0:
//        USART_ITConfig(USART1, USART_IT_TC, DISABLE);
//        USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        UART_IntConfig(LPC_UART0,UART_INTCFG_THRE,DISABLE);
      
        break;
        
    case 1:
//        USART_ITConfig(USART2, USART_IT_TC, DISABLE);
//        USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
        UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1,UART_INTCFG_THRE,DISABLE);

        break;
        
    case 2:
//        USART_ITConfig(USART3, USART_IT_TC, DISABLE);
//        USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        UART_IntConfig(LPC_UART2,UART_INTCFG_THRE,DISABLE);

        break;
        
    case 3:
//        USART_ITConfig(UART4, USART_IT_TC, DISABLE);
//        USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
        UART_IntConfig(LPC_UART3,UART_INTCFG_THRE,DISABLE);

        break;
    }
    CPU_CRITICAL_EXIT();
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
    CPU_SR  cpu_sr = 0;

    CPU_CRITICAL_ENTER();
    
    UART_IntConfig(pch->USARTx,UART_INTCFG_THRE,ENABLE);
        
    CPU_CRITICAL_EXIT();
    return;
    
    switch (pch->PortNbr) {                       /* Just enable the receiver interrupt                */
    case 0:
//        USART_ITConfig(USART1, USART_IT_TC, ENABLE);
//        USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
        UART_IntConfig(LPC_UART0,UART_INTCFG_THRE,ENABLE);

        break;
        
    case 1:
//        USART_ITConfig(USART2, USART_IT_TC, ENABLE);
//        USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
        UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1,UART_INTCFG_THRE,ENABLE);
        break;
        
    case 2:
//        USART_ITConfig(USART3, USART_IT_TC, ENABLE);
//        USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
        UART_IntConfig(LPC_UART2,UART_INTCFG_THRE,ENABLE);
        break;
        
    case 3:
//        USART_ITConfig(UART4, USART_IT_TC, ENABLE);
//        USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
        UART_IntConfig(LPC_UART3,UART_INTCFG_THRE,ENABLE);

        break;
    }
    CPU_CRITICAL_EXIT();
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
    TIM_TIMERCFG_Type TIM_ConfigStruct;
    TIM_MATCHCFG_Type TIM_MatchConfigStruct;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);

	// Initialize timer 0, prescale count time of 1000000uS = 1S
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000000;
	TIM_ConfigStruct.PrescaleValue	= 1;
    
    TIM_Init(LPC_TIM3, TIM_TIMER_MODE,&TIM_ConfigStruct);

	// Configure 3 match channels
	// use channel 0, MR0
	TIM_MatchConfigStruct.MatchChannel = 0;
	// Enable interrupt when MR0 matches the value in TC register
	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	//Enable reset on MR0: TIMER will reset if MR0 matches it
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	//Stop on MR0 if MR0 matches it
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	//时间到后，端口不操作
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	// Set Match value
	TIM_MatchConfigStruct.MatchValue   = 1000;

    TIM_ConfigMatch(LPC_TIM3, &TIM_MatchConfigStruct);

	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_ResetCounter(LPC_TIM3);

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER3_IRQn, TIMER3_IRQn+10);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER3_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM3,ENABLE);							

    MB_RTU_TmrResetAll();                                     /* Reset all the RTU timers, we changed freq. */
}
#endif

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
    //TIM_Cmd(TIM3,DISABLE);              //禁止计数器 
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);
  TIM_DeInit(LPC_TIM3);

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

void TIMER3_IRQHandler(void)
{
    MB_RTU_TmrISR_Handler();
}

void  MB_RTU_TmrISR_Handler (void)
{
//    if(TIM_GetITStatus(TIM3, TIM_IT_Update)== SET) {//检测是否发生溢出更新事件
//      TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);/* Clear timer #1 interrupt                           */
//      MB_RTU_TmrCtr++;                              /* Indicate that we had activities on this interrupt. */
//      MB_RTU_TmrUpdate();                           /* Check for RTU timers that have expired             */
//    }
 
//   TIM_Cmd(LPC_TIM3,DISABLE);
	TIM_ClearIntPending(LPC_TIM3, TIM_MR0_INT);
	TIM_ResetCounter(LPC_TIM3);
    
    MB_RTU_TmrCtr++;                              /* Indicate that we had activities on this interrupt. */
    MB_RTU_TmrUpdate();                           /* Check for RTU timers that have expired             */
}

#endif
                      
void    UARTPutString(MODBUS_CH  *pch, const char *printfbuf)              
{
    int nbr_bytes   = strlen(printfbuf);
    
    if ( (nbr_bytes > 0) && (nbr_bytes < MB_DATA_NBR_REGS * 2 ) ) {  
        NMB_Tx((MODBUS_CH   *)pch,
               (CPU_INT08U  *)printfbuf,
               (CPU_INT16U   )nbr_bytes);
    }
}

//////////////////////////////////////////////////////////////

void WriteEN_485_3(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(EN_485_3,1);
	}
	else
	{
		GPIO_SetOrClearValue(EN_485_3,0);		
	}	
}