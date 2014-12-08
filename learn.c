/*
 * learn.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "learn.h"
#include "random.h"

void learn_model(double *y, double **features, int n_samples, int n_features, double **wa, double **wb, int iter, double eps, double sigma, char *model){
    int len = n_features * 2;
    int *seq;
    int i, m, t, f;
    int accept;
    double acceptance_ratio;
    double loglikelihood;
    FILE *ofp_mcmclog;
    char outfilename[100];
    
    sprintf(outfilename,"%s.mcmclog",model);
    if(NULL == (ofp_mcmclog = fopen(outfilename,"w"))){
        fprintf(stderr,"learn:: cannnot open %s",outfilename);
        exit(1);
    }
    
    (*wa) = (double *)calloc(n_features,sizeof(double));
    (*wb) = (double *)calloc(n_features,sizeof(double));
    seq = (int *)calloc(len,sizeof(int));
    for(i = 0;i < len;i++){
        seq[i] = i;
    }
    init_random();
    
    // MCMC
    for(m = 0;m < iter;m++){
        accept = 0;
        seq_shuffle(seq, len);
        for(t = 0;t < len;t++){
            if(seq[t] < n_features){
                f = seq[t];
                accept += update((*wa), f, (*wa), (*wb), y, features, n_samples, n_features, eps, sigma);
            }else{
                f = seq[t] - n_features;
                accept += update((*wb), f, (*wa), (*wb), y, features, n_samples, n_features, eps, sigma);
            }
        }
        acceptance_ratio = (double)accept / (double)len * 100.0;
        loglikelihood = gammaglm_likelihood((*wa), (*wb), y, features, n_samples, n_features);
        printf("iter[%d] ...LogLikelihood = %.8f\tAcceptance Ratio = %.2f%%\n",m,loglikelihood,acceptance_ratio);
        fprintf(ofp_mcmclog,"%d\t%.8f\t%.2f\n",m,loglikelihood,acceptance_ratio);
    }
    fclose(ofp_mcmclog);
    return;
}

int update(double *w, int f, double *wa, double *wb, double *y, double **features, int n_samples, int n_features, double eps, double sigma){
    double pw = w[f];
    double lik0,lik1;
    
    lik0 = gammaglm_likelihood(wa, wb, y, features, n_samples, n_features) + lnorm(w[f], sigma);
    w[f] += eps * rand_snormal();
    lik1 = gammaglm_likelihood(wa, wb, y, features, n_samples, n_features) + lnorm(w[f], sigma);
    
    if(bernoulli(exp(lik1 - lik0))){
        return 1; // accept
    }else{
        w[f] = pw;
        return 0; // revert
    }
}

double gammaglm_likelihood(double *wa, double *wb, double *y, double **features, int n_samples, int n_features){
    double a;
    double b;
    int n,k;
    double lik = 0.0;
    
    for(n = 0;n < n_samples;n++){
        a = 0.0;
        b = 0.0;
        for(k = 0;k < n_features;k++){
            a += wa[k] * features[n][k];
            b += wb[k] * features[n][k];
        }
        a = exp(a);
        b = exp(b);
        lik += gamma_likelihood(a,b,y[n]);
    }
    return lik;
}

double gamma_likelihood(double a, double b, double yn){
    return (a - 1.0) * log(yn) - lgamma(a) - a * log(b) - yn / b;
}

double lnorm(double w, double sigma){
    return - (w * w) / (2.0 * sigma * sigma);
}
