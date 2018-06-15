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


/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "send_IAP.h"

stcIapStart gsIapStart;		//IAP����


stcIAPPara	gsIapPara =
{
	0x10,
	0x20,
	0,
	0,
	0,
	0
};

/*******************************************************************************************
���ݷ��ͣ� 	SendCsnrIapDataDeal
�����ݰ���Э���ʽ���͡�
*******************************************************************************************/
void	SendCsnrIapDataDeal(char *buf,int len)
{
	memcpy(sCtrl.PC.wr,buf,len);							//���ݿ����������ַ�		
	sCtrl.PC.ConnCtrl.sendlen 		= len;					//��������������

	sCtrl.PC.ConnCtrl.sourceaddr	= 0xcA;					//Դ��ַ
	sCtrl.PC.ConnCtrl.DestAddr		= HOST_ADDR; 				//Ŀ�ĵ�ַ
	sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 				//���
	sCtrl.PC.ConnCtrl.FrameCode		= IAP_FRAME_CODE;		//֡������	

	sCtrl.PC.ConnCtrl.SendFlg 		= 1;					//�������� ��CVI_bsComm,���̣߳�
} 	

/*******************************************************************************************
��ʼ��IAP�ṹ��
*******************************************************************************************/
void InitIPACtrl(void)
{
	gsIapCtrl.echoflg 	= 0;
	gsIapCtrl.endflg 	= 0;
	gsIapCtrl.filesize 	= gsBinFileInfo.size;
	gsIapCtrl.recvnum	= 0;
	gsIapCtrl.resendflg = 0;
	gsIapCtrl.sendnum	= 0;
	gsIapCtrl.sendsize  = 0;
	gsIapCtrl.startflg 	= 0;
}


/*******************************************************************************************
���ݷ��ͣ� SendFileData()
*******************************************************************************************/
void	SendIapTask(void)
{
	static	char	buf[256]; 
	static	int		len = 0;
	static	int 	resendtimes = 0;
	int		per;
	short	tmp16;
	
	static	int	sendtime = 0;
	static	uint64_t     crc32   = 0x00000000FFFFFFFFL;


	if( gsIapCtrl.sendeable == 0)
		return;	
	
	if(			gsIapCtrl.startflg
			|| 	gsIapCtrl.echoflg
			|| 	gsIapCtrl.resendflg 
	  )	
	{//
		if(gsIapCtrl.startflg)						//��ʼ���أ����Ϳ�ʼ����ָ��
		{
			//�����������ļ�crc32У��   180326
			crc32   = 0x00000000FFFFFFFFL; 			//��ֵ
			gsBinFileInfo.deallen 	= 0;			//��ֵ
			while(gsBinFileInfo.deallen < gsBinFileInfo.size)
			{
				int readlen = ReadFileData(gsBinFileInfo.deallen,&buf[0],128);//���ļ��ж�ȡ����
				gsBinFileInfo.deallen += readlen;
				
				crc32   = GetCrc32Chk( crc32, buf, readlen);
			}
			//������180326 
			
			InitIPACtrl();							//��ʼ�����Ʊ���
			
			gsIapPara.softsize 		= gsBinFileInfo.size;
			gsBinFileInfo.deallen 	= 0;
			
			len = 0;

			tmp16 = 0x01;							//��ʼָ��
			memcpy(&buf[len],(char *)&tmp16,sizeof(tmp16));
			len += sizeof(tmp16);
			
			memcpy(&buf[len],(char *)&gsIapPara,sizeof(gsIapPara));
			len +=sizeof(gsIapPara);
			
			//����crcУ�飨ȫ�ļ��� 180316
			crc32   = crc32 ^ 0x00000000FFFFFFFFL;
    		crc32  &= 0x00000000FFFFFFFFL;				
			
			memcpy(&buf[len],(char *)&crc32,sizeof(uint32));
			len += sizeof(uint32);			
			//����crc
			
			//SendCsnrIapDataDeal(buf,len);											//��������
			
			int i = 100000;
			while(i--);
			SendCsnrIapDataDeal(buf,len);											//��������

			sendtime = 	g_sysIaptime; ;
			
		}else if(gsIapCtrl.echoflg)												//�յ���ȷ��Ӧ�𣬼������ݷ���
		{
			gsIapCtrl.echoflg 	= 0;

			len = 0;

			resendtimes = 10;		//�ط�����
			sendtime = 	g_sysIaptime; ;
				
			printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"�������:%03d\r\n",gsIapCtrl.sendnum);	

			if(gsBinFileInfo.deallen <gsBinFileInfo.size)						//�ѳ����ļ�����С���ļ�����
			{
				tmp16 = 0x02;
				memcpy(&buf[len],(char *)&tmp16,sizeof(tmp16));   				//ָ��
				len += sizeof(tmp16);
				
				memcpy(&buf[len],(char *)&gsIapCtrl.sendnum,sizeof(tmp16));   	//��ţ��ڽ������ۼ�
				len += sizeof(gsIapCtrl.sendnum);
					
				int readlen = ReadFileData(gsBinFileInfo.deallen,&buf[len],128);//���ļ��ж�ȡ����
		 		len +=  readlen;
				
				per = SetFileDealPer();
				SetCtrlVal (gBinFilePanelHandle, IAP_PANEL_PRE, per);			//���ðٷֱ�(���ؽ���) 
				
				SendCsnrIapDataDeal(buf,len);									//��������
				
				gsBinFileInfo.deallen += readlen;								//�Ѵ������� �����ۼ�len
				
				if(gsBinFileInfo.deallen >= gsBinFileInfo.size)					//���ݷ������
				{
					//i = 0;
				}
				
				gsIapPara.framenum 		= gsIapCtrl.sendnum;					//��¼�ѷ���� 

			}
			else	//���ݷ�����ɣ����ͽ�����ʾ
			{
				tmp16 = 0x03;													//���ͽ���ָ��
				memcpy(&buf[len],(char *)&tmp16,sizeof(tmp16));   				//ָ��
				len += sizeof(tmp16); 
				resendtimes = 0;		//�ط�����

				memcpy(&buf[len],(char *)&gsIapPara,sizeof(gsIapPara));
				len +=sizeof(gsIapPara);				
				gsIapPara.framenum  = 0;									
				
				//����crcУ�飨ȫ�ļ��� 180316
				crc32   = crc32 ^ 0x00000000FFFFFFFFL;
        		crc32  &= 0x00000000FFFFFFFFL;				
				
				memcpy(&buf[len],(char *)&crc32,sizeof(uint32));
				len += sizeof(uint32);
				//����crc
				printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"�������:%03d�����ݷ������\r\n",gsIapCtrl.sendnum);	

				SendCsnrIapDataDeal(buf,len);									//��������
				
			}
		}
		else if(gsIapCtrl.resendflg)											//δ�յ���ȷָ��ط�
		{
			 gsIapCtrl.resendflg = 0;
			 SendCsnrIapDataDeal(buf,len);										//���������ϴε�����
		}
	}
	
	//�ط�����
	if(  	g_sysIaptime - sendtime > 100*10	//1s���ط�ʱ����ƣ�
		&&  resendtimes							//�ط���������1
		)
	{
		sendtime =  g_sysIaptime;
		resendtimes--;
		
		printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"�������:%03dR\r\n",gsIapCtrl.sendnum);	

		SendCsnrIapDataDeal(buf,len);											//���������ϴε�����       
	}     
																																											 
	return;
}

