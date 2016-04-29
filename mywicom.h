/************************************************************************
   mywicom.h -- Header file / basic functions of wireless communication

   Written:  2016.04.29  Yuto Hama / Yokohama National University

   Update :  2016.04.29  Yuto Hama / Yokohama National University      
   Reason :  nothing

   Copyright (c) Yuto Hama
*************************************************************************/

#ifndef MYWICOM_H
#define MYWICOM_H

#include<stdlib.h>
#include<math.h>
#include<complex.h>


/****** prototype declaration ******/
void setup_prot(int *interval, int *point, double define_interval, int *n_trial, int define_trial, int n_error);
void calculate_ber(int *be, int *x, int *y, int *trial, int n_error, int define_trial_min, int *flag, int n);
void make_signal(int *x, int n);
void BPSKmodulation(int *x, complex *y, int n);
void BPSKdemodulation(complex *x, int *y, int n);
void QPSKmodulation(int *x, complex *y, int n);
void QPSKdemodulation(complex *x, int *y, int n);
void gaussiannoise(complex *x, double sigma, int n);


#endif
