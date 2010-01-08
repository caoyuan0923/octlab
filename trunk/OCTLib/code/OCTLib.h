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
// global function prototypes

I32 find_index(map<DBL, I32> *spectrum_map, DBL key);

/******************************************************************************/

#endif
#endif

/******************************************************************************/
