#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void iniciar(int v[], int n){
    for(int i=0; i<n; i++){
        v[i] = i+1;
    }   
}

#define N 20
int vector[N];

int main ( int argc, char **argv ){
    int procesos, proceso, maestro=1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    
    if(proceso == maestro){
       iniciar(vector,N); 
    }

    MPI_Bcast(vector, N, MPI_INT, maestro, MPI_COMM_WORLD); //nose,cantidad, tipo

    int numero = vector[proceso%N];
    int suma=0, maximo=0;

    MPI_Reduce(&numero, &suma, 1, MPI_INT, MPI_SUM, maestro, MPI_COMM_WORLD);
    MPI_Reduce(&numero, &maximo, 1, MPI_INT, MPI_MAX, maestro, MPI_COMM_WORLD);
    
    printf("Proceso %d suma=%d maximo %d \n", proceso, suma, maximo);

    MPI_Finalize();
}







