#include <stdio.h>

void initialize_f(double ***f, int N) {
    int i, j, k;
    int radxi = 0,
        radxf = (5 * N)/16, // (-3/8 + 1) * N/2
        radyi = 0,
        radyf = N/4, // (_1/2 + 1) * N/2
        radzi = N/6 + (N%6 > 0), // (-2/3 + 1) * N/2 truncating upwards if there's some remainder.
        radzf = N/2; // (0 + 1) * N/2
    
    printf("X: %d - %d. Y: %d - %d. Z: %d - %d\n", radxi, radxf, radyi, radyf, radzi, radzf);
    // This loop may be completely useless
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                f[i][j][k] = 0;
            }
        }
    }

    for (i = radxi; i <= radxf; i++) {
        for (j = radyi; j <= radyf; j++) {
            for (k = radzi; k <= radzf; k++) {
                f[i][j][k] = 200;
            }
        }
    }

}

void initialize_u(double ***u, int N, double start_T) {
    int i, j, k;

    // First we initialize everything to temperature start_T
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                u[i][j][k] = start_T;
            }
        }
    }

    // We set the walls x=-1 and x=1
    for(j = 0; j < N; j++) {
        for (k = 0; k < N; k++) {
            u[0][j][k] = 20;
            u[N-1][j][k] = 20;
        }
    }

    // We set the walls y=-1 y=1
    for (i = 1; i < N-1; i++){
        for (k = 0; k < N; k++){
            u[i][0][k] = 0;
            u[i][N-1][k] = 20;
        }
    }

    // Lastly, the walls z=-1 and z=1
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            u[i][j][0] = 20;
            u[i][j][N-1] = 20;
        }
    }

    // for (i = 0; i < N; i++) {
    //     for (j = 0; j < N; j++) {
            
    //         u[i][0][j] = 0;
    //         u[i][N-1][j] = 20;

    //         u[0][i][j] = 20;
    //         u[N-1][i][j] = 20;

    //         u[i][j][0] = 20;
    //         u[i][j][N-1] = 20;
    //     }
    // }

}
