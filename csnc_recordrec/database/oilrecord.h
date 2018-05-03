/*******************************************************************************
 *   Filename:       setmodel.h
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    统计模块油箱模型设置

					 双击选中 otr 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 Otr 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 OTR 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   在 app_cfg.h 中指定本任务的 优先级  （ APP_TASK_COMM_PRIO     ）
 *                                            和 任务堆栈（ APP_TASK_COMM_STK_SIZE ）大小
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	OIL_RECORD_H
#define	OIL_RECORD_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "asynctmr.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <formatio.h> 
#include <comconfig.h>         
#include "pc_csnr.h"
#include "includes.h"

/*******************************************************************************
* MACROS
*/
//ODBC 数据源(32 位),DSN
#define		ODBC_DNS	"MySql32"


/*******************************************************************************************
/结构体																				 
*******************************************************************************************/

typedef  struct _stcFlshRec   	//定义油尺记录数据结构
{
	uint32	StoreCnt;         	//存储流水号    		4   追踪记录用

	uint8	RecTypCod;       	//记录类型          	1   数据类型（开机、上班卡、下班卡、数据记录）
	uint8	RelSpeed[3];      	//实速              	3   D9~D0：实速，D19~D10：预留

	uint32	Time;          	    //月/日/时/分/秒      	4   D5~D0:秒,D11~D6:分,D16~D12:时D21~D17：日，
	                               	//                      	D25~D22：月 ;D26~D31:年
	uint8	LocoTyp;          	//机车型号          	1   
	uint8	E_LocoTyp;        	//机车型号扩展字节  	1   机车型号扩充字节,定义与LKJ2000格式相同
	uint16 	LocoNum;       	    //机车号            	2	

	uint32 	TrainTyp;     	    //车次种类          	4   车次种类,车次编码新方案(铁运[2005]72号文件)
	                             	//                      	的车次种类标识符,定义与LKJ2000格式相同
	                             	
	uint8	TrainNum[3];     	//车次数字部分      	3   车次编码新方案(铁运[2005]72号文)的车次数据部分
	uint8 	Car_Truck;       	//本/补、客/货       	1   D0＝0/1 → 货/客   D1＝0/1 → 本/补   
	 
	uint8 	VoitureCnt;       	//辆数              	1	
	uint8 	KmMark[3];   		//公里标            	3   单位：米

	uint16 	Weight;       	    //总重              	2
	uint16 	PlanLen;       	    //计长              	2   单位：0.1   

	uint16 	MstDriverNum;  	    //司机号            	2	
	uint8 	E_MstDriverNum; 	//司机号扩展字节    	1   
	uint8 	E_SlvDriverNum;   	//副司机号扩展字节  	1   

	uint16 	SlvDriverNum;  	    //副司机号          	2   
	uint16	DriverUnitNum;  	//司机单位编号      	2   //用来唯一确定司机

	uint8 	RoadNum;          	//区段号(交路号)     	1	
	uint8  	RelRoadNum;     	//实际交路号         	1   定义格式与LKJ2000相同   
	uint8  	StationNum;     	//车站号            	1
	uint8  	E_StationNum;   	//车站号扩展字节    	1   车站号扩展字节

	uint8 	SignalTyp;        	//信号机类型        	1   B2-B0 :2-出站,3-进站,4-通过,5-预告,6-容许
	uint8 	LocoSign;        	//机车信号          	1   B4 = 0/1  单灯/多灯;   B3~B0 0-无灯,1-绿,2-黄, 
	                            	//                      	3-双黄,4-红黄,5-红,6-白,7-绿黄,8-黄
	uint8 	LocoWorkState;    	//机车工况          	1   b0-零位,B1-向后,B2-向前,B3-制动,B4-牵引
	uint8 	LocoState;      	//装置状态          	1   B0 = 1/0 - 降级/监控; B2 = 1/0 - 调车/非调车

//	uint8 	SignalNum[2];      	//信号机编号        	2   
//	uint8 	LocoPipePress[2]; 	//列车管压          	2   B9-B0:管压(单位:1kPa)

	uint16	Myspeed1;			//自测速度1				2
	uint16	Myspeed2;			//自测速度2				2	
	  
	uint32 	MstDip;           	//主机油量          	4   主油尺油量(主从机级联时为主机油量,否则为本机车油量)

//	uint32 	SlvDip;           	//从机油量          	4   主油尺油量(主从机级联时为从机油量,否则此油量值为空)
	uint32	MyKileMeter;		//总里程				4
		
	int32 	MyMstLocoPower;     //主机机车功率       	4   主机外接设备测量

//	int32 	SlvLocoPower;     	//从机机车功率       	4   从机外接设备测量
	uint32	MyPower;			//累计电量				4	
	//090901
 	//uint16	MstDip1Prs;        	//压强            		2   主机油尺1压强值
	//uint16	MstDip2Prs;        	//压强            		2   主机油尺2压强值
	int16		Myhig1;				//液位高度1				2	
	int16		Myhig2;				//液位高度2				2							

	uint16	SlvDip1Prs;       	//压强            		2   从机油尺1压强值
	uint16 	SlvDip2Prs;       	//压强            		2   从机油尺2压强值
	
	uint8  	MyYear;           	//年      				1   装置时间的年
	uint8 	MyMonth;         	//月      				1   装置时间的月
	uint8 	MyData;          	//日      				1   装置时间的日
	uint8 	MyHour;           	//时      				1   装置时间的时
	
	uint8 	MyMinute;     		//分      				1   装置时间的分
	uint8 	MySecond;       	//秒       				1   装置时间的秒
	uint16	MstDensity;			//密度							2	主机燃油密度
	
//	uint16	SlvDensity;			//密度						2	从机燃油密度
//	uint16	GpsHeight;			//高度						2	地理高度
	int16	MyAddspeed;			//自测加速度					2
	uint16	MyDip;				//自测油量							2
		
	int32	GpsLongitude;		//经度					4	地理经度
	int32	GpsLatitude;		//纬度					4	地理纬度
		
	int16	MstEngRotSpd;		//主机柴油机转速		2	主机柴油机转速
//	int16	SlvEngRotSpd;		//从机柴油机转速		2	从机柴油机转速
	int16	MyEngRotSpd;		//从机柴油机转速		2	从机柴油机转速

	//补充内容 
	//与自加时钟芯片配套的数据有
	uint16 	JcRealType;			//机车型号				2   外部设置的机车型号
	uint16 	JcRealNo;			//机车编号				2   外部设置的机车编号
	
//	uint16 	MstPotPress;		//主机缸压				2	预留接监控	
//	uint16 	SlvPotPress;		//从机缸压				2	预留接监控	
	uint16	MyDip1Tmp;	  		//油尺1温度
	uint16	MyDip2Tmp;			//油尺2温度
		
//	uint16 	MstPot1;			//主机均缸1				2	预留接监控	
//	uint16 	MstPot2;			//主机均缸2				2	预留接监控
	uint16	MyDip1Den;
	uint16	MyDip2Den;	

	
	
//	uint16 	SlvPot1;			//从机均缸1				2	预留接监控		
//	uint16 	SlvPot2;			//从机均缸2				2	预留接监控
	uint16	MyDip1Err;
	uint16	MyDip2Err;
	
	uint16 	MaxSpeed;			//限速					2	预留接监控	
//	uint16 	MstOcurrent;		//主机原边电流   		2	预留接监控
	uint16	ErrNum;				//现有故障条数			2	
	
	
	uint8	ErrorCode;			//故障代码				1   0~255
//	uint8 	DipValChgState;  	//油量变化状态   		1   油量变化情况分：两油尺增加/减小、变化平稳、轻微波动、剧烈波动
	uint8	MyLocoWorkState;	//自测机车状态			1
	//090901
	uint8	MstDipTemp;			//温度					1	主机温度
	uint8	OilBoxModel;		//油箱模型				1	机车油箱代码
	
	uint8	SoftVes;        	//软件版本          	1   
	uint8	Reserve1;        	//预留          		1  	
//	uint16	Reserve0;        	//预留          		2   
	uint16 	CrcCheck;         	//存储的校验和    		2   Flash记录存储CRC校验
}stcFlshRec;



