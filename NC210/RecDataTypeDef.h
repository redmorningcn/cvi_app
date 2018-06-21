/*******************************************************************************
* Description  :  ����洢��¼�����ݽṹ
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/

#ifndef  _RecDataTypeDef_h_
#define  _RecDataTypeDef_h_

#include <includes.h>
#define	 __packed   /* */	

/**************************************************************
* Description  : tax��ͨѶ-ʱ���ʽ����
* Author       : 2018/6/4 ����һ, by redmorningcn
*/
typedef struct {
    u32      Sec                 : 6;        // D05~D00����
    u32      Min                 : 6;        // D11~D06����
    u32      Hour                : 5;        // D16~D12��ʱ
    u32      Day                 : 5;        // D21~D17����
    u32      Mon                 : 4;        // D25~D22����
    u32      Year                : 6;        // D31~D26����
} StrLkjTime;                                       // 04 LKJʱ��
    
/*******************************************************************************
* Description  : �ٶ�ͨ���洢���ݽṹ
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/
typedef struct _stcSpeed
{
    union{
        struct{
            u8  Freq1Lose   :1 ;   //�����壻
            u8  Freq1None   :1 ;   //���źţ�
            u8  rec         :4 ;   //Ԥ��
            u8  FreqLess    :1 ;   //Ƶ����
            u8  FreqMore    :1 ;   //Ƶ�ʶ� 
        }Err[2];
        u8 flgs[2];
    }sta;
    u16     phase;
    u16     vcc;
    u16     freq;
    struct _stcCH
    {
        u16     raise;
        u16     fail;
        u16     ratio;    
        u16     hig;
        u16     low;    
    }ch[2];
}sSpeed;

typedef union _strDevicErr
{
    struct{
        u16                  Speed1Comm     : 1;    //D0=1���ٶȼ���1ͨѶ����
        u16                  Speed2Comm     : 1;    //D1=1���ٶȼ���2ͨѶ����
        u16                  Speed3Comm     : 1;    //D2=1���ٶȼ���3ͨѶ����
        u16                  Speed1Lose     : 1;    //D3=1���ٶȼ���1��������ϣ������ͨ��sta��
        u16                  Speed2Lose     : 1;    //D4=1���ٶȼ���2��������ϣ������ͨ��sta��
        u16                  Speed3Lose     : 1;    //D5=1���ٶȼ���3��������ϣ������ͨ��sta��
        u16                  LocoComm       : 1;    //D6=1�������źż���ͨѶ����
        u16                  Disp1CommErr   : 1;    //D7=1��һ����ʾģ��ͨѶ����
        u16                  Disp2CommErr   : 1;    //D8=1��������ʾģ��ͨѶ����
        u16                  TaxCommErr     : 1;    //D9=1��TAXͨѶ����
        u16                  FlashErr       : 1;    //D10=1���洢������
        u16                  FramErr        : 1;    //D11=1���������
        u16                  TimeErr        : 1;    //D12=1��ʱ�����
        u16                  RsvErr         : 3;   //     ��Ԥ��
    };
    u32                 Flags;
}strDeviceErr;

/*******************************************************************************
* Description  : ����ռ��flash�洢�����ݽṹ��128�ֽڣ�
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/
__packed
typedef  struct _stcFlshRec                 //����ռ��¼���ݽṹ
{
    u8   				CmdTpye		        ;//��������       1
    u8   				EvtType             ;//�¼�����       1
    u16   				LocoType            ;//�����ͺ�       2
    u16   				LocoNbr             ;//�� �� ��       2
    u32   				RecordId            ;//��¼��ˮ��     4
    
    struct {                                //��¼ʱ��        4
        u32      Sec                 : 6    ;// D05~D00����
        u32      Min                 : 6    ;// D11~D06����
        u32      Hour                : 5    ;// D16~D12��ʱ
        u32      Day                 : 5    ;// D21~D17����
        u32      Mon                 : 4    ;// D25~D22����
        u32      Year                : 6    ;// D31~D26����
    };                                                  // 
    
    sSpeed      speed[3]                    ;//�ٶ�ͨ���ź�   3*24
    
    struct {  
        u16     vcc                         ;//110V��ѹ
        u16     qy                          ;//ǣ����ѹ
        u16     xq                          ;//��ǰ��ѹ
        u16     xh                          ;//����ѹ
        u16     lw                          ;//��λ��ѹ
    }Vol;                                    //������ѹ
    
    u32  				Longitude           ;//����           4
    u32     			Latitude	        ;//γ��           4
    
    u16   				GpsSpeed       :10  ;//GPS�ٶ�         2
    u16   				GpsPos         : 3  ;//�����ϱ�����   2  1������2���ϣ�3������4���ϣ�����δ֪
    u16                 OffHightFlag   : 1  ;//�߶ȵ�����־
    u16   				Rsv            : 2  ;//����           2
    u8                  Rssi                ;//�ź�ǿ��       1
    u8                  rsvbyte[3]          ;//Ԥ���ֽ�
    
    strDeviceErr        Err                 ;//�����ʶ         4            

    u16   				CrcCheck            ;//У��   2                 
} stcFlshRec;


#endif
