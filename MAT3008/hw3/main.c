#include <stdio.h>
#include <string.h>
#include "functions.c"
#include "methods.c"
#define ABS(X) (X < 0 ? -X : X)
#define EPSILON 0.000001
#define NB 200
#define N 10000


// original function and function to be used with determinating
typedef void(*funcdPtr)(float,float*,float*);

// two function
typedef struct funcd{
	funcdPtr ptr;
	char* name;
	float lx;
	float rx;
}funcd;

// method pointer. for Linear Interpolation, secant, bisection
typedef float(*method_ptr)(funcdPtr, float, float, float, int*);

// method struct
typedef struct method{
	method_ptr ptr;
	char* name;
}method;


int main(){
	funcd functions[5] = {
		{bessel, "Bessel function", 1.0, 10.0}, 
		{myfunc_1, "myfunc_1", 0.1, 1.0}, 
		{myfunc_2, "myfunc_2", 0.0, 1.0}, 
		{myfunc_3, "myfunc_3", -2.0, -1.0},
		{myfunc_4, "myfunc_4", -1.0, 1.0}
	};	
	method methods[6] = {
		{rtbis, "Bisection"}, 
		{rtflsp, "Linear Interpolation"}, 
		{rtsec, "Secant"}, 
		{rtnewt, "Newton-Raphson"}, 
		{rtsafe, "Newton with Bracketing"},
		{muller, "Muller"}
	};

	int n=N, nb=NB;
	float xb1[NB], xb2[NB];
	float xacc=1e-6;
	
	float answer;
	int iter=-1;
	
	// select function
	for(int i=0;i<5;i++){
		funcdPtr func = functions[i].ptr;
		char* func_name = functions[i].name;
		float lx = functions[i].lx;
		float rx = functions[i].rx;
		
		printf("\n\n###%d function: %s\n", i+1, func_name);
		
		// set xb
		zbrak(func, lx, rx, n, xb1, xb2, &nb);
		// select method
		for(int j=0;j<6;j++){
			method_ptr method_function = methods[j].ptr;
			char* method_name = methods[j].name;
			
			printf("\n--method: %s\n", method_name);
			// solve problem
			for(int k=1;k<=nb;k++){
				answer = method_function(func, xb1[k], xb2[k], xacc, &iter);
				
				// check if selected method failed
				if(iter==-1)continue;
				printf("- area #%d:\t\tanswer : %.23f\t\titeration time: %d\n", k, answer, iter);
			}
		}
	}
	
	return 0;
}
