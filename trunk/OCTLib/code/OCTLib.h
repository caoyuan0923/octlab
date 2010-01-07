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

#ifndef OCTLIB_H
#define OCTLIB_H
#ifdef __cplusplus

// if we use M$ VS C compiler
#if defined(_MSC_VER)  // M$ Visual Studio
  #pragma warning(disable: 4996)
  #define DllExport __declspec(dllexport)
#else
  #define DllExport
#endif

/******************************************************************************/
// define some external global header files

// define OpenMP support
#ifdef _OPENMP
  #include <omp.h>
#endif
// need for built-in math functions
#include <cmath>
// need for STL algorithms
#include <numeric>
#include <algorithm>
#include <map>
// common for c++
using namespace std;

/******************************************************************************/
// define some global constants

const double kTwoPi = 6.28318530717958623;

/******************************************************************************/
// define some type defs and variables
// NOTE!!! avoid any defines in other source files!!!

typedef unsigned char   U8;   // 1 byte
typedef unsigned short  U16;  // 2 bytes
typedef unsigned long   U32;  // 4 bytes
typedef signed char     I8;   // 1 byte
typedef short           I16;  // 2 bytes
typedef int             I32;  // 4 bytes
typedef float           SGL;  // 4 bytes
typedef double          DBL;  // 8 bytes
typedef pair<DBL, I32>  DI_Pair;

/******************************************************************************/
// global functions

/************rsm_frame2************/
template <typename T1, typename T2>
I8 rsm_frame2(U32 X, U32 Y, U32 radius, T2 *line_1, T2 *line_2, T1 *lineOUT,
              T1 (*fp)(U32, T2 *, T2 *)) {
  U32 r2 = 2 * radius, x_d = X - r2, d = r2 + 1, size = d * d;
  I32 k;
  // parallel run by columns
  #pragma omp parallel for default(shared) private(k)
  for (k = 0; k < static_cast<I32>(x_d); k++) {
    T2 *line1 = new T2[size];
    T2 *line2 = new T2[size];
    for (U32 y = 0, pos = k, pos2 = 0; y < r2;
         y++, pos = pos + X, pos2 = pos2 + d) {
      copy(line_1 + pos, line_1 + pos + d, line1 + pos2);
      copy(line_2 + pos, line_2 + pos + d, line2 + pos2);
    }
    for (U32 y = r2, pos = r2 * X + k, pos2 = k; y < Y;
         y++, pos = pos + X, pos2 = pos2 + x_d) {
      copy(line_1 + pos, line_1 + pos + d, line1 + d * (y % d));
      copy(line_2 + pos, line_2 + pos + d, line2 + d * (y % d));
      lineOUT[pos2] = fp(size, line1, line2);
    }
    delete [] line1;
    delete [] line2;
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/************ find_index ************/
inline I32 find_index(map<DBL, I32> *spectrum_map, DBL key) {
  map<DBL, I32>::iterator spectrum_p = spectrum_map->lower_bound(key);
  return (spectrum_p->second - 1);
}

/******************************************************************************/

#endif
#endif

/******************************************************************************/
