/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <stdio.h>
#include <math.h>


initial(double start_T,int N, double ***u, double ***f){
	int i,j,k;
	
	/*step is equal to step=(1-(-1))/(N-1)*/
	double step= 2./(N);
	
	/*the limits are (given_limit-(-1))/(step)*/	
	
	//int limitXup=round(/step); //(0.622)=(-0.378+1)
	int limitXup=3;
	int limitYup=round(0.5/step);	//0.5=(-0.5)+1
	int limitZlow=round(0.333/step); //0.65=-(2/3)+1
	int limitZup=round(1/step); //0.65=-(2/3)+1


	
	
	printf("to step einai %f\n",step);
	printf("to anw orio gia to x einai %d\n",limitXup);
	printf("to anw orio gia to y einai %d\n",limitYup);
	printf("to katw orio gia to z einai %d\n",limitZlow);
	printf("to anw orio gia to z einai %d\n",limitZup);

	
	//initialize u and f based on the boundary conditions
	for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				for(k=0;k<N;k++){
					u[i][j][k]=start_T;
					f[i][j][k]=0;
				}
				
			}
		}

	

	for(i=0;i<N;i++){
            for(j=0;j<N;j++){
		
		
		u[i][0][j]=0.;
		u[i][N-1][j]=20.;

		u[i][j][0]=20.;
		u[i][j][N-1]=20.;

		u[0][i][j]=20.;
                u[N-1][i][j]=20.;
		
		
	        }
		
            }


	/*

            for(j=0;j<N;j++){
		//katw epipedo grammh
		u[N-1][0][j]=20.;
		//deksia gwnia 
		u[j][0][N-1]=20.;
		}
*/
		
	for(i=0;i<limitXup;i++){
			for(j=0;j<limitYup;j++){
				for(k=limitZlow;k<limitZup;k++){
					f[i][j][k]=200.;
				}
			}
		}
	
	

}

int
jacobi(double start_T,int N,double tolerance,int iter_max, double ***u, double ***f,double *** uOld) {
    
	int k1=0;
	double norm=100000000000000000;
	double h=1/6.;
	double delta=1/N;
	int i,j,k;
	

	/*step is equal to step=(1-(-1))/(N-1)*/
	
	double step= 2./(N);
	
	initial(start_T,N, u, f);
	
	
	while (/*(norm>tolerance)&&*/(k1<iter_max)){
		
		double sum_of_sq=0;
		int temp;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				for(k=0;k<N;k++){
					uOld[i][j][k]=u[i][j][k];
				}
			}
		}
		
		for(i=1;i<N-1;i++){
		   for(j=1;j<N-1;j++){
			for(k=1;k<N-1;k++){
				temp=uOld[i-1][j][k]+uOld[i+1][j][k]+uOld[i][j-1][k]+uOld[i][j+1][k]+uOld[i][j][k-1]+uOld[i][j][k+1]+step*step*f[i][j][k];
				u[i][j][k]=temp*h;
				sum_of_sq+= u[i][j][k]*u[i][j][k]-uOld[i][j][k]*uOld[i][j][k];
				}
			}
		}
		
	
		norm=sqrt(sum_of_sq);
		k1=k1+1;
	}
return k1;
}
