#ifndef	INCLUDES_H_
#define	INCLUDES_H_   0

#include  "stdint.h"

typedef	unsigned char  uint8;					/* �޷���8λ���ͱ���						*/
typedef	    	 char  int8;					/* �з���8λ���ͱ���						*/
//typedef	unsigned char  uint8;				/* �޷���8λ���ͱ���						*/
//typedef	signed	 char  int8;				/* �з���8λ���ͱ���						*/
typedef	unsigned short uint16;					/* �޷���16λ���ͱ���						*/
typedef	signed	 short int16;					/* �з���16λ���ͱ���						*/
typedef	unsigned int   uint32;					/* �޷���32λ���ͱ���						*/
typedef	signed	 int   int32;					/* �з���32λ���ͱ���						*/
typedef	float		   fp32;					/* �����ȸ�������32λ���ȣ�					*/
typedef	double		   fp64;					/* ˫���ȸ�������64λ���ȣ�					*/

typedef	unsigned char  UINT8;					/* �޷���8λ���ͱ���						*/
typedef	signed	 char  INT8;					/* �з���8λ���ͱ���						*/
typedef	unsigned short UINT16;					/* �޷���16λ���ͱ���						*/
typedef	signed	 short INT16;					/* �з���16λ���ͱ���						*/
typedef	unsigned int   UINT32;					/* �޷���32λ���ͱ���						*/
typedef	signed	 int   INT32;					/* �з���32λ���ͱ���						*/
typedef	float		   FP32;					/* �����ȸ�������32λ���ȣ�					*/
typedef	double		   FP64;					/* ˫���ȸ�������64λ���ȣ�					*/

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

