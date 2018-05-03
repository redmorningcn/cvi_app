/*******************************************************************************
 *   Filename:       setmodel.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    
					 
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#include "oilmodel_db.h"
#include <ansi_c.h>
#include <utility.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>

 /********************************************************************************************/
/* 定时器管理变量结构体																				    */
/********************************************************************************************/
typedef struct	_stcTableCtrl_
{
	int		hdbc_handel;	//数据库管理器句柄
	int		hmap;			//超时值

	char	*dnsname;		//数据库DNS的name	
	char	*tablename;		//超时数
	int		* poverFlg;		//超时标识
}stcTableCtrl;				//数据库表操作



/*******************************************************************************
* CONSTANTS
*/

int cvi_hdbc_mysql_handle;			//数据库连接句柄
int globalvalue;
int db_panelHandle;

/*******************************************************************************
* GLOBAL VARIABLES
*/
void	ConnectDB(void);
void	CloseDB(void);
void	ChangeRecordValue(void);


/********************************************************************************************/
/*打开数据库面板																	            */
/********************************************************************************************/
int CVICALLBACK OpenOilModelCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			if ((db_panelHandle = LoadPanel (0, "oilmodel_db.uir", SETM_PANEL)) < 0)
				return -1;	
	
			//ConnectDB();	//连接数据库
	
			DisplayPanel (db_panelHandle);

			break;
	}
	
	return 0;
}



/*******************************************************************************
* 名    称： ConnectDB
* 功    能： 连接数据库
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 和数据库建立连接。ODBC 数据源(32 位)支持，提供DNS
*******************************************************************************/
void	ConnectDB(void)
{
	//建立数据库联接，并获得联接句柄
	char	dsnbuf[64];
	sprintf(dsnbuf,"DSN=%s",ODBC_DNS);
	cvi_hdbc_mysql_handle = DBConnect (dsnbuf);
}

/*******************************************************************************
* 名    称： CloseDB
* 功    能： 连接数据库
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
void	CloseDB(void)
{
	//当退出应用程序时，关闭数据库连接
	DBDisconnect (cvi_hdbc_mysql_handle); 	
}


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
int	CreateDBTableMap(int * hmap,stcCalcModel *sCalcModel)
{
	long	tmp64;
	int		i,j=0;
	char	tmpbuf[32];
	int 	resultcode;

	DBMapColumnToShort (*hmap, "MODEL_NUM",&sCalcModel->ModelNum,&tmp64);	//油箱模型编号
	DBMapColumnToShort (*hmap, "POT_NUM", &sCalcModel->PotNum,&tmp64);		//模型点数
	DBMapColumnToShort (*hmap, "SET_OIL", &sCalcModel->StartOil, &tmp64);	//模型初始值
	
	for(i = 0;i < 100;i++)						   
	{
		sprintf(tmpbuf,"HIG%02d",i);
		resultcode = DBMapColumnToShort (*hmap, tmpbuf, &sCalcModel->sModPot[i].HigVal, &tmp64);	//高度
		
		sprintf(tmpbuf,"OIL%02d",i);
		resultcode = DBMapColumnToShort (*hmap, tmpbuf, &sCalcModel->sModPot[i].DipVal, &tmp64);	//油量
	}	
	
	return 1;
}

/*******************************************************************************
* 名    称： CreateDBBindColCalcModel
* 功    能： 创建数据表绑定
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-06
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
int	CreateDBBindColCalcModel(int * hstat,stcCalcModel *sCalcModel)
{
	long	tmp64;
	int		i,j=1;

	j=1;
	
	DBBindColShort (*hstat, j++, &sCalcModel->ModelNum,&tmp64);  				//油箱模型编号 
	DBBindColShort (*hstat, j++, &sCalcModel->PotNum,&tmp64);					//模型点数  
	DBBindColShort (*hstat, j++, &sCalcModel->StartOil, &tmp64);				//模型初始值   
	
	for(i = 0;i < 100;i++)						   
	{
		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].HigVal, &tmp64);	//高度
		
		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].DipVal, &tmp64);	//油量
	}	

	return 1;
}

/*******************************************************************************
* 名    称： CreateDBTable
* 功    能： 创建数据表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注：DBBindColInt 
*******************************************************************************/
int	CreateDBTable(char *tabelname)
{
	int 	resultcode;
	int 	hmap;	
 
	hmap = DBBeginMap (cvi_hdbc_mysql_handle); 				//创建一个数据库映射

	CreateDBTableMap(&hmap,&gsCalcModel);					//创建一个数据表映射

	resultcode = DBCreateTableFromMap (hmap, tabelname);	//由此映射创建一个数据表

	DBDeactivateMap (hmap); 								//结束映射 

	return 1;
}

