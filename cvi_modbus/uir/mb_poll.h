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

#define  MB_POLL                          1       /* callback function: mb_PollPanelCB */
#define  MB_POLL_BUF                      2       /* control type: textBox, callback function: (none) */
#define  MB_POLL_INFO                     3       /* control type: textBox, callback function: (none) */
#define  MB_POLL_DECORATION_3             4       /* control type: deco, callback function: (none) */
#define  MB_POLL_DECORATION_2             5       /* control type: deco, callback function: (none) */
#define  MB_POLL_TEXTMSG_2                6       /* control type: textMsg, callback function: (none) */
#define  MB_POLL_TEXTMSG_3                7       /* control type: textMsg, callback function: (none) */
#define  MB_POLL_DECORATION               8       /* control type: deco, callback function: (none) */
#define  MB_POLL_NUM                      9       /* control type: numeric, callback function: (none) */
#define  MB_POLL_ADDR                     10      /* control type: numeric, callback function: (none) */
#define  MB_POLL_ID                       11      /* control type: numeric, callback function: (none) */
#define  MB_POLL_SLAVE                    12      /* control type: textMsg, callback function: (none) */
#define  MB_POLL_DOFLG                    13      /* control type: binary, callback function: (none) */
#define  MB_POLL_RUN                      14      /* control type: command, callback function: RunCallback */
#define  MB_POLL_AUTOFLG                  15      /* control type: radioButton, callback function: (none) */
#define  MB_POLL_SPLITTER                 16      /* control type: splitter, callback function: (none) */
#define  MB_POLL_TEXTMSG                  17      /* control type: textMsg, callback function: (none) */
#define  MB_POLL_FORMAT                   18      /* control type: ring, callback function: (none) */
#define  MB_POLL_TEXTMSG_4                19      /* control type: textMsg, callback function: (none) */
#define  MB_POLL_TIMER                    20      /* control type: timer, callback function: MBPollTimerCallback */
#define  MB_POLL_AUTOTIME                 21      /* control type: timer, callback function: AutoRunTimerCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AutoRunTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mb_PollPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MBPollTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
