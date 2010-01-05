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
DllExport DBL OL_pearson(U32, DBL *, DBL *);
DllExport I8  OL_pearson_map(U32, U32, U32, DBL *, DBL *, DBL *);
}

// speckle pearson coefficient main function
DBL OL_pearson(U32 SIZE, DBL *ptr1, DBL *ptr2) {
  DBL sum_value1 = 0.0, sum_value2 = 0.0, sum_value3 = 0.0;
  DBL mean_value1 = accumulate(ptr1, ptr1 + SIZE, 0.0) / SIZE;
  DBL mean_value2 = accumulate(ptr2, ptr2 + SIZE, 0.0) / SIZE;

  for (DBL *t1 = ptr1, *t2 = ptr2; t1 < ptr1 + SIZE; t1++, t2++) {
    sum_value1 = sum_value1 + (*t1 - mean_value1) * (*t1 - mean_value1);
    sum_value2 = sum_value2 + (*t2 - mean_value2) * (*t2 - mean_value2);
    sum_value3 = sum_value3 + (*t1 - mean_value1) * (*t2 - mean_value2);
  }
  return (SIZE * sum_value3) / ((SIZE - 1) * sqrt(sum_value1 * sum_value2));
}
DBL (*fp_pearson)(U32, DBL *, DBL *) = OL_pearson;

/************OL_pearson_map************/
I8 OL_pearson_map(U32 X, U32 Y, U32 radius, DBL *line1, DBL *line2,
                  DBL *lineOUT) {
  return rsm_frame2(X, Y, radius, line1, line2, lineOUT, fp_pearson);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
