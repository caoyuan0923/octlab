/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2010. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: PanelCB */
#define  PANEL_TIMEVALUE                  2       /* control type: numeric, callback function: (none) */
#define  PANEL_VALUE                      3       /* control type: numeric, callback function: (none) */
#define  PANEL_DATALOOPS                  4       /* control type: numeric, callback function: (none) */
#define  PANEL_ALAZARLOOPS                5       /* control type: numeric, callback function: (none) */
#define  PANEL_BUFFERSIZE                 6       /* control type: numeric, callback function: (none) */
#define  PANEL_MAXSAMPLESPERCHANNEL       7       /* control type: numeric, callback function: (none) */
#define  PANEL_BYTESPERSAMPLE             8       /* control type: numeric, callback function: (none) */
#define  PANEL_SYSTEMCOUNT                9       /* control type: numeric, callback function: (none) */
#define  PANEL_BOARDNUMBER                10      /* control type: numeric, callback function: (none) */
#define  PANEL_RUNBUTTON                  11      /* control type: command, callback function: RunCB */
#define  PANEL_CLOCKSOURCE                12      /* control type: ring, callback function: (none) */
#define  PANEL_SAMPLERATE                 13      /* control type: ring, callback function: (none) */
#define  PANEL_CLOCKEDGE                  14      /* control type: ring, callback function: (none) */
#define  PANEL_REFERENCECHANNEL           15      /* control type: ring, callback function: (none) */
#define  PANEL_SAMPLECHANNEL              16      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGEXTTRIG            17      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGREFCH              18      /* control type: ring, callback function: (none) */
#define  PANEL_INPUTRANGEREFCH            19      /* control type: ring, callback function: (none) */
#define  PANEL_IMPVALUEREFCH              20      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGSAMPLECH           21      /* control type: ring, callback function: (none) */
#define  PANEL_INPUTRANGESAMPLECH         22      /* control type: ring, callback function: (none) */
#define  PANEL_IMPVALUESAMPLECH           23      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINEOP               24      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINE2                25      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGSOURCE2                26      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGLEVEL2                 27      /* control type: numeric, callback function: (none) */
#define  PANEL_TRIGSLOPE2                 28      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINE1                29      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGSOURCE1                30      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGLEVEL1                 31      /* control type: numeric, callback function: (none) */
#define  PANEL_TRIGSLOPE1                 32      /* control type: ring, callback function: (none) */
#define  PANEL_RANGEIDEXTTRIG             33      /* control type: ring, callback function: (none) */
#define  PANEL_MODE                       34      /* control type: ring, callback function: (none) */
#define  PANEL_STOPBUTTON                 35      /* control type: textButton, callback function: StopCB */
#define  PANEL_STATUS                     36      /* control type: numeric, callback function: (none) */
#define  PANEL_RAWBLINESIZE               37      /* control type: numeric, callback function: (none) */
#define  PANEL_ALINEINDEX                 38      /* control type: numeric, callback function: ALineCB */
#define  PANEL_RAWALINESIZE               39      /* control type: numeric, callback function: (none) */
#define  PANEL_ERRORMSG                   40      /* control type: textBox, callback function: (none) */
#define  PANEL_ALINEGRAPH                 41      /* control type: graph, callback function: (none) */
#define  PANEL_CHANNELSWITCH              42      /* control type: binary, callback function: ChannelCB */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ALineCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChannelCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
