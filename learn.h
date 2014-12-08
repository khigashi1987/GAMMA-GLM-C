/*
 * learn.h
 */
#ifndef GAMMAGLM_LEARN_H
#define GAMMAGLM_LEARN_H
#include <stdio.h>
#include <stdlib.h>
#include "random.h"

extern void learn_model(double *y, double **features, int n_samples, int n_features, double **wa, double **wb, int iter, double eps, double sigma, char *model);
int update(double *w, int f, double *wa, double *wb, double *y, double **features, int n_samples, int n_features, double eps, double sigma);
double gammaglm_likelihood(double *wa, double *wb, double *y, double **features, int n_samples, int n_features);
double gamma_likelihood(double a, double b, double yn);
double lnorm(double w, double sigma);

#endif
