/************************************************************************
   awgn_bpsk.c -- Program / the BER performance with BPSK modulaton

   Written:  2015.08.26  Yuto Hama / Yokohama National University

   Update :  2016.04.29  Yuto Hama / Yokohama National University      
   Reason :  Bug fix

   Copyright (c) Yuto Hama
*************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<complex.h>

#define INFO_LENGTH 2048 // information length
#define PI M_PI 
#define TRIAL 1000 // the number of trial
#define TRIAL_MIN 2000
#define EbN0_MAX 10
#define EbN0_MIN 0
#define INTERVAL 0.25 // prot interval (limited as x*INTERVAL = 1)
#define N_ERROR 2000 // the number of error to break (if it's 0, not break)
#define INF 1000000000


/****** functions ******/

void setup_prot(int *interval, int *point, int *n_trial){

  if(INTERVAL >= 1){
    *interval = INTERVAL;
    *point = 1;
  }else{
    *interval = 1;
    *point = (int) 1.0 / INTERVAL;
  }

  if(N_ERROR == 0){
    *n_trial = TRIAL;
  }else{
    *n_trial = INF;
  }
  
}

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

void calculate_ber(int *be, int *x, int *y, int *trial, int *flag){

  int i;
  
  for(i=0;i<INFO_LENGTH;i++){
    if(x[i] != y[i]){
      (*be)++;
    }
  }

  if(N_ERROR != 0 && *be > N_ERROR && *trial >= (TRIAL_MIN-1)){
    (*trial)++;
    *flag = 1;
  }
  
}


/****** main ******/

int main(void){

  int i, j, k;
  int interval, point;
  int n_trial;
  int *x1, *x3;
  complex *x2;
  int EbN0;
  int trial;
  double snr, sigma;
  int be;
  double ber, ber_trial;
  int flag = 0;
  FILE *fp1;
  char name1[100];

  // メモリの動的確保
  x1 = malloc(sizeof(int) *INFO_LENGTH);
  x2 = malloc(sizeof(complex) *INFO_LENGTH);
  x3 = malloc(sizeof(int) *INFO_LENGTH);

  
  // random関数の初期化
  srandom((unsigned)time(NULL));

  // ファイル出力の設定
  sprintf(name1,"awgn_bpsk_ber.txt");
  fp1 = fopen(name1, "w");

  // シミュレーションに関する値の設定
  setup_prot(&interval, &point, &n_trial);

  for(EbN0=EbN0_MIN;EbN0<=EbN0_MAX*point;EbN0+=interval){

    snr=pow(10,(EbN0/(double)point/(double)10.0));
    sigma=sqrt((double)1.0/(double)(2*snr));

    be = 0;
    flag = 0;

    for(trial=0;trial<n_trial;trial++){

      make_signal(x1, INFO_LENGTH);
      BPSKmodulation(x1, x2, INFO_LENGTH);

      gaussiannoise(x2, sigma, INFO_LENGTH);
      BPSKdemodulation(x2, x3, INFO_LENGTH);

      calculate_ber(&be, x1, x3, &trial, &flag);
      if(flag == 1){
        break;
      }

      ber_trial = be / (INFO_LENGTH * (double) (trial+1));
      fprintf(stderr,"EbN0 = %f trial = %d BER = %e\r",EbN0/(double)point, trial, ber_trial);
      
    }

    ber = be / (INFO_LENGTH * (double) trial);
    printf("EbN0 = %f trial = %d BER = %e\n",EbN0/(double)point, trial, ber);

    fprintf(fp1,"%lf %lf\n", EbN0/(double)point, ber);
    fflush(fp1);
    
  }

  fflush(stdout);
  fflush(stderr);

  return 0;
}
