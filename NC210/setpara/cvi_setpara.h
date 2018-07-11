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
#define  SETP_PANEL_DECORATION_19         2       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_DECORATION_18         3       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_7             4       /* control type: command, callback function: DetectWriteCallback */
#define  SETP_PANEL_DECORATION_17         5       /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_8             6       /* control type: command, callback function: DetectReadCallback */
#define  SETP_PANEL_DETECT_NODE           7       /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_DETECT_LEN            8       /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_DETECT_ADDR           9       /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_SETLOCO_6             10      /* control type: command, callback function: ParaWriteCallback */
#define  SETP_PANEL_DECORATION_16         11      /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_5             12      /* control type: command, callback function: ParaReadCallback */
#define  SETP_PANEL_PARA_LEN              13      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_PARA_ADDR             14      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_DECORATION_15         15      /* control type: deco, callback function: (none) */
#define  SETP_PANEL_SETLOCO_4             16      /* control type: command, callback function: SetLocoCallBack */
#define  SETP_PANEL_LOCONUM               17      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_SPLITTER_2            18      /* control type: splitter, callback function: (none) */
#define  SETP_PANEL_LOCOTYPE              19      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_DETECT_BUF            20      /* control type: string, callback function: (none) */
#define  SETP_PANEL_SETTIME               21      /* control type: command, callback function: SetTimeCallBack */
#define  SETP_PANEL_SETLOCO_2             22      /* control type: command, callback function: SetProductCallBack */
#define  SETP_PANEL_PRO_TYPE              23      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_PRO_NUM               24      /* control type: numeric, callback function: (none) */
#define  SETP_PANEL_SPLITTER              25      /* control type: splitter, callback function: (none) */
#define  SETP_PANEL_TIMER                 26      /* control type: timer, callback function: SetParaTimerCallback */
#define  SETP_PANEL_PARA_BUF              27      /* control type: string, callback function: (none) */
#define  SETP_PANEL_DECORATION_20         28      /* control type: deco, callback function: (none) */
#define  SETP_PANEL_DECORATION            29      /* control type: deco, callback function: (none) */
#define  SETP_PANEL_DATEANDTIME           30      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DetectReadCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DetectWriteCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ParaReadCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ParaWriteCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetLocoCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetParaPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetParaTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetProductCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetTimeCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
