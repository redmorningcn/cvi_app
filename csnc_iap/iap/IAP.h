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

#define  IAP_PANEL                        1       /* callback function: BinFilePanelCB */
#define  IAP_PANEL_DOWNLOAD               2       /* control type: command, callback function: SetProgramFlgCallback */
#define  IAP_PANEL_INFOTEXTBOX            3       /* control type: textBox, callback function: (none) */
#define  IAP_PANEL_BINPAHT                4       /* control type: string, callback function: (none) */
#define  IAP_PANEL_COMMANDBUTTON          5       /* control type: command, callback function: OpenBinFileCallback */
#define  IAP_PANEL_DECORATION_2           6       /* control type: deco, callback function: (none) */
#define  IAP_PANEL_DECORATION_3           7       /* control type: deco, callback function: (none) */
#define  IAP_PANEL_TEXTMSG_2              8       /* control type: textMsg, callback function: (none) */
#define  IAP_PANEL_TEXTMSG_4              9       /* control type: textMsg, callback function: (none) */
#define  IAP_PANEL_TEXTMSG_3              10      /* control type: textMsg, callback function: (none) */
#define  IAP_PANEL_PRE                    11      /* control type: scale, callback function: (none) */
#define  IAP_PANEL_IAP_TIMER              12      /* control type: timer, callback function: IaptimerCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK BinFilePanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IaptimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenBinFileCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetProgramFlgCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
