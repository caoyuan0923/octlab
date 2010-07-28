/*******************************************************************************
*  $Id$
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the http://octlab.googlecode.com/svn/trunk/COPYRIGHT.TXT web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include "test.h"
#include "thread.h"

int CVICALLBACK threadFunc (void *functionData)
{
  char textline[1024];
  volatile int stop = 0, loop = 0;
  
  // wait for tread lock
  CmtGetLock (lock);
  // release the lock
  CmtReleaseLock (lock);
  
  status = 2; // run while loop
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  
  SetCtrlVal(panelHandle, PANEL_TEXTSTRING, "Nice! thread() has been started!");
  Delay (1.0);
  
  while (stop == 0)
  {
    GetCtrlVal (panelHandle, PANEL_STOPBUTTON, &stop);
    Delay (0.2);
    sprintf (textline, "%i, %i", loop++, stop);
    SetCtrlVal (panelHandle, PANEL_TEXTSTRING, textline); 
  }
  
  SetCtrlVal(panelHandle, PANEL_TEXTSTRING, "Nice! thread() has been stopped!");
  Delay (1.0);
  
  status = 3; // exit threadFunc()
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  
  return 0;
}
