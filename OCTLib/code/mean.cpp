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

// common header
#include "./OCTLib.h"

// for DLL export
extern "C" {
DllExport DBL OL_mean(U32, DBL *);
DllExport I8  OL_mean_map(U32, U32, U32, DBL *, DBL *);
}

// mean main function
DBL OL_mean(U32 SIZE, DBL *ptr) {
  return accumulate(ptr, ptr + SIZE, 0.0) / SIZE;
}
DBL (*fp_mean)(U32, DBL *) = OL_mean;

/************OL_mean_map************/
I8 OL_mean_map(U32 X, U32 Y, U32 radius, DBL *lineIN, DBL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_mean);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
