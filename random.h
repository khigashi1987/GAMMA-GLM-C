/*
 * random.h
 */
#ifndef GAMMAGLM_RANDOM_H
#define GAMMAGLM_RANDOM_H
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void init_random(void);
extern void seq_shuffle(int *seq, int len);
extern double Uniform(void);
extern double rand_snormal(void);
extern int bernoulli(double p);

#endif
