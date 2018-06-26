/**************************************************************************/
//author:redmorningcn 20180623
//LKJ�������
/**************************************************************************/
#ifndef		CVI_LKJTEST_TYPE_H_
#define		CVI_LKJTEST_TYPE_H_ 	1

#include 	<userint.h>
#include 	"includes.h"
#ifdef __cplusplus
    extern "C" {
#endif

		
		
/*******************************************************************************
* Description  : ͨ��������ָ��
* Author       : 2018/6/24 ������, by redmorningcn
*******************************************************************************/
typedef	struct _strSpeedDetect_
{
    /*******************************************************************************
    * Description  : ͨ������ָ��
    * Author       : 2018/6/24 ������, by redmorningcn
    *******************************************************************************/
    struct  {
        uint32              period;                         //���ڣ�  0.00-2000000.00us ��0.5Hz��
        uint32              freq;                           //Ƶ�ʣ�  0-100000hz              
        uint16              raise;                          //�����أ�0.00-50.00us
        uint16              fail;                           //�½��أ�0.00-50.00us
        uint16              ratio;                          //ռ�ձȣ�0.00-100.00%
        uint16              Vol;                            //�͵�ƽ��0.00-30.00V
        uint16              Voh;                            //�ߵ�ƽ��0.00-30.00V
        uint16				status;                         //ͨ��״̬
    }para[2];
    
    uint32  ch1_2phase;                                     //��λ�0.00-360.00��
    uint16  vcc_vol;                                        //�����ѹ
    uint16  stand_vol;                                      //�ο���ѹ
}strSpeedDetect;

/*******************************************************************************
* Description  : �����ź�ͨ��������ݽṹ����
* Author       : 2018/6/23  by redmorningcn
*******************************************************************************/
typedef	struct _strpara_ {          
    uint16              vcc;                           //Ԥ��
    uint16              qy;                             //ǣ��
    uint16              zd;                             //�ƶ�
    uint16              xq;                             //��ǰ
    uint16              xh;                             //���
    uint16              lw;                             //��λ
}strLocoDetect;





extern	void	RecDetectInfoReadCode(void) ;
extern	void	GetRecDetectInfo(void);
extern	void	SpeedDetectDisplay(void);
extern	void	InitSpeedCtrlID(void);
extern	void	InitLocoCtrlID(void);
extern	void	LocoDetectDisplay(void);
extern	void	RecordDisplay(void);


#ifdef __cplusplus
    }
#endif
#endif
