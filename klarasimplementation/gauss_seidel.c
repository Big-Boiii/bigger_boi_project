/* gauss_seidel.c - Poisson problem in 3d
 *
 */
/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <math.h>
#include <limits.h>

double iteration_step(double*** u, double*** f, int N){
	double squarednorm=0.0;
	double step_width=2./(double)N;
	int i,j,k;
	for (i=1; i<N-1; i++){
		for (j=1; j<N-1; j++){
			for (k=1; k<N-1; k++){
				double placeholder=u[i][j][k];
				double temp=u[i-1][j][k] + u[i+1][j][k]+ u[i][j-1][k] + u[i][j+1][k] + u[i][j][k-1] + u[i][j][k+1] + step_width*step_width*f[i][j][k];
				u[i][j][k]=temp * 0.5*step_width;
				placeholder-=u[i][j][k];
				squarednorm+=placeholder*placeholder;
			}
		}
	}
	return squarednorm;
}


void
gauss_seidel(double*** u, double*** f, int N, int iter_max, double tolerance) {
  double realnorm= tolerance+1;
  //setting the walls of the cube
  //iteration: checking norm and Nr of iterations at the same time
	int i=0;
	//while (*norm < tolerance || i<iter_max){
	while(i<iter_max && realnorm > tolerance){
		realnorm=iteration_step(u,f,N);
		printf("realnorm %lf \n", realnorm);
		i++;
		}
	printf("We needed %d iterations to converge \n", i);


    // fill in your code here
}

