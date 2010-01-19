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
DllExport I8 OL_doppler_fltr_M(U32, U32, U32, U32, DBL, DBL, DBL *, DBL *,
                               DBL *, DBL *);
}

/* Doppler OCT with filtering for M-stripped data main function
  PURPOSE:
    calculate Doppler frequency shifts using Kasai autocorrelation function
    for B-scan stripped by M-mode strips, then filter obtained phases based on
    intensity information. If intensity is out of defined range the phase is
    zero. Read description for Doppler.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    stripsize - width of M-mode strips within B-scan
    offset - start position of first M-mode strip within B-scan
    min - minimum value for intensity range
    max - maximum value for intensity range
    intensity - pointer to buffer with intensities, structure B-scan after FFT
    (size: X * Y)
    Re - pointer to buffer with real part of B-scan after FFT (size: X * Y)
    Im - pointer to buffer with imaginary part of B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: ((X - offset) / stripsize) * Y)
  
  REMARKS:
    note that last row will contain ZEROs
*/
I8 OL_doppler_fltr_M(U32 X, U32 Y, U32 stripsize, U32 offset, DBL min, DBL max,
                     DBL *intensity, DBL *Re, DBL *Im, DBL *out) {
  // simple checks
  if (stripsize < 2) return EXIT_FAILURE;
  I32 d = (X - offset) / stripsize;
  if (d < 2) return EXIT_FAILURE;
  DBL _max = max * stripsize, _min = min * stripsize;
  I32 x, y, shift = (Y - 1) * d;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (x = 0; x < d; x++) {  // horizontal
    for (y = 0; y < static_cast<I32>(Y - 1); y++) {  // vertical
      DBL tmp_1 = 0.0, tmp_2 = 0.0, sum = 0.0;
      for (U32 i = x * stripsize; i < (x + 1) * stripsize; i++) {
        // Q(m)I(m+1) - I(m)Q(m+1)
        tmp_1 = tmp_1 + Im[y * X + i + offset] * Re[(y + 1) * X + i + offset] -\
                Re[y * X + i + offset] * Im[(y + 1) * X + i + offset];
        // Q(m)Q(m+1) + I(m)I(m+1)
        tmp_2 = tmp_2 + Im[y * X + i + offset] * Im[(y + 1) * X + i + offset] +\
                Re[y * X + i + offset] * Re[(y + 1) * X + i + offset];
        // mean value
        sum = sum + intensity[y * X + i + offset];
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
