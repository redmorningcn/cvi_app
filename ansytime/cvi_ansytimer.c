/*******************************************************************************
 *   Filename:       ansytime.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:
					 1���첽ʱ�ӡ����첽ʱ�ӣ�ͨ�������첽ʱ�ӹ�������������첽��ʱ����������ʱ��
					 2��ʹ�÷�����
				     2.1 ����cvi_InitAnsyTimer������1��ȫ���첽��ʱ���������첽��������CVI_ANSY_TIME_VAL�ж�ʱ�䣩��
					 2.2 ������ʱ������stcAnsyTimerMgr���磺ansyTime1����ָ�����ⲿ���������ⲿ�����ʶ���������ֵ��ȷ���������͡�
					 2.3 ��ansyTime1����ͨ��AddTimeOutVarToAnsyTimer���붨���������С���ע����ͨ��ָ�����ʵ�֣���ʱ���ٸ�д����
					 2.4 ȡȫ�֣��첽��ʱ�ӣ�GetAnsySysTime��
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include <cvi_ansytimer.h>		 			//��ʱ������

/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/
//uir�ļ���

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
int					g_AnsyTime = 0;
stcAnsyTimerMgr		sTimerMgr[CVI_ANSYTIME_VAR_MAX_NUM];  //�첽������


/********************************************************************************************/
/* local Prototypes																			*/
/********************************************************************************************/

/*---------------------------------------------------------------------------*/
/* This is the Async. timer callback routine.                                */
//	�첽ʱ�Ӵ���, ��ʱ����   ��redmorningcn 2017-09-23��
/*---------------------------------------------------------------------------*/
int  CVICALLBACK AnsyTimerCallback (	int reserved, int theTimerId, int event,
                       		void *callbackData, int eventData1,
                         	int eventData2)
{
	int		i;

	g_AnsyTime++;												//ϵͳʱ��

	for(i =0 ;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
	{
		if(   ((sTimerMgr[i].flg & 0x01) == 0x01) 				//��Ч
			&&	sTimerMgr[i].poverFlg  != NULL					//ָʾֵ����
			&&	sTimerMgr[i].Settime
			)
		{
			if(* (sTimerMgr[i].ptimeout) == 0)					//���¿�ʼ����
				sTimerMgr[i].startflg = 1;
				
			if(sTimerMgr[i].startflg)							//��ʼ��������
				(*sTimerMgr[i].ptimeout)++;

			if( 	
			   	(* (sTimerMgr[i].ptimeout)) > sTimerMgr[i].Settime //��ʱֵ��Ч 
				&&  sTimerMgr[i].startflg == 1
			  )	
			{
				*sTimerMgr[i].poverFlg 	= 1;					 //�ó�ʱ��ʶ
				sTimerMgr[i].startflg	= 0;					 //ֹͣ����		
			}
		}
	}

	return 0;
}


/*---------------------------------------------------------------------------*/
//	�����������첽ʱ�ӡ�(startstus,0���ⲿ������1����������)  ��redmorningcn 2017-09-23��
/*---------------------------------------------------------------------------*/
int AddTimeOutVarToAnsyTimer(stcAnsyTimerMgr  sAnsyTime)
{
	int		i;

	for(i =0 ;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
	{
		if(
			(sTimerMgr[i].flg & 0x01) == 0x00 					//��Ч
		  )
		{
			sTimerMgr[i].flg 		|= 0x01;					//����Ч

			if( sAnsyTime.Settime )
				sTimerMgr[i].Settime = sAnsyTime.Settime;		//��ʱֵ��Ч,ֱ�Ӹ�ֵ
			else
				sTimerMgr[i].Settime = 3;						//��Ч����3

		
			sTimerMgr[i].poverFlg 	= sAnsyTime.poverFlg;		//
			*sTimerMgr[i].poverFlg 	= 0;						//�ó�ʱ��ʶ 0
			
			sTimerMgr[i].ptimeout	= sAnsyTime.ptimeout;		//��ʱ������
			*sTimerMgr[i].ptimeout	= sAnsyTime.Settime;		//

			sTimerMgr[i].startflg	= sAnsyTime.startflg;		//������ʶ

			
			return 1;
		}
	}

	return 0;
}

/*---------------------------------------------------------------------------*/
//	���������첽ʱ���Ƴ���(timeout:��ʱʱ�䣬*Var:�ź���)  ��redmorningcn 2017-09-23��
/*---------------------------------------------------------------------------*/
int DelTimeOutVarFromAnsyTimer(stcAnsyTimerMgr  sAnsyTime)
{
	int		i;

	for(i =0; i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
	{
		if(
				(sTimerMgr[i].flg & 0x01) == 0x01 				//��Ч
			&&  sAnsyTime.poverFlg == sTimerMgr[i].ptimeout		//ֵ���
		  )
		{
			sTimerMgr[i].flg 	   &= 0x00;						//����Ч
			sTimerMgr[i].ptimeout	= NULL;						//��ʱ������
			sTimerMgr[i].poverFlg 	= NULL;

			return 1;
		}
	}

	return 0;
}

int	ansytimerid = 0; 
/********************************************************************************************/
//cvi_InitAnsyTimer  ��ʼ���첽��ʱ��,�����첽��ʱ��ID
//����첽��ʱ���ѳ�ʼ�������ظ����ã���ֹ�̹߳��ࣩ��
//��ʱ���ж�ʱ�� CVI_ANSY_TIME_VAL =0.01ms
/********************************************************************************************/
int cvi_InitAnsyTimer(void)
{
	 int	i;

	 if(ansytimerid == 0)											//�����ظ��� 
	 {
		 for(i = 0;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
		 {
			 sTimerMgr[i].flg 		= 0;							//��Ч
			 sTimerMgr[i].Settime	= 5;							//Ĭ�ϳ�ʱ��Ϊ5
			 sTimerMgr[i].poverFlg 	= NULL;
			 sTimerMgr[i].ptimeout 	= NULL;
		 }

	 	 ansytimerid	= NewAsyncTimer ( CVI_ANSY_TIME_VAL , -1,	//���첽��ʱ����5��������ʱ�䡣
	   									1, AnsyTimerCallback, NULL);
	 }
	 return ansytimerid;
}

/*---------------------------------------------------------------------------*/
//	ɾ���첽��ʱ����  ��redmorningcn 2017-09-23��
/*---------------------------------------------------------------------------*/
int	DelAnsySysTimer(void)
{
	DiscardAsyncTimer(ansytimerid);
	return 1;
}

/*---------------------------------------------------------------------------*/
//	ȡ�첽ʱ��ֵ��(timeout:��ʱʱ�䣬*Var:�ź���)  ��redmorningcn 2017-09-23��
/*---------------------------------------------------------------------------*/
int	GetAnsySysTime(void)
{
	return	g_AnsyTime;
}

