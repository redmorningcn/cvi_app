/**************************************************************************/
//author:redmorningcn 20180629
//LKJ�ٶ��ź�У׼�ṹ�嶨��
/**************************************************************************/
#ifndef		CVI_SPEEDCALI_TYPE_H_
#define		CVI_SPEEDCALI_TYPE_H_ 		1

#include <userint.h>
#include <includes.h>
//���Զ���
#include <cvi_LocoCaliType.h>   
#include <cvi_LKJTestType.h>   


#ifdef __cplusplus
    extern "C" {
#endif
		
#define		SPEED_GROUP_NUM  			(9)			/* �ٶ��ź�У׼����			*/
#define		SPEED_TYPE_NUM  			(3)			/* ÿ���ź�У׼����			*/	

#define		SPEED_CALI_BASE_ADDR		(2800)		/* �ٶ��ź�У׼�洢����ַ	*/
#define		SPEED_PARA_BASE_ADDR		(ADDR_SPEED_DETECT)		/* �ٶ��źŲ����洢����ַ	*/

		

/**************************************************************
* Description  : ��������
* Author       : 2018/6/29  by redmorningcn
*/
extern	void	SpeedInitCaliCtrlId(void)	;
extern	void	SpeedCaliCommcode(void)		;
extern	void	SpeedCaliDisplay(void)		;
extern	void	SpeedGetCaliCtrlVal(void)	;   
extern	void	SpeedCtrlDimmedSendControl(u8	dimmed);  
extern	void	SpeedCtrlDimmedControl(u8 id);
extern	void	SpeedMeasureCtrlSetVal(void);  
extern	void	SpeedGetRecvCaliInfo(void);

#ifdef __cplusplus
    }
#endif

#endif
