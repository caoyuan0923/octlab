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
DllExport I8 OL_simple_threshold(U32, DBL, DBL, DBL *);
}

// simple Threshold main function
I8 OL_simple_threshold(U32 SIZE, DBL min, DBL max, DBL *ptr) {
  I32 i;
  #pragma omp parallel for default(shared) private(i)
  for (i = 0; i < static_cast<I32>(SIZE); i++) {
    if (ptr[i] > max)
      ptr[i] = max;
    else if (ptr[i] < min)
      ptr[i] = min;
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
