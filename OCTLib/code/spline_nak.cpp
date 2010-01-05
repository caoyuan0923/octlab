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
// header for spline interpolation
#include "./interp.h"

// for DLL export
extern "C" {
DllExport I8 OL_spline_nak(U32, U32, DBL *, DBL *, DBL *, DBL *);
}

// spline_nak main function
I8 OL_spline_nak(U32 n, U32 Y, DBL *x, DBL *XX, DBL *in, DBL *out) {
  I32 i;
  #pragma omp parallel for default(shared) private(i)
  for (i = 0; i < static_cast<I32>(Y); i++) {
    DBL *b = new DBL[n];
    DBL *c = new DBL[n];
    DBL *d = new DBL[n];
    cubic_nak(n, x, in + n * i, b, c, d);
    for (U32 j = 0; j < n; j++)
      out[n * i + j] = spline_eval(n, x, in + n * i, b, c, d, XX[j]);
    delete [] b;
    delete [] c;
    delete [] d;
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
