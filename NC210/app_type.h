/*******************************************************************************
* Description  : 定义通用结构体
* Author       : 2018/5/10 星期四, by redmorningcn
*******************************************************************************/
#ifndef  APP_TYPE_H_
#define  APP_TYPE_H_

#include  <includes.h>
#include  <RecDataTypeDef.h>


#define     SOFT_VERSION                (101)          /* 软件版本         */
#define     MODBUS_PASSWORD             (6237)          /* modbus通讯密码   */

/**************************************************************
* Description  : 记录事件定义
* Author       : 2018/6/4 星期一, by redmorningcn
*/
#define     EVT_START                   (0x031)         /* 开机事件         */

#pragma pack( 1 )
typedef struct {     
 	u16     Type;       //机车类型	2	参见机车类型代码表
 	u16     Nbr;        //机车号		2	
} stcLocoId;

/*******************************************************************************
* Description  : 控制结构体头部（程序识别）
* Author       : 2018/5/16 星期三, by redmorningcn
*/
#pragma pack( 1 )      
typedef struct { 
    u16                 Password;                       // 	2  	用于MODEBUS通讯确认密钥，默认为6237，防止非法改数据
    u32                 systime;                        //  4   系统时间
    u16   		        Rsv[5];				            //	2  	软件版本
} StrRecHeadInfo;

//__packed
//typedef struct {     
// 	u16   	            Type;				        //机车类型	2	参见机车类型代码表
// 	u16   	            Nbr;				        //机车号		2	
//} stcLocoId;

 #pragma pack( 1 )
typedef struct {
    u32                 Head;
    u32                 Tail;
} StrRecord;

//记录号管理:当前记录号，卡已读记录号，无线发送模块记录号
//16 bytes
 #pragma pack( 1 )
typedef struct _StrRecNumMgr {
    u32   		        Current;			        //当前记录号	0~0xffffffff(计算地址)
    u32   		        Record;				        //文件号
    u32   		        GrsRead;			        //无线已读取记录号
    u32   		        PointNum;                   //读取指定记录号
}StrRecNumMgr;

//产品信息:型号 + 编号
//12 bytes
 #pragma pack( 1 )
typedef struct _StrProductInfo {
	u32   		        Type;			            //产品类别
	u32   		        Id;				            //产品编号	16110002
	stcLocoId		    LocoId;		                //机车信息	104(DF4B) - 1000
    u16                 HwVer;                      //硬件版本
    u16                 SwVer;                      //软件版本
    u16                 LoadingTime;                //装车时间
    u16                 LoadingStaff;               //装车人员
    u16                 RepairTime;                 //维修时间
    u16                 RepairStaff;                //维修人员
    u8                  Rsv[12];                    //预留12个
}StrProductInfo;


//运行参数，装置运行相关，数据存储周期，显示参数，恢复出厂设置
//8 bytes
 #pragma pack( 1 )
