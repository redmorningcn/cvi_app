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
*                                     uC/MODBUS SLAVE COMMAND PROCESSOR
*
* Filename      : mbm_core.c
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

#define  MBM_MODULE
#include <global.h>
#include <includes.h>

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)

void  MB_OS_RxWait (MODBUS_CH   *pch,
                    CPU_INT16U  *perr);

void  MB_OS_TxWait (MODBUS_CH   *pch,
                    CPU_INT16U  *perr);

void  MB_OS_TxOver (MODBUS_CH   *pch );  


#endif

//#include <diagcounter.h>
/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/
#define  MBM_FCXX_ADDR          (pch->RxFrameData[0])
#define  MBM_FCXX_CODE          (pch->RxFrameData[1])
#define  MBM_TX_FCXX_ADDR       (pch->TxFrameData[0])
#define  MBM_TX_FCXX_CODE       (pch->TxFrameData[1])
#define  MBM_RX_FCXX_ADDR       (pch->RxFrameData[0])
#define  MBM_RX_FCXX_CODE       (pch->RxFrameData[1])

/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC01_COIL_RD
*/
#define  MBM_RX_FC01_DATA_COIL      (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_FC01_DATA_COIL_H     (pch->RxFrameData[4])
#define  MBM_RX_FC01_DATA_COIL_L     (pch->RxFrameData[5])
#define  MBM_TX_FC01_DATA_COIL      (((CPU_INT16U)pch->TxFrameData[4] << 8) + (CPU_INT16U)pch->TxFrameData[5])
#define  MBM_TX_FC01_DATA_COIL_H     (pch->TxFrameData[4])
#define  MBM_TX_FC01_DATA_COIL_L     (pch->TxFrameData[5])
#define  MBM_RX_FC01_DATA(i)         (pch->RxFrameData[3 + i])
#define  MBM_RX_FC01_NBYTE           (pch->RxFrameData[2])

/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC02_DI_RD
*/
/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC03_HOLDING_REG_RD
*/
#define  MBM_TX_FC03_REG      (((CPU_INT16U)pch->TxFrameData[2] << 8) + (CPU_INT16U)pch->TxFrameData[3])
#define  MBM_TX_FC03_REG_H      (pch->TxFrameData[2])
#define  MBM_TX_FC03_REG_L      (pch->RxFrameData[3])
#define  MBM_TX_FC03_NREG     (((CPU_INT16U)pch->TxFrameData[4] << 8) + (CPU_INT16U)pch->TxFrameData[5])
#define  MBM_TX_FC03_NREG_H     (pch->TxFrameData[4])
#define  MBM_TX_FC03_NREG_L     (pch->TxFrameData[5])
#define  MBM_TX_FC03_CRC      (((CPU_INT16U)pch->TxFrameData[6] << 8) + (CPU_INT16U)pch->TxFrameData[7])
#define  MBM_TX_FC03_CRC_H      (pch->TxFrameData[6])
#define  MBM_TX_FC03_CRC_L      (pch->TxFrameData[7])


#define  MBM_RX_FC03_NBYTE      (pch->RxFrameData[2])
#define  MBM_RX_FC03_DATA(i)  (((CPU_INT16U)pch->RxFrameData[3 + i * 2] << 8) + (CPU_INT16U)pch->RxFrameData[4 + i * 2])
#define  MBM_RX_FC03_DATA_H(i)  (pch->RxFrameData[3 + i * 2])
#define  MBM_RX_FC03_DATA_L(i)  (pch->RxFrameData[4 + i * 2])

#define  MBM_RX_FC03_IDX_NBYTE  2
#define  MBM_RX_FC03_IDX_DATA   3
#define  MBM_RX_FC03_IDX_DATA_H 3
#define  MBM_RX_FC03_IDX_DATA_L 4

