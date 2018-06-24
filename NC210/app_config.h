#ifndef	CVI_APP_CONFIG_H
#define	CVI_APP_CONFIG_H

#include <cvirte.h>
#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

//CSNC�豸��ַ
#define		ADDR_SET		(0xC2)		/* �����豸��ַ		*/
#define		ADDR_PC			(0xCA)		/* pc����ַ			*/
#define		ADDR_FIX		(0x84)	    /* װ�õ�ַ			*/

//CSNC֡��ʽ		
#define IAP_FRAME_CODE       0x0a      /* IAP ����֡������     */
#define SET_FRAME_CODE       0x02      /* SET ���ÿ�����       */
#define RECORD_FRAME_CODE    0x00      /* ���ݼ�¼csnc������   */   
		
//modbus node
#define	NODE_SPEED1			(0x01)	   /* �ٶȼ���1 node��ַ */
#define	NODE_SPEED2			(0x02)	   /* �ٶȼ���2 node��ַ */
#define	NODE_SPEED3			(0x03)	   /* �ٶȼ���3 node��ַ */
#define	NODE_LOCO			(0x04)	   /* ��������  node��ַ */
		
		
#ifdef __cplusplus
    }
#endif

#endif  
