#include <ansi_c.h>
#include <userint.h>
#include "modbus_poll.h"
#include "mb_salve.h"
#include "uirbsp_mb_salve.h"
#include "includes.h"


//定义面板名称
#define		UIR_SLAVE_NAME	"mb_salve.uir"

//全局变量
int	    	gSlavePanelHandle = 0;
extern	 	int panelHandle;						//主

//定义从机控制字。
strMBSlave	gsMBSlave;								//从机控制字

//打开salve面板，关闭主面板。
int CVICALLBACK OpenSlaveCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gSlavePanelHandle	= LoadPanel (0,UIR_SLAVE_NAME, MB_SLAVE);
				DisplayPanel (gSlavePanelHandle);						//显示设置面板	
				HidePanel (panelHandle);								//隐藏设置面板			
		break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.关闭salve面板，显示主面板。						    */
/********************************************************************************************/
int CVICALLBACK mb_SlavePanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gSlavePanelHandle);								//退出窗口
			gSlavePanelHandle = 0;										//
			
			DisplayPanel(panelHandle);

			break;
		}
	return 0;
}

//将单词转换为指定格式的数据。
int	wordtodata(char *word,char 	format)
{
	char	wordlen;
	char	multy;			//系数基准	
	int		tmp;
	int		data;
	int		i;
	
	switch(format)
	{
		case 0:
			multy =10;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '9'){
					//MessagePopup ("ERR MEssage", "有大于9或小0的字符");
					
					return 0;
				}
			break;
		case 1:
			multy = 16;
			
			for(i = 0;i < strlen(word);i++)
				if(  ( (word[i]>('a'-1))&& (word[i]>('f'+1)))  
				  || ((word[i]>('A'-1))&& (word[i]>('F'+1))) 
				  || ( (word[i]>('0'-1))&& (word[i]>('9'+1)))  
				  == 0
				 ){
					//MessagePopup ("ERR MEssage", "有非16进制字符");
					
					return 0;
				}
			break;
		case 2:
			multy = 8;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '7'){
					//MessagePopup ("ERR MEssage", "有大于7或小0的字符");
					
					return 0;
				}			
			break;
		case 3:
			multy = 2;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '1'){
					//MessagePopup ("ERR MEssage", "有大于1或小0的字符");
					
					return 0;
				}			
			break;
		default:
			multy = 10;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '9'){
					//MessagePopup ("ERR MEssage", "有大于9或小0的字符");
					
					return 0;
				}
	}

	tmp 	= 1;
	data 	= 0;
	wordlen	= (char)strlen(word);

	while(wordlen)
	{
		data += tmp * (word[--wordlen]-'0');
		tmp  *= multy;
	}
	
	return	data;
}
 
//按指定格式，字符串转换为数组（已空格或,分段）
int	stringtobuf(char *string,short *buf,char 	format)				//按指定格式，转换数据。
{
	char	word[16];
	char	wordlen;
	int		buflen;
	int		i = 0;
	char	*p = string;
	
	wordlen 	= 0;
	buflen 		= 0;
	
	for(i = 0;i < strlen(string);i++)
	{
		if(*p == ',' || *p == ' ' )	//数据转换
		{
			word[wordlen++] = '\0';
			
			buf[buflen++] = (short)wordtodata(word,format);
			
			wordlen = 0;
			p++;  
		}
		else
		{
			if(wordlen < 16)
			{
				word[wordlen++] = *p;
			}
			p++;  
		}
	}
	return	buflen;
}

//显示面板值
void CVI_MBSlavePanelHandle(int panel)
{
	char	string[512];
	int		buflen;
	
	if(gSlavePanelHandle == 0)												//面板打开状态下，才执行函数处理
		return;
	
	if(gsMBSlave.writeflg == 0)
	{
		GetCtrlVal(panel,MB_SLAVE_ID,		&gsMBSlave.node) ;				//取设备ID
		GetCtrlVal(panel,MB_SLAVE_ADDR,		&gsMBSlave.addr) ;				//取数据地址
		GetCtrlVal(panel,MB_SLAVE_FORMAT,	&gsMBSlave.format) ;			//取数据地址
	
		GetCtrlVal(panel,MB_SLAVE_BUF,string);								//取数据区
		buflen = stringtobuf(string,&gsMBSlave.buf[gsMBSlave.addr],gsMBSlave.format);//将字符串改为数组	
	}
	
	if(gsMBSlave.writeflg )
	{
		int	i;
		char	word[16];
		gsMBSlave.writeflg  = 0;
		
		gsMBSlave.len  = (char)(MB_ChTbl[0].RxFrameData[5]+MB_ChTbl[0].RxFrameData[4]*256);		//
		gsMBSlave.addr = (char)(MB_ChTbl[0].RxFrameData[3]+MB_ChTbl[0].RxFrameData[2]*256); 
		SetCtrlVal(panel,MB_SLAVE_ADDR,gsMBSlave.addr);
		SetCtrlVal(panel,MB_SLAVE_LEN,gsMBSlave.len);

		string[0] = '\0'; 
		for(i = 0; i<gsMBSlave.len;i++ )
		{
			word[0] = '\0';
			switch(gsMBSlave.format)
			{
				case 0:
					sprintf(word,"%d,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;
				case 1:
					sprintf(word,"%x,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;		
				case 2:
					sprintf(word,"%0,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;
				case 3:
					sprintf(word,"%b,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;						
				default:
					sprintf(word,"%d,",gsMBSlave.buf[gsMBSlave.addr+i]);
			}
			strcat(string,word);
		}
		if(strlen(string))
		{
			string[strlen(string) - 1]  =  '\0' ;
			ResetTextBox(panel, MB_SLAVE_BUF,"");
			SetCtrlVal (panel, MB_SLAVE_BUF,  string);					//接收到的数据打印出来
		}
	}
}


int CVICALLBACK MBSlaveTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_MBSlavePanelHandle(panel); 
			break;
	}
	return 0;
}
