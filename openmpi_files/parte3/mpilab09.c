#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void imprimir(int pro, char *tit, int vec[], int ini, int fin){
    printf("Proceso %d [%s] = {", pro, tit);
    for(int i=ini; i<fin; i++){
        printf("%4d ",vec[i]);
    }
    printf("}\n");
}

void iniciar(int v[], int n){
    for(int i=0; i<n; i++){
        v[i] = i+1;
    }   
}

void iniciar2(int pro, int v[], int n){
    for(int i=0; i<n; i++){
        v[i] = (pro+1)*10 + (i+1);
    }   
}
#define N 20
int fuente[N];
int destino[N];

int main ( int argc, char **argv ){
    int procesos, proceso, maestro=1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    
    iniciar2(proceso, fuente, N);

    imprimir(proceso, "fuente", fuente, 0, N);
    MPI_Reduce(fuente, destino, N, MPI_INT, MPI_SUM, maestro, MPI_COMM_WORLD);
    
    imprimir(proceso,"destino", destino, 0, N);

    MPI_Finalize();
}







