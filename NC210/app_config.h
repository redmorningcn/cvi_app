#ifndef	CVI_APP_CONFIG_H
#define	CVI_APP_CONFIG_H

#include <cvirte.h>
#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

//CSNC�豸��ַ
#define		ADDR_SET		(0xC2)		//�����豸��ַ
#define		ADDR_PC			(0xCA)		//pc����ַ
#define		ADDR_FIX		(0x84)	    //װ�õ�ַ	

//CSNC֡��ʽ		
#define IAP_FRAME_CODE              0x0a      /* IAP ����֡������     */
#define SET_FRAME_CODE              0x02      /* SET ���ÿ�����       */
#define RECORD_FRAME_CODE           0x00      /* ���ݼ�¼csnc������    */     
		
#ifdef __cplusplus
    }
#endif

#endif  