/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC04_IN_REG_RD
*/
/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC05_COIL_WR
*/
#define  MBM_RX_FC05_COIL         (((CPU_INT16U)pch->RxFrameData[2] << 8) + (CPU_INT16U)pch->RxFrameData[3])
#define  MBM_RX_FC05_COIL_H         (pch->RxFrameData[2])
#define  MBM_RX_FC05_COIL_L         (pch->RxFrameData[3])
#define  MBM_RX_FC05_COIL_DATA    (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_FC05_COIL_DATA_H    (pch->RxFrameData[4])
#define  MBM_RX_FC05_COIL_DATA_L    (pch->RxFrameData[5])
#define  MBM_RX_FC05_COIL_CRC     (((CPU_INT16U)pch->RxFrameData[6] << 8) + (CPU_INT16U)pch->RxFrameData[7])
#define  MBM_RX_FC05_COIL_CRC_H     (pch->RxFrameData[6])
#define  MBM_RX_FC05_COIL_CRC_L     (pch->RxFrameData[7])
/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC06_HOLDING_REG_WR
*/
#define  MBM_TX_FC06_REG      (((CPU_INT16U)pch->TxFrameData[2] << 8) + (CPU_INT16U)pch->TxFrameData[3])
#define  MBM_TX_FC06_REG_H      (pch->TxFrameData[2])
#define  MBM_TX_FC06_REG_L      (pch->RxFrameData[3])
#define  MBM_TX_FC06_DATA     (((CPU_INT16U)pch->TxFrameData[4] << 8) + (CPU_INT16U)pch->TxFrameData[5])
#define  MBM_TX_FC06_DATA_H     (pch->TxFrameData[4])
#define  MBM_TX_FC06_DATA_L     (pch->TxFrameData[5])
#define  MBM_TX_FC06_CRC      (((CPU_INT16U)pch->TxFrameData[6] << 8) + (CPU_INT16U)pch->TxFrameData[7])
#define  MBM_TX_FC06_CRC_H      (pch->TxFrameData[6])
#define  MBM_TX_FC06_CRC_L      (pch->TxFrameData[7])

#define  MBM_RX_FC06_REG      (((CPU_INT16U)pch->RxFrameData[2] << 8) + (CPU_INT16U)pch->RxFrameData[3])
#define  MBM_RX_FC06_REG_H      (pch->RxFrameData[2])
#define  MBM_RX_FC06_REG_L      (pch->RxFrameData[3])
#define  MBM_RX_FC06_DATA     (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_FC06_DATA_H     (pch->RxFrameData[4])
#define  MBM_RX_FC06_DATA_L     (pch->RxFrameData[5])
#define  MBM_RX_FC06_CRC      (((CPU_INT16U)pch->RxFrameData[6] << 8) + (CPU_INT16U)pch->RxFrameData[7])
#define  MBM_RX_FC06_CRC_H      (pch->RxFrameData[6])
#define  MBM_RX_FC06_CRC_L      (pch->RxFrameData[7])

/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC08_LOOPBACK
*/
/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC15_COIL_WR_MULTIPLE
*/
#define  MBM_RX_FC15_COIL      (((CPU_INT16U)pch->RxFrameData[2] << 8) + (CPU_INT16U)pch->RxFrameData[3])
#define  MBM_RX_FC15_COIL_H      (pch->RxFrameData[2])
#define  MBM_RX_FC15_COIL_L      (pch->RxFrameData[3])
#define  MBM_RX_FC15_COIL_DATA (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_FC15_COIL_DATA_H (pch->RxFrameData[4])
#define  MBM_RX_FC15_COIL_DATA_L (pch->RxFrameData[5])
#define  MBM_RX_FC15_COIL_BYTES  (pch->RxFrameData[6])

/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC16_HOLDING_REG_WR_MULTIPLE
*/
#define  MBM_TX_FC16_REG      (((CPU_INT16U)pch->TxFrameData[2] << 8) + (CPU_INT16U)pch->TxFrameData[3])
#define  MBM_TX_FC16_REG_H      (pch->TxFrameData[2])
#define  MBM_TX_FC16_REG_L      (pch->RxFrameData[3])
#define  MBM_TX_FC16_NREG     (((CPU_INT16U)pch->TxFrameData[4] << 8) + (CPU_INT16U)pch->TxFrameData[5])
#define  MBM_TX_FC16_NREG_H     (pch->TxFrameData[4])
#define  MBM_TX_FC16_NREG_L     (pch->TxFrameData[5])
#define  MBM_TX_FC16_NBYTE      (pch->TxFrameData[6])
#define  MBM_TX_FC16_DATA_IDX   7

#define  MBM_TX_FC16_DATA(i)  (((CPU_INT16U)pch->TxFrameData[7 + i * 2] << 8) + (CPU_INT16U)pch->TxFrameData[8 + i * 2])
#define  MBM_TX_FC16_DATA_H(i)  (pch->TxFrameData[7 + i * 2])
#define  MBM_TX_FC16_DATA_L(i)  (pch->TxFrameData[8 + i * 2])

