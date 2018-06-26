/*******************************************************************************
* Description  : ����ͨ�ýṹ��
* Author       : 2018/5/10 ������, by redmorningcn
*******************************************************************************/
#ifndef  APP_TYPE_H_
#define  APP_TYPE_H_

#include  <includes.h>
#include  <RecDataTypeDef.h>


#define     SOFT_VERSION                (101)          /* ����汾         */
#define     MODBUS_PASSWORD             (6237)          /* modbusͨѶ����   */

/**************************************************************
* Description  : ��¼�¼�����
* Author       : 2018/6/4 ����һ, by redmorningcn
*/
#define     EVT_START                   (0x031)         /* �����¼�         */

#pragma pack( 1 )
typedef struct {     
 	u16     Type;       //��������	2	�μ��������ʹ����
 	u16     Nbr;        //������		2	
} stcLocoId;

/*******************************************************************************
* Description  : ���ƽṹ��ͷ��������ʶ��
* Author       : 2018/5/16 ������, by redmorningcn
*/
#pragma pack( 1 )      
typedef struct { 
    u16                 Password;                       // 	2  	����MODEBUSͨѶȷ����Կ��Ĭ��Ϊ6237����ֹ�Ƿ�������
    u32                 systime;                        //  4   ϵͳʱ��
    u16   		        Rsv[5];				            //	2  	����汾
} StrRecHeadInfo;

//__packed
//typedef struct {     
// 	u16   	            Type;				        //��������	2	�μ��������ʹ����
// 	u16   	            Nbr;				        //������		2	
//} stcLocoId;

 #pragma pack( 1 )
typedef struct {
    u32                 Head;
    u32                 Tail;
} StrRecord;

//��¼�Ź���:��ǰ��¼�ţ����Ѷ���¼�ţ����߷���ģ���¼��
//16 bytes
 #pragma pack( 1 )
typedef struct _StrRecNumMgr {
    u32   		        Current;			        //��ǰ��¼��	0~0xffffffff(�����ַ)
    u32   		        Record;				        //�ļ���
    u32   		        GrsRead;			        //�����Ѷ�ȡ��¼��
    u32   		        PointNum;                   //��ȡָ����¼��
}StrRecNumMgr;

//��Ʒ��Ϣ:�ͺ� + ���
//12 bytes
 #pragma pack( 1 )
typedef struct _StrProductInfo {
	u32   		        Type;			            //��Ʒ���
	u32   		        Id;				            //��Ʒ���	16110002
	stcLocoId		    LocoId;		                //������Ϣ	104(DF4B) - 1000
    u16                 HwVer;                      //Ӳ���汾
    u16                 SwVer;                      //����汾
    u16                 LoadingTime;                //װ��ʱ��
    u16                 LoadingStaff;               //װ����Ա
    u16                 RepairTime;                 //ά��ʱ��
    u16                 RepairStaff;                //ά����Ա
    u8                  Rsv[12];                    //Ԥ��12��
}StrProductInfo;


//���в�����װ��������أ����ݴ洢���ڣ���ʾ�������ָ���������
//8 bytes
 #pragma pack( 1 )
