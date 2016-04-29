/************************************************************************
   mymimo.h -- Header file / functions for MIMO systems

   Written:  2016.04.29  Yuto Hama / Yokohama National University

   Update :  2016.04.29  Yuto Hama / Yokohama National University      
   Reason :  nothing

   Copyright (c) Yuto Hama
*************************************************************************/

#ifndef MYMIMO_H
#define MYMIMO_H

#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<mymatrix.h>

/****** prototype declaration ******/
void MIMO_make_signal(int *x, int **y, int a, int n);
void MIMO_BPSKmodulation(int **x, complex **y, int a, int n);
void MIMO_BPSKdemodulation(complex **x, int **y, int a, int n);
void MIMO_QPSKmodulation(int **x, complex **y, int a, int n);
void MIMO_QPSKdemodulation(complex **x, int **y, int a, int n);
complex MIMO_make_fading(int path);
void MIMO_gaussiannoise(complex **x, double sigma, int r, int n);
void MIMO_fading(complex **x, complex **y, complex **h, int t, int r, int n);
void considering_noise_mmse(complex **x, double sigma, int t);
void make_weight_matrix_mmse(complex **h, int r, int t, double sigma, complex **w);
void simplified_matched_filter(complex **x, int t, int r, complex **y);
void make_weight_matrix_mf(complex **h, int r, int t, complex **w);
void return_signal_int(int **x, int *y, int a, int n);
void return_signal_couble(double **x, double *y, int a, int n);
void return_signal_complex(complex **x, complex *y, int a, int n);

  
#endif
