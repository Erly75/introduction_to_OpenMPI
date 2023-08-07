#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void iniciar(int v[], int n){
    for(int i=0; i<n; i++){
        v[i] = i+1;
    }   
}

void imprimir(int pro, char *tit, int vec[], int ini, int fin){
    printf("Proceso %d [%s] = {", pro, tit);
    for(int i=ini; i<fin; i++){
        printf("%4d ",vec[i]);
    }
    printf("}\n");
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
       imprimir(proceso, "vector", vector, 0, N);
    }

    MPI_Bcast(vector, N, MPI_INT, maestro, MPI_COMM_WORLD); //nose,cantidad, tipo

    //imprimir(proceso, "DESPUES vector",vector, 0, N);
    int suma=0;
    int bloque = N/procesos;
    for(int i=proceso*bloque; i<(proceso+1)*bloque; i++){
        suma = suma+vector[i]; 
    }
    
    printf("proceso %d suma -> %d \n", proceso, suma);
    
    if(proceso == maestro){
        int total = suma;
        for(int i=0; i<procesos; i++){
            if(i != maestro){
                MPI_Recv(&suma, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                total += suma;
            }
        }
        printf("Suma total = %d \n", total);
    } else {
        MPI_Send(&suma, 1, MPI_INT, maestro, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}







