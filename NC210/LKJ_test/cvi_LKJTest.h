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
#define  LKJTEST_CH6_STATUS               4       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_LOW                  5       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_HIG                  6       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_FAIL                 7       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_RAISE                8       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_RATIO                9       /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH6_FREQ                 10      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_STATUS               11      /* control type: numeric, callback function: (none) */
#define  LKJTEST_V110                     12      /* control type: numeric, callback function: (none) */
#define  LKJTEST_RECORDNUM                13      /* control type: numeric, callback function: SpecialRecordCallback */
#define  LKJTEST_LW                       14      /* control type: numeric, callback function: (none) */
#define  LKJTEST_XH                       15      /* control type: numeric, callback function: (none) */
#define  LKJTEST_XQ                       16      /* control type: numeric, callback function: (none) */
#define  LKJTEST_ZD                       17      /* control type: numeric, callback function: (none) */
#define  LKJTEST_QY                       18      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_LOW                  19      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_HIG                  20      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_FAIL                 21      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_RAISE                22      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_RATIO                23      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH5_FREQ                 24      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G2_STANDARD              25      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G2_VCC                   26      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G2_PHASE                 27      /* control type: numeric, callback function: (none) */
#define  LKJTEST_TEXTMSG_7                28      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_8                29      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_10               30      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_9                31      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_DECORATION_14            32      /* control type: deco, callback function: (none) */
#define  LKJTEST_CH4_STATUS               33      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_LOW                  34      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_HIG                  35      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_FAIL                 36      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_RAISE                37      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_RATIO                38      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH4_FREQ                 39      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_STATUS               40      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_LOW                  41      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_HIG                  42      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_FAIL                 43      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_RAISE                44      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_RATIO                45      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH3_FREQ                 46      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G1_STANDARD              47      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G1_VCC                   48      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G1_PHASE                 49      /* control type: numeric, callback function: (none) */
#define  LKJTEST_TEXTMSG_4                50      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_5                51      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_6                52      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_CH2_STATUS               53      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_LOW                  54      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_HIG                  55      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_FAIL                 56      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_RAISE                57      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_RATIO                58      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH2_FREQ                 59      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_STATUS               60      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_LOW                  61      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_HIG                  62      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_FAIL                 63      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_RAISE                64      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_RATIO                65      /* control type: numeric, callback function: (none) */
#define  LKJTEST_CH1_FREQ                 66      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G0_STANDARD              67      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G0_VCC                   68      /* control type: numeric, callback function: (none) */
#define  LKJTEST_G0_PHASE                 69      /* control type: numeric, callback function: (none) */
#define  LKJTEST_DECORATION_21            70      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_17            71      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_5             72      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_19            73      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_20            74      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_15            75      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_16            76      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_3             77      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_4             78      /* control type: deco, callback function: (none) */
#define  LKJTEST_TEXTMSG                  79      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_2                80      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_TEXTMSG_3                81      /* control type: textMsg, callback function: (none) */
#define  LKJTEST_DECORATION_22            82      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_18            83      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION               84      /* control type: deco, callback function: (none) */
#define  LKJTEST_READREC                  85      /* control type: command, callback function: ReadRecordCallback */
#define  LKJTEST_CLEARREC_2               86      /* control type: command, callback function: ResetSysCallback */
#define  LKJTEST_CLEARREC                 87      /* control type: command, callback function: ClearRecordCallback */
#define  LKJTEST_DECORATION_2             88      /* control type: deco, callback function: (none) */
#define  LKJTEST_DECORATION_6             89      /* control type: deco, callback function: (none) */


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
