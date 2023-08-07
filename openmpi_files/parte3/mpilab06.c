#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>


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
    
    int respuesta=0;

    if(proceso==maestro){
       iniciar(vector,N); 
    }

    imprimir(proceso, "ANTES vector",vector, 0, N);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(vector, N, MPI_INT, maestro, MPI_COMM_WORLD); //nose,cantidad, tipo

    //imprimir(proceso, "DESPUES vector",vector, 0, N);
    int suma=0;
    int bloque = N/procesos;
    for(int i=proceso*bloque; i<(proceso+1)*bloque; i++){
        suma = suma+vector[i];
    }
    printf("Proceso %d suma = %d\n", proceso, suma);

    MPI_Finalize();
}







