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
#define  SPEEDCALI_SPLITTER_12            8       /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_SPLITTER_9             9       /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_33             10      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_34             11      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_35             12      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_36             13      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_26          14      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G3SPEED1               15      /* control type: command, callback function: G3_Speed1CaliCallback */
#define  SPEEDCALI_G3SPEED1_HIG_MEASURE   16      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3SPEED1_HIG_STAND     17      /* control type: numeric, callback function: G3_Speed1HigCallback */
#define  SPEEDCALI_G3SPEED1_LOW_MEASURE   18      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_SPLITTER_13            19      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_G3SPEED1_LOW_STAND     20      /* control type: numeric, callback function: G3_Speed1LowCallback */
#define  SPEEDCALI_SPLITTER_10            21      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_37             22      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_38             23      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_39             24      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_40             25      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_27          26      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G3VCC                  27      /* control type: command, callback function: G3_VccCaliCallback */
#define  SPEEDCALI_G3VCC_HIG_MEASURE      28      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3VCC_HIG_STAND        29      /* control type: numeric, callback function: G3_VccHigCallback */
#define  SPEEDCALI_SPLITTER_14            30      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_G3VCC_LOW_MEASURE      31      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3VCC_LOW_STAND        32      /* control type: numeric, callback function: G3_VccLowCallback */
#define  SPEEDCALI_SPLITTER_11            33      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_41             34      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_42             35      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_43             36      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_44             37      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G3SPEED2_SYNC          38      /* control type: radioButton, callback function: G3Speed2SyncCallback */
#define  SPEEDCALI_G3VCC_SYNC             39      /* control type: radioButton, callback function: G3VCCSyncCallback */
#define  SPEEDCALI_G3SPEED1_SYNC          40      /* control type: radioButton, callback function: G3Speed1SyncCallback */
#define  SPEEDCALI_DECORATION_21          41      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_DECORATION_28          42      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G2SPEED2               43      /* control type: command, callback function: G2_Speed2CaliCallback */
#define  SPEEDCALI_G2SPEED2_HIG_MEASURE   44      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_SPLITTER_15            45      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_HIG_STAND     46      /* control type: numeric, callback function: G2_Speed2HigCallback */
#define  SPEEDCALI_G2SPEED2_LOW_MEASURE   47      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_LOW_STAND     48      /* control type: numeric, callback function: G2_Speed2lowCallback */
#define  SPEEDCALI_SPLITTER_6             49      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_21             50      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_22             51      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_23             52      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_24             53      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_22          54      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G2SPEED1               55      /* control type: command, callback function: G2_Speed1CaliCallback */
#define  SPEEDCALI_SPLITTER_16            56      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_G2SPEED1_HIG_MEASURE   57      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED1_HIG_STAND     58      /* control type: numeric, callback function: G2_Speed1HigCallback */
#define  SPEEDCALI_G2SPEED1_LOW_MEASURE   59      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED1_LOW_STAND     60      /* control type: numeric, callback function: G2_Speed1LowCallback */
#define  SPEEDCALI_SPLITTER_7             61      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_25             62      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_26             63      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_27             64      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_28             65      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_23          66      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_SPLITTER_17            67      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_G2VCC                  68      /* control type: command, callback function: G2_VccCaliCallback */
#define  SPEEDCALI_G2VCC_HIG_MEASURE      69      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2VCC_HIG_STAND        70      /* control type: numeric, callback function: G2_VccHigCallback */
#define  SPEEDCALI_G2VCC_LOW_MEASURE      71      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2VCC_LOW_STAND        72      /* control type: numeric, callback function: G2_VccLowCallback */
#define  SPEEDCALI_SPLITTER_8             73      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_29             74      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_30             75      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_53             76      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_54             77      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_55             78      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_50             79      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_51             80      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_52             81      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_49             82      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_48             83      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_47             84      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_31             85      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_32             86      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_SYNC          87      /* control type: radioButton, callback function: G2Speed2SyncCallback */
#define  SPEEDCALI_G2VCC_SYNC             88      /* control type: radioButton, callback function: G2VCCSyncCallback */
#define  SPEEDCALI_G2SPEED1_SYNC          89      /* control type: radioButton, callback function: G2Speed1SyncCallback */
#define  SPEEDCALI_DECORATION_20          90      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_SPLITTER_18            91      /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_DECORATION_24          92      /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G1SPEED2               93      /* control type: command, callback function: G1_Speed2CaliCallback */
#define  SPEEDCALI_G3SPEED2_CUR_INFO      94      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_HIG_MEASURE   95      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G3SPEED1_CUR_INFO      96      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_HIG_STAND     97      /* control type: numeric, callback function: G1_Speed2HigCallback */
#define  SPEEDCALI_G3VCC_CUR_INFO         98      /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_LOW_MEASURE   99      /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G2SPEED2_CUR_INFO      100     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_LOW_STAND     101     /* control type: numeric, callback function: G1_Speed2lowCallback */
#define  SPEEDCALI_G2SPEED1_CUR_INFO      102     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_SPLITTER_5             103     /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_G2VCC_CUR_INFO         104     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_17             105     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_CUR_INFO      106     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_18             107     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED1_CUR_INFO      108     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_19             109     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1VCC_CUR_INFO         110     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_SPLITTER_19            111     /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_20             112     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_18          113     /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G1SPEED1               114     /* control type: command, callback function: G1_Speed1CaliCallback */
#define  SPEEDCALI_G1SPEED1_HIG_MEASURE   115     /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1SPEED1_HIG_STAND     116     /* control type: numeric, callback function: G1_Speed1HigCallback */
#define  SPEEDCALI_G1SPEED1_LOW_MEASURE   117     /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1SPEED1_LOW_STAND     118     /* control type: numeric, callback function: G1_Speed1LowCallback */
#define  SPEEDCALI_SPLITTER_3             119     /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_9              120     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_10             121     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_SPLITTER_20            122     /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_11             123     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_12             124     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_DECORATION_17          125     /* control type: deco, callback function: (none) */
#define  SPEEDCALI_G1VCC                  126     /* control type: command, callback function: G1_VccCaliCallback */
#define  SPEEDCALI_G1VCC_HIG_MEASURE      127     /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1VCC_HIG_STAND        128     /* control type: numeric, callback function: G1_VccHigCallback */
#define  SPEEDCALI_G1VCC_LOW_MEASURE      129     /* control type: numeric, callback function: (none) */
#define  SPEEDCALI_G1VCC_LOW_STAND        130     /* control type: numeric, callback function: G1_VccLowCallback */
#define  SPEEDCALI_SPLITTER_2             131     /* control type: splitter, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_5              132     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_6              133     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_7              134     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_8              135     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_G1SPEED2_SYNC          136     /* control type: radioButton, callback function: G1Speed2SyncCallback */
#define  SPEEDCALI_G1VCC_SYNC             137     /* control type: radioButton, callback function: G1VCCSyncCallback */
#define  SPEEDCALI_G1SPEED1_SYNC          138     /* control type: radioButton, callback function: G1Speed1SyncCallback */
#define  SPEEDCALI_TIMER                  139     /* control type: timer, callback function: SpeedCaliTimerCallback */
#define  SPEEDCALI_DECORATION             140     /* control type: deco, callback function: (none) */
#define  SPEEDCALI_TEXTMSG                141     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_46             142     /* control type: textMsg, callback function: (none) */
#define  SPEEDCALI_TEXTMSG_45             143     /* control type: textMsg, callback function: (none) */


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
