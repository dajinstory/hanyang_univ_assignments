#include <math.h>
#include <malloc.h>
#include <stdlib.h>

#define SWAP(a,b) {float temp=(a);(a)=(b);(b)=temp;}

int* ivector(int s, int e){
	int* arr;
	int idx, size=e-s+1;

	arr = (int *)malloc(sizeof(int)*size);
	for(idx=0;idx<size;idx++){
		arr[idx]=s+idx;
	}
	return arr;
}

void free_ivector(int* arr){
	free(arr);
}

void nrerror(char error_text[]) {
    printf("[calculating error] %s\n", error_text);
    //exit(1);
}

void gaussj(float** a, int n, float** b,int m)
{
	int *indxc,*indxr,*ipiv;
	int i,icol,irow,j,k,l,ll;
	float big,dum,pivinv;

	indxc=ivector(1,n);
	indxr=ivector(1,n);
	ipiv=ivector(1,n);
	for (j=1;j<=n;j++) ipiv[j]=0;
	for (i=1;i<=n;i++) {
		big=0.0;
		for (j=1;j<=n;j++)
			if (ipiv[j] != 1)
				for (k=1;k<=n;k++) {
					if (ipiv[k] == 0) {
						if (fabs(a[j][k]) >= big) {
							big=fabs(a[j][k]);
							irow=j;
							icol=k;
						}
					} else if (ipiv[k] > 1) nrerror("GAUSSJ: Singular Matrix-1");
				}
		++(ipiv[icol]);
		if (irow != icol) {
			for (l=1;l<=n;l++) SWAP(a[irow][l],a[icol][l])
			for (l=1;l<=m;l++) SWAP(b[irow][l],b[icol][l])
		}
		indxr[i]=irow;
		indxc[i]=icol;
		if (a[icol][icol] == 0.0) nrerror("GAUSSJ: Singular Matrix-2");
		pivinv=1.0/a[icol][icol];
		a[icol][icol]=1.0;
		for (l=1;l<=n;l++) a[icol][l] *= pivinv;
		for (l=1;l<=m;l++) b[icol][l] *= pivinv;
		for (ll=1;ll<=n;ll++)
			if (ll != icol) {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for (l=1;l<=n;l++) a[ll][l] -= a[icol][l]*dum;
				for (l=1;l<=m;l++) b[ll][l] -= b[icol][l]*dum;
			}
	}
	for (l=n;l>=1;l--) {
		if (indxr[l] != indxc[l])
			for (k=1;k<=n;k++)
				SWAP(a[k][indxr[l]],a[k][indxc[l]]);
	}
	free_ivector(ipiv);
	free_ivector(indxr);
	free_ivector(indxc);
}

#undef SWAP
