#ifndef  _uirbsp_mb_poll_h_
#define  _uirbsp_mb_poll_h_

/********************************************************************************************/
/* 串口配置结构体																				    */
/********************************************************************************************/
typedef struct	_strMBPoll_
{
	char	node;			//端口
	char	addr;			//地址 
	char	format;			//显示格式
	char	len;
	
	int		readflg:1;		//读寄存器标识
	int 	writeflg:1;		//写寄存器标识
	int		autoflg:1;		//自动操作
	int  	tmpflg:6;		//
	
	short	buf[512];		//备用
}strMBPoll;					//串口配置结构体

#endif
