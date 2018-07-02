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
		
#define		LOCO_GROUP_NUM  		(6)			/* ��ЧУ׼��			*/	
#define		LOCO_CALI_BASE_ADDR		(340)		/* ����У׼�洢����ַ	*/
		
//У׼�ṹ��		
typedef struct _strLineCali_
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
	u8		calisend:	1;			//У׼���ͱ�ʶ
	u8		caliErr:	1;			//У׼ֵ�쳣
	u8		tmpflg:		3;			//Ԥ��
	
	u8		tmp8[3];				//Ԥ��
	
	u16		line;				
	s16		zero;
	u16		info;
}strLineCali;


/**************************************************************
* Description  : У׼����
* Author       : 2018/5/22 ���ڶ�, by redmorningcn
*/

typedef struct {
    u32     line;       //�������Զ�  
    int16   Delta;      //����ƫ��
    int16   tmp;        //Ԥ��

}strLineCalibration;

/**************************************************************
* Description  : ����������
* Author       : 2018/5/22 ���ڶ�, by redmorningcn
*/
typedef struct{
    union   {
        struct{
            strLineCalibration  VccVol;         //��ƽ
            strLineCalibration  QY_Vol;         //
            strLineCalibration  ZD_Vol;         //
            strLineCalibration  XQ_Vol;         //
            strLineCalibration  XH_Vol;         //
            strLineCalibration  LW_Vol;         //
        };
        strLineCalibration      CaliBuf[10];
    };
}strLineCaliTable;


/**************************************************************
* Description  : ��������
* Author       : 2018/5/24 ���ڶ�, by redmorningcn
*/
extern	void	LocoInitCaliCtrlId(void);
extern	void	LocoCaliCommcode(void)	;
extern	void	LocoCaliDisplay(void)	;
extern	void	LocoGetCaliCtrlVal(void);   
extern	void	LocoCtrlDimmedSendControl(u8	dimmed);  
extern	void	LocoCtrlDimmedControl(u8 id);
extern	void	LocoMeasureCtrlSetVal(void);  
extern	void	LocoGetRecvCaliInfo(void);
extern	void	LocoStandCtrlSetVal(void);    

//ͨ��У׼����
extern	void	CalcCaliVal(strLineCali *cali);

#ifdef __cplusplus
    }
#endif

#endif