typedef struct _stcRunPara_					
{
	u16   		        StoreTime;                  // 1    ���ݼ�¼�洢����
	//
    u8   		        MtrErr[2];                  // 1    �������������
	
    u8   		        SysErr;                     // 1    ϵͳ�������
	u8   		        StoreType ;                 // 1    �洢����
	u8                  AvgCnt;                     // 1    ����ƽ������
	u8					rec0;						// 1    Ԥ��
	
    /**************************************************************
    * Description  : �����������
    * Author       : 2018/5/22 ���ڶ�, by redmorningcn
    */
    union ___u_Framflg {
        struct {
            u16             WrHead      : 1;        // дsCtrlͷ
            u16             WrNumMgr    : 1;        // д��¼����
            u16             WrProduct   : 1;        // д��Ʒ��Ϣ
            u16             WrRunPara   : 1;        // д���в���
            
            u16             RdHead      : 1;        // ��sCtrlͷ
            u16             RdNumMgr    : 1;        // ����¼����
            u16             RdProduct   : 1;        // ����Ʒ��Ϣ
            u16             RdRunPara   : 1;        // �����в���
            
            u16             WrSpecial   : 1;        // дָ���ض�λ��
            u16             RdSpecial   : 1;        // ��ָ���ض�λ��    
            
            u16             rev         : 6;        // ָ����ַ   
        } ;
        u16                 Flags;
    } FramFlg;
    
    union ___u_err_mask_flag {
        struct  {
            u16   		        ALFlag          : 1;        //����λ������ֹ
            u16   		        AHFlag          : 1;        //����λ������ֹ
            u16   		        Mtr1Flag        : 1;        //����ģ��1��ֹ
            u16   		        Mtr2Flag        : 1;        //����ģ��2��ֹ
            
            u16   		        EngMtrFlag      : 1;        //���ٲ�����ֹ    
            u16   	            SpdMtrFlag      : 1;        //�ٶȲ�����ֹ
            u16   		        ExtCommFlag     : 1;        //��չͨѶ��ֹ
            u16   		        ExtDispFlag     : 1;        //��չ��ʾ��ֹ
            
            u16   		        PwrCommFlag     : 1;        //����ģ��ģ���ֹ
            u16   	            TaxCommFlag     : 1;        //TAX�������ֹ    
            u16   	            IcCommFlag      : 1;        //IC��ģ���ֹ
            u16   	            DtuCommFlag     : 1;        //����ģ���ֹ
            
            u16   	            Rsv             : 4;        //����
        } Flag;
        u16                 Flags;
    }Mask;                                          		// ��������	
	
    union ___u_init_flag {
        struct  {
            u32                 ConnIcCardFlag  : 1;        // IC��ģ�����ӳɹ���־ �ɹ������� 
            u32                 SetLocoFlag     : 1;        // ���������óɹ���־ �ɹ�������
            u32                 SetOilModFlag   : 1;        // ����ģ�����óɹ���־ �ɹ�������
            u32                 SetOilNbrFlag   : 1;        // ģ�ͱ�����óɹ���־ �ɹ�������
            
            u32                 SetDensityFlag  : 1;        // �����ܶȳɹ���־ �ɹ�������
            u32                 SetOffIncFlag   : 1;        // ���ø߶ȼӳɹ���־ �ɹ�������
            u32                 SetOffDecFlag   : 1;        // ���ø߶ȼ��ɹ���־ �ɹ�������
            u32                 TestDumpFlag    : 1;        // ת�����Գɹ���־ �ɹ�������
            
            u32                 ConnMtr1Flag    : 1;        // ����ģ��1���ӳɹ���־ �ɹ�������
            u32                 ConnMtr2Flag    : 1;        // ����ģ��2���ӳɹ���־ �ɹ������� 
            u32                 ConnDtuFlag     : 1;        // ����ģ�����ӳɹ���־ �ɹ�������
            u32                 ConnTaxFlag     : 1;        // TAXͨѶ�ɹ���־ �ɹ�������
            
            u32                 TestEngFlag     : 1;        // ���ٲ��Գɹ���־ �ɹ�������
            u32                 TestSpdFlag     : 1;        // �ٶȲ��Գɹ���־ �ɹ�������
            u32                 ConnPwrFlag     : 1;        // ����ģ�����ӳɹ���־ �ɹ������� 
            u32                 ConnGpsFlag     : 1;        // GPSģ�����ӳɹ���־ �ɹ�������
            
            u32                 SetTimeFlag     : 1;        // ����ʱ��ɹ���־ �ɹ������� 
            u32                 TestIapFlag     : 1;        // IAP�����ɹ���־ �ɹ�������
            u32                 RsvFalg         :12;        // ����
            u32                 OkFlag          : 1;        // ȫ����ʼ���ɹ���־��δ����0�㣬��ʼ������Ϊ1
            u32                 InstallFlag     : 1;        // װ����ɱ�־��δ����0�㣬��ʼ������Ϊ1
        };
        u32                 Flags;
    } InitFlag;
    
    union ___u_dev_cfg {
        struct  {
            u8   		        PwrEnFlag       : 1;        //
            u8   		        OtrEnFlag       : 1;        //
            u8   		        ExtComEnFlag    : 1;        //
            u8   		        Dsp1EnFlag      : 1;        //
            
            u8   		        Dsp2EnFlag      : 1;        //
            u8   		        TaxEnFlag       : 1;        //    
            u8   		        GpsEnFlag       : 1;        //
            u8   	            Rsv             : 1;        //����
        } Flag;
        u8                      Flags;                      // �豸����B0:����ģ��;B1:��չͨѶģ�飻B2:��ʾģ��1��B3��ʾģ��2��B4:GPSģ�飻B5~B7Ԥ��
    } DevCfg; 
	
	u8	rec1;												// Ԥ��1
	
    union ___u_system_sts {
        struct  {
            u16                 DispLevel       : 4;        // 4        ��ʾ���� 1~15 
            u16                 Rsv1            : 4;        // 4 
            u16   		        StartFlg        : 1;        // 1    	�״�����
            u16   		        RecClear        : 1;        // 1		���ݼ�¼���㣬��StrRecNumMgr����
            u16   		        SysReset        : 1;        // 1    	ϵͳ�������ã���StrRecNumMgr + StrOilPara 	�е����ݡ�
            u16   		        SetBitFlg       : 1;        // 1        ������Чλָʾ
            u16   	            Rsv2            : 4;        //����
        } ;
        u16                  Flags;                     // 
    } SysSts; 
    
    strDeviceErr            Err;                    // �������
    
    strDeviceErr            ErrMask;
    
    u8                  Rsv2[8];                    // Ԥ��8���ֽ�
}stcRunPara;

#pragma pack( 1 )
typedef union _Unnctrl_ {
   struct{
        /***************************************************
        * ������ ϵͳ��������ʼ��ַ = 000   ͨѶ���룬����汾����¼�ţ���Ʒ��Ϣ
        */ 
        StrRecHeadInfo      sHeadInfo;                      // 16
        
        /***************************************************
        * ��������¼�Ź����ַ����ʼ��ַ = 016
        */
        StrRecNumMgr        sRecNumMgr;			            // 16
        
        /***************************************************
        * ��������Ʒ��Ϣ����ʼ��ַ = 032
        */
        StrProductInfo	    sProductInfo;			        // 32
        
        /***************************************************
        * ������ϵͳ���в�������ʼ��ַ = 064
        */
        stcRunPara	        sRunPara;				        // 32
        
        /*******************************************************************************
        * Description  : ���ݼ�¼
        * Author       : 2018/5/16 ������, by redmorningcn
        */
        stcFlshRec          Rec;
        
        /*******************************************************************************
        * Description  : ���ڿ�����
        * Author       : 2018/5/16 ������, by redmorningcn
        */
        //StrCOMCtrl          ComCtrl[4];                         //��������
        
        /*******************************************************************************
        * Description  : ����ϵͳ����
        * Author       : 2018/5/18 ������, by redmorningcn
        */
        //StrCtrlOS           Os;      
        
        /**************************************************************
        * Description  : GPSͨѶ
        * Author       : 2018/6/4 ����һ, by redmorningcn
        */
        //StrGpsInfo          Gps;

    };
   
    u16   buf[512];
        
}Unnctrl;


//��������
extern      Unnctrl     Ctrl;


#endif                                                          /* End of  include.                       */

