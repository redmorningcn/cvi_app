/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    
					 
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#include "databaseoperate.h"

/*******************************************************************************
* CONSTANTS
*/

/*******************************************************************************
* GLOBAL VARIABLES
*/
int		g_cvihdbc_handel = 0;

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

/*******************************************************************************
* 名    称： ConnectDB
* 功    能： 连接数据库
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改： 2017-12-20  //防多次调用
* 修改日期：
* 备    注： 和数据库建立连接。ODBC 数据源(32 位)支持，提供DNS
*******************************************************************************/
void	ConnectDB(void)
{
	//建立数据库联接，并获得联接句柄
	char	dsnbuf[64];
	
	if(g_cvihdbc_handel == 0)					//防止重复调用
	{
		DBInit(DB_INIT_MULTITHREADED);			//多线程
	
		sprintf(dsnbuf,"DSN=%s",ODBC_DNS);
		g_cvihdbc_handel = DBConnect (dsnbuf);
	}
}

/*******************************************************************************
* 名    称： CloseDB
* 功    能： 连接数据库
* 入口参数： 无
* 出口参数： 无
* 作　 　者：redmorningcn.
* 创建日期： 2017-09-05
* 修    改： 2017-12-20    //防多次调用，断开连接后，连接号置0
* 修改日期：
* 备    注： 
*******************************************************************************/
void	CloseDB(void)
{
	//当退出应用程序时，关闭数据库连接
	if( g_cvihdbc_handel )
	{
		DBDisconnect (g_cvihdbc_handel); 	//断开连接
		g_cvihdbc_handel = 0;				//连接号设初值
	}
}

