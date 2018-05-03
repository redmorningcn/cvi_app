/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    2017-10-15
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#include  	"modeltable.h"


/*******************************************************************************
* CONSTANTS
*/

int 				cvi_hdbc_mysql_handle;				//数据库连接句柄
int 				db_panelHandle;
stcThreadModel		gsThreadModel;		//油箱模型线程 （191017）

extern	stcCalcModel	gsCalcModel;	//油箱模型（运算用）


/*******************************************************************************
* GLOBAL VARIABLES
*/

stcModelTableCtrl	gsSetModelTable;	//模型参数表
stcOilPara			gsOilPara;			//油量运算参数	

stcThreadModel		gsThreadModel;		//油箱模型线程 （191017）

/*******************************************************************************
* 功    能： 初始化模型表控制表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
void	InitModelTableCtrl(void)
{
	gsSetModelTable.phdbc = &g_cvihdbc_handel;
	gsSetModelTable.map   = 0;
	gsSetModelTable.sql   = 0;
	strcpy((char *)gsSetModelTable.tablename,MODEL_TABLE_NAME);
	
	gsSetModelTable.Operate.rdEndFlg 	= 0;
	gsSetModelTable.Operate.rdStartFlg 	= 0;
	gsSetModelTable.Operate.wrEndFlg 	= 0;
	gsSetModelTable.Operate.wrStartFlg 	= 0;	
}

/*******************************************************************************
* 功    能： 创建数据表映射
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
int	CreateModelToTableMap(stcModelTableCtrl * stable)
{
	long	tmp64;
	int		i;
	char	tmpbuf[32];
	int 	resultcode;

	stable->map = DBBeginMap(*stable->phdbc);																//创立映射，开始赋值
	
	DBMapColumnToShort (stable->map, "MODEL_NUM",(short *)&stable->sMode.ModelNum,	&tmp64);						//油箱模型编号
	DBMapColumnToShort (stable->map, "POT_NUM",  (short *)&stable->sMode.PotNum,		&tmp64);						//模型点数
	DBMapColumnToShort (stable->map, "SET_OIL",  (short *)&stable->sMode.StartOil, 	&tmp64);						//模型初始值
	
	for(i = 0;i < 100;i++)						   
	{
		sprintf(tmpbuf,"HIG%02d",i);
		resultcode = DBMapColumnToShort (stable->map, tmpbuf, (short *)&stable->sMode.sModPot[i].HigVal, &tmp64);	//高度
		
		sprintf(tmpbuf,"OIL%02d",i);
		resultcode = DBMapColumnToShort (stable->map, tmpbuf, (short *)&stable->sMode.sModPot[i].DipVal, &tmp64);	//油量
	}	
	
	return 1;
}


/*******************************************************************************
* 功    能： 读取指定值得数据表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-06
* 修    改：
* 修改日期：
* 备    注： 从数据库中读取指定的数据，并返回 
*******************************************************************************/
int	ReadModelFromTable(int	keyval)
{
	int 	total = 0;
//	char	tmpbuf[64];

	DisableBreakOnLibraryErrors ();
			
	gsSetModelTable.sql = DBActivateMap(gsSetModelTable.map,gsSetModelTable.tablename);			//激活映射
	total = DBNumberOfRecords (gsSetModelTable.sql); 											//获得记录的总数

	if (total > 0)
	{
		//取数据记录，并打印
		while (DBFetchNext(gsSetModelTable.sql) != DB_EOF)    									//数据比较大，建议先做查询，进行数据过滤
		{
			if(gsSetModelTable.sMode.ModelNum == keyval)
			{
				memcpy((char *)&gsSetModelTable.Operate.rdModel,
					   (char *)&gsSetModelTable.sMode,
					   sizeof(stcCalcModel));													//拷贝数据，防止异常改写
				
				gsSetModelTable.Operate.rdEndFlg = 1;											//读标识为1，数据读取完成 
				break;
				//return 1;
			}
		}
	}
	
	//激活关闭查询
	DBDeactivateSQL (gsSetModelTable.sql);
	return 0;
}


