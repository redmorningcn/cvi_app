/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    2017-10-14
 *   Notes:
 *     				 E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "oilmodel_db.h"
#include "cvi_db.h"

#include "modeltable.h"
#include "oilmath.h"

/*******************************************************************************
* LOCAL VARIABLES
*/

/********************************************************************************************/
// local Prototypes																		
/********************************************************************************************/
int		gdb_panelHandle;
int		gdb_ChildpanelHandle;

int		gmodeltime = 0;  				//定时器重新赋值

/*******************************************************************************
* LOCAL fun
*/
void	InitOilPara(void);


/********************************************************************************************/
/*打开oilmodel面板																            */
/********************************************************************************************/
int CVICALLBACK OpenOilModelCallback (int panel, int control, int event,
								  	  void *callbackData, int eventData1, int eventData2)
{
	char	tmp;
	switch (event)
	{
		case EVENT_COMMIT:

			if ((gdb_panelHandle 		= LoadPanel (0, "oilmodel_db.uir", SETM_PANEL)) < 0)
				return -1;	
			
			if ((gdb_ChildpanelHandle 	= LoadPanel (gdb_panelHandle, "oilmodel_db.uir", CHILD)) < 0)
				return -1;	
		
			ConnectDB();	//连接数据库
	
			DisplayPanel (gdb_panelHandle);
			
			InitModelTableCtrl();						//初始化结构体
			InitOilPara();								//
			CreateModelToTableMap(&gsSetModelTable);	//建立数据库映射
			
			refreshmodlecallback(panel,SETM_PANEL_MODEL_NUM,EVENT_COMMIT,&tmp,0,0); 
			
			break;
	}
	
	return 0;
}

/********************************************************************************************/
/*模型面板显示															            		*/
/********************************************************************************************/
void 	ModelDistoPanle(void)
{
	stcCalcModel 	*psModel;
	char			tmpbuf[128];
	tmpbuf[127] = '\0';
	
	if(gsSetModelTable.Operate.rdEndFlg == 1 ||gsSetModelTable.Operate.ModefyModelFlg == 1)   						//已经读到模型
	{
		gsSetModelTable.Operate.rdEndFlg = 0;						//
		gsSetModelTable.Operate.ModefyModelFlg = 0;
		
		psModel = &gsSetModelTable.Operate.rdModel;
		//删除面板中的表格控件所有行
		DeleteTableRows (gdb_panelHandle, SETM_PANEL_TABLE, 1, -1);
		
		//插入与数据表中记录数相同的行数
		InsertTableRows (gdb_panelHandle, SETM_PANEL_TABLE, 1, psModel->PotNum, VAL_USE_MASTER_CELL_TYPE);
		
		if (psModel->ModelNum > 0)
		{
			//利用数据指针逐行写入面板表格控件中
			for(char i = 1;i < psModel->PotNum +1;i++)
			{
				SetTableCellVal (gdb_panelHandle, SETM_PANEL_TABLE, MakePoint(1,i), psModel->sModPot[i-1].HigVal);
				SetTableCellVal (gdb_panelHandle, SETM_PANEL_TABLE, MakePoint(2,i), psModel->sModPot[i-1].DipVal);
			}
		}
		
		//设置油量显示值
		sprintf(tmpbuf,"模型编号:%02d,模型点数:%02d"
																,psModel->ModelNum
																,psModel->PotNum
			   													);
		SetCtrlVal(gdb_panelHandle, SETM_PANEL_TEXTMSG,tmpbuf);
	
	}
}

//显示油量数据显示表    
void	DisplayModelTabl(int panel)
{
	char 	modelnum;
	GetCtrlVal(gdb_panelHandle,SETM_PANEL_MODEL_NUM, &modelnum);  //取要设置的模型编号
	
	gsSetModelTable.Operate.rdRecNum 	= modelnum;
	gsSetModelTable.Operate.rdStartFlg 	= 1;					  //开始读操作
	
	//ReadModelFromTable(modelnum);  							  //读取数据表中的数据 
	
	return;
}

//读取数据，即刷新数据
int CVICALLBACK refreshmodlecallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
 			DisplayModelTabl(panel);						//初始化

			gsOilPara.cvi_calcOilflg = 1;					//计算油量（）

			break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.														*/
/********************************************************************************************/
int CVICALLBACK oilmodelPB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

		    HidePanel(gdb_panelHandle);								//退出窗口
			gdb_panelHandle = 0;
			break;
	}
	return 0;
}

/*******************************************************************************
 * 功    能：       取计算的面板参数.
 * 入口参数：       无
 * 出口参数： 	    无
 * 作　 　者： 	    redmornigcn
 * 创建日期： 	    2017-05-16
 * 修    改：
 * 修改日期：
 *******************************************************************************/
void    GetModelPanelVal(int panel)
{
	GetCtrlVal(panel,SETM_PANEL_SLOPE, &gsOilPara.Slope);  		//取要设置的取高度值   
	GetCtrlVal(panel,SETM_PANEL_START, &gsSetModelTable.Operate.rdModel.StartOil);  		
																//取要设置的取高度值   
	GetCtrlVal(panel,SETM_PANEL_OIL,   &gsOilPara.cvi_oilval);  
	GetCtrlVal(panel,SETM_PANEL_HIGHT, &gsOilPara.cvi_higval);  
}

