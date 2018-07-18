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

#define  LKJTEST                          1       /* callback function: LKJTestPanelCB */
#define  LKJTEST_INFOTEXTBOX              2       /* control type: textBox, callback function: (none) */
#define  LKJTEST_IAP_TIMER                3       /* control type: timer, callback function: LKJTestTimerCallback */
#define  LKJTEST_CH6_LOW                  4       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_HIG                  5       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_FAIL                 6       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_RAISE                7       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_RATIO                8       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_FREQ                 9       /* control type: numeric, callback function: (none) */
#define  LKJTEST_V110                     10      /* control type: numeric, callback function: (none) */
#define  LKJTEST_RECORDNUM                11      /* control type: numeric, callback function: SpecialRecordCallback */
#define  LKJTEST_LW                       12      /* control type: numeric, callback function: (none) */
#define  LKJTEST_XH                       13      /* control type: numeric, callback function: (none) */
#define  LKJTEST_XQ                       14      /* control type: numeric, callback function: (none) */
#define  LKJTEST_ZD                       15      /* control type: numeric, callback function: (none) */
#define  LKJTEST_QY                       16      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_LOW                  17      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_HIG                  18      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_FAIL                 19      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_RAISE                20      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_RATIO                21      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_FREQ                 22      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G2_STANDARD              23      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G2_VCC                   24      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G2_PHASE                 25      /* control type: numeric, callback function: (none) */
#define  LKJTEST_TEXTMSG_7                26      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_8                27      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_10               28      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_9                29      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_DECORATION_14            30      /* control type: deco, callback function: (none) */
#define  LKJTEST_CH4_LOW                  31      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_HIG                  32      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_FAIL                 33      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_RAISE                34      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_RATIO                35      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_FREQ                 36      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_LOW                  37      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_HIG                  38      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_FAIL                 39      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_RAISE                40      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_RATIO                41      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_FREQ                 42      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G1_STANDARD              43      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G1_VCC                   44      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G1_PHASE                 45      /* control type: numeric, callback function: (none) */
#define  LKJTEST_TEXTMSG_4                46      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_5                47      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_6                48      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_CH2_LOW                  49      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_HIG                  50      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_FAIL                 51      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_RAISE                52      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_RATIO                53      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_FREQ                 54      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_LOW                  55      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_HIG                  56      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_FAIL                 57      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_RAISE                58      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_RATIO                59      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_FREQ                 60      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G0_STANDARD              61      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G0_VCC                   62      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G0_PHASE                 63      /* control type: numeric, callback function: (none) */
#define  LKJTEST_DECORATION_21            64      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_17            65      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_5             66      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_19            67      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_20            68      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_15            69      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_16            70      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_3             71      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_4             72      /* control type: deco, callback function: (none) */
#define  LKJTEST_TEXTMSG                  73      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_2                74      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_3                75      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_DECORATION_22            76      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_18            77      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION               78      /* control type: deco, callback function: (none) */
#define  LKJTEST_READREC                  79      /* control type: command, callback function: ReadRecordCallback */
#define  LKJTEST_CLEARREC_2               80      /* control type: command, callback function: ResetSysCallback */
#define  LKJTEST_CLEARREC                 81      /* control type: command, callback function: ClearRecordCallback */
#define  LKJTEST_DECORATION_2             82      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_6             83      /* control type: deco, callback function: (none) */
#define  LKJTEST_CH6_STATUS               84      /* control type: ring, callback function: (none) */
#define  LKJTEST_CH5_STATUS               85      /* control type: ring, callback function: (none) */
#define  LKJTEST_CH4_STATUS               86      /* control type: ring, callback function: (none) */
#define  LKJTEST_CH3_STATUS               87      /* control type: ring, callback function: (none) */
#define  LKJTEST_CH1_STATUS               88      /* control type: ring, callback function: (none) */
#define  LKJTEST_CH2_STATUS               89      /* control type: ring, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ClearRecordCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LKJTestPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LKJTestTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ReadRecordCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResetSysCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpecialRecordCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
