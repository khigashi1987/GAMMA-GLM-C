/*
 * gammaglm.c
 * MCMC parameter estimation for Gamma-Generalized linear model
 * Koichi HIGASHI
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gammaglm.h"
#include "read.h"
#include "write.h"

static char opts[] = "s:e:I:h";

int main(int argc, char **argv){
    char c;
    char *train;
    char *model;
    int iter = ITER_DEFAULT;
    double sigma = SIGMA_DEFAULT;
    double eps = EPS_DEFAULT;
    int n_samples;
    int n_features;
    double *y;
    double **features;
    double *wa;
    double *wb;
    
    while((c = getopt(argc, argv, opts)) != -1){
        switch(c){
            case 's': sigma = atof(optarg); break;
            case 'e': eps = atof(optarg); break;
            case 'I': iter = atoi(optarg); break;
            case 'h': usage(); break;
            default: usage(); break;
        }
    }
    if(argc - optind != 2){
        usage();
    }else{
        train = argv[optind];
        model = argv[optind+1];
    }

    read_data(train, &y, &features, &n_samples, &n_features);
    fprintf(stdout,"n_samples  : %d\n",n_samples);
    fprintf(stdout,"n_features : %d\n",n_features);
    learn_model(y, features, n_samples, n_features, &wa, &wb, iter, eps, sigma, model);
    save_model(model, wa, wb, n_features);
    
    return 0;
}

void usage(){
    fprintf(stderr,"gammaglm: MCMC parameter estimation for Gamma-Generalized linear model\n");
    fprintf(stderr,"usage: gammaglm [-I iter] [-e eps] [-s sigma] TRAIN MODEL\n");
    exit(1);
}
