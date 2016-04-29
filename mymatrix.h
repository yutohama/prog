/************************************************************************
   mymatrix.h -- Header file / functions to use some matrix calculation

   Written:  2016.04.29  Yuto Hama / Yokohama National University

   Update :  2016.04.29  Yuto Hama / Yokohama National University      
   Reason :  nothing

   Copyright (c) Yuto Hama
*************************************************************************/

#ifndef MYMATRIX_H
#define MYMATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>

/****** prototype declaration ******/
void hermitian_transpose(double _Complex **x, double _Complex **y, int m, int n);
void multi_matrix(double _Complex **a, int m_a, int n_a, double _Complex **b, int m_b, int n_b, double _Complex **y);
void inv(double _Complex **x, double _Complex **y, int n);

  
#endif
