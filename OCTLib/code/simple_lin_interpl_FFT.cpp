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

// standart headers
#include <functional>
#include <algorithm>
#include <map>
// common header
#include "./OCTLib.h"
// need for FFT analysis
#include "./fftw3.h"

// for DLL export
extern "C" {
DllExport I8 OL_smpl_lin_fft_u8(U32, U32, U32, U32, I8, I8, DBL *, U8 *,
                                DBL *, DBL *);
DllExport I8 OL_smpl_lin_fft_i16(U32, U32, U32, U32, I8, I8, DBL *, I16 *,
                                 DBL *, DBL *);
DllExport I8 OL_smpl_lin_fft_u16(U32, U32, U32, U32, I8, I8, DBL *, U16 *,
                                 DBL *, DBL *);
DllExport I8 OL_smpl_lin_fft_i32(U32, U32, U32, U32, I8, I8, DBL *, I32 *,
                                 DBL *, DBL *);
DllExport I8 OL_smpl_lin_fft_u32(U32, U32, U32, U32, I8, I8, DBL *, U32 *,
                                 DBL *, DBL *);
DllExport I8 OL_smpl_lin_fft_sgl(U32, U32, U32, U32, I8, I8, DBL *, SGL *,
                                 DBL *, DBL *);
DllExport I8 OL_smpl_lin_fft_dbl(U32, U32, U32, U32, I8, I8, DBL *, DBL *,
                                 DBL *, DBL *);
}

template <typename T1>
I8 simple_lin_fft(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                  I8 dB_flag, DBL *spectrum, T1 *in, DBL *intensity,
                  DBL *phase) {
  // initialize map
  map<DBL, I32> spectrum_map;
  U32 size = end_index - start_index;
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
  I32 *li = static_cast<I32 *>(fftw_malloc(sizeof(I32) * (size - 2)));
  DBL *p = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * (size - 2)));
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_r2r_1d(size, intensity, phase, FFTW_R2HC,
                    FFTW_ESTIMATE);
  U32 width = static_cast<U32>(size/2);
  I32 j, z;
  // load wavelength spectrum
  for (z = 0; z < static_cast<I32>(size); z++)
    spectrum_map.insert(DI_Pair(spectrum[z], z));
  DBL start_wavenumber = 1 / spectrum[0];
  // linear wavenumber step
  DBL wavenumber_step = (start_wavenumber - (1 / spectrum[size - 1])) / \
                        (size - 1);
  // Hanning window for first and last elements
  if (hann_flag)
    hann_win[0] = hann_win[size - 1] = 0.0;
  else
    hann_win[0] = hann_win[size - 1] = 1.0;
  // Hanning window for all other elements and coefficients and indexes for
  // linear interpolation
  #pragma omp parallel for default(shared) private(z)
  for (z = 1; z < static_cast<I32>(size - 1); z++) {
    if (hann_flag)
      hann_win[z] = 0.5 * (1 - cos(kTwoPi * z / size));
    else
      hann_win[z] = 1.0;
    // nonlinear wavelength corresponding to linear wavenumber
    DBL nl = 1 / (start_wavenumber - wavenumber_step * z);
    // close spectrum wavelength (its index) from left side
    li[z - 1] = find_index(&spectrum_map, nl);
    // the relative distance (in range 0...1) between linear and nonlinear
    // wavelengths calculated before
    p[z - 1] = (nl - spectrum[li[z - 1]]) / \
               (spectrum[li[z - 1] + 1] - spectrum[li[z - 1]]);
  }
  // parallel run by A-lines
  #pragma omp parallel for default(shared) private(j)
  for (j = 0; j < static_cast<I32>(Y); j++) {
    DBL *tmp_fft_in = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    DBL *tmp_fft_out = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    U32 pos = j * width;
    U32 _pos = j * X + start_index;
    // linear interpolation: keep first and last elements
    tmp_fft_in[0] = hann_win[0] * in[_pos];
    tmp_fft_in[size - 1] = hann_win[size - 1] * in[_pos + size - 1];
    // linear interpolation
    // new value for calculated nonlinear wavelength but linear in wavenumber
    for (U32 i = 0; i < size - 2; i++)
      tmp_fft_in[i + 1] = hann_win[i + 1] * ((1 - p[i]) * in[_pos + li[i]] + \
                          p[i] * in[_pos + li[i] + 1]);
    // perform FFT using FFTW3 library
    fftw_execute_r2r(fft_p, tmp_fft_in, tmp_fft_out);
    // ZERO components
    if (dB_flag)
      intensity[pos] = 20 * log10(abs(tmp_fft_out[0]));
    else
      intensity[pos] = tmp_fft_out[0];
    phase[pos] = 0.0;
    // construct intensity and phase information
    for (U32 pos1 = 1, pos2 = size - 1; pos1 < width; pos1++, pos2--) {
      // intensity
      if (dB_flag)
        intensity[pos + pos1] = 20 * log10(sqrt(tmp_fft_out[pos1] * \
                                tmp_fft_out[pos1] + tmp_fft_out[pos2] * \
                                tmp_fft_out[pos2]));
      else
        intensity[pos + pos1] = sqrt(tmp_fft_out[pos1] * tmp_fft_out[pos1] + \
                                tmp_fft_out[pos2] * tmp_fft_out[pos2]);
      // phase
      phase[pos + pos1] = atan2(tmp_fft_out[pos2], tmp_fft_out[pos1]);
    }
    fftw_free(tmp_fft_in);
    fftw_free(tmp_fft_out);
  }  // end of parallel code
  fftw_destroy_plan(fft_p);
  fftw_free(hann_win);
  fftw_free(li);
  fftw_free(p);
  return EXIT_SUCCESS;
}