#define  MBM_RX_FC16_REG      (((CPU_INT16U)pch->RxFrameData[2] << 8) + (CPU_INT16U)pch->RxFrameData[3])
#define  MBM_RX_FC16_REG_H      (pch->RxFrameData[2])
#define  MBM_RX_FC16_REG_L      (pch->RxFrameData[3])
#define  MBM_RX_FC16_NREG     (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_FC16_NREG_H     (pch->RxFrameData[4])
#define  MBM_RX_FC16_NREG_L     (pch->RxFrameData[5])
#define  MBM_RX_FC16_CRC      (((CPU_INT16U)pch->RxFrameData[6] << 8) + (CPU_INT16U)pch->RxFrameData[7])
#define  MBM_RX_FC16_CRC_H      (pch->RxFrameData[6])
#define  MBM_RX_FC16_CRC_L      (pch->RxFrameData[7])

/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC20_FILE_RD
*/
/***********************************************
* 描述：接收帧数据格式，代码：MODBUS_FC21_FILE_WR
*/


#define  MBM_TX_FRAME_DATA      (pch->TxFrameData[2])

#define  MBM_RX_DATA_START     (((CPU_INT16U)pch->RxFrameData[2] << 8) + (CPU_INT16U)pch->RxFrameData[3])
#define  MBM_RX_DATA_START_H    (pch->RxFrameData[2])
#define  MBM_RX_DATA_START_L    (pch->RxFrameData[3])

#define  MBM_RX_DATA_POINTS    (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_DATA_POINTS_H   (pch->RxFrameData[4])
#define  MBM_RX_DATA_POINTS_L   (pch->RxFrameData[5])

#define  MBM_RX_DATA_COIL      (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_DATA_COIL_H     (pch->RxFrameData[4])
#define  MBM_RX_DATA_COIL_L     (pch->RxFrameData[5])

#define  MBM_RX_DATA_REG       (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_DATA_REG_H      (pch->RxFrameData[4])
#define  MBM_RX_DATA_REG_L      (pch->RxFrameData[5])

#define  MBM_RX_DIAG_CODE      (((CPU_INT16U)pch->RxFrameData[2] << 8) + (CPU_INT16U)pch->RxFrameData[3])
#define  MBM_RX_DIAG_CODE_H     (pch->RxFrameData[2])
#define  MBM_RX_DIAG_CODE_L     (pch->RxFrameData[3])
#define  MBM_RX_DIAG_DATA      (((CPU_INT16U)pch->RxFrameData[4] << 8) + (CPU_INT16U)pch->RxFrameData[5])
#define  MBM_RX_DIAG_DATA_H     (pch->RxFrameData[4])
#define  MBM_RX_DIAG_DATA_L     (pch->RxFrameData[5])

#define  MBM_RX_FRAME          (&pch->RxFrame)
#define  MBM_RX_FRAME_ADDR      (pch->RxFrameData[0])
#define  MBM_RX_FRAME_FC        (pch->RxFrameData[1])
#define  MBM_RX_FRAME_DATA      (pch->RxFrameData[2])
#define  MBM_RX_FRAME_NBYTES    (pch->RxFrameNDataBytes)


#define  MBM_TX_DATA_START_H    (pch->TxFrameData[2])
#define  MBM_TX_DATA_START_L    (pch->TxFrameData[3])

#define  MBM_TX_DATA_POINTS_H   (pch->TxFrameData[4])
#define  MBM_TX_DATA_POINTS_L   (pch->TxFrameData[5])

#define  MBM_TX_DATA_COIL_H     (pch->TxFrameData[4])
#define  MBM_TX_DATA_COIL_L     (pch->TxFrameData[5])

#define  MBM_TX_DATA_REG_H      (pch->TxFrameData[4])
#define  MBM_TX_DATA_REG_L      (pch->TxFrameData[5])

#define  MBM_TX_DIAG_CODE_H     (pch->TxFrameData[2])
#define  MBM_TX_DIAG_CODE_L     (pch->TxFrameData[3])
#define  MBM_TX_DIAG_DATA_H     (pch->TxFrameData[4])
#define  MBM_TX_DIAG_DATA_L     (pch->TxFrameData[5])


#define  MBM_TX_FRAME          (&pch->TxFrame)
#define  MBM_TX_FRAME_ADDR      (pch->TxFrameData[0])
#define  MBM_TX_FRAME_FC        (pch->TxFrameData[1])
#define  MBM_TX_FRAME_DATA      (pch->TxFrameData[2])
#define  MBM_TX_FRAME_NBYTES    (pch->TxFrameNDataBytes)

//SE Added defines from this point forward
#define  MBM_FC100_DATA_BYTES    (5u)

