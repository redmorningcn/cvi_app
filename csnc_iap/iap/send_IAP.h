/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	SNED_IAP_H
#define	SNED_IAP_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include <IAP.h>

#include "cvi_config.h"  
#include "cvi_file.h"  
#include "cvi_comm.h"  

/********************************************************************************************/
/* Constants																					*/
/********************************************************************************************/
#define     IAP_FRAME_CODE      10 
#define		MY_ADDR				ADDR_PC

#define		COM_START_CODE		0x55
#define		PC_ADDR				0xaa
//#define		HOST_ADDR			0x82
#define		HOST_ADDR			ADDR_FIX
#define		SLAVE_ADDR			0xA1

/*******************************************************************************************
/�ṹ��																				 
*******************************************************************************************/
typedef  struct   _stcIAPPara_
{
    short  	hardver;        //Ӳ���汾
    short  	softver;        //����汾
    int  	softsize;       //�����С
    int  	addr;           //��ǰ��ַ
    int  	framenum;       //֡���
    short  	code;           //ָ���� 01����ʾ����ȷ�Ŀ���
    short  	crc16;
}stcIAPPara;					

//typedef  struct   _stcIAPPara_
//{
//    uint16          HwVer;          //Ӳ���汾
//    uint16          SwVer;          //����汾
//    uint32          Size;           //�����С
//    uint32          Addr;           //��ǰ��ַ
//    uint32          Idx;            //֡���
//    uint16          Cmd;            //ָ���� 01����ʾ����ȷ�Ŀ���
//    uint16          Chk;            //У��
//    uint32          Crc32;          //����У����
//    uint16          IdxNbr;         //֡��
//}stcIAPPara;

typedef	struct	_stcIapCtrl_
{
	int		filesize;		//???t�䨮D?
	int		sendsize;		//��?����?��???t�䨮D?
	short	sendnum;		//�̡�?��D��o?
	short	recvnum;		//?����?D��o?
	char	endflg;			//?����?������?
	char	echoflg;		//��|��e������?
	char	resendflg;		//??���������?
	char	startflg;
	char	sendeable;	
}stcIapCtrl;

typedef struct  _stcIAPStart_
{
    uint16  HardVer;        //Ӳ���汾
    uint16  SoftVer;        //����汾
    uint32  SoftSize;       //�����С
    uint32  Addr;           //��ǰ��ַ
    uint16  CurNum;         //��ǰ���
}stcIapStart;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	stcIapCtrl		gsIapCtrl;
extern	stcFileInfo		gsBinFileInfo;

/*******************************************************************************************
���ݷ��ͣ� SendFileData()
*******************************************************************************************/
void	SendIapTask(void);

/*******************************************************************************************
��ʼ��IAP��������
*******************************************************************************************/
void	IapRecTask(void);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
