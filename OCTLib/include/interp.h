/*******************************************************************************
*  $Id$
*  Copyright (C) 2006 Brian Bradie (bbradie@cnu.edu)
*  All rights reserved.
*  web-site: http://www.pcs.cnu.edu/~bbradie/cinterpolation.html
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the http://octlab.googlecode.com/svn/trunk/COPYRIGHT.TXT web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

double neville ( int, double*, double*, double );
double* divdiff ( int, double*, double* );
double nf_eval ( int, double*, double*, double );
void cubic_nak ( int, double*, double*, double*, double*, double* );
void cubic_clamped ( int, double*, double*, double*, double*,
                     double*, double, double );
double spline_eval ( int, double*, double*, double*, double*,
                     double*, double );
