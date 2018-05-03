#include <ansi_c.h>
#include    "includes.h"              



//将单词转换为指定格式的数据。
short	wordtodata(char *word,char 	format)
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
				if(  ( (word[i]>('a'-1))&& (word[i]<('f'+1)))  
				  || ((word[i]>('A'-1))&& (word[i]<('F'+1))) 
				  || ( (word[i]>('0'-1))&& (word[i]<('9'+1)))  
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
		if(*p != ',' && *p != ' ' && (i +1) < strlen(string) )	//数据转换
		{
			if(wordlen < 16)
			{
				word[wordlen++] = *p;
			}
			p++;  

		}
		else
		{
			if((i +1) == strlen(string))	//结尾处理
				word[wordlen++] = *p;		
			
			word[wordlen++] = '\0';
			
			buf[buflen++] = (short)wordtodata(word,format);
			
			wordlen = 0;
			p++;  
		}
	}
	return	buflen;
}










