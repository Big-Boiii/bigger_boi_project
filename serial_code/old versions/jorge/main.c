/* main.c - Poisson problem in 3D
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"
#include "initialize.h"

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

#define N_DEFAULT 100

int main(int argc, char *argv[]) {
    int     i, j, k;
    int 	N = N_DEFAULT;
    int 	iter_max = 1000;
    double	tolerance;
    double	start_T;
    int		output_type = 0;
    char	*output_prefix = "poisson_res";
    char        *output_ext    = "";
    char	output_filename[FILENAME_MAX];
    double 	***u = NULL, ***u_old = NULL, ***f = NULL;


    /* get the paramters from the command line */
    N         = atoi(argv[1]);	// grid size
    iter_max  = atoi(argv[2]);  // max. no. of iterations
    tolerance = atof(argv[3]);  // tolerance
    start_T   = atof(argv[4]);  // start T for all inner grid points
    if (argc == 6) {
	output_type = atoi(argv[5]);  // ouput type
    }

    // allocate memory
    if ( (u = d_malloc_3d(N, N, N)) == NULL ) {
        perror("array u: allocation failed");
        exit(-1);
    }

    if ( (u_old = d_malloc_3d(N, N, N)) == NULL ) {
        perror("array u_old: allocation failed");
        exit(-1);
    }

    if ( (f = d_malloc_3d(N, N, N)) == NULL ) {
        perror("array f: allocation failed");
        exit(-1);
    }

    // Initialize matrices
    initialize_f(f, N);    
    initialize_u(u, N, start_T);
    // initializing u_old not needed for serial version but we'll need it later for the NUMA version.

    // Call the functions
    #ifdef _JACOBI
    jacobi(u, u_old, f, N, iter_max, tolerance);
    #endif

    #ifdef _GAUSS_SEIDEL
    gauss_seidel(u, u_old, f, N, iter_max, tolerance);
    #endif


    // dump  results if wanted 
    switch(output_type) {
	case 0:
	    // no output at all
	    break;
	case 2:
        for(i = 0; i < N; i++){
            printf("%dth slice\n", i);
            for(j = 0; j < N; j++){
                for (k = 0; k < N; k++) {
                    printf("%.2f \t\t", u[i][j][k]);
                }
                printf("\n");
            }
            printf("\n\n");
        }
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
    free(u_old);
    free(f);

    return(0);
}
