/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <stdio.h>
#include <math.h>

double sqr(double number){
    return number * number;
}

void copy_matrix(double ***original, double ***copy, int size) {
    // Copies the content in original to copy
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                copy[i][j][k] = original[i][j][k];
            }
        }
    }
}

void jacobi_step(double ***u, double ***u_old, double ***f, int N) {
    // Performs an iteration over u taking the values on u_old
    int     i, j, k;
    double  lambda = 2.0/N,
            lambda_2 = sqr(lambda),
            coef = 1.0/6.0,
            temp;
    
    for (i = 1; i < N - 1; i++) {
        for (j = 1; j < N - 1; j++) {
            for (k = 1; k < N - 1; k++) {
                temp = u_old[i-1][j][k] + u_old[i+1][j][k] + u_old[i][j-1][k] + u_old[i][j+1][k] + u_old[i][j][k-1] + u_old[i][j][k+1] + lambda_2*f[i][j][k];
                u[i][j][k] = temp *coef;
            }
        }
    }
}

double get_norm(double ***u, double ***u_old, int N) {
    int i, j, k;
    double norm_2 = 0.0;
    
    for (i = 1; i < N - 1; i++) {
        for (j = 1; j < N - 1; j++) {
            for (k = 1; k < N - 1; k++) {
                norm_2 += sqr(u[i][j][k] - u_old[i][j][k]);
            }
        }
    }

    return sqrt(norm_2);
}

void jacobi(double ***u, double ***u_old, double ***f, int N, int iter_max, double tolerance) {
    // while loop that performs iterations over jacobi_step until iter_max is reached or we get the norm smaller than the tolerance
    int iter_no = 0;
    double norm = 2000;

    while (norm > tolerance && iter_no < iter_max) {
        copy_matrix(u, u_old, N);
        jacobi_step(u, u_old, f, N);
        norm = get_norm(u, u_old, N);
        iter_no += 1;
    }
    // if (norm <= tolerance) {
    //     printf("The tolerance has been reached. Norm: %.2f/%.2f\n", norm, tolerance);
    // }
    // if (iter_no >= iter_max) {
    //     printf("Max number of iterations reached! %d/%d\n", iter_no, iter_max);
    // }
    printf("Tolerance reached: %.2f/%.2f. Iterations needed: %d/%d.\n", norm, tolerance, iter_no, iter_max);
}
