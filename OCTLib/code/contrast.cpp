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
DllExport I8 OL_contrast_map(U32, U32, U32, U32, DBL *, DBL *);
}

/* OL_contrast_map main function
  PURPOSE:
    calculate speckle contrast K for spatially sliding 2D window within B-scan:
      K = SD(I)/<I>
      where K is speckle contrast, SD(I) is sample standard deviation with
      Bessel's correction, <I> is mean value for input intensity
      distribution (I).
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    x_r - horizontal radius, defines width of 2D sliding window (2 * x_r + 1)
    y_r - vertical radius, defines height of 2D sliding window (2 * y_r + 1)
    in - pointer to buffer with B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: (X - 2 * x_r) * (Y - 2 * y_r))
  
  REFERENCES:
    [1] http://en.wikipedia.org/wiki/Speckle_pattern
    [2] http://wifi.bli.uci.edu/?page=LSI
    [3] http://en.wikipedia.org/wiki/Bessel's_correction
*/
I8 OL_contrast_map(U32 X, U32 Y, U32 x_r, U32 y_r, DBL *in, DBL *out) {
  U32 d = X - 2 * x_r, x_d = 2 * x_r + 1, y_d = 2 * y_r + 1, size = x_d * y_d;
  I32 x, y;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (x = 0; x < static_cast<I32>(d); x++) {  // horizontal
    for (y = 0; y < static_cast<I32>(Y - 2 * y_r); y++) {  // vertical
      DBL mean = 0.0;
      // loop for mean
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // sum
          mean = mean + in[pos];
        }
      }
      mean = mean / size;
      DBL  tmp = 0.0;
      // loop for contrast
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // sum^2
          tmp = tmp + (in[pos] - mean) * (in[pos] - mean);
        }
      }
      // fill out
      out[y * d + x] = sqrt(tmp / (size - 1)) / mean;
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
