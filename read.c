/*
 * read.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read.h"

#define BUFFSIZE 65536

void read_data(char *train, double **y, double ***features, int *n_samples, int *n_features){
    FILE *fp;
    char buf[BUFFSIZE];
    int i,j;
    
    if((fp = fopen(train,"r")) == NULL){
        fprintf(stderr,"read.c: cannot open train data file.\n");
        exit(1);
    }
    
    (*n_samples) = count_lines(fp);
    (*n_features) = count_fields(fp);
    
    (*y) = (double *)calloc((*n_samples),sizeof(double));
    (*features) = (double **)calloc((*n_samples),sizeof(double *));
    for(i = 0;i < (*n_samples);i++){
        (*features)[i] = (double *)calloc((*n_features),sizeof(double));
    }
    
    i = 0;
    while(NULL != fgets(buf,sizeof(buf),fp)){
        if(buf[0] == '#') continue;
        char *lp = buf;
        char *sp = buf;
        j = 0;
        while(*lp){
            if((sp = strpbrk(lp, " \t\n")) == NULL)
                break;
            *sp = '\0';
            if(j == 0){
                (*y)[i] = atof(lp);
            }else{
                (*features)[i][j-1] = atof(lp);
            }
            lp = sp + 1;
            j++;
        }
        (*features)[i][(*n_features)-1] = 1.0; // add constant
        i++;
    }
    return;
}

int count_lines(FILE *fp){
    int n = 0;
    char buf[BUFFSIZE];
    while(NULL != fgets(buf, sizeof(buf), fp)){
        if(buf[0] == '#') continue;
        n++;
    }
    rewind(fp);
    return n;
}

int count_fields(FILE *fp){
    int n = 0;
    char buf[BUFFSIZE];
    while(NULL != fgets(buf, sizeof(buf), fp)){
        char *lp = buf;
        char *sp = buf;
        while(*lp){
            if((sp = strpbrk(lp, " \t\n")) == NULL)
                break;
            *sp = '\0';
            lp = sp + 1;
            n++;
        }
        break;
    }
    rewind(fp);
    return n;
}
