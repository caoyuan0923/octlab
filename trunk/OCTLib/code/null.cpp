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
DllExport I8  OL_null_map_i16(U32, U32, U32, I16 *, SGL *);
DllExport I8  OL_null_map_u16(U32, U32, U32, U16 *, SGL *);
DllExport I8  OL_null_map_i32(U32, U32, U32, I32 *, DBL *);
DllExport I8  OL_null_map_u32(U32, U32, U32, U32 *, DBL *);
DllExport I8  OL_null_map_sgl(U32, U32, U32, SGL *, SGL *);
DllExport I8  OL_null_map_dbl(U32, U32, U32, DBL *, DBL *);
}

// null main function
template <typename T1, typename T2>
T1 null(U32 SIZE, T2 *ptr) {
  for (T2 *t = ptr; t < ptr+SIZE; t++) *t;
  return *ptr;
}
SGL (*fp_null_i16)(U32, I16 *) = null;
SGL (*fp_null_u16)(U32, U16 *) = null;
DBL (*fp_null_i32)(U32, I32 *) = null;
DBL (*fp_null_u32)(U32, U32 *) = null;
SGL (*fp_null_sgl)(U32, SGL *) = null;
DBL (*fp_null_dbl)(U32, DBL *) = null;

/************OL_null_map************/
// null map for I16
I8 OL_null_map_i16(U32 X, U32 Y, U32 radius, I16 *lineIN, SGL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_null_i16);
}

// null map for U16
I8 OL_null_map_u16(U32 X, U32 Y, U32 radius, U16 *lineIN, SGL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_null_u16);
}

// null map for I32
I8 OL_null_map_i32(U32 X, U32 Y, U32 radius, I32 *lineIN, DBL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_null_i32);
}

// null map for U32
I8 OL_null_map_u32(U32 X, U32 Y, U32 radius, U32 *lineIN, DBL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_null_u32);
}

// null map for SGL
I8 OL_null_map_sgl(U32 X, U32 Y, U32 radius, SGL *lineIN, SGL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_null_sgl);
}

// null map for DBL
I8 OL_null_map_dbl(U32 X, U32 Y, U32 radius, DBL *lineIN, DBL *lineOUT) {
  return rsm_frame(X, Y, radius, lineIN, lineOUT, fp_null_dbl);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
