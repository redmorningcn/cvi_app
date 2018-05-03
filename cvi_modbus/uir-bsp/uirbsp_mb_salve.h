#ifndef  _uirbsp_mb_slave_h_
#define  _uirbsp_mb_slave_h_

/********************************************************************************************/
/* 串口配置结构体																				    */
/********************************************************************************************/
typedef struct	_strMBSlave_
{
	char	node;			//端口
	char	addr;			//地址 
	char	format;			//显示格式
	char	len;
	
	int		readflg:1;		//读寄存器标识
	int 	writeflg:1;		//写寄存器标识
	int  	tmpflg:6;		//
	
	short	buf[512];		//备用
}strMBSlave;				//串口配置结构体


#endif