/*$PAGE*/
/*
*********************************************************************************************************
*                                    LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_FCxx_Handler()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : MBM_ASCII_Task()
*               MBM_RTU_Task
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
CPU_BOOLEAN  MBM_FCxx_Handler (MODBUS_CH  *pch)
{
    CPU_BOOLEAN   send_reply;

    if (MBM_RX_FRAME_ADDR == pch->NodeAddr) {

        switch (MBM_RX_FRAME_FC) {
#if (MODBUS_CFG_FC01_EN == DEF_ENABLED)
            case MODBUS_FC01_COIL_RD:
                 break;
#endif

#if (MODBUS_CFG_FC02_EN == DEF_ENABLED)
            case MODBUS_FC02_DI_RD:
                 break;
#endif

#if (MODBUS_CFG_FC03_EN == DEF_ENABLED)
            case MODBUS_FC03_HOLDING_REG_RD:
                 break;
#endif

#if (MODBUS_CFG_FC04_EN == DEF_ENABLED)
            case MODBUS_FC04_IN_REG_RD:
                 break;
#endif

#if (MODBUS_CFG_FC05_EN == DEF_ENABLED)
            case MODBUS_FC05_COIL_WR:
                 if (pch->WrEn == DEF_TRUE) {
                 } else {
                     send_reply  = DEF_FALSE;
                 }
                 break;
#endif

#if (MODBUS_CFG_FC06_EN == DEF_ENABLED)
            case MODBUS_FC06_HOLDING_REG_WR:
                 if (pch->WrEn == DEF_TRUE) {
                 } else {
                     send_reply  = DEF_FALSE;
                 }
                 break;
#endif

#if (MODBUS_CFG_FC08_EN == DEF_ENABLED)
            case MODBUS_FC08_LOOPBACK:
                 break;
#endif

#if (MODBUS_CFG_FC15_EN == DEF_ENABLED)
            case MODBUS_FC15_COIL_WR_MULTIPLE:
                 if (pch->WrEn == DEF_TRUE) {
                 } else {
                     send_reply  = DEF_FALSE;
                 }
                 break;
#endif

#if (MODBUS_CFG_FC16_EN == DEF_ENABLED)
            case MODBUS_FC16_HOLDING_REG_WR_MULTIPLE:
                 if (pch->WrEn == DEF_TRUE) {
                 } else {
                     send_reply  = DEF_FALSE;
                 }
                 break;
#endif

#if (MODBUS_CFG_FC20_EN == DEF_ENABLED)
            case MODBUS_FC20_FILE_RD:
                 break;
#endif

#if (MODBUS_CFG_FC21_EN == DEF_ENABLED)
            case MODBUS_FC21_FILE_WR:
                 if (pch->WrEn == DEF_TRUE) {
                 } else {
                     send_reply = DEF_FALSE;
                 }
                 break;
#endif

#if MODBUS_FC43_EN > 0 // Read Device ID
           case MODBUS_FC43_READ_DEV_ID:
            break;
#endif

#if MODBUS_FC100_EN > 0 // Scattered Read
            case MODBUS_FC100_SCATTERED_READ:
            break;
#endif

            default:
                 pch->Err   = MODBUS_ERR_ILLEGAL_FC;
                 send_reply = DEF_TRUE;
                 break;
        }
    } else {
    }

    return (send_reply);
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_TxCmd()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : MBM_FCxx_xx()
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
void MBM_TxCmd(MODBUS_CH *pch)
{
#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
    MB_RTU_Tx (pch);
#endif
#if (MODBUS_CFG_ASCII_EN == DEF_ENABLED)
    MB_ASCII_Tx(pch);
#endif
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_RxReply()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : MBM_FCxx_xx
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
CPU_BOOLEAN MBM_RxReply(MODBUS_CH *pch )
{
#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
    return MB_RTU_Rx(pch);

#endif
#if (MODBUS_CFG_ASCII_EN == DEF_ENABLED)
    return MB_ASCII_Rx(pch);
#endif
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBS_FC01_CoilRd()
*
* Description : Responds to a request to read the status of any number of coils.
*
* Argument(s) : pch       Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : DEF_TRUE      If a response needs to be sent
*               DEF_FALSE     If not
*
* Caller(s)   : MBS_FCxx_Handler()
*
* Note(s)     : none
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
#if (MODBUS_CFG_FC01_EN == DEF_ENABLED)
CPU_INT16U  MBM_FC01_CoilRd          (MODBUS_CH   *pch,
                                      CPU_INT08U   slave_node,
                                      CPU_INT16U   slave_addr,
                                      CPU_INT08U  *p_coil_tbl,
                                      CPU_INT16U   nbr_coils)
{
    CPU_INT16U      nbr_bytes;
    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;

    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return 0;
    ptx_data    = &(pch->TxFrameData[0]);
    pch->TxFrameNDataBytes  = 4;

   *ptx_data++ = slave_node;
   *ptx_data++ = MODBUS_FC01_COIL_RD;
   *ptx_data++ = HI_INT16U(slave_addr);
   *ptx_data++ = LO_INT16U(slave_addr);
   *ptx_data++ = HI_INT16U(nbr_coils);
   *ptx_data++ = LO_INT16U(nbr_coils);
    nbr_bytes  = 0;

    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = 5;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == 0X81) {
              pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码03H： 读寄存器值错误响应
              //第1字节	    ADR      	：	从机地址码（=001～254）
              //第2字节　   83H			：	读寄存器值出错
              //第3字节　   信息码		：	见信息码表
              //第4、5字节	CRC			：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              nbr_bytes  = 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确,且输入指针与数据指针不相等
              */
              nbr_bytes        = MBM_RX_FC01_NBYTE;
              INT8U    idx    = 0;
              while(idx < nbr_bytes) {
                p_coil_tbl[idx]    = MBM_RX_FC01_DATA(idx);
                idx++;
              }
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return nbr_bytes;
}
#endif
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBS_FC05_CoilWr()
*
* Description : Responds to a request to force a coil to a specified state.
*
* Argument(s) : pch       Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : DEF_TRUE      If a response needs to be sent
*               DEF_FALSE     If not
*
* Caller(s)   : MBS_FCxx_Handler()
*
* Note(s)     : none
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
#if (MODBUS_CFG_FC05_EN  == DEF_ENABLED)
CPU_INT16U  MBM_FC05_CoilWr          (MODBUS_CH   *pch,
                                      CPU_INT08U   slave_node,
                                      CPU_INT16U   slave_addr,
                                      CPU_BOOLEAN  coil_val)
{

    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;
    CPU_INT32U      timeout;


    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return 0;
    ptx_data  = &(pch->TxFrameData[0]);

   *ptx_data++ = slave_node;
   *ptx_data++ = MODBUS_FC05_COIL_WR;
   *ptx_data++ = HI_INT16U(slave_addr);
   *ptx_data++ = LO_INT16U(slave_addr);
   *ptx_data++ = (coil_val) ? 0xff : 0x00;
   *ptx_data++ = 0x00;
    pch->TxFrameNDataBytes  = 4;

    coil_val   = 0;

    timeout = pch->RxTimeout;
    MB_MasterTimeoutSet(pch, 300u);                    // 设置MODBUS主机超时为500ms
    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = 5;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

    MB_MasterTimeoutSet(pch, timeout);                // 设置MODBUS主机超时为500ms

    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == 0X85) {
              pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码06H： 写单个寄存器值
              //第1字节	    ADR      		：从机地址码（=001～254）
              //第2字节　   86H			    ：写寄存器值出错功能码
              //第3字节　   错误数息码		：	见信息码表
              //第4、5字节	CRC			    ：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              coil_val   = (MBM_RX_FC05_COIL_DATA_H) ? 1 : 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确
              */
              coil_val = (MBM_RX_FC05_COIL_DATA_H) ? 1 : 0;
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return coil_val;
}
#endif
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_FC03_HoldingRegRd()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)   && \
    (MODBUS_CFG_RTU_EN == DEF_ENABLED)      && \
    (MODBUS_CFG_FC03_EN == DEF_ENABLED)
