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

#define  SETP_PANEL                       1       /* callback function: SetParaPanelCB */
#define  SETP_PANEL_DECORATION_18         2       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_DECORATION_17         3       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_6             4       /* control type: command, callback function: (none) */
#define  SETP_PANEL_DECORATION_16         5       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_5             6       /* control type: command, callback function: (none) */
#define  SETP_PANEL_LOCONUM_2             7       /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_LOCOTYPE_2            8       /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_DECORATION_15         9       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_4             10      /* control type: command, callback function: SetLocoCallBack */
#define  SETP_PANEL_LOCONUM               11      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_LOCOTYPE              12      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_SETTIME               13      /* control type: command, callback function: SetTimeCallBack */
#define  SETP_PANEL_SETLOCO_2             14      /* control type: command, callback function: SetProductCallBack */
#define  SETP_PANEL_PRO_TYPE              15      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_PRO_NUM               16      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_SPLITTER              17      /* control type: splitter, callback function: (none) */
#define  SETP_PANEL_TIMER                 18      /* control type: timer, callback function: SetParaTimerCallback */
#define  SETP_PANEL_STRING                19      /* control type: string, callback function: (none) */
#define  SETP_PANEL_DATEANDTIME           20      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK SetLocoCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetParaPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetParaTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetProductCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetTimeCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
