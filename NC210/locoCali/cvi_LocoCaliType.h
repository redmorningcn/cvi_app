/**************************************************************************/
//author:redmorningcn 20180621
//LKJ�����ź�У׼�ṹ�嶨��
/**************************************************************************/
#ifndef		CVI_LOCOCALI_TYPE_H_
#define		CVI_LOCOCALI_TYPE_H_ 	1

#include <userint.h>
#include <includes.h>

#ifdef __cplusplus
    extern "C" {
#endif

		
//У׼�ṹ��		
typedef struct _strLocoCali_
{

	u16		lowstandard;
	u16		lowmeasure;
	u16		higstandard;
	u16		higmeasure;
	u16		send;
	u16		rec16;
	u32		ansyflg;				//ͬ����ʶ
	
	u8		califlg :	1;			//��ʼУ׼��ʶ
	u8		lowflg:		1;			//��λ����ʶ
	u8		higflg:		1;			//��λ����ʶ
	u8		tmpflg:		5;			//Ԥ��
	
	u8		tmp8[3];				//Ԥ��
	
	u16		line;				
	u16		zero;
}strLocoCali;



extern	void	InitLocoCaliCtrlId(void)   ;


#ifdef __cplusplus
    }
#endif

#endif