CPU_INT16U  MBM_FC03_HoldingRegRd    (MODBUS_CH   *pch,
                                      CPU_INT08U   slave_node,
                                      CPU_INT16U   slave_addr,
                                      CPU_INT16U  *p_reg_tbl,
                                      CPU_INT16U   nbr_regs)
{
    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;
	 

	
    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return 0;
    ptx_data    = &(pch->TxFrameData[0]);
    pch->TxFrameNDataBytes  = 4;

   *ptx_data++ = slave_node;
   *ptx_data++ = MODBUS_FC03_HOLDING_REG_RD;
   *ptx_data++ = HI_INT16U(slave_addr);
   *ptx_data++ = LO_INT16U(slave_addr);
   *ptx_data++ = HI_INT16U(nbr_regs);
   *ptx_data++ = LO_INT16U(nbr_regs);
    nbr_regs    = 0;

    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = 5;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

	
    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == 0X83) {
              pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码03H： 读寄存器值错误响应
              //第1字节	    ADR      	：	从机地址码（=001～254）
              //第2字节　   83H			：	读寄存器值出错
              //第3字节　   信息码		：	见信息码表
              //第4、5字节	CRC			：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              nbr_regs  = 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确,且输入指针与数据指针不相等
              */
              nbr_regs        = MBM_RX_FC03_NBYTE / 2;
              INT8U    idx    = 0;
              while(idx < nbr_regs) {
                p_reg_tbl[idx]    = MBM_RX_FC03_DATA(idx);
                idx++;
              }
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return nbr_regs;
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_FC06_HoldingRegWr()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)   && \
    (MODBUS_CFG_RTU_EN == DEF_ENABLED)      && \
    (MODBUS_CFG_FC06_EN == DEF_ENABLED)
