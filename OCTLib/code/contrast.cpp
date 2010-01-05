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
DllExport DBL OL_contrast(U32, DBL *);
DllExport I8 OL_contrast_map(U32, U32, U32, DBL *, DBL *);
}

/* speckle contrast main function
  PURPOSE:
    calculate speckle contrast (K):
      K = SD(I)/<I>
      where K is speckle contrast, SD(I) is sample standard deviation with
      Bessel's correction, <I> is mean value for input intensity
      distribution (I).
  
  INPUTS:
    SIZE - total number of elements
    ptr - pointer to buffer with intensity values
  
  OUTPUTS:
    contrast value
  
  REFERENCES:
    [1] http://en.wikipedia.org/wiki/Speckle_pattern
    [2] http://wifi.bli.uci.edu/?page=LSI
    [3] http://en.wikipedia.org/wiki/Bessel's_correction
*/
DBL OL_contrast(U32 SIZE, DBL *ptr) {
  DBL mean_value = accumulate(ptr, ptr + SIZE, 0.0) / SIZE;
  DBL sum_value = 0.0;
  for (DBL *t = ptr; t < ptr + SIZE; t++)
    sum_value = sum_value + (*t - mean_value) * (*t - mean_value);
  return sqrt(sum_value / (SIZE - 1)) / mean_value;
}
DBL (*fp_contrast)(U32, DBL *) = OL_contrast;

/************OL_contrast_map************/
I8 OL_contrast_map(U32 X, U32 Y, U32 radius, DBL *lineIN, DBL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_contrast);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
