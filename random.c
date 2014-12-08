/*
 * random.c
 */
#include <stdlib.h>
#include "random.h"
#include "MT.h"

void init_random(void){
    init_genrand((unsigned)time(NULL));
}

void seq_shuffle(int *seq, int len){
    int i,j,k;
    for(i = 0;i < len;i++){
        j = abs(genrand_int32() % len);
        int t = seq[i];
        seq[i] = seq[j];
        seq[j] = t;
    }
}

double Uniform(void){
    return genrand_real3();
}

double rand_snormal(void){
    return sqrt( -2.0*log(Uniform()) ) * sin( 2.0*M_PI*Uniform() );
}

int bernoulli(double p){
    if(genrand_real3() < p){
        return 1;
    }else{
        return 0;
    }
}