/************OL_smpl_lin_fft************/
// simple linear interpolation + FFT for U8
I8 OL_smpl_lin_fft_u8(U32 X, U32 Y, U32 start_index, U32 end_index,
                      I8 hann_flag, I8 dB_flag, DBL *spectrum, U8 *in,
                      DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

// simple linear interpolation + FFT for I16
I8 OL_smpl_lin_fft_i16(U32 X, U32 Y, U32 start_index, U32 end_index,
                       I8 hann_flag, I8 dB_flag, DBL *spectrum, I16 *in,
                       DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

// simple linear interpolation + FFT for U16
I8 OL_smpl_lin_fft_u16(U32 X, U32 Y, U32 start_index, U32 end_index,
                       I8 hann_flag, I8 dB_flag, DBL *spectrum, U16 *in,
                       DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

// simple linear interpolation + FFT for I32
I8 OL_smpl_lin_fft_i32(U32 X, U32 Y, U32 start_index, U32 end_index,
                       I8 hann_flag, I8 dB_flag, DBL *spectrum, I32 *in,
                       DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

// simple linear interpolation + FFT for U32
I8 OL_smpl_lin_fft_u32(U32 X, U32 Y, U32 start_index, U32 end_index,
                       I8 hann_flag, I8 dB_flag, DBL *spectrum, U32 *in,
                       DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

// simple linear interpolation + FFT for SGL
I8 OL_smpl_lin_fft_sgl(U32 X, U32 Y, U32 start_index, U32 end_index,
                       I8 hann_flag, I8 dB_flag, DBL *spectrum, SGL *in,
                       DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

// simple linear interpolation + FFT for DBL
I8 OL_smpl_lin_fft_dbl(U32 X, U32 Y, U32 start_index, U32 end_index,
                       I8 hann_flag, I8 dB_flag, DBL *spectrum, DBL *in,
                       DBL *intensity, DBL *phase) {
  return simple_lin_fft(X, Y, start_index, end_index, hann_flag, dB_flag,
                        spectrum, in, intensity, phase);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
