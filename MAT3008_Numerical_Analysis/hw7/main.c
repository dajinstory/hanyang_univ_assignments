#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gasdev.c"
#include "jacobi.c"
#include "eigsrt.c"
#define NSIZE 11

typedef double(*funcPtr)(double, double, int*);
typedef struct distributor{
    funcPtr func;
    char* name;
    double arg1;
    double arg2; 
} distributor;

double uniform_random(double l, double r, int* idum);
double gaussian_random(double  m, double s, int* idum);
void make_distribution(distributor generator, int sections, int samples);

int main(){
    distributor distributors[2] = {
        { uniform_random, "Uniform Distribution", -3.0, 2.0 },
        { gaussian_random, "Gaussian Distribution", -0.5, 1.5 }
    }; 

    int idum, nrot, n=NSIZE;
    float** matrix;
    float** eigenvector;
    float eigenvalue[NSIZE+1];

    matrix = (float**)malloc(sizeof(float*)*(NSIZE+1));
    eigenvector = (float**)malloc(sizeof(float*)*(NSIZE+1));
    for(int i=0;i<n+1;i++){
        matrix[i] = (float*)malloc(sizeof(float)*(NSIZE+1));
        eigenvector[i] = (float*)malloc(sizeof(float)*(NSIZE+1));
    }

    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            matrix[i][j]=matrix[j][i]=gaussian_random(0,1.0,&idum);
        }
    }

    jacobi(matrix, n, eigenvalue, eigenvector, &nrot);
    eigsrt(eigenvalue, eigenvector, n);
    for(int i=1;i<=n;i++){
        printf("\nvalue: %f\nvector: ", eigenvalue[i]);
        for(int j=1;j<=n;j++) printf("%f ", eigenvector[i][j]);
    }

    return 0;
}

double uniform_random(double l, double r, int* idum){
    double p = ran1(idum);
    return l + (r-l)*p;
}
double gaussian_random(double  m, double s, int* idum){
    double n = gasdev(idum);
    return n*s + m;
}