/*******************************************************************************************
��ʼ��IAP��������
*******************************************************************************************/
void	IapRecTask(void)
{
	unsigned char	tmp16;
	
	if(	sCtrl.PC.RxCtrl.recvflg 			&&		//�����ݽ���
		sCtrl.PC.RxCtrl.DestAddr == MY_ADDR &&		//��ַ��Ч
		sCtrl.PC.RxCtrl.FrameCode== IAP_FRAME_CODE	//IAPָ֡��
	  )   			//���յ�����
	{
		sCtrl.PC.RxCtrl.recvflg = 0;				//������ɱ�ʶ
		
		memcpy((uint8 *)&tmp16,sCtrl.PC.rd,sizeof(tmp16));	//����	

		gsIapCtrl.endflg  	= 0;
		gsIapCtrl.resendflg	= 0;
		gsIapCtrl.echoflg   = 0;
		
		if(tmp16 == 1 || tmp16 == 2) 					//��������
		{
			if(tmp16 == 1)								//��ʼ���ͣ���������
			{
				gsIapCtrl.echoflg = 1;	
				
				memcpy((uint8 *)&gsIapStart,&sCtrl.PC.rd[2],sizeof(gsIapStart));	//����Ӧ��	
				
				//printf("\r\n��������յ������: %d",gsIapStart.CurNum);
																			//�ϵ�����
				if(
							gsIapStart.CurNum   							//Ӧ��֡��Ų�Ϊ�㣬��ʼ�ϵ�����
						&&	gsIapStart.SoftSize == gsBinFileInfo.size		//�ļ���С��ͬ
				  )				
				{
					gsIapCtrl.sendnum  		= gsIapStart.CurNum;			//�������			
					gsIapCtrl.sendsize 		= gsIapStart.CurNum * 128;		//�ѷ�����
					gsBinFileInfo.deallen  	= gsIapStart.CurNum * 128;  	//�ļ��Ѵ�����
				}
			}
			else
			{
				memcpy((uint8 *)&gsIapCtrl.recvnum,&sCtrl.PC.rd[2],sizeof(gsIapCtrl.recvnum));	   //ȡ�������
				if(gsIapCtrl.recvnum == gsIapCtrl.sendnum)  
				{
					gsIapCtrl.sendnum++;
					gsIapCtrl.echoflg 	= 1;			  //����������ȷ��Ӧ���ʾ��1
				}else{
					gsIapCtrl.resendflg	= 1;			  //�������ش����ط���ʾ��1
				}
			}
		} else if(tmp16 == 3 || tmp16 == 4)
		{
			gsIapCtrl.endflg = 1;
		}
		
		if(sCtrl.PC.rd[1])
			printftext(gBinFilePanelHandle,IAP_PANEL_INFOTEXTBOX,"\r\nͨѶ�쳣�����룺%0x\r\n",sCtrl.PC.rd[1]);	

			//printf("\r\nͨѶ�쳣�����룺%0x ",sCtrl.PC.rd[1]);
	}
}
