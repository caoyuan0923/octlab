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
DllExport I8 OL_phase_calibration(U32, U32, U32, DBL *, DBL *);
}

// phase calibration main function
I8 OL_phase_calibration(U32 X, U32 Y, U32 level, DBL *ref, DBL *ptr) {
  I32 i, j;
  #pragma omp parallel for default(shared) private(i, j)
  for (i = 0; i < static_cast<I32>(Y); i++)
    for (j =  0; j < static_cast<I32>(X); j++)
      if (j < static_cast<I32>(level))
        ptr[i * X + j] = ptr[i * X + j] - ref[i] * j / level;
      else
        ptr[i * X + j] = ptr[i * X + j] - ref[i];
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
