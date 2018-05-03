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

#define  MAIN                             1       /* callback function: mb_mainPanelCB */
#define  MAIN_SLAVE                       2       /* control type: command, callback function: OpenSlaveCallback */
#define  MAIN_POLL                        3       /* control type: command, callback function: OpenPollCallback */
#define  MAIN_COMCONFIG                   4       /* control type: command, callback function: OpenCom1Callback */
#define  MAIN_TEXTMSG_4                   5       /* control type: textMsg, callback function: (none) */
#define  MAIN_MAIN_TIMER                  6       /* control type: timer, callback function: MainTimerCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MainTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mb_mainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenCom1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenPollCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenSlaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
