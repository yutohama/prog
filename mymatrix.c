#include "mymatrix.h"


/****** functions for calculating matrix ******/

void hermitian_transpose(double _Complex **x, double _Complex **y, int m, int n){

   int i,j;

   // 転置
   for(i=0;i<m;i++){
     for(j=0;j<n;j++){
       y[j][i]=x[i][j];
     }
   }
   // 複素共役を取る
   for(i=0;i<n;i++){
     for(j=0;j<m;j++){
       y[i][j]=conj(y[i][j]);
     }
   }

 }

void multi_matrix(double _Complex **a, int m_a, int n_a, double _Complex **b, int m_b, int n_b, double _Complex **y){

  int i, j, k;

  if(n_a != m_b){
    printf("These matrix can't be multiplied.\n");
  }

  else{
    for(i=0;i<m_a;i++){
      for(j=0;j<n_b;j++){
        y[i][j] = 0.0 + 0.0*I;
        for(k=0;k<n_a;k++){
          y[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }

}

void inv(double _Complex **x, double _Complex **y, int n){

  int i, j, k;
  double _Complex buf;
  double _Complex **z; // xの退避用行列

  z = malloc(sizeof(double _Complex*) *n);
  for(i=0;i<n;i++){
    z[i] = malloc(sizeof(double _Complex) *n);
  }
  for(j=0;j<n;j++){
    for(i=0;i<n;i++){
      z[i][j] = x[i][j];
    }
  }

  //単位行列を作る
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      y[i][j]=(i==j)?1.0:0.0;
    }
  }
  //掃き出し法
  for(i=0;i<n;i++){
    buf=1/z[i][i];
    for(j=0;j<n;j++){
      z[i][j]*=buf;
      y[i][j]*=buf;
    }
    for(j=0;j<n;j++){
      if(i!=j){
        buf=z[j][i];
        for(k=0;k<n;k++){
          z[j][k]-=z[i][k]*buf;
          y[j][k]-=y[i][k]*buf;
        }
      }
    }
  }

  for(i=0;i<n;i++){
    free(z[i]);
  }
  free(z);

}
