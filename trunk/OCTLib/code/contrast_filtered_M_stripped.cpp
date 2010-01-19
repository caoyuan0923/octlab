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

// standard header
#include <numeric>
// common header
#include "./OCTLib.h"

// for DLL export
extern "C" {
DllExport I8 OL_contrast_map_fl_M(U32, U32, U32, U32, DBL, DBL, DBL *, DBL *);
}

/* contrast_map with filtering for M-stripped data main function
  PURPOSE:
    calculate speckle contrast for B-scan stripped by M-mode strips, then filter
    obtained contrast values based on intensity information. If intensity is out
    of defined range the contrast values is zero. Read description for
    contrast.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    stripsize - width of M-mode strips within B-scan
    offset - start position of first M-mode strip within B-scan
    min - minimum value for intensity range
    max - maximum value for intensity range
    in - pointer to buffer with B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: ((X - offset) / stripsize) * Y)
*/
I8 OL_contrast_map_fl_M(U32 X, U32 Y, U32 stripsize, U32 offset, DBL min,
                        DBL max, DBL *in, DBL *out) {
  // simple checks
  if (stripsize < 2) return EXIT_FAILURE;
  I32 d = (X - offset) / stripsize;
  if (d < 2) return EXIT_FAILURE;
  I32 x, y;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (x = 0; x < d; x++) {  // horizontal
    for (y = 0; y < static_cast<I32>(Y); y++) {  // vertical
      DBL mean = 0.0;
      // loop for mean
      for (U32 i = x * stripsize; i < (x + 1) * stripsize; i++) {
        mean = mean + in[y * X + i + offset];
      }
      mean = mean / stripsize;
      // fill out
      if (mean > max)
        out[y * d + x] = 0.0;
      else
        if (mean < min) {
          out[y * d + x] = 0.0;
        } else {
          DBL  tmp = 0.0;
          // loop for contrast
          for (U32 i = x * stripsize; i < (x + 1) * stripsize; i++) {
            tmp = tmp + (in[y * X + i + offset] - mean) * \
                  (in[y * X + i + offset] - mean);
          }
          // simple checks
          if (mean == 0.0) mean = 1.0;
          out[y * d + x] = sqrt(tmp / (stripsize - 1)) / mean;
        }
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
