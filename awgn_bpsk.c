/*
AWGN BPSK
2015.8.26
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<complex.h>

#define INFO_LENGTH 2048
#define PI M_PI
#define TRIAL 1000

void make_signal(int *x, int n){

  int i;
  
  for(i=0;i<n;i++){
    x[i] = random() % 2;
  }
  
}

void BPSKmodulation(int *x, complex *y, int n){

  int i;

  for(i=0;i<n;i++){
    y[i] = 2 * x[i] - 1;
  }
}

void gaussiannoise(complex *x, double sigma, int n){

  int i;
  double u1, u2;
  complex v;

  //ボックス・ミュラー
  for(i=0;i<n;i++){
    
    do{
      u1=(double)random()/RAND_MAX;
    }while(u1==0.0);
    do{
      u2=(double)random()/RAND_MAX;
    }while(u2==0.0);
 
    v=sqrt(-2.0*log(u1))*cos(2.0*PI*u2)+I*sqrt(-2.0*log(u1))*sin(2.0*PI*u2);
 
    x[i] = x[i] + v * sigma;

  }
  
}

void BPSKdemodulation(complex *x, int *y, int n){

  int i;

  for(i=0;i<n;i++){
    if(creal(x[i]) < 0){
      y[i] = 0;
    }else{
      y[i] = 1;
    }
  }
  
}

int main(void){

  int i, j, k;
  int *x1, *x3;
  complex *x2;
  int EbN0;
  int trial;
  double snr, sigma;
  int be;
  double ber, ber_trial;

  // メモリの動的確保
  x1 = malloc(sizeof(int) *INFO_LENGTH);
  x2 = malloc(sizeof(complex) *INFO_LENGTH);
  x3 = malloc(sizeof(int) *INFO_LENGTH);

  // random関数の初期化
  srandom((unsigned)time(NULL));

  for(EbN0=0;EbN0<31;EbN0+=1){

    snr=pow(10,(EbN0/(double)10.0));
    sigma=sqrt((double)1.0/(double)(2*snr));

    be = 0;

    for(trial=0;trial<TRIAL;trial++){

      make_signal(x1, INFO_LENGTH);
      BPSKmodulation(x1, x2, INFO_LENGTH);

      gaussiannoise(x2, sigma, INFO_LENGTH);
      BPSKdemodulation(x2, x3, INFO_LENGTH);

      for(i=0;i<INFO_LENGTH;i++){
        if(x1[i] != x3[i]){
          be++;
        }
      }

      ber_trial = be / (INFO_LENGTH * (double) (trial+1));
      fprintf(stderr,"EbN0 = %d trial = %d BER = %e\r",EbN0, trial, ber_trial);
      
    }

    ber = be / (INFO_LENGTH * (double) TRIAL);
    printf("EbN0 = %d trial = %d BER = %e\n",EbN0, trial+1, ber);
    
  }

  return 0;
}
