#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"

void reset_matrix(int n, int k, double **C){
    for (int i=0; i<n; i++){
        for (int j=0; j<k; j++){
            C[i][j]=0;
        }
    }
}


void assign(double*** arr, int m, int n, int k)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int h=0; h<k; h++)
			arr[i][j][h]=f(i,j,h);
		}
	}
}
 
 int main(int argc, char *argv[]){
   int m =10;
   int n=10;
   int k=10;
   char fname='f';
   double ***A = d_malloc_3d(m,n,k);
   assign(A,m,n,k);
   print_vtk(&fname, 100, A);

    return 0;
 }
