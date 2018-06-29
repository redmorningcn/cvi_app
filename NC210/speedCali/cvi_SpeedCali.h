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

#define  SPEEDCALI                        1       /* callback function: SpeedCaliPanelCB */
#define  SPEEDCALI_DECORATION_25          2       /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G3SPEED2               3       /* control type: command, callback function: G3_Speed2CaliCallback */
#define  SPEEDCALI_G3SPEED2_HIG_MEASURE   4       /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3SPEED2_HIG_STAND     5       /* control type: numeric, callback function: G3_Speed2HigCallback */
#define  SPEEDCALI_G3SPEED2_LOW_MEASURE   6       /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3SPEED2_LOW_STAND     7       /* control type: numeric, callback function: G3_Speed2lowCallback */
#define  SPEEDCALI_SPLITTER_9             8       /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_33             9       /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_34             10      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_35             11      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_36             12      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_26          13      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G3SPEED1               14      /* control type: command, callback function: G3_Speed1CaliCallback */
#define  SPEEDCALI_G3SPEED1_HIG_MEASURE   15      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3SPEED1_HIG_STAND     16      /* control type: numeric, callback function: G3_Speed1HigCallback */
#define  SPEEDCALI_G3SPEED1_LOW_MEASURE   17      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3SPEED1_LOW_STAND     18      /* control type: numeric, callback function: G3_Speed1LowCallback */
#define  SPEEDCALI_SPLITTER_10            19      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_37             20      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_38             21      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_39             22      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_40             23      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_27          24      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G3VCC                  25      /* control type: command, callback function: G3_VccCaliCallback */
#define  SPEEDCALI_G3VCC_HIG_MEASURE      26      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3VCC_HIG_STAND        27      /* control type: numeric, callback function: G3_VccHigCallback */
#define  SPEEDCALI_G3VCC_LOW_MEASURE      28      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3VCC_LOW_STAND        29      /* control type: numeric, callback function: G3_VccLowCallback */
#define  SPEEDCALI_SPLITTER_11            30      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_41             31      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_42             32      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_43             33      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_44             34      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G3SPEED2_SYNC          35      /* control type: radioButton, callback function: G3Speed2SyncCallback */
#define  SPEEDCALI_G3VCC_SYNC             36      /* control type: radioButton, callback function: G3VCCSyncCallback */
#define  SPEEDCALI_G3SPEED1_SYNC          37      /* control type: radioButton, callback function: G3Speed1SyncCallback */
#define  SPEEDCALI_DECORATION_21          38      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_DECORATION_28          39      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G2SPEED2               40      /* control type: command, callback function: G2_Speed2CaliCallback */
#define  SPEEDCALI_G2SPEED2_HIG_MEASURE   41      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_HIG_STAND     42      /* control type: numeric, callback function: G2_Speed2HigCallback */
#define  SPEEDCALI_G2SPEED2_LOW_MEASURE   43      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_LOW_STAND     44      /* control type: numeric, callback function: G2_Speed2lowCallback */
#define  SPEEDCALI_SPLITTER_6             45      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_21             46      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_22             47      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_23             48      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_24             49      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_22          50      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G2SPEED1               51      /* control type: command, callback function: G2_Speed1CaliCallback */
#define  SPEEDCALI_G2SPEED1_HIG_MEASURE   52      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED1_HIG_STAND     53      /* control type: numeric, callback function: G2_Speed1HigCallback */
#define  SPEEDCALI_G2SPEED1_LOW_MEASURE   54      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED1_LOW_STAND     55      /* control type: numeric, callback function: G2_Speed1LowCallback */
#define  SPEEDCALI_SPLITTER_7             56      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_25             57      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_26             58      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_27             59      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_28             60      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_23          61      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G2VCC                  62      /* control type: command, callback function: G2_VccCaliCallback */
#define  SPEEDCALI_G2VCC_HIG_MEASURE      63      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2VCC_HIG_STAND        64      /* control type: numeric, callback function: G2_VccHigCallback */
#define  SPEEDCALI_G2VCC_LOW_MEASURE      65      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2VCC_LOW_STAND        66      /* control type: numeric, callback function: G2_VccLowCallback */
#define  SPEEDCALI_SPLITTER_8             67      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_29             68      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_30             69      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_31             70      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_32             71      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_SYNC          72      /* control type: radioButton, callback function: G2Speed2SyncCallback */
#define  SPEEDCALI_G2VCC_SYNC             73      /* control type: radioButton, callback function: G2VCCSyncCallback */
#define  SPEEDCALI_G2SPEED1_SYNC          74      /* control type: radioButton, callback function: G2Speed1SyncCallback */
#define  SPEEDCALI_DECORATION_20          75      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_DECORATION_24          76      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G1SPEED2               77      /* control type: command, callback function: G1_Speed2CaliCallback */
#define  SPEEDCALI_G1SPEED2_HIG_MEASURE   78      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_HIG_STAND     79      /* control type: numeric, callback function: G1_Speed2HigCallback */
#define  SPEEDCALI_G1SPEED2_LOW_MEASURE   80      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_LOW_STAND     81      /* control type: numeric, callback function: G1_Speed2lowCallback */
#define  SPEEDCALI_SPLITTER_5             82      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_17             83      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_18             84      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_19             85      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_20             86      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_18          87      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G1SPEED1               88      /* control type: command, callback function: G1_Speed1CaliCallback */
#define  SPEEDCALI_G1SPEED1_HIG_MEASURE   89      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1SPEED1_HIG_STAND     90      /* control type: numeric, callback function: G1_Speed1HigCallback */
#define  SPEEDCALI_G1SPEED1_LOW_MEASURE   91      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1SPEED1_LOW_STAND     92      /* control type: numeric, callback function: G1_Speed1LowCallback */
#define  SPEEDCALI_SPLITTER_3             93      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_9              94      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_10             95      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_11             96      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_12             97      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_17          98      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G1VCC                  99      /* control type: command, callback function: G1_VccCaliCallback */
#define  SPEEDCALI_G1VCC_HIG_MEASURE      100     /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1VCC_HIG_STAND        101     /* control type: numeric, callback function: G1_VccHigCallback */
#define  SPEEDCALI_G1VCC_LOW_MEASURE      102     /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1VCC_LOW_STAND        103     /* control type: numeric, callback function: G1_VccLowCallback */
#define  SPEEDCALI_SPLITTER_2             104     /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_5              105     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_6              106     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_7              107     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_8              108     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_SYNC          109     /* control type: radioButton, callback function: G1Speed2SyncCallback */
#define  SPEEDCALI_G1VCC_SYNC             110     /* control type: radioButton, callback function: G1VCCSyncCallback */
#define  SPEEDCALI_G1SPEED1_SYNC          111     /* control type: radioButton, callback function: G1Speed1SyncCallback */
#define  SPEEDCALI_TIMER                  112     /* control type: timer, callback function: SpeedCaliTimerCallback */
#define  SPEEDCALI_DECORATION             113     /* control type: deco, callback function: (none) */
#define  SPEEDCALI_TEXTMSG                114     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_46             115     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_45             116     /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK G1_Speed1CaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_Speed1HigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_Speed1LowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_Speed2CaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_Speed2HigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_Speed2lowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_VccCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_VccHigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1_VccLowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1Speed1SyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1Speed2SyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G1VCCSyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_Speed1CaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_Speed1HigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_Speed1LowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_Speed2CaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_Speed2HigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_Speed2lowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_VccCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_VccHigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2_VccLowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2Speed1SyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2Speed2SyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G2VCCSyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_Speed1CaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_Speed1HigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_Speed1LowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_Speed2CaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_Speed2HigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_Speed2lowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_VccCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_VccHigCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3_VccLowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3Speed1SyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3Speed2SyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK G3VCCSyncCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpeedCaliPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpeedCaliTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