typedef struct _stcRunPara_					
{
	u16   		        StoreTime;                  // 1    数据记录存储周期
	//
    u8   		        MtrErr[2];                  // 1    传感器错误代码
	
    u8   		        SysErr;                     // 1    系统错误代码
	u8   		        StoreType ;                 // 1    存储类型
	u8                  AvgCnt;                     // 1    测量平均次数
	u8					rec0;						// 1    预留
	
    /**************************************************************
    * Description  : 参数保存控制
    * Author       : 2018/5/22 星期二, by redmorningcn
    */
    union ___u_Framflg {
        struct {
            u16             WrHead      : 1;        // 写sCtrl头
            u16             WrNumMgr    : 1;        // 写记录管理
            u16             WrProduct   : 1;        // 写产品信息
            u16             WrRunPara   : 1;        // 写运行参数
            
            u16             RdHead      : 1;        // 读sCtrl头
            u16             RdNumMgr    : 1;        // 读记录管理
            u16             RdProduct   : 1;        // 读产品信息
            u16             RdRunPara   : 1;        // 读运行参数
            
            u16             WrSpecial   : 1;        // 写指定特定位置
            u16             RdSpecial   : 1;        // 读指定特定位置    
            
            u16             rev         : 6;        // 指定地址   
        } ;
        u16                 Flags;
    } FramFlg;
    
    union ___u_err_mask_flag {
        struct  {
            u16   		        ALFlag          : 1;        //低油位报警禁止
            u16   		        AHFlag          : 1;        //高油位报警禁止
            u16   		        Mtr1Flag        : 1;        //测量模块1禁止
            u16   		        Mtr2Flag        : 1;        //测量模块2禁止
            
            u16   		        EngMtrFlag      : 1;        //柴速测量禁止    
            u16   	            SpdMtrFlag      : 1;        //速度测量禁止
            u16   		        ExtCommFlag     : 1;        //扩展通讯禁止
            u16   		        ExtDispFlag     : 1;        //扩展显示禁止
            
            u16   		        PwrCommFlag     : 1;        //电量模块模块禁止
            u16   	            TaxCommFlag     : 1;        //TAX箱测量禁止    
            u16   	            IcCommFlag      : 1;        //IC卡模块禁止
            u16   	            DtuCommFlag     : 1;        //无线模块禁止
            
            u16   	            Rsv             : 4;        //保留
        } Flag;
        u16                 Flags;
    }Mask;                                          		// 故障屏蔽	
	
    union ___u_init_flag {
        struct  {
            u32                 ConnIcCardFlag  : 1;        // IC卡模块连接成功标志 成功后清零 
            u32                 SetLocoFlag     : 1;        // 机车号设置成功标志 成功后清零
            u32                 SetOilModFlag   : 1;        // 油箱模型设置成功标志 成功后清零
            u32                 SetOilNbrFlag   : 1;        // 模型编号设置成功标志 成功后清零
            
            u32                 SetDensityFlag  : 1;        // 设置密度成功标志 成功后清零
            u32                 SetOffIncFlag   : 1;        // 设置高度加成功标志 成功后清零
            u32                 SetOffDecFlag   : 1;        // 设置高度减成功标志 成功后清零
            u32                 TestDumpFlag    : 1;        // 转储测试成功标志 成功后清零
            
            u32                 ConnMtr1Flag    : 1;        // 测量模块1连接成功标志 成功后清零
            u32                 ConnMtr2Flag    : 1;        // 测量模块2连接成功标志 成功后清零 
            u32                 ConnDtuFlag     : 1;        // 无线模块连接成功标志 成功后清零
            u32                 ConnTaxFlag     : 1;        // TAX通讯成功标志 成功后清零
            
            u32                 TestEngFlag     : 1;        // 柴速测试成功标志 成功后清零
            u32                 TestSpdFlag     : 1;        // 速度测试成功标志 成功后清零
            u32                 ConnPwrFlag     : 1;        // 电量模块连接成功标志 成功后清零 
            u32                 ConnGpsFlag     : 1;        // GPS模块连接成功标志 成功后清零
            
            u32                 SetTimeFlag     : 1;        // 设置时间成功标志 成功后清零 
            u32                 TestIapFlag     : 1;        // IAP升级成功标志 成功后清零
            u32                 RsvFalg         :12;        // 备用
            u32                 OkFlag          : 1;        // 全部初始化成功标志，未初化0零，初始化化后为1
            u32                 InstallFlag     : 1;        // 装车完成标志，未初化0零，初始化化后为1
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
            u8   	            Rsv             : 1;        //保留
        } Flag;
        u8                      Flags;                      // 设备配置B0:电量模块;B1:扩展通讯模块；B2:显示模块1；B3显示模块2；B4:GPS模块；B5~B7预留
    } DevCfg; 
	
	u8	rec1;												// 预留1
	
    union ___u_system_sts {
        struct  {
            u16                 DispLevel       : 4;        // 4        显示亮度 1~15 
            u16                 Rsv1            : 4;        // 4 
            u16   		        StartFlg        : 1;        // 1    	首次运行
            u16   		        RecClear        : 1;        // 1		数据记录清零，清StrRecNumMgr内容
            u16   		        SysReset        : 1;        // 1    	系统参数重置，清StrRecNumMgr + StrOilPara 	中的内容。
            u16   		        SetBitFlg       : 1;        // 1        设置有效位指示
            u16   	            Rsv2            : 4;        //保留
        } ;
        u16                  Flags;                     // 
    } SysSts; 
    
    strDeviceErr            Err;                    // 错误代码
    
    strDeviceErr            ErrMask;
    
    u8                  Rsv2[8];                    // 预留8个字节
}stcRunPara;

#pragma pack( 1 )
typedef union _Unnctrl_ {
   struct{
        /***************************************************
        * 描述： 系统参数：起始地址 = 000   通讯密码，软件版本，记录号，产品信息
        */ 
        StrRecHeadInfo      sHeadInfo;                      // 16
        
        /***************************************************
        * 描述：记录号管理地址：起始地址 = 016
        */
        StrRecNumMgr        sRecNumMgr;			            // 16
        
        /***************************************************
        * 描述：产品信息：起始地址 = 032
        */
        StrProductInfo	    sProductInfo;			        // 32
        
        /***************************************************
        * 描述：系统运行参数：起始地址 = 064
        */
        stcRunPara	        sRunPara;				        // 32
        
        /*******************************************************************************
        * Description  : 数据记录
        * Author       : 2018/5/16 星期三, by redmorningcn
        */
        stcFlshRec          Rec;
        
        /*******************************************************************************
        * Description  : 串口控制字
        * Author       : 2018/5/16 星期三, by redmorningcn
        */
        //StrCOMCtrl          ComCtrl[4];                         //串控制字
        
        /*******************************************************************************
        * Description  : 操作系统参数
        * Author       : 2018/5/18 星期五, by redmorningcn
        */
        //StrCtrlOS           Os;      
        
        /**************************************************************
        * Description  : GPS通讯
        * Author       : 2018/6/4 星期一, by redmorningcn
        */
        //StrGpsInfo          Gps;

    };
   
    u16   buf[512];
        
}Unnctrl;


//变量声明
extern      Unnctrl     Ctrl;


#endif                                                          /* End of  include.                       */

