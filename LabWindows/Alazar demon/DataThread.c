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
  unsigned __int64 loop = 0;
  U16 *data;
  
  // wait for tread lock
  CmtGetLock (dataThreadLock);
  // release the lock
  CmtReleaseLock (dataThreadLock);
  
  status = 3; // DataThread() is started
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! DataThread() has been started!\n");
  
  // run until button STOP pressed
  while (stop == 0)
  {
    // wait for event from AlazarAcquire()
    WaitForSingleObject (eventData, INFINITE);
    
    // remove buffer from FIFO buffer and free memory space
    while (FIFOBuff->f_head != FIFOBuff->f_tail)
    {
      data = FIFO_Remove (FIFOBuff); // remove buffer from FIFO queue
      // update counters
      SetCtrlAttribute (panelHandle, PANEL_DATALOOPS, ATTR_CTRL_VAL, loop++);
      SetCtrlAttribute (panelHandle, PANEL_ALAZARLOOPS, ATTR_CTRL_VAL,
        alazarLoop);
      SetCtrlAttribute (panelHandle, PANEL_TIMEVALUE, ATTR_CTRL_VAL,
        timerValue * 1000.0);
      
      // draw plot
      DeleteGraphPlot (panelHandle, PANEL_ALINEGRAPH, -1, VAL_DELAYED_DRAW);
      PlotY (panelHandle, PANEL_ALINEGRAPH,
        data + rawAlineSize * (rawBscanSize * channel + aLineIndex),
        rawAlineSize, VAL_UNSIGNED_SHORT_INTEGER, VAL_FAT_LINE,
        VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_CYAN);
      
      free (data); // free buffer obtained from FIFO queue
    }
    
  }
  
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! DataThread() has been stopped!\n");
  
  return 0;
}