CPU_INT16U  MBM_FC06_HoldingRegWr (  MODBUS_CH   *pch,
                                     CPU_INT08U   slave_node,
                                     CPU_INT16U   slave_addr,
                                     CPU_INT16U   reg_val)
{
    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;
    CPU_INT32U      timeout;


    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return (reg_val    = ~reg_val);                 // 取反，防止数据为0时相等
    ptx_data  = &(pch->TxFrameData[0]);

   *ptx_data++ = slave_node;
   *ptx_data++ = MODBUS_FC06_HOLDING_REG_WR;
   *ptx_data++ = HI_INT16U(slave_addr);
   *ptx_data++ = LO_INT16U(slave_addr);
   *ptx_data++ = HI_INT16U(reg_val);
   *ptx_data++ = LO_INT16U(reg_val);
    reg_val    = ~reg_val;                              // 取反，防止数据为0时相等
    pch->TxFrameNDataBytes  = 4;

    timeout = pch->RxTimeout;
    MB_MasterTimeoutSet(pch, 300u);                     // 设置MODBUS主机超时为500ms

    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = 5;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

    MB_MasterTimeoutSet(pch, timeout);                // 设置MODBUS主机超时为500ms

    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == 0X86) {
              pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码06H： 写单个寄存器值
              //第1字节	    ADR      		：从机地址码（=001～254）
              //第2字节　   86H			    ：写寄存器值出错功能码
              //第3字节　   错误数息码		：	见信息码表
              //第4、5字节	CRC			    ：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              reg_val   = 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确
              */
              reg_val = MBM_RX_FC06_DATA;
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return reg_val;
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                       MBS_FC15_CoilWrMultiple()
*
* Description : Processes the MODBUS "Force Multiple COILS" command and writes the COIL states.
*
* Argument(s) : pch       Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : DEF_TRUE      If a response needs to be sent
*               DEF_FALSE     If not
*
* Caller(s)   : MBS_FCxx_Handler()
*
* Note(s)     : none
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)
#if (MODBUS_CFG_FC15_EN  == DEF_ENABLED)
CPU_INT16U  MBM_FC15_CoilWr          (MODBUS_CH   *pch,
                                      CPU_INT08U   slave_node,
                                      CPU_INT16U   slave_addr,
                                      CPU_INT08U  *p_coil_tbl,
                                      CPU_INT16U   nbr_coils)
{
    CPU_INT16U      nbr_bytes       = (nbr_coils - 1) / 8 + 1;    /* Get the byte count for the data.                         */
    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;
    CPU_INT16U      ctr             = nbr_bytes;

    if ( nbr_coils == 0 )
      return 0;
    /***************************************************
    * 描述：
    */
    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return 0;

    ptx_data    = &(pch->TxFrameData[MBM_TX_FC16_DATA_IDX]);
    /***************************************************
    * 描述： 如果输入数组与数据数组是同一数组，且是从第0个数据开始
    */
    if ( (CPU_INT08U *)p_coil_tbl == &(pch->TxFrameData[0]) ) {
      ptx_data  += nbr_bytes + MBM_TX_FC16_DATA_IDX-1;                          // 指向数据的最后一个元素
      p_coil_tbl += nbr_bytes-1;                              // 指向最后一个寄存器

      while(ctr--) {
       *ptx_data--      = *p_coil_tbl--;
      }
    /***************************************************
    * 描述： 如果输入指针不是当前通道的数据帧的第7个元素，则拷贝元素到数据帧数组
    */
    } else if ( (CPU_INT08U *)p_coil_tbl == &(pch->TxFrameData[MBM_TX_FC16_DATA_IDX]) ) {
      while(ctr--) {
       *ptx_data++      = *p_coil_tbl++;
      }
    } else {
      while(ctr--) {
       *ptx_data++      = *p_coil_tbl++;
      }
    }

    ptx_data    = &(pch->TxFrameData[0]);
    /***************************************************
    * 描述：
    */
   *ptx_data++ = slave_node;
   *ptx_data++ = MODBUS_FC15_COIL_WR_MULTIPLE;
   *ptx_data++ = HI_INT16U(slave_addr);
   *ptx_data++ = LO_INT16U(slave_addr);
   *ptx_data++ = HI_INT16U(nbr_coils);
   *ptx_data++ = LO_INT16U(nbr_coils);
    pch->TxFrameNDataBytes  = 5 + nbr_bytes;
   *ptx_data++ = pch->TxFrameNDataBytes - 5;

    nbr_bytes    = 0;

    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = 5;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

    /***************************************************
    * 描述：
    */
    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == 0X8F) {
                pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码10H： 连续写多个寄存器值
              //第1字节	    ADR      		：	从机地址码（=001～254）
              //第2字节　   90H			    ：　写寄存器值出错
              //第3字节　   错误信息码		：	见信息码表
              //第4、5字节	CRC			    ：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              nbr_bytes = 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确
              */
              nbr_bytes = MBM_RX_FC15_COIL_BYTES;
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return nbr_bytes;
}
#endif
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_FC16_HoldingRegWrN()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)   && \
    (MODBUS_CFG_RTU_EN == DEF_ENABLED)      && \
    (MODBUS_CFG_FC16_EN == DEF_ENABLED)