/********************************************************************************************/
//计算并显示
/********************************************************************************************/
void	MathAndSetPanel(int panel)
{
	if(gsOilPara.cvi_calcOilflg)
	{
		gsOilPara.cvi_calcOilflg = 0;							//CVI开始计算油量
		
		gsOilPara.cvi_oilval = GetMathOilVal(gsOilPara.cvi_higval);
		
		SetCtrlVal(panel,SETM_PANEL_OIL,		gsOilPara.cvi_oilval);	//面板显示油量
		SetCtrlVal(panel,SETM_PANEL_OIL_CHART,	gsOilPara.cvi_oilval);	//面板显示油量
	}
	
	if(gsOilPara.cvi_calchigflg)
	{
		gsOilPara.cvi_calchigflg = 0;								//cvi开始计算高度
		
		gsOilPara.cvi_higval = GetMathHigVal(gsOilPara.cvi_oilval); 
		SetCtrlVal(panel,SETM_PANEL_HIGHT,gsOilPara.cvi_higval);	//面板高度重新赋值
	}
}

/*******************************************************************************
* 功    能： 运行参数表
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
void	InitOilPara(void)
{
	gsOilPara.cvi_calchigflg = 0;
	gsOilPara.cvi_calcOilflg = 0;
}


/********************************************************************************************/
//定时器函数
/********************************************************************************************/
int CVICALLBACK ModelTimerCallBack (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

////////////////////////////////////////////////////////////面板数据表显示				
			ModelDistoPanle();					
			
			GetModelPanelVal(panel);			//取面板参数
			
			if(sCtrl.PC.sCom->sConfig.open == 1)	//串口打开了
				MathAndSetPanel(panel);				//计算面板并显示计算值（需先调用GetModelPanelVal）
			
			break;
	}
	return 0;
}


/********************************************************************************************/
//高度转换为油量
/********************************************************************************************/
int CVICALLBACK hightToOilCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calcOilflg = 1;		//计算油量
			break;
	}
	return 0;
}

int CVICALLBACK OilToHightCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{

	
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calchigflg = 1;  		//计算高度
			break;
	}
	return 0;
}


int CVICALLBACK sclopeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calcOilflg = 1;		//计算油量

			break;
	}
	return 0;
}

int CVICALLBACK modefyHigCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calcOilflg = 1;		//计算油量

			break;
	}
	return 0;
}

int CVICALLBACK modefyCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			InstallPopup(gdb_ChildpanelHandle);			//调出设置面板
			 
			break;
	}
	return 0;
}

int CVICALLBACK SetModelCallBack (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			l_eqiupmentcode = RUN_MODEL_PARA;  		  //下发油箱模型数据
			break;
	}
	return 0;
}

int CVICALLBACK ConfigOkCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	char	modelnum,potnum;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,CHILD_MODELNUM,&modelnum);
			GetCtrlVal(panel,CHILD_POTNUM,&potnum);
			
			if(modelnum && potnum>2 && modelnum<64 && potnum < 100)  //参数有效性判断
			{
				gsSetModelTable.Operate.ModefyModelFlg = 1;		//
		
				gsSetModelTable.Operate.rdModel.ModelNum = modelnum;
				gsSetModelTable.Operate.rdModel.PotNum   = potnum;	
			}
			else
			{
				MessagePopup("错误提示","参数错误，请确认！");
			}
			
			RemovePopup(gdb_ChildpanelHandle);		 //关闭设置面板
			
			break;
	}
	return 0;
}

int CVICALLBACK ModefyModelTableCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point colrow;
	switch (event)
	{
		//当在面板中的表格控件中双击时，产生以下操作
		case EVENT_LEFT_DOUBLE_CLICK:
		
		case EVENT_COMMIT:

			
			//获得活动表格当前的行与列
			GetActiveTableCell (gdb_ChildpanelHandle, CHILD_TABLE, &colrow);
		
			//设置表格为可修改状态
			SetCtrlAttribute (gdb_ChildpanelHandle, CHILD_TABLE, ATTR_CTRL_MODE, VAL_HOT);
			//获得本行一列中数据的ID号
			//GetTableCellVal (gdb_ChildpanelHandle, CHILD_TABLE, MakePoint(1, colrow.y), &value);
		
			//将ID号作为全局变量处理
			//globalvalue = value;	
			break;
	}
	return 0;
}

int CVICALLBACK PotNumCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	char	potnum;	
	switch (event)
	{
		case EVENT_COMMIT:
					//插入与数据表中记录数相同的行数
			GetCtrlVal(panel,CHILD_POTNUM,&potnum);
			
			DeleteTableRows (gdb_ChildpanelHandle, CHILD_TABLE, 1, -1);
			InsertTableRows (gdb_ChildpanelHandle, CHILD_TABLE, 1, potnum, VAL_USE_MASTER_CELL_TYPE);
		
			break;
	}
	return 0;
}