typedef  struct _stcFlshRecSql   	//定义油尺记录数据结构_数据库兼容
{
	uint32	StoreCnt;         	//存储流水号    		4   追踪记录用

	uint32	RecTypCod;       	//记录类型          	1   数据类型（开机、上班卡、下班卡、数据记录）
	uint32	RelSpeed;      		//实速              	3   D9~D0：实速，D19~D10：预留

	uint32	Time;          	    //月/日/时/分/秒      	4   D5~D0:秒,D11~D6:分,D16~D12:时D21~D17：日，
	                          	//                      	D25~D22：月 ;D26~D31:年
	uint32	LocoTyp;          	//机车型号          	1   
	uint32	E_LocoTyp;        	//机车型号扩展字节  	1   机车型号扩充字节,定义与LKJ2000格式相同
	uint32 	LocoNum;       	    //机车号            	2	

	uint8 	TrainTyp[4];     	//车次种类          	4   车次种类,车次编码新方案(铁运[2005]72号文件)
	                            //                      	的车次种类标识符,定义与LKJ2000格式相同
	uint32	TrainNum;     		//车次数字部分      	3   车次编码新方案(铁运[2005]72号文)的车次数据部分
	uint8 	Car_Truck[4];       //本/补、客/货       	1   D0＝0/1 → 货/客   D1＝0/1 → 本/补   
	 
	uint32 	VoitureCnt;       	//辆数              	1	
	uint32 	KmMark;   		//公里标            	3   单位：米

	uint32 	Weight;       	    //总重              	2
	uint32 	PlanLen;       	    //计长              	2   单位：0.1   

	uint32 	MstDriverNum;  	    //司机号            	2	
	uint32 	E_MstDriverNum; 	//司机号扩展字节    	1   
	uint32 	E_SlvDriverNum;   	//副司机号扩展字节  	1   

	uint32 	SlvDriverNum;  	    //副司机号          	2   
	uint32	DriverUnitNum;  	//司机单位编号      	2   //用来唯一确定司机

	uint32 	RoadNum;          	//区段号(交路号)     	1	
	uint32  RelRoadNum;     	//实际交路号         	1   定义格式与LKJ2000相同   
	uint32 	StationNum;     	//车站号            	1
	uint32 	E_StationNum;   	//车站号扩展字节    	1   车站号扩展字节

	uint8 	SignalTyp[4];       //信号机类型        	1   B2-B0 :2-出站,3-进站,4-通过,5-预告,6-容许
	uint8 	LocoSign[4];        //机车信号          	1   B4 = 0/1  单灯/多灯;   B3~B0 0-无灯,1-绿,2-黄, 
	                            	//                      	3-双黄,4-红黄,5-红,6-白,7-绿黄,8-黄
	uint32 	LocoWorkState;    	//机车工况          	1   b0-零位,B1-向后,B2-向前,B3-制动,B4-牵引
	uint32 	LocoState;      	//装置状态          	1   B0 = 1/0 - 降级/监控; B2 = 1/0 - 调车/非调车

//	uint8 	SignalNum[2];      	//信号机编号        	2   
//	uint8 	LocoPipePress[2]; 	//列车管压          	2   B9-B0:管压(单位:1kPa)

	uint32	Myspeed1;			//自测速度1				2
	uint32	Myspeed2;			//自测速度2				2	
	  
	uint32 	MstDip;           	//主机油量          	4   主油尺油量(主从机级联时为主机油量,否则为本机车油量)

//	uint32 	SlvDip;           	//从机油量          	4   主油尺油量(主从机级联时为从机油量,否则此油量值为空)
	uint32	MyKileMeter;		//总里程				4
		
	int32 	MyMstLocoPower;     //主机机车功率       	4   主机外接设备测量

//	int32 	SlvLocoPower;     	//从机机车功率       	4   从机外接设备测量
	uint32	MyPower;			//累计电量				4	
	//090901
 	//uint16	MstDip1Prs;        	//压强            		2   主机油尺1压强值
	//uint16	MstDip2Prs;        	//压强            		2   主机油尺2压强值
	int32		Myhig1;				//液位高度1				2	
	int32		Myhig2;				//液位高度2				2							

	uint32	SlvDip1Prs;       	//压强            		2   从机油尺1压强值
	uint32 	SlvDip2Prs;       	//压强            		2   从机油尺2压强值
	
	uint32  	MyYear;           	//年      				1   装置时间的年
	uint32 	MyMonth;         	//月      				1   装置时间的月
	uint32 	MyData;          	//日      				1   装置时间的日
	uint32 	MyHour;           	//时      				1   装置时间的时
	
	uint32 	MyMinute;     		//分      				1   装置时间的分
	uint32 	MySecond;       	//秒       				1   装置时间的秒
	uint32	MstDensity;			//密度							2	主机燃油密度
	
//	uint16	SlvDensity;			//密度						2	从机燃油密度
//	uint16	GpsHeight;			//高度						2	地理高度
	int32	MyAddspeed;			//自测加速度					2
	uint32	MyDip;				//自测油量							2
		
	int32	GpsLongitude;		//经度					4	地理经度
	int32	GpsLatitude;		//纬度					4	地理纬度
		
	int32	MstEngRotSpd;		//主机柴油机转速		2	主机柴油机转速
//	int16	SlvEngRotSpd;		//从机柴油机转速		2	从机柴油机转速
	int32	MyEngRotSpd;		//从机柴油机转速		2	从机柴油机转速

	//补充内容 
	//与自加时钟芯片配套的数据有
	uint32 	JcRealType;			//机车型号				2   外部设置的机车型号
	uint32 	JcRealNo;			//机车编号				2   外部设置的机车编号
	
//	uint16 	MstPotPress;		//主机缸压				2	预留接监控	
//	uint16 	SlvPotPress;		//从机缸压				2	预留接监控	
	uint32	MyDip1Tmp;	  		//油尺1温度
	uint32	MyDip2Tmp;			//油尺2温度
		
//	uint16 	MstPot1;			//主机均缸1				2	预留接监控	
//	uint16 	MstPot2;			//主机均缸2				2	预留接监控
	uint32	MyDip1Den;
	uint32	MyDip2Den;	

	
	
//	uint16 	SlvPot1;			//从机均缸1				2	预留接监控		
//	uint16 	SlvPot2;			//从机均缸2				2	预留接监控
	uint32	MyDip1Err;
	uint32	MyDip2Err;
	
	uint32 	MaxSpeed;			//限速					2	预留接监控	
//	uint16 	MstOcurrent;		//主机原边电流   		2	预留接监控
	uint32	ErrNum;				//现有故障条数			2	
	
	
	uint32	ErrorCode;			//故障代码				1   0~255
//	uint8 	DipValChgState;  	//油量变化状态   		1   油量变化情况分：两油尺增加/减小、变化平稳、轻微波动、剧烈波动
	uint32	MyLocoWorkState;	//自测机车状态			1
	//090901
	uint32	MstDipTemp;			//温度					1	主机温度
	uint32	OilBoxModel;		//油箱模型				1	机车油箱代码
	
	uint32	SoftVes;        	//软件版本          	1   
	uint32	Reserve1;        	//预留          		1  	
//	uint16	Reserve0;        	//预留          		2   
	uint32 	CrcCheck;         	//存储的校验和    		2   Flash记录存储CRC校验
}stcFlshRecSql;