//----------------------------------------------------------------------------
// 功    能： 串口的收、发控制.通过标识位，线程，控制程序收发协调
// 参    数：
// 作    者： redmornigcn 20170927
//----------------------------------------------------------------------------
static int CVICALLBACK Thread_DB (void *functionData)
{
	
	while (!gsThreadModel.ThreadExit)							//线程不退出
	{
//////////////////////////////////////////////////////////////////数据库写操作
		if(gsSetModelTable.Operate.rdStartFlg)					//读取开始读取数据
		{
			gsSetModelTable.Operate.rdStartFlg = 0;
			ReadModelFromTable(gsSetModelTable.Operate.rdRecNum);//读取数据记录	
			
			memcpy((uint8 *)&gsCalcModel,
				   (uint8 *)&gsSetModelTable.sMode,
				   sizeof(gsCalcModel));						//更新油尺模型文件数据
		}
	}

	return 0;
}

//----------------------------------------------------------------------------
// 功    能： 初始化模型表数据库操作线程。为实现数据库操作必须开启此线程
// 参    数：
// 作    者： redmornigcn 20171027
//----------------------------------------------------------------------------
int	cvi_InitBspDB(stcThreadModel * T_Ctrl)
{
	if(T_Ctrl->ThreadID == 0)				//初始化收发控制线程
	{
		//T_Ctrl->sCom = &gsCom1Contrl;		//串口1建立关联
		T_Ctrl->ThreadExit = 0;				//线程不释放

		//cvi_OpenCom(T_Ctrl->sCom);			//打开该该线程对应的串口
		
		CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,
									   Thread_DB,		//该线程处理函数
									   NULL,
							   		   &T_Ctrl->ThreadID);
	}
	
	return	T_Ctrl->ThreadID;				//返回线程ID
}


///*******************************************************************************
//* 名    称： CreateDBBindColCalcModel
//* 功    能： 创建数据表绑定
//* 入口参数： 无
//* 出口参数： 无
//* 作　 　者：redmorningcn.
//* 创建日期： 2017-09-06
//* 修    改：
//* 修改日期：
//* 备    注： 
//*******************************************************************************/
//int	CreateDBBindColCalcModel(int * hstat,stcCalcModel *sCalcModel)
//{
//	long	tmp64;
//	int		i,j=1;

//	j=1;
//	
//	DBBindColShort (*hstat, j++, &sCalcModel->ModelNum,&tmp64);  				//油箱模型编号 
//	DBBindColShort (*hstat, j++, &sCalcModel->PotNum,&tmp64);					//模型点数  
//	DBBindColShort (*hstat, j++, &sCalcModel->StartOil, &tmp64);				//模型初始值   
//	
//	for(i = 0;i < 100;i++)						   
//	{
//		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].HigVal, &tmp64);	//高度
//		
//		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].DipVal, &tmp64);	//油量
//	}	

//	return 1;
//}

///*******************************************************************************
//* 名    称： CreateDBTable
//* 功    能： 创建数据表
//* 入口参数： 无
//* 出口参数： 无
//* 作　 　者：redmorningcn.
//* 创建日期： 2017-09-05
//* 修    改：
//* 修改日期：
//* 备    注：DBBindColInt 
//*******************************************************************************/
//int	CreateDBTable(char *tabelname)
//{
//	int 	resultcode;
//	int 	hmap;	
// 
//	hmap = DBBeginMap (cvi_hdbc_mysql_handle); 				//创建一个数据库映射

//	CreateDBTableMap(&hmap,&gsCalcModel);					//创建一个数据表映射

//	resultcode = DBCreateTableFromMap (hmap, tabelname);	//由此映射创建一个数据表

//	DBDeactivateMap (hmap); 								//结束映射 

//	return 1;
//}

///*******************************************************************************
//* 名    称： ReadRecFromDB
//* 功    能： 从数据库表中，读取数据记录
//* 入口参数： 无
//* 出口参数： 无
//* 作　 　者：redmorningcn.
//* 创建日期： 2017-09-06
//* 修    改：
//* 修改日期：
//* 备    注： 从数据库中读取指定的数据，并返回 
//*******************************************************************************/
//int	ReadRecFromDB(char *tabelname,int	keyval)
//{
//	int 	resultcode;
//	long 	idstatus;
//	int 	idvalue;
//	int 	hstat;
//	int 	total = 0;
//	int 	i = 1;
//	char	tmpbuf[64];

//	DisableBreakOnLibraryErrors ();
//			
//	//激活SQL查询
//	
//	sprintf(tmpbuf,"SELECT * FROM %s WHERE MODEL_NUM = %d",tabelname,keyval);	//查找指定键值数据
//	hstat = DBActivateSQL (cvi_hdbc_mysql_handle, tmpbuf);

