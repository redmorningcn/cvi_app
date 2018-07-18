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

#define  MAINPANEL                        1       /* callback function: mainPanelCB */
#define  MAINPANEL_OPEN_COM               2       /* control type: command, callback function: OpenCom1Callback */
#define  MAINPANEL_OPEN_IAP               3       /* control type: command, callback function: OpenIapPanelCallback */
#define  MAINPANEL_MAIN_TIMER             4       /* control type: timer, callback function: MainTimerCallback */
#define  MAINPANEL_FIX                    5       /* control type: ring, callback function: FixChooseCallback */
#define  MAINPANEL_TEXTMSG                6       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_2              7       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_3              8       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_4              9       /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_DECORATION             10      /* control type: deco, callback function: (none) */
#define  MAINPANEL_TEXTMSG_5              11      /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_SPLITTER               12      /* control type: splitter, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK FixChooseCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenCom1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenIapPanelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
