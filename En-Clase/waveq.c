#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FLOAT float
#define PI 3.141592


FLOAT * get_memory(int n_points){
    FLOAT * x;
    if(!(x = malloc(sizeof(FLOAT) * n_points))){
        printf("problem with memory allocation");
        exit(1);
    }
    return x;
}

void copy(FLOAT *u, FLOAT *u_past, int n_points){
    
    int i;
    for(i=0;i<n_points;i++){
        u_past[i] = u[i];
    }
}



int main(int argc, char **argv){

    
    int n_points = 80; //n_points in x
    int n_t = 300;
    
    FLOAT *x;
    FLOAT *u;
    FLOAT *u_past;
    FLOAT dx;
    FLOAT dt;
    FLOAT c = 1.0;
    x = get_memory(n_points);
    u = get_memory(n_points);
    u_past = get_memory(n_points);
    int i,j;
    
    x[0] = 0.0;
    
    for (i=0; i<n_points; i++) {

        
        
        u[i] = 1.0;
        
        if (i!=0) {
        x[i] = x[i-1] + (2.0)/n_points;
            
        if(x[i]<1.25 && x[i]>0.75){
            u[i] = 2.0;
            }
        }
    }
    
    dx = x[1]-x[0];
    dt = 0.001;
    printf("%f\n", c*dt/dx);
    for(i=0;i<n_t;i++){
        copy(u, u_past, n_points);
        for(j=1;j<n_points-1;j++){
            u[i] = u_past[i] - c*dt/dx * (u_past[i]-u_past[i-1]);
        }
    }
    
    
    FILE *in = fopen("datos.dat","w");
    
    
    for(i=0;i<n_points;i++){
        fprintf(in,"%f %f \n",x[i],u[i]);
    }
    
    
    
    fclose(in);
    
    return 0;
    
    
}
