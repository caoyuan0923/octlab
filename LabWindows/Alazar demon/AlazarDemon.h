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
#define  PANEL_VALUE                      2       /* control type: numeric, callback function: (none) */
#define  PANEL_BUFFERSIZE                 3       /* control type: numeric, callback function: (none) */
#define  PANEL_MAXSAMPLESPERCHANNEL       4       /* control type: numeric, callback function: (none) */
#define  PANEL_BYTESPERSAMPLE             5       /* control type: numeric, callback function: (none) */
#define  PANEL_SYSTEMCOUNT                6       /* control type: numeric, callback function: (none) */
#define  PANEL_BOARDNUMBER                7       /* control type: numeric, callback function: (none) */
#define  PANEL_RUNBUTTON                  8       /* control type: command, callback function: RunCB */
#define  PANEL_CLOCKSOURCE                9       /* control type: ring, callback function: (none) */
#define  PANEL_SAMPLERATE                 10      /* control type: ring, callback function: (none) */
#define  PANEL_CLOCKEDGE                  11      /* control type: ring, callback function: (none) */
#define  PANEL_REFERENCECHANNEL           12      /* control type: ring, callback function: (none) */
#define  PANEL_SAMPLECHANNEL              13      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGEXTTRIG            14      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGREFCH              15      /* control type: ring, callback function: (none) */
#define  PANEL_INPUTRANGEREFCH            16      /* control type: ring, callback function: (none) */
#define  PANEL_IMPVALUEREFCH              17      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGSAMPLECH           18      /* control type: ring, callback function: (none) */
#define  PANEL_INPUTRANGESAMPLECH         19      /* control type: ring, callback function: (none) */
#define  PANEL_IMPVALUESAMPLECH           20      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINEOP               21      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINE2                22      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGSOURCE2                23      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGLEVEL2                 24      /* control type: numeric, callback function: (none) */
#define  PANEL_TRIGSLOPE2                 25      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINE1                26      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGSOURCE1                27      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGLEVEL1                 28      /* control type: numeric, callback function: (none) */
#define  PANEL_TRIGSLOPE1                 29      /* control type: ring, callback function: (none) */
#define  PANEL_RANGEIDEXTTRIG             30      /* control type: ring, callback function: (none) */
#define  PANEL_MODE                       31      /* control type: ring, callback function: (none) */
#define  PANEL_STOPBUTTON                 32      /* control type: textButton, callback function: (none) */
#define  PANEL_STATUS                     33      /* control type: numeric, callback function: (none) */
#define  PANEL_RAWBLINESIZE               34      /* control type: numeric, callback function: (none) */
#define  PANEL_RAWALINESIZE               35      /* control type: numeric, callback function: (none) */
#define  PANEL_ERRORMSG                   36      /* control type: textBox, callback function: (none) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
