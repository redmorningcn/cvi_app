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
#define  MAINPANEL_OPEN_SETPARA_5         2       /* control type: command, callback function: (none) */
#define  MAINPANEL_OPEN_SETPARA_4         3       /* control type: command, callback function: (none) */
#define  MAINPANEL_OPEN_SETPARA_3         4       /* control type: command, callback function: (none) */
#define  MAINPANEL_OPEN_SETPARA_2         5       /* control type: command, callback function: (none) */
#define  MAINPANEL_OPEN_SETPARA           6       /* control type: command, callback function: OpenSetParaPanelCallback */
#define  MAINPANEL_MAIN_TIMER             7       /* control type: timer, callback function: MainTimerCallback */
#define  MAINPANEL_OPEN_COM               8       /* control type: command, callback function: OpenCom1Callback */
#define  MAINPANEL_PICTURE                9       /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK mainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenCom1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenSetParaPanelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
