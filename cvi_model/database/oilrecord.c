/*******************************************************************************
 *   Filename:       oilrecord.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    
					 
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#include "cvi_db.h"
#include <ansi_c.h>
#include <utility.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "databasesample.h"  
#include "oilrecord.h"
#include "setpara.h"
#include "CrcCheck.h"

long	goiltablemainkey;

/*******************************************************************************
* CONSTANTS
*/

int cvi_hdbc_mysql_handle;			//数据库连接句柄
int globalvalue;
int db_panelHandle;

stcRecOilRecordCtrl	gsRecvOilRecordCtrl;  
/*******************************************************************************
* GLOBAL VARIABLES
*/


char	g_datatime[32];

/*******************************************************************************
* 名    称： CreateDBTableMap
* 功    能： 创建数据表映射
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
int	CreateDBTableMapOilRecord(int * hmap,stcFlshRecSql *sFlshRecSql)
{
	long	tmp64;
	int		i,j=0;
	char	tmpbuf[32];
	int 	resultcode;
	short	tmp16;
	int		tmp32;
	
	
	DBMapColumnToInt (*hmap,"storecnt",			&sFlshRecSql->StoreCnt		,&tmp64);	
	DBMapColumnToInt (*hmap,"rectypcod",		&sFlshRecSql->RecTypCod		,&tmp64);	
	DBMapColumnToInt (*hmap,"relspeed",			&sFlshRecSql->RelSpeed		,&tmp64);

	
	DBMapColumnToChar (*hmap,"time",20,&g_datatime,&tmp32,"");
	
	DBMapColumnToInt (*hmap,"locotyp",			&sFlshRecSql->LocoTyp		,&tmp64);
	DBMapColumnToInt (*hmap,"e_locotyp",		&sFlshRecSql->E_LocoTyp		,&tmp64); 
	DBMapColumnToInt (*hmap,"loconum",			&sFlshRecSql->LocoNum		,&tmp64);	
//	DBMapColumnToInt (*hmap,"traintyp",			&sFlshRecSql->TrainTyp     	,&tmp64);	
	DBMapColumnToInt (*hmap,"trainnum",			&sFlshRecSql->TrainNum		,&tmp64);
//	DBMapColumnToInt (*hmap,"car_truck",		&sFlshRecSql->Car_Truck		,&tmp64);
	DBMapColumnToInt (*hmap,"voiturecnt",		&sFlshRecSql->VoitureCnt	,&tmp64); 	
	DBMapColumnToInt (*hmap,"kmmark",			&sFlshRecSql->KmMark		,&tmp64);	
	DBMapColumnToInt (*hmap,"weight",			&sFlshRecSql->Weight		,&tmp64);	
	DBMapColumnToInt (*hmap,"planlen",			&sFlshRecSql->PlanLen		,&tmp64);	
	DBMapColumnToInt (*hmap,"mstdrivernum",		&sFlshRecSql->MstDriverNum	,&tmp64);	
	DBMapColumnToInt (*hmap,"e_mstdrivernum",	&sFlshRecSql->E_MstDriverNum,&tmp64);	
	DBMapColumnToInt (*hmap,"e_slvdrivernum",	&sFlshRecSql->E_SlvDriverNum,&tmp64);	
	DBMapColumnToInt (*hmap,"slvdrivernum",		&sFlshRecSql->SlvDriverNum	,&tmp64);	
	DBMapColumnToInt (*hmap,"myvolume",			&sFlshRecSql->DriverUnitNum ,&tmp64);	
	DBMapColumnToInt (*hmap,"roadnum",			&sFlshRecSql->RoadNum		,&tmp64);	
	DBMapColumnToInt (*hmap,"relroadnum",		&sFlshRecSql->RelRoadNum	,&tmp64);	
	DBMapColumnToInt (*hmap,"stationnum",		&sFlshRecSql->StationNum	,&tmp64);	
	DBMapColumnToInt (*hmap,"e_stationnum",		&sFlshRecSql->E_StationNum	,&tmp64);	
//	DBMapColumnToInt (*hmap,"signaltyp",		&sFlshRecSql->SignalTyp		,&tmp64);	
//	DBMapColumnToInt (*hmap,"locosign1",		&sFlshRecSql->LocoSign		,&tmp64);	
//	DBMapColumnToInt (*hmap,"locosign2",		&sFlshRecSql->LocoWorkState	,&tmp64);	
	DBMapColumnToInt (*hmap,"locoworkstate1",	&sFlshRecSql->LocoState		,&tmp64);	
	DBMapColumnToInt (*hmap,"myspeed1",			&sFlshRecSql->Myspeed1		,&tmp64);	
	DBMapColumnToInt (*hmap,"myspeed2",			&sFlshRecSql->Myspeed2		,&tmp64);	
	DBMapColumnToInt (*hmap,"mstdip",			&sFlshRecSql->MstDip		,&tmp64);	
	DBMapColumnToInt (*hmap,"totaldis",			&sFlshRecSql->MyKileMeter	,&tmp64);	
	DBMapColumnToInt (*hmap,"mstlocopower",		&sFlshRecSql->MyMstLocoPower,&tmp64);	
	DBMapColumnToInt (*hmap,"totalw",			&sFlshRecSql->MyPower		,&tmp64);	
	DBMapColumnToInt (*hmap,"levelheight1",		&sFlshRecSql->Myhig1		,&tmp64);	
	DBMapColumnToInt (*hmap,"levelheight2",		&sFlshRecSql->Myhig2		,&tmp64);	
	DBMapColumnToInt (*hmap,"excitationa",		&sFlshRecSql->SlvDip1Prs	,&tmp64);	
	DBMapColumnToInt (*hmap,"rectifyv",			&sFlshRecSql->SlvDip2Prs	,&tmp64);	
	DBMapColumnToInt (*hmap,"myyear",			&sFlshRecSql->MyYear		,&tmp64);	
	DBMapColumnToInt (*hmap,"mymonth",			&sFlshRecSql->MyMonth		,&tmp64);	
	DBMapColumnToInt (*hmap,"mydata",			&sFlshRecSql->MyData		,&tmp64);	
	DBMapColumnToInt (*hmap,"myhour",			&sFlshRecSql->MyHour		,&tmp64);	
	DBMapColumnToInt (*hmap,"myminute",			&sFlshRecSql->MyMinute     	,&tmp64);	
	DBMapColumnToInt (*hmap,"mysecond",			&sFlshRecSql->MySecond		,&tmp64);	
	DBMapColumnToInt (*hmap,"density",			&sFlshRecSql->MstDensity	,&tmp64);	
	DBMapColumnToInt (*hmap,"myspeed",			&sFlshRecSql->MyAddspeed	,&tmp64);	
	DBMapColumnToInt (*hmap,"mydip",			&sFlshRecSql->MyDip			,&tmp64);	
	DBMapColumnToInt (*hmap,"gpslongitude",		&sFlshRecSql->GpsLongitude	,&tmp64);	
	DBMapColumnToInt (*hmap,"gpslatitude",		&sFlshRecSql->GpsLatitude	,&tmp64);	
	DBMapColumnToInt (*hmap,"engrotspd",		&sFlshRecSql->MstEngRotSpd	,&tmp64);	
	DBMapColumnToInt (*hmap,"myengrotspd",		&sFlshRecSql->MyEngRotSpd	,&tmp64);	
	DBMapColumnToInt (*hmap,"jcrealtype",		&sFlshRecSql->JcRealType	,&tmp64);	
	DBMapColumnToInt (*hmap,"jcrealno",			&sFlshRecSql->JcRealNo		,&tmp64);	
	DBMapColumnToInt (*hmap,"electrica1",		&sFlshRecSql->MyDip1Tmp	  	,&tmp64);	
	DBMapColumnToInt (*hmap,"electrica2",		&sFlshRecSql->MyDip2Tmp		,&tmp64);	
	DBMapColumnToInt (*hmap,"electrica3",		&sFlshRecSql->MyDip1Den		,&tmp64);	
	DBMapColumnToInt (*hmap,"electrica4",		&sFlshRecSql->MyDip2Den		,&tmp64);	
	DBMapColumnToInt (*hmap,"electrica5",		&sFlshRecSql->MyDip1Err		,&tmp64);	
	DBMapColumnToInt (*hmap,"electrica6",		&sFlshRecSql->MyDip2Err		,&tmp64);	
	DBMapColumnToInt (*hmap,"maxspeed",			&sFlshRecSql->MaxSpeed		,&tmp64);	
	DBMapColumnToInt (*hmap,"errorcount",		&sFlshRecSql->ErrNum		,&tmp64);	
	DBMapColumnToInt (*hmap,"errorcode",		&sFlshRecSql->ErrorCode		,&tmp64);	
	DBMapColumnToInt (*hmap,"mylocoworkstate1",	&sFlshRecSql->MyLocoWorkState,&tmp64);	
	DBMapColumnToInt (*hmap,"mylocoworkstate2",	&sFlshRecSql->MstDipTemp	,&tmp64);	
	DBMapColumnToInt (*hmap,"oilboxmodel",		&sFlshRecSql->OilBoxModel	,&tmp64);	
	DBMapColumnToInt (*hmap,"reserve0",			&sFlshRecSql->SoftVes       ,&tmp64);	
	DBMapColumnToInt (*hmap,"crccheck",			&sFlshRecSql->CrcCheck      ,&tmp64);	                                            		
	
	return 1;
}


/*******************************************************************************
* 名    称： ChangeRecordValue
* 功    能： 插入数据记录
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 由于数据库操作，现建立映射，在赋值改写数据，再数据入库。 
*******************************************************************************/
void	ChangeRecordValueOilRecord(stcFlshRec *sFlshRec,stcFlshRecSql *sFlshRecSql)
{
	goiltablemainkey++;
	gsFlshRec.StoreCnt++;
	
	//sFlshRec->StoreCnt =  gsFlshRec.StoreCnt;
	uint32	tmp32;
	
	
	
	memset((uint8 *)sFlshRecSql,0,sizeof(stcFlshRecSql));
	
	memcpy (&sFlshRecSql->StoreCnt			,&sFlshRec->StoreCnt		,sizeof(sFlshRec->StoreCnt		));	
	memcpy (&sFlshRecSql->RecTypCod			,&sFlshRec->RecTypCod		,sizeof(sFlshRec->RecTypCod		));	
//	memcpy (&sFlshRecSql->RelSpeed			,&sFlshRec->RelSpeed[0]		,sizeof(sFlshRec->RelSpeed		));	
	
	memcpy((uint8 *)&tmp32,&sFlshRec->RelSpeed[0],sizeof(tmp32));
	tmp32 &= 0x000003ff; 
	memcpy (&sFlshRecSql->RelSpeed			,(uint8 *)&tmp32			,sizeof(sFlshRec->RelSpeed		));	
	
	memcpy (&sFlshRecSql->Time				,&sFlshRec->Time			,sizeof(sFlshRec->Time			));
	memcpy (&sFlshRecSql->LocoTyp			,&sFlshRec->LocoTyp			,sizeof(sFlshRec->LocoTyp		));
	memcpy (&sFlshRecSql->E_LocoTyp			,&sFlshRec->E_LocoTyp		,sizeof(sFlshRec->E_LocoTyp		)); 
	memcpy (&sFlshRecSql->LocoNum			,&sFlshRec->LocoNum			,sizeof(sFlshRec->LocoNum		));	
	memcpy (&sFlshRecSql->TrainTyp     		,&sFlshRec->TrainTyp     	,sizeof(sFlshRec->TrainTyp     	));	
	memcpy (&sFlshRecSql->TrainNum			,&sFlshRec->TrainNum[0]		,sizeof(sFlshRec->TrainNum		));
	memcpy (&sFlshRecSql->Car_Truck			,&sFlshRec->Car_Truck		,sizeof(sFlshRec->Car_Truck		));
	memcpy (&sFlshRecSql->VoitureCnt		,&sFlshRec->VoitureCnt		,sizeof(sFlshRec->VoitureCnt	)); 	
	memcpy (&sFlshRecSql->KmMark			,&sFlshRec->KmMark[0]		,sizeof(sFlshRec->KmMark		));	
	memcpy (&sFlshRecSql->Weight			,&sFlshRec->Weight			,sizeof(sFlshRec->Weight		));	
	memcpy (&sFlshRecSql->PlanLen			,&sFlshRec->PlanLen			,sizeof(sFlshRec->PlanLen		));	
	memcpy (&sFlshRecSql->MstDriverNum		,&sFlshRec->MstDriverNum	,sizeof(sFlshRec->MstDriverNum	));	
	memcpy (&sFlshRecSql->E_MstDriverNum	,&sFlshRec->E_MstDriverNum	,sizeof(sFlshRec->E_MstDriverNum));	
	memcpy (&sFlshRecSql->E_SlvDriverNum	,&sFlshRec->E_SlvDriverNum	,sizeof(sFlshRec->E_SlvDriverNum));	
	memcpy (&sFlshRecSql->SlvDriverNum		,&sFlshRec->SlvDriverNum	,sizeof(sFlshRec->SlvDriverNum	));	
	memcpy (&sFlshRecSql->DriverUnitNum 	,&sFlshRec->DriverUnitNum 	,sizeof(sFlshRec->DriverUnitNum ));	
	memcpy (&sFlshRecSql->RoadNum			,&sFlshRec->RoadNum			,sizeof(sFlshRec->RoadNum		));	
	memcpy (&sFlshRecSql->RelRoadNum		,&sFlshRec->RelRoadNum		,sizeof(sFlshRec->RelRoadNum	));	
	memcpy (&sFlshRecSql->StationNum		,&sFlshRec->StationNum		,sizeof(sFlshRec->StationNum	));	
	memcpy (&sFlshRecSql->E_StationNum		,&sFlshRec->E_StationNum	,sizeof(sFlshRec->E_StationNum	));	
	memcpy (&sFlshRecSql->SignalTyp			,&sFlshRec->SignalTyp		,sizeof(sFlshRec->SignalTyp		));	
	memcpy (&sFlshRecSql->LocoSign			,&sFlshRec->LocoSign		,sizeof(sFlshRec->LocoSign		));	
	memcpy (&sFlshRecSql->LocoWorkState		,&sFlshRec->LocoWorkState	,sizeof(sFlshRec->LocoWorkState	));	
	memcpy (&sFlshRecSql->LocoState			,&sFlshRec->LocoState		,sizeof(sFlshRec->LocoState		));	
	memcpy (&sFlshRecSql->Myspeed1			,&sFlshRec->Myspeed1		,sizeof(sFlshRec->Myspeed1		));	
	memcpy (&sFlshRecSql->Myspeed2			,&sFlshRec->Myspeed2		,sizeof(sFlshRec->Myspeed2		));	
	memcpy (&sFlshRecSql->MstDip			,&sFlshRec->MstDip			,sizeof(sFlshRec->MstDip		));	
	memcpy (&sFlshRecSql->MyKileMeter		,&sFlshRec->MyKileMeter		,sizeof(sFlshRec->MyKileMeter	));	
	memcpy (&sFlshRecSql->MyMstLocoPower	,&sFlshRec->MyMstLocoPower	,sizeof(sFlshRec->MyMstLocoPower));	
	memcpy (&sFlshRecSql->MyPower			,&sFlshRec->MyPower			,sizeof(sFlshRec->MyPower		));	
	memcpy (&sFlshRecSql->Myhig1			,&sFlshRec->Myhig1			,sizeof(sFlshRec->Myhig1		));	
	memcpy (&sFlshRecSql->Myhig2			,&sFlshRec->Myhig2			,sizeof(sFlshRec->Myhig2		));	
	memcpy (&sFlshRecSql->SlvDip1Prs		,&sFlshRec->SlvDip1Prs		,sizeof(sFlshRec->SlvDip1Prs	));	
	memcpy (&sFlshRecSql->SlvDip2Prs		,&sFlshRec->SlvDip2Prs		,sizeof(sFlshRec->SlvDip2Prs	));	
	memcpy (&sFlshRecSql->MyYear			,&sFlshRec->MyYear			,sizeof(sFlshRec->MyYear		));	
	memcpy (&sFlshRecSql->MyMonth			,&sFlshRec->MyMonth			,sizeof(sFlshRec->MyMonth		));	
	memcpy (&sFlshRecSql->MyData			,&sFlshRec->MyData			,sizeof(sFlshRec->MyData		));	
	memcpy (&sFlshRecSql->MyHour			,&sFlshRec->MyHour			,sizeof(sFlshRec->MyHour		));	
	memcpy (&sFlshRecSql->MyMinute     		,&sFlshRec->MyMinute     	,sizeof(sFlshRec->MyMinute     	));	
	memcpy (&sFlshRecSql->MySecond			,&sFlshRec->MySecond		,sizeof(sFlshRec->MySecond		));	
	memcpy (&sFlshRecSql->MstDensity		,&sFlshRec->MstDensity		,sizeof(sFlshRec->MstDensity	));	
	memcpy (&sFlshRecSql->MyAddspeed		,&sFlshRec->MyAddspeed		,sizeof(sFlshRec->MyAddspeed	));	
	memcpy (&sFlshRecSql->MyDip				,&sFlshRec->MyDip			,sizeof(sFlshRec->MyDip			));	
	memcpy (&sFlshRecSql->GpsLongitude		,&sFlshRec->GpsLongitude	,sizeof(sFlshRec->GpsLongitude	));	
	memcpy (&sFlshRecSql->GpsLatitude		,&sFlshRec->GpsLatitude		,sizeof(sFlshRec->GpsLatitude	));	
	memcpy (&sFlshRecSql->MstEngRotSpd		,&sFlshRec->MstEngRotSpd	,sizeof(sFlshRec->MstEngRotSpd	));	
	memcpy (&sFlshRecSql->MyEngRotSpd		,&sFlshRec->MyEngRotSpd		,sizeof(sFlshRec->MyEngRotSpd	));	
	memcpy (&sFlshRecSql->JcRealType		,&sFlshRec->JcRealType		,sizeof(sFlshRec->JcRealType	));	
	memcpy (&sFlshRecSql->JcRealNo			,&sFlshRec->JcRealNo		,sizeof(sFlshRec->JcRealNo		));	
	memcpy (&sFlshRecSql->MyDip1Tmp	  		,&sFlshRec->MyDip1Tmp	  	,sizeof(sFlshRec->MyDip1Tmp	  	));	
	memcpy (&sFlshRecSql->MyDip2Tmp			,&sFlshRec->MyDip2Tmp		,sizeof(sFlshRec->MyDip2Tmp		));	
	memcpy (&sFlshRecSql->MyDip1Den			,&sFlshRec->MyDip1Den		,sizeof(sFlshRec->MyDip1Den		));	
	memcpy (&sFlshRecSql->MyDip2Den			,&sFlshRec->MyDip2Den		,sizeof(sFlshRec->MyDip2Den		));	
	memcpy (&sFlshRecSql->MyDip1Err			,&sFlshRec->MyDip1Err		,sizeof(sFlshRec->MyDip1Err		));	
	memcpy (&sFlshRecSql->MyDip2Err			,&sFlshRec->MyDip2Err		,sizeof(sFlshRec->MyDip2Err		));	
	memcpy (&sFlshRecSql->MaxSpeed			,&sFlshRec->MaxSpeed		,sizeof(sFlshRec->MaxSpeed		));	
	memcpy (&sFlshRecSql->ErrNum			,&sFlshRec->ErrNum			,sizeof(sFlshRec->ErrNum		));	
	memcpy (&sFlshRecSql->ErrorCode			,&sFlshRec->ErrorCode		,sizeof(sFlshRec->ErrorCode		));	
	memcpy (&sFlshRecSql->MyLocoWorkState	,&sFlshRec->MyLocoWorkState	,sizeof(sFlshRec->MyLocoWorkState));	
	memcpy (&sFlshRecSql->MstDipTemp		,&sFlshRec->MstDipTemp		,sizeof(sFlshRec->MstDipTemp	));	
	memcpy (&sFlshRecSql->OilBoxModel		,&sFlshRec->OilBoxModel		,sizeof(sFlshRec->OilBoxModel	));	
	memcpy (&sFlshRecSql->SoftVes       	,&sFlshRec->SoftVes       	,sizeof(sFlshRec->SoftVes       ));	
	memcpy (&sFlshRecSql->CrcCheck      	,&sFlshRec->CrcCheck      	,sizeof(sFlshRec->CrcCheck      ));	
	
	sprintf(g_datatime,"%4d-%02d-%02d %02d:%02d:%02d"	,((0x3f)&(uint8)(sFlshRec->Time >> 26)) +2000
										,(0x0f)&(uint8)(sFlshRec->Time >> 22) 
										,(0x1f)&(uint8)(sFlshRec->Time >> 17) 
										,(0x1f)&(uint8)(sFlshRec->Time >> 12) 
										,(0x3f)&(uint8)(sFlshRec->Time >> 6) 
										,(0x3f)&(uint8)(sFlshRec->Time >> 0) 
		   );	
	
}

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
int  InsertoilRecToDB (char *tabelname,stcFlshRec *sFlshRec)
{
	int 	resultcode;
	int 	hstat;
	int 	numberofrecords;
	int 	hmap;	
	stcFlshRecSql	sFlshRecSql;
	
	
	hmap = DBBeginMap (cvi_hdbc_mysql_handle);  //创建一个数据库映射关系
	
	CreateDBTableMapOilRecord(&hmap,&sFlshRecSql);//创建一个数据表映射

	hstat = DBActivateMap (hmap, tabelname); 	//激活映射
	
	ChangeRecordValueOilRecord(sFlshRec,&sFlshRecSql);//修改记录值 
	
	DBCreateRecord(hstat);  					//创建记录  

	resultcode = DBPutRecord (hstat);			//更新数据库  
			
	resultcode = DBDeactivateMap (hmap);		//释放被激活的句柄 

	return 0;
}
void     ReadTime(stcTime * sTime);

void	storerectofile(uint8* buf,int len)
{
	char	dirstring[512];
	char	filestring[512];
	int		filehandle;
	stcTime  sTime;
	
	ReadTime((stcTime *)&sTime);											// ê±??   
	
	if(strlen(gsRecvOilRecordCtrl.ICstorefile) == 0)
		sprintf(gsRecvOilRecordCtrl.ICstorefile,"%d_%d_%d %d_%d_%d.oil"
			     ,sTime.Year ,sTime.Month,sTime.Date,sTime.Hour,sTime.Min,sTime.Sec
			   );
	
	GetProjectDir (dirstring);
	MakePathname (dirstring, gsRecvOilRecordCtrl.ICstorefile, filestring);  //创建文件目录
	
	filehandle = OpenFile (filestring, VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_BINARY);					 
	
	SetFilePtr (filehandle, 0, 2);											//指向最後

	WriteFile(filehandle,buf,len);
	
	CloseFile(filehandle);
	
	return 1;
}

