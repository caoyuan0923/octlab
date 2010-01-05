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
DllExport I8 OL_doppler_fltr(U32, U32, U32, U32, DBL, DBL, DBL *, DBL *, DBL *,
                             DBL *);
}

/* Doppler OCT with filtering main function
  PURPOSE:
    calculate Doppler frequency shifts using Kasai autocorrelation function
    for spatially sliding 2D window within B-scan, then filter obtained phases
    based on intensity information.  If intensity is out of defined range phase
    is zero. Read description for Doppler.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    x_r - horizontal radius, defines width of 2D sliding window (2 * x_r + 1)
    y_r - vertical radius, defines height of 2D sliding window (2 * y_r + 1)
    min - minimum value for intensity range
    max - maximum value for intensity range
    intensity - pointer to buffer with intensities, structure B-scan after FFT
    (size: X * Y)
    Re - pointer to buffer with real part of B-scan after FFT (size: X * Y)
    Im - pointer to buffer with imaginary part of B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: (X - 2 * x_r) * (Y - 2 * y_r))
  
  REMARKS:
    note that last row will contain ZEROs
*/
I8 OL_doppler_fltr(U32 X, U32 Y, U32 x_r, U32 y_r, DBL min, DBL max,
                   DBL *intensity, DBL *Re, DBL *Im, DBL *out) {
  U32 d = X - 2 * x_r, x_d = 2 * x_r + 1, y_d = 2 * y_r + 1,
    shift = (Y - y_d) * d;
  DBL _max = max * x_d * y_d, _min = min * x_d * y_d;
  I32 x, y;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (x = 0; x < static_cast<I32>(d); x++) {  // horizontal
    for (y = 0; y < static_cast<I32>(Y - y_d); y++) {  // vertical
      DBL tmp_1 = 0.0, tmp_2 = 0.0, sum = 0.0;
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // Q(m)I(m+1) - I(m)Q(m+1)
          tmp_1 = tmp_1 + Im[pos] * Re[pos + X] - Re[pos] * Im[pos + X];
          // Q(m)Q(m+1) + I(m)I(m+1)
          tmp_2 = tmp_2 + Im[pos] * Im[pos + X] + Re[pos] * Re[pos + X];
          // mean value
          sum = sum + intensity[pos];
        }
      }
      // fill out
      if (sum > _max)
        out[y * d + x] = 0.0;
      else
        if (sum < _min)
          out[y * d + x] = 0.0;
        else
          out[y * d + x] = atan2(tmp_1, tmp_2);
    }
    // zero filling
    out[shift + x] = 0.0;
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
