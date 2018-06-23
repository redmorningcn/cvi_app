#ifndef	CVI_APP_CONFIG_H
#define	CVI_APP_CONFIG_H

#include <cvirte.h>
#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

//CSNC设备地址
#define		ADDR_SET		(0xC2)		//设置设备地址
#define		ADDR_PC			(0xCA)		//pc机地址
#define		ADDR_FIX		(0x84)	    //装置地址	

//CSNC帧格式		
#define IAP_FRAME_CODE              0x0a      /* IAP 下载帧控制字     */
#define SET_FRAME_CODE              0x02      /* SET 设置控制字       */
#define RECORD_FRAME_CODE           0x00      /* 数据记录csnc控制字    */     
		
#ifdef __cplusplus
    }
#endif

#endif  
