/* main.c - Poisson problem in 3D
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

#define N_DEFAULT 100

void
assign_u(double*** u, int N){
	int i,j,k;
	for (i=0; i<N; i++){
		for (j=0;j<N;j++){
			for (k=0; k<N; k++){
				if (i==0 || i==N-1) u[i][j][k]=20;
				//comment: this here will do that at the edge of the wall the temperature is 0
				// (since it was not specified whether it should be 0 or 20)
				else if (j==0) u[i][j][k]=0;
				else if (j==N-1) u[i][j][k]=20;
				else if (k==0 || k==N-1) u[i][j][k]=20;
				else u[i][j][k]=0; 
			}
		}
	}
}

void assign_f(double*** f, int N){
	int i,j,k;
	for (i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){	
				double x=-1+i/(double)N;
				double y=-1+j/(double)N;
				double z= -1+k/(double)N;	
				if (x<= -3.0/8.0 && y<=-0.5 && z<=-2.0/3.0 && z<=0){
				f[i][j][k]=200;}
				else f[i][j][k]=0;
			}
		}
	}
}

void set_to_0(double*** A, int N){
	int i,j,k;
	for (i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){	
				A[i][j][k]=0;
			}
		}
	}
}
 //testing function: simply printing matrix
void print_matrix(double*** A, int N){
	int i,j,k;
	for (i=0; i<N; i++){
		printf("\n %d -th Layer \n", i);
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){	
				printf("%lf \t", A[i][j][k]);
			}
		printf("\n");
		}
	}
}

int
main(int argc, char *argv[]) {

    int 	N = 5;
    int 	iter_max = 10;
    double	tolerance = 5; //possibly initialize to avoid segmentation error 
    double	start_T;
    int		output_type = 0;
    char	*output_prefix = "poisson_res";
    char    *output_ext    = "";
    char	output_filename[FILENAME_MAX];
    double 	***u = NULL;


    /* get the paramters from the command line */
    N         = atoi(argv[1]);	// grid size
    iter_max  = atoi(argv[2]);  // max. no. of iterations
    tolerance = atof(argv[3]);  // tolerance
    start_T   = atof(argv[4]);  // start T for all inner grid points
    if (argc == 6) {
	output_type = atoi(argv[5]);  // ouput type
    }
	printf("This has started successfully! \n");
    //allocate memory
    if ( (u = d_malloc_3d(N, N, N)) == NULL ) {
        perror("array u: allocation failed");
        exit(-1);
    }
	printf("Tolerance is %lf \n", tolerance);
	printf("Size of matrix %d \n", N);
	//allocate f	
    double*** f=d_malloc_3d(N,N,N);
    //assign f
    assign_f(f,N);

	//set boundaries of u to given values, rest to 0
	assign_u(u,N);
	//assign f and prev_u --> only initialize prev_u
	//initialze u with 0 to create first touch for NUMA
	#if _GAUSS_SEIDEL
	printf("We are now doing a Gauss-Seidel Magic Trick");
	double* norm =&tolerance;
	gauss_seidel(u,f, N,iter_max, tolerance);
	print_matrix(u,N);
	#endif
	#if _JACOBI
	printf("We are going to perform a magic Jacobi Trick");
	//only allocate prev_u here:
	double*** prev_u=d_malloc_3d(N,N,N);
	assign_u(prev_u,N);
	double* norm = &tolerance;
	//set_to_0(prev_u,N);
	jacobi(u,prev_u,f,N, iter_max,tolerance);
	print_matrix(u,N);
	#endif
	
    /*
     * first: set boundaries of u to desired values, rest to 0
     * call function
     *
     * fill in your code here 
     *
     *
     */
	//while(norm < tolerance
    // dump  results if wanted 
    switch(output_type) {
	case 0:
	    // no output at all
	    break;
	case 3:
	    output_ext = ".bin";
	    sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
	    fprintf(stderr, "Write binary dump to %s: ", output_filename);
	    print_binary(output_filename, N, u);
	    break;
	case 4:
	    output_ext = ".vtk";
	    sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
	    fprintf(stderr, "Write VTK file to %s: ", output_filename);
	    print_vtk(output_filename, N, u);
	    break;
	default:
	    fprintf(stderr, "Non-supported output type!\n");
	    break;
    }

    // de-allocate memory
    free(u);

    return(0);
}