CPU_INT16U  MBM_FC16_HoldingRegWrN   (MODBUS_CH   *pch,
                                      CPU_INT08U   slave_node,
                                      CPU_INT16U   slave_addr,
                                      CPU_INT16U  *p_reg_tbl,
                                      CPU_INT16U   nbr_regs)
{
    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;
    CPU_INT16U      temp;
    CPU_INT16U      ctr         = nbr_regs;

    if ( nbr_regs == 0 )
      return 0;
    /***************************************************
    * 描述：
    */
    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return 0;

    ptx_data    = &(pch->TxFrameData[MBM_TX_FC16_DATA_IDX]);
    /***************************************************
    * 描述： 如果输入数组与数据数组是同一数组，且是从第0个数据开始
    */
    if ( (CPU_INT08U *)p_reg_tbl == &(pch->TxFrameData[0]) ) {
      ptx_data  += nbr_regs * 2 + MBM_TX_FC16_DATA_IDX-1;   // 指向数据的最后一个元素
      p_reg_tbl += nbr_regs-1;                              // 指向最后一个寄存器

      while(ctr--) {
       *ptx_data--      = LO_INT16U(*p_reg_tbl);
       *ptx_data--      = HI_INT16U(*p_reg_tbl);
        p_reg_tbl--;
      }
    /***************************************************
    * 描述： 如果输入指针不是当前通道的数据帧的第7个元素，则拷贝元素到数据帧数组
    */
    } else if ( (CPU_INT08U *)p_reg_tbl == &(pch->TxFrameData[MBM_TX_FC16_DATA_IDX]) ) {
      while(ctr--) {
        temp            = *p_reg_tbl;
       *ptx_data++      = HI_INT16U(temp);
       *ptx_data++      = LO_INT16U(temp);
        p_reg_tbl++;
      }
    } else {
      while(ctr--) {
        temp            = *p_reg_tbl;
       *ptx_data++      = HI_INT16U(temp);
       *ptx_data++      = LO_INT16U(temp);
        p_reg_tbl++;
      }
    }

    ptx_data    = &(pch->TxFrameData[0]);
    /***************************************************
    * 描述：
    */
   *ptx_data++ = slave_node;
   *ptx_data++ = MODBUS_FC16_HOLDING_REG_WR_MULTIPLE;
   *ptx_data++ = HI_INT16U(slave_addr);
   *ptx_data++ = LO_INT16U(slave_addr);
   *ptx_data++ = HI_INT16U(nbr_regs);
   *ptx_data++ = LO_INT16U(nbr_regs);
    pch->TxFrameNDataBytes  = 5 + nbr_regs * 2;
   *ptx_data++ = pch->TxFrameNDataBytes - 5;

    nbr_regs    = 0;

    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = 5;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

    /***************************************************
    * 描述：
    */
    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == 0X90) {
                pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码10H： 连续写多个寄存器值
              //第1字节	    ADR      		：	从机地址码（=001～254）
              //第2字节　   90H			    ：　写寄存器值出错
              //第3字节　   错误信息码		：	见信息码表
              //第4、5字节	CRC			    ：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              nbr_regs = 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确
              */
              nbr_regs = MBM_RX_FC16_NREG;
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return nbr_regs;
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                           MBM_FCU_HoldingRegWrN()
*
* Description : This is the main processing function for MODBUS commands.  The message integrity is
*               verified, and if valid, the function requested is processed.  Unimplemented functions
*               will generate an Illegal Function Exception Response code (01).
*
* Argument(s) : pch      Is a pointer to the Modbus channel's data structure.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_MASTER_EN == DEF_ENABLED)   && \
    (MODBUS_CFG_RTU_EN == DEF_ENABLED)      && \
    (MODBUS_CFG_FCU_EN == DEF_ENABLED)
CPU_INT16U  MBM_FCU_HoldingRegWrN(  MODBUS_CH   *pch,
                                    CPU_INT08U   slave_node,
                                    CPU_INT08U   fc,
                                    CPU_INT16U   block,
                                    CPU_INT16U   blocks,
                                    CPU_INT16U  *p_reg_tbl,
                                    CPU_INT16U   nbr_regs)
{
    CPU_INT08U     *ptx_data;
    CPU_INT16U      err;
    CPU_BOOLEAN     ok;
    CPU_INT16U      calc_crc;


    MB_OS_TxWait(pch,&err);
    if ( err != MODBUS_ERR_NONE )
        return 0;
    ptx_data    = &(pch->TxFrameData[0]);

   *ptx_data++ = slave_node;                        // 地址
   *ptx_data++ = fc;                                // 写文件

   *ptx_data++ = HI_INT16U(block);                  // 当前块
   *ptx_data++ = LO_INT16U(block);

   *ptx_data++ = HI_INT16U(blocks);                 // 总块数
   *ptx_data++ = LO_INT16U(blocks);
   *ptx_data++ = HI_INT16U(nbr_regs);
   *ptx_data++ = LO_INT16U(nbr_regs);

    pch->TxFrameNDataBytes  = 7 + nbr_regs * 2;

    while(nbr_regs--) {
     *ptx_data++   = HI_INT16U(*p_reg_tbl);
     *ptx_data++   = LO_INT16U(*p_reg_tbl);
      p_reg_tbl++;
    }
    nbr_regs    = 0;

    /***********************************************
    * 描述： 发送
    */
    INT08S  retrys  = pch->Retrys;
    do {
      MBM_TxCmd(pch);
      MB_OS_RxWait(pch,&err);
    } while ( ( err == MODBUS_ERR_TIMED_OUT ) && --retrys  );

    if ( err == MODBUS_ERR_NONE ) {
        ok = MBM_RxReply(pch);
        if ( DEF_TRUE == ok ) {
            calc_crc = MB_RTU_RxCalcCRC(pch);          /* Do our own calculation of the CRC.                              */
            if (calc_crc != pch->RxFrameCRC) {         /* If the calculated CRC does not match the CRC received,          */
              /***********************************************
              * 描述： 校验错误
              */
              pch->StatCRCErrCtr++;                    /* then the frame was not received properly.                       */
            } else if (MBM_RX_FCXX_CODE == (fc | 0x80)) {
                pch->StatExceptCtr++;
              /***********************************************
              * 描述： 其他错误
              //功能码10H： 连续写多个寄存器值
              //第1字节	    ADR      		：	从机地址码（=001～254）
              //第2字节　   90H			    ：　写寄存器值出错
              //第3字节　   错误信息码		：	见信息码表
              //第4、5字节	CRC			    ：	从字节1到3的CRC16校验和
              //数息码	    表示意义
              //01H	        非法的功能号
              //02H	        非法的数据地址
              //03H	        非法的数据值
              //04H	        CRC16校验错
              //05H	        接收正确
              //06H	        接收错误
              //07	        参数错误
              */
              nbr_regs = 0;
            } else {
              pch->StatMsgCtr++;
#if MBM_STAT_CTR_AUTO_CLR_EN        == DEF_ENABLED
              pch->StatNoRespCtr    = 0;
              pch->StatCRCErrCtr    = 0;
              pch->StatExceptCtr    = 0;
#endif
              /***********************************************
              * 描述： 接收正确
              */
              nbr_regs = MBM_RX_FC16_NREG;
            }
        }
    } else {
        pch->StatNoRespCtr++;
    }

    pch->RxBufByteCtr = 0;
    pch->RxBufPtr     = &pch->RxBuf[0];

    MB_OS_TxOver(pch);

    return nbr_regs;
}
#endif
