#ifndef	INCLUDES_H_
#define	INCLUDES_H_   0

#include  "stdint.h"

typedef	unsigned char  uint8;					/* 无符号8位整型变量						*/
typedef	    	 char  int8;					/* 有符号8位整型变量						*/
//typedef	unsigned char  uint8;				/* 无符号8位整型变量						*/
//typedef	signed	 char  int8;				/* 有符号8位整型变量						*/
typedef	unsigned short uint16;					/* 无符号16位整型变量						*/
typedef	signed	 short int16;					/* 有符号16位整型变量						*/
typedef	unsigned int   uint32;					/* 无符号32位整型变量						*/
typedef	signed	 int   int32;					/* 有符号32位整型变量						*/
typedef	float		   fp32;					/* 单精度浮点数（32位长度）					*/
typedef	double		   fp64;					/* 双精度浮点数（64位长度）					*/

typedef	unsigned char  UINT8;					/* 无符号8位整型变量						*/
typedef	signed	 char  INT8;					/* 有符号8位整型变量						*/
typedef	unsigned short UINT16;					/* 无符号16位整型变量						*/
typedef	signed	 short INT16;					/* 有符号16位整型变量						*/
typedef	unsigned int   UINT32;					/* 无符号32位整型变量						*/
typedef	signed	 int   INT32;					/* 有符号32位整型变量						*/
typedef	float		   FP32;					/* 单精度浮点数（32位长度）					*/
typedef	double		   FP64;					/* 双精度浮点数（64位长度）					*/

typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;  /* Read Only */
typedef signed short const sc16;  /* Read Only */
typedef signed char  const sc8;   /* Read Only */

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed long  const vsc32;  /* Read Only */
typedef volatile signed short const vsc16;  /* Read Only */
typedef volatile signed char  const vsc8;   /* Read Only */

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;  /* Read Only */
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;   /* Read Only */

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */


#endif

