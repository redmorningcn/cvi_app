/*******************************************************************************
 *   Filename:       ansytime.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:
					 1、异步时钟。打开异步时钟，通过对向异步时钟管理缓冲区，添加异步超时变量，管理超时。
					 2、使用方法：
				     2.1 调用cvi_InitAnsyTimer，启动1个全局异步定时器，启动异步处理函数（CVI_ANSY_TIME_VAL中断时间）。
					 2.2 创建软定时器变量stcAnsyTimerMgr（如：ansyTime1），指定好外部计数器及外部溢出标识，和溢出阀值，确定启动类型。
					 2.3 将ansyTime1变量通过AddTimeOutVarToAnsyTimer加入定期器队列中。（注：可通过指针队列实现（有时间再改写））
					 2.4 取全局（异步）时钟，GetAnsySysTime。
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include <cvi_ansytimer.h>		 			//定时器变量

/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/
//uir文件名

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
int					g_AnsyTime = 0;
stcAnsyTimerMgr		sTimerMgr[CVI_ANSYTIME_VAR_MAX_NUM];  //异步管理区


/********************************************************************************************/
/* local Prototypes																			*/
/********************************************************************************************/

/*---------------------------------------------------------------------------*/
/* This is the Async. timer callback routine.                                */
//	异步时钟处理, 定时处理。   （redmorningcn 2017-09-23）
/*---------------------------------------------------------------------------*/
int  CVICALLBACK AnsyTimerCallback (	int reserved, int theTimerId, int event,
                       		void *callbackData, int eventData1,
                         	int eventData2)
{
	int		i;

	g_AnsyTime++;												//系统时间

	for(i =0 ;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
	{
		if(   ((sTimerMgr[i].flg & 0x01) == 0x01) 				//有效
			&&	sTimerMgr[i].poverFlg  != NULL					//指示值不空
			&&	sTimerMgr[i].Settime
			)
		{
			if(* (sTimerMgr[i].ptimeout) == 0)					//重新开始计数
				sTimerMgr[i].startflg = 1;
				
			if(sTimerMgr[i].startflg)							//开始计数启动
				(*sTimerMgr[i].ptimeout)++;

			if( 	
			   	(* (sTimerMgr[i].ptimeout)) > sTimerMgr[i].Settime //超时值有效 
				&&  sTimerMgr[i].startflg == 1
			  )	
			{
				*sTimerMgr[i].poverFlg 	= 1;					 //置超时标识
				sTimerMgr[i].startflg	= 0;					 //停止计数		
			}
		}
	}

	return 0;
}


/*---------------------------------------------------------------------------*/
//	将变量加入异步时钟。(startstus,0；外部启动；1，马上启动)  （redmorningcn 2017-09-23）
/*---------------------------------------------------------------------------*/
int AddTimeOutVarToAnsyTimer(stcAnsyTimerMgr  sAnsyTime)
{
	int		i;

	for(i =0 ;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
	{
		if(
			(sTimerMgr[i].flg & 0x01) == 0x00 					//无效
		  )
		{
			sTimerMgr[i].flg 		|= 0x01;					//置有效

			if( sAnsyTime.Settime )
				sTimerMgr[i].Settime = sAnsyTime.Settime;		//超时值有效,直接赋值
			else
				sTimerMgr[i].Settime = 3;						//无效，置3

		
			sTimerMgr[i].poverFlg 	= sAnsyTime.poverFlg;		//
			*sTimerMgr[i].poverFlg 	= 0;						//置超时标识 0
			
			sTimerMgr[i].ptimeout	= sAnsyTime.ptimeout;		//超时计数器
			*sTimerMgr[i].ptimeout	= sAnsyTime.Settime;		//

			sTimerMgr[i].startflg	= sAnsyTime.startflg;		//启动标识

			
			return 1;
		}
	}

	return 0;
}

/*---------------------------------------------------------------------------*/
//	将变量从异步时钟移除。(timeout:超时时间，*Var:信号量)  （redmorningcn 2017-09-23）
/*---------------------------------------------------------------------------*/
int DelTimeOutVarFromAnsyTimer(stcAnsyTimerMgr  sAnsyTime)
{
	int		i;

	for(i =0; i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
	{
		if(
				(sTimerMgr[i].flg & 0x01) == 0x01 				//有效
			&&  sAnsyTime.poverFlg == sTimerMgr[i].ptimeout		//值相符
		  )
		{
			sTimerMgr[i].flg 	   &= 0x00;						//置有效
			sTimerMgr[i].ptimeout	= NULL;						//超时计数器
			sTimerMgr[i].poverFlg 	= NULL;

			return 1;
		}
	}

	return 0;
}

int	ansytimerid = 0; 
/********************************************************************************************/
//cvi_InitAnsyTimer  初始化异步定时器,返回异步定时器ID
//如果异步定时器已初始化，则不重复调用（防止线程过多）。
//定时器中断时间 CVI_ANSY_TIME_VAL =0.01ms
/********************************************************************************************/
int cvi_InitAnsyTimer(void)
{
	 int	i;

	 if(ansytimerid == 0)											//避免重复打开 
	 {
		 for(i = 0;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
		 {
			 sTimerMgr[i].flg 		= 0;							//无效
			 sTimerMgr[i].Settime	= 5;							//默认超时数为5
			 sTimerMgr[i].poverFlg 	= NULL;
			 sTimerMgr[i].ptimeout 	= NULL;
		 }

	 	 ansytimerid	= NewAsyncTimer ( CVI_ANSY_TIME_VAL , -1,	//开异步定时器，5个波特率时间。
	   									1, AnsyTimerCallback, NULL);
	 }
	 return ansytimerid;
}

/*---------------------------------------------------------------------------*/
//	删除异步定时器。  （redmorningcn 2017-09-23）
/*---------------------------------------------------------------------------*/
int	DelAnsySysTimer(void)
{
	DiscardAsyncTimer(ansytimerid);
	return 1;
}

/*---------------------------------------------------------------------------*/
//	取异步时钟值。(timeout:超时时间，*Var:信号量)  （redmorningcn 2017-09-23）
/*---------------------------------------------------------------------------*/
int	GetAnsySysTime(void)
{
	return	g_AnsyTime;
}

