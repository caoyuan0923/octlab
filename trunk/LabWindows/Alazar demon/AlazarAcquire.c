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

#include "AlazarThread.h"

// thread to acquire Alazar card
int CVICALLBACK AlazarAcquire (void *functionData)
{
  char textline[4096];
  volatile int stop = 0;
  BOOL success = TRUE;
  RETURN_CODE retCode;
  U32 timeout_ms = 5000;
  
  // wait for tread lock
  CmtGetLock (AlazarThreadLock);
  // release the lock
  CmtReleaseLock (AlazarThreadLock);
  
  // create buffer
  FIFOBuff = (fifo_t *) malloc (sizeof (fifo_t));
  FIFOBuff->f_head = NULL;
  FIFOBuff->f_tail = NULL;
  
  // set status
  status = 2; // AlazarAcquire is started
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! AlazarAcquire() has been started!\n");
  
  // Arm the board to begin acquisition
  retCode = AlazarStartCapture (boardHandle);
  if (retCode != ApiSuccess)
  {
    sprintf (textline,
      "Error: AlazarStartCapture failed -- %s\n", AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textline);
    success = FALSE;
    return FALSE;
  }
  
  // run until button STOP pressed
  while (stop == 0)
  {
    // check button STOP
    GetCtrlVal (panelHandle, PANEL_STOPBUTTON, &stop);
  
    // wait for new Alazar card buffer
    retCode = AlazarWaitNextAsyncBufferComplete (
      boardHandle,
      Buffer,
      bytesPerBuffer,
      timeout_ms
      );
    if (retCode == ApiSuccess)
    {
      // wait for tread lock to freeze DataThread()
      CmtGetLock (DataThreadLock);
      
      // add acquired buffer to FIFO buffer and re-create memory space for next
      // buffer from Alazar card
      fifo_add (FIFOBuff, Buffer);
      Buffer = NULL;
      Buffer = (U16 *) malloc (bytesPerBuffer);
      
      // release the lock to unfreeze DataThread()
      CmtReleaseLock (DataThreadLock);
    }
    else if (retCode == ApiTransferComplete)
    {
      // This buffer is full, and it's the last buffer in the acquisition
    }
    else
    {
      sprintf (textline,
        "Error: AlazarWaitNextAsyncBufferComplete failed -- %s\n",
        AlazarErrorToText(retCode));
      SetCtrlVal (panelHandle, PANEL_ERRORMSG, textline);
      Delay (5.0);
      return FALSE;
    }
  }
  
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! AlazarAcquire() has been stopped!\n");
  
  return 0;
}
