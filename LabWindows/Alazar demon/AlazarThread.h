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

BOOL AlazarInit (void);
int CVICALLBACK AlazarAcquire (void *);
int CVICALLBACK DataThread (void *);
void fifo_add (fifo_t *, void *);
void *fifo_remove (fifo_t *);

  
int panelHandle;
HANDLE boardHandle;

CmtThreadLockHandle AlazarThreadLock;
int AlazarThreadId;
CmtThreadLockHandle DataThreadLock;
int DataThreadId;
int status;

U32 rawAlineSize;     // Number of samples in a signle A-line
U32 bytesPerSample;   // Size of a single sample in bytes
U32 rawBscanSize;     // Number of A-lines in a B-scan
U32 bytesPerBuffer;   // Size of buffer for 2 channels
U16 *Buffer;          // DMA Memory Buffer


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AlazarThread_H__ */
