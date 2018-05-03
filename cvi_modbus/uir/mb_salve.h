/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MB_SLAVE                         1       /* callback function: mb_SlavePanelCB */
#define  MB_SLAVE_BUF                     2       /* control type: textBox, callback function: (none) */
#define  MB_SLAVE_INFO                    3       /* control type: textBox, callback function: (none) */
#define  MB_SLAVE_DECORATION_3            4       /* control type: deco, callback function: (none) */
#define  MB_SLAVE_TEXTMSG_2               5       /* control type: textMsg, callback function: (none) */
#define  MB_SLAVE_DECORATION              6       /* control type: deco, callback function: (none) */
#define  MB_SLAVE_LEN                     7       /* control type: numeric, callback function: (none) */
#define  MB_SLAVE_ADDR                    8       /* control type: numeric, callback function: (none) */
#define  MB_SLAVE_ID                      9       /* control type: numeric, callback function: (none) */
#define  MB_SLAVE_SLAVE                   10      /* control type: textMsg, callback function: (none) */
#define  MB_SLAVE_TEXTMSG                 11      /* control type: textMsg, callback function: (none) */
#define  MB_SLAVE_FORMAT                  12      /* control type: ring, callback function: (none) */
#define  MB_SLAVE_TEXTMSG_4               13      /* control type: textMsg, callback function: (none) */
#define  MB_SLAVE_TIMER                   14      /* control type: timer, callback function: MBSlaveTimerCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK mb_SlavePanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MBSlaveTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