//	CreateDBBindColCalcModel(&hstat,&gsCalcModel);  							//绑定记录到相关记录的数据结构中 
//	
//	total = DBNumberOfRecords (hstat); 											//获得记录的总数

//	if (total > 0)
//	{
//		//取数据记录，并打印
//		//while (DBFetchNext(hstat) != DB_EOF)
//		if (DBFetchNext(hstat) != DB_EOF)    
//		{
//			//删除面板中的表格控件所有行
//			DeleteTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, -1);
//			
//			//插入与数据表中记录数相同的行数
//			InsertTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, gsCalcModel.PotNum, VAL_USE_MASTER_CELL_TYPE);
//			
//			if (gsCalcModel.ModelNum > 0)
//			{
//				//利用数据指针逐行写入面板表格控件中
//				for(i = 1;i < gsCalcModel.PotNum +1;i++)
//				{
//					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(1,i), gsCalcModel.sModPot[i-1].HigVal);
//					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(2,i), gsCalcModel.sModPot[i-1].DipVal);
//				}
//			}			
//			
//			//设置油量显示值
//			sprintf(tmpbuf,"模型信息：（模型编号：%2d;模型点数：%2d;起始油量：%2d）"
//																	,gsCalcModel.ModelNum
//																	,gsCalcModel.PotNum
//																	,gsCalcModel.StartOil
//				   													);
//			SetCtrlVal(db_panelHandle, SETM_PANEL_TEXTMSG,tmpbuf);
//	
//			gsCalcModel.CrcCheck = GetCrc16Check((uint8 *)&gsCalcModel,sizeof(gsCalcModel)-2);	//计算校验	
//			
//			l_eqiupmentcode = RUN_MODEL_PARA;								//设置为参数模型卡
//		}
//	}
//	
//	//激活关闭查询
//	DBDeactivateSQL (hstat);
//	
//	return 1;
//}

///*******************************************************************************
//* 名    称： InsertRecToDB
//* 功    能： 插入数据记录
//* 入口参数： 无
//* 出口参数： 无
//* 作　 　者：redmorningcn.
//* 创建日期： 2017-09-05
//* 修    改：
//* 修改日期：
//* 备    注： 由于数据库操作，现建立映射，在赋值改写数据，再数据入库。 
//*******************************************************************************/
//int CVICALLBACK InsertRecToDB (char *tabelname,stcCalcModel *sCalcModel)
//{
//	int 	resultcode;
//	int 	hstat;
//	int 	numberofrecords;
//	int 	hmap;	
//	
//	hmap = DBBeginMap (cvi_hdbc_mysql_handle);  //创建一个数据库映射关系
//	
//	CreateDBTableMap(&hmap,sCalcModel);			//创建一个数据表映射

//	hstat = DBActivateMap (hmap, tabelname); 	//激活映射
//	
//	ChangeRecordValue();	  					//修改记录值 
//	
//	DBCreateRecord(hstat);  					//创建记录  

//	resultcode = DBPutRecord (hstat);			//更新数据库  
//			
//	resultcode = DBDeactivateMap (hmap);		//释放被激活的句柄 

//	return 0;
//}

///*******************************************************************************
//* 名    称： ChangeRecordValue
//* 功    能： 插入数据记录
//* 入口参数： 无
//* 出口参数： 无
//* 作　 　者：redmorningcn.
//* 创建日期： 2017-09-05
//* 修    改：
//* 修改日期：
//* 备    注： 由于数据库操作，现建立映射，在赋值改写数据，再数据入库。 
//*******************************************************************************/
//void	ChangeRecordValue(void)
//{
//	gsCalcModel.ModelNum++;
//	gsCalcModel.PotNum = 3;
//	
//	gsCalcModel.sModPot[0].HigVal = 0;
//	gsCalcModel.sModPot[0].DipVal = 1200;
//	
//	gsCalcModel.sModPot[1].HigVal = 1558;
//	gsCalcModel.sModPot[1].DipVal = 3400;
//	
//	gsCalcModel.sModPot[2].HigVal = 7529;
//	gsCalcModel.sModPot[2].DipVal = 9000;
//	
//	for(int i = 3;i<100;i++)
//	{
//		gsCalcModel.sModPot[i].HigVal = 7529;
//		gsCalcModel.sModPot[i].DipVal = 9000;
//	}
//}

