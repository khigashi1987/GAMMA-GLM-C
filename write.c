/*
 * write.c
 */
#include <stdio.h>
#include <stdlib.h>

void save_model(char *model, double *wa, double *wb, int n_features){
    char outfilename[100];
    FILE *ofp;
    int i;
    
    sprintf(outfilename,"%s.tsv",model);
    if(NULL == (ofp = fopen(outfilename,"w"))){
        fprintf(stderr,"write:: cannot open %s\n",outfilename);
        exit(1);
    }
    
    for(i = 0;i < n_features;i++){
        fprintf(ofp,"%.8f\t%.8f\n",wa[i],wb[i]);
    }
    fclose(ofp);
}