/*******************************************************************************
* 名    称： ReadRecFromDB
* 功    能： 从数据库表中，读取数据记录
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-06
* 修    改：
* 修改日期：
* 备    注： 从数据库中读取指定的数据，并返回 
*******************************************************************************/
int	ReadRecFromDB(char *tabelname,int	keyval)
{
	int 	resultcode;
	long 	idstatus;
	int 	idvalue;
	int 	hstat;
	int 	total = 0;
	int 	i = 1;
	char	tmpbuf[64];

	DisableBreakOnLibraryErrors ();
			
	//激活SQL查询
	
	sprintf(tmpbuf,"SELECT * FROM %s WHERE MODEL_NUM = %d",tabelname,keyval);	//查找指定键值数据
	hstat = DBActivateSQL (cvi_hdbc_mysql_handle, tmpbuf);

	CreateDBBindColCalcModel(&hstat,&gsCalcModel);  							//绑定记录到相关记录的数据结构中 
	
	total = DBNumberOfRecords (hstat); 											//获得记录的总数

	if (total > 0)
	{
		//取数据记录，并打印
		//while (DBFetchNext(hstat) != DB_EOF)
		if (DBFetchNext(hstat) != DB_EOF)    
		{
			//删除面板中的表格控件所有行
			DeleteTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, -1);
			
			//插入与数据表中记录数相同的行数
			InsertTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, gsCalcModel.PotNum, VAL_USE_MASTER_CELL_TYPE);
			
			if (gsCalcModel.ModelNum > 0)
			{
				//利用数据指针逐行写入面板表格控件中
				for(i = 1;i < gsCalcModel.PotNum +1;i++)
				{
					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(1,i), gsCalcModel.sModPot[i-1].HigVal);
					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(2,i), gsCalcModel.sModPot[i-1].DipVal);
				}
			}			
			
			//设置油量显示值
			sprintf(tmpbuf,"模型信息：（模型编号：%2d;模型点数：%2d;起始油量：%2d）"
																	,gsCalcModel.ModelNum
																	,gsCalcModel.PotNum
																	,gsCalcModel.StartOil
				   													);
			SetCtrlVal(db_panelHandle, SETM_PANEL_TEXTMSG,tmpbuf);
	
			gsCalcModel.CrcCheck = GetCrc16Check((uint8 *)&gsCalcModel,sizeof(gsCalcModel)-2);	//计算校验	
			
			l_eqiupmentcode = RUN_MODEL_PARA;								//设置为参数模型卡
		}
	}
	
	//激活关闭查询
	DBDeactivateSQL (hstat);
	
	return 1;
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
int CVICALLBACK InsertRecToDB (char *tabelname,stcCalcModel *sCalcModel)
{
	int 	resultcode;
	int 	hstat;
	int 	numberofrecords;
	int 	hmap;	
	
	hmap = DBBeginMap (cvi_hdbc_mysql_handle);  //创建一个数据库映射关系
	
	CreateDBTableMap(&hmap,sCalcModel);			//创建一个数据表映射

	hstat = DBActivateMap (hmap, tabelname); 	//激活映射
	
	ChangeRecordValue();	  					//修改记录值 
	
	DBCreateRecord(hstat);  					//创建记录  

	resultcode = DBPutRecord (hstat);			//更新数据库  
			
	resultcode = DBDeactivateMap (hmap);		//释放被激活的句柄 

	return 0;
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
void	ChangeRecordValue(void)
{
	gsCalcModel.ModelNum++;
	gsCalcModel.PotNum = 3;
	
	gsCalcModel.sModPot[0].HigVal = 0;
	gsCalcModel.sModPot[0].DipVal = 1200;
	
	gsCalcModel.sModPot[1].HigVal = 1558;
	gsCalcModel.sModPot[1].DipVal = 3400;
	
	gsCalcModel.sModPot[2].HigVal = 7529;
	gsCalcModel.sModPot[2].DipVal = 9000;
	
	for(int i = 3;i<100;i++)
	{
		gsCalcModel.sModPot[i].HigVal = 7529;
		gsCalcModel.sModPot[i].DipVal = 9000;
	}
}
