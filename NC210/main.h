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
#define  MAINPANEL_SPEED_CALI             2       /* control type: command, callback function: OpenSpeedCaliCallback */
#define  MAINPANEL_TEST                   3       /* control type: command, callback function: OpenLKJTestCallback */
#define  MAINPANEL_IAP                    4       /* control type: command, callback function: OpenIapPanelCallback */
#define  MAINPANEL_LOCO_CALI              5       /* control type: command, callback function: OpenLocoCaliCallback */
#define  MAINPANEL_OPEN_SETPARA           6       /* control type: command, callback function: OpenSetParaPanelCallback */
#define  MAINPANEL_MAIN_TIMER             7       /* control type: timer, callback function: MainTimerCallback */
#define  MAINPANEL_OPEN_COM               8       /* control type: command, callback function: OpenCom1Callback */
#define  MAINPANEL_PICTURE                9       /* control type: picture, callback function: (none) */
#define  MAINPANEL_TEXTMSG                10      /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_2              11      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK mainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenCom1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenIapPanelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenLKJTestCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenLocoCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenSetParaPanelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenSpeedCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
