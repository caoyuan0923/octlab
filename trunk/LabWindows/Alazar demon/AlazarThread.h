/*******************************************************************************
*  $Id$
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the http://octlab.googlecode.com/svn/trunk/COPYRIGHT.TXT web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#ifndef __AlazarThread_H__
#define __AlazarThread_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "AlazarApi.h" 
#include "AlazarError.h"
#include "AlazarCmd.h"
#include <utility.h>
#include <ansi_c.h>
#include "AlazarDemon.h"
#include "rsmfifo.h"

// function prototypes
BOOL AlazarInit (void);                 // initialization of Alazar card
int CVICALLBACK AlazarAcquire (void *); // acquisition of Alazar card
int CVICALLBACK DataThread (void *);    // data processing through FIFO queue
void FIFO_Add (fifo_t *, void *);       // add buffer to FIFO queue
void *FIFO_Remove (fifo_t *);           // remove buffer from FIFO queue

int panelHandle;    // global handle for UI panel
HANDLE boardHandle; // global handle for Alazar card
volatile int stop;  // global flag for pressed STOP button
unsigned int channel; // global variable for channel selection
unsigned int aLineIndex; // global variable for ALine selection

// for thread management
CmtThreadLockHandle alazarThreadLock; // lock to control AlazarAcquire() startup
int alazarThreadId;                   // ID of AlazarAcquire()
CmtThreadLockHandle dataThreadLock;   // lock to control DataThread() startup
int dataThreadId;                     // ID of DataThread()
int status;                           // status of whole application
HANDLE eventData;                     // handle for event
unsigned __int64 alazarLoop;          // number of buffers acquired by Alazar
double timerValue;                    // the time period for each Alazar
                                      // acquisition

U32 rawAlineSize;     // Number of samples in a signle A-line
U32 bytesPerSample;   // Size of a single sample in bytes
U32 rawBscanSize;     // Number of A-lines in a B-scan
U32 bytesPerBuffer;   // Size of buffer for 2 channels
U16 *frameBuffer;     // DMA Memory Buffer

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AlazarThread_H__ */
