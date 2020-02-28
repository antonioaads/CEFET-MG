#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void main(void){
    int i=1;
    double pi=0, aux1=1;

    #pragma omp parallel
    {
        #pragma omp for
        for(i=1;i<=100000;i++){
            if(i%2!=0)
                pi=pi+4/aux1;
            else
                pi=pi-4/aux1;

            aux1=aux1+2;
        }
    }
    printf("\n\n%.10f\n\n",pi);
}