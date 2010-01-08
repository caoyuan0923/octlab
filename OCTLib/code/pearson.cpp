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
DllExport I8 OL_pearson_map(U32, U32, U32, U32, DBL *, DBL *, DBL *);
}

I8 OL_pearson_map(U32 X, U32 Y, U32 x_r, U32 y_r, DBL *in1, DBL *in2,
                  DBL *out) {
  U32 d = X - 2 * x_r, x_d = 2 * x_r + 1, y_d = 2 * y_r + 1, size = x_d * y_d;
  I32 x, y;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (x = 0; x < static_cast<I32>(d); x++) {  // horizontal
    for (y = 0; y < static_cast<I32>(Y - 2 * y_r); y++) {  // vertical
      DBL mean1 = 0.0, mean2 = 0.0;
      // loop for mean
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // sum1 & sum2
          mean1 = mean1 + in1[pos];
          mean2 = mean2 + in2[pos];
        }
      }
      mean1 = mean1 / size;
      mean2 = mean2 / size;
      DBL sum1 = 0.0, sum2 = 0.0, sum12 = 0.0;
      // loop for pearson
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // sum^2
            sum1 = sum1 + (in1[pos] - mean1) * (in1[pos] - mean1);
            sum2 = sum2 + (in2[pos] - mean2) * (in2[pos] - mean2);
          sum12 = sum12 + (in1[pos] - mean1) * (in2[pos] - mean2);
        }
      }
      // fill out
      out[y * d + x] = sum12 / (sqrt(sum1 * sum2));
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
