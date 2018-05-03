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

#define  CHILD                            1
#define  CHILD_TABLE                      2       /* control type: table, callback function: ModefyModelTableCallback */
#define  CHILD_POTNUM                     3       /* control type: numeric, callback function: PotNumCallback */
#define  CHILD_MODELNUM                   4       /* control type: numeric, callback function: (none) */
#define  CHILD_COMMANDBUTTON              5       /* control type: command, callback function: ConfigOkCallback */
#define  CHILD_TYPE                       6       /* control type: string, callback function: (none) */

#define  SETM_PANEL                       2       /* callback function: oilmodelPB */
#define  SETM_PANEL_TABLE                 2       /* control type: table, callback function: (none) */
#define  SETM_PANEL_MODEL_NUM             3       /* control type: ring, callback function: refreshmodlecallback */
#define  SETM_PANEL_OIL_CHART             4       /* control type: scale, callback function: (none) */
#define  SETM_PANEL_OIL                   5       /* control type: numeric, callback function: OilToHightCallback */
#define  SETM_PANEL_HIGHT                 6       /* control type: numeric, callback function: hightToOilCallback */
#define  SETM_PANEL_TEXTMSG_4             7       /* control type: textMsg, callback function: (none) */
#define  SETM_PANEL_TEXTMSG_3             8       /* control type: textMsg, callback function: (none) */
#define  SETM_PANEL_TEXTMSG_2             9       /* control type: textMsg, callback function: (none) */
#define  SETM_PANEL_START                 10      /* control type: numeric, callback function: modefyHigCallback */
#define  SETM_PANEL_SLOPE                 11      /* control type: numeric, callback function: sclopeCallback */
#define  SETM_PANEL_SPLITTER              12      /* control type: splitter, callback function: (none) */
#define  SETM_PANEL_DECORATION_4          13      /* control type: deco, callback function: (none) */
#define  SETM_PANEL_DECORATION_2          14      /* control type: deco, callback function: (none) */
#define  SETM_PANEL_TEXTMSG               15      /* control type: textMsg, callback function: (none) */
#define  SETM_PANEL_DECORATION_3          16      /* control type: deco, callback function: (none) */
#define  SETM_PANEL_MODEL_TIMER           17      /* control type: timer, callback function: ModelTimerCallBack */
#define  SETM_PANEL_MODIFY                18      /* control type: command, callback function: modefyCallback */
#define  SETM_PANEL_SENDMODEL             19      /* control type: command, callback function: SetModelCallBack */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ConfigOkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK hightToOilCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK modefyCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK modefyHigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModefyModelTableCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModelTimerCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK oilmodelPB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OilToHightCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PotNumCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK refreshmodlecallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK sclopeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetModelCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
