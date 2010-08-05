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

int CVICALLBACK DataThread (void *functionData)
{
  char textline[4096];
  volatile int stop = 0, loop = 0;
  U16 *data;
  
  // wait for tread lock
  CmtGetLock (DataThreadLock);
  // release the lock
  CmtReleaseLock (DataThreadLock);
  
  status = 3; // DataThread() is started
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! DataThread() has been started!\n");
  
  // run until button STOP pressed
  while (stop == 0)
  {
    // wait for tread lock
    CmtGetLock (DataThreadLock);
    // release the lock
    CmtReleaseLock (DataThreadLock);
    
    // check button STOP
    GetCtrlVal (panelHandle, PANEL_STOPBUTTON, &stop);
    
    // remove buffer from FIFO buffer and free memory space
    while (FIFOBuff->f_head != FIFOBuff->f_tail)
    {
      data = fifo_remove (FIFOBuff);
      sprintf (textline, "%i, %i\n", loop++, stop);
      SetCtrlVal (panelHandle, PANEL_ERRORMSG, textline);
      free (data);
    }
    
  }
  
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! DataThread() has been stopped!\n");
  
  return 0;
}