typedef  struct _stcRecoilRecordCtrl   	//定义油尺记录数据结构_数据库兼容
{
	uint8	recnum;			//	
	uint8	storeflg;		
	uint8   ICflg;
	uint8	enableflg;		//
	uint32	currecnum;		//当前记录号
	uint32	ICreadnum;		//开始记录号
	uint8	ICstorefile[128];//IC卡文件保存名字
}stcRecOilRecordCtrl;

typedef struct _stcTinyRec{  
    uint8   Addr;
    uint8   ModelNum;
    uint16  Oil;
    uint32  CurRecNum;
    uint16  Speed1;
    uint16  Speed2;
    uint16  Speedcs;
    int16   Hig1;
    int16   Hig2;
    uint8   LocoWorkSta;
}stcTinyRec;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	int 				cvi_hdbc_mysql_handle;		//数据库连接句柄
extern	int 				globalvalue;
extern	int 				db_panelHandle;
extern	stcFlshRec			gsFlshRec;
extern	stcRecOilRecordCtrl	gsRecvOilRecordCtrl;

/*******************************************************************************
* 名    称： InsertRecToDB
* 功    能： 插入数据记录
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 由于数据库操作，现建立映射，在赋值改写数据，再数据入库。 
*******************************************************************************/
int  InsertoilRecToDB (char *tabelname,stcFlshRec *sFlshRec);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
