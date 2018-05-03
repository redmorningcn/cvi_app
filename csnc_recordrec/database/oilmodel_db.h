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

#define  RECO_PANEL                       1       /* callback function: oilmodelPB */
#define  RECO_PANEL_TEXTMSG               2       /* control type: textMsg, callback function: (none) */
#define  RECO_PANEL_RECV_OIL_2            3       /* control type: command, callback function: ICRecvOilCallBack */
#define  RECO_PANEL_DECORATION            4       /* control type: deco, callback function: (none) */
#define  RECO_PANEL_RECORD_TIMER          5       /* control type: timer, callback function: RecordTimerCallBack */
#define  RECO_PANEL_CUR_NUM               6       /* control type: numeric, callback function: (none) */
#define  RECO_PANEL_ICREAD_NUM            7       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ICRecvOilCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK oilmodelPB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecordTimerCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
