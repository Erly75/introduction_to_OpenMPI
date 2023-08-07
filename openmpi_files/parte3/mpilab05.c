#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>

int main ( int argc, char **argv ){
    int procesos, proceso;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    
    int respuesta=0;

    if(proceso==0){
        FILE *file = fopen("mpilab05.txt","r");
        assert(file!=NULL);
        fscanf(file, "%d", &respuesta);
        fclose(file);
    }

    printf("ANTES: proceso %d respuesta %d \n", proceso, respuesta);

    MPI_Bcast(&respuesta, 1, MPI_INT, 0, MPI_COMM_WORLD); //nose,cantidad, tipo

    printf("DESPUES: proceso %d respuesta %d \n", proceso, respuesta);

    MPI_Finalize();
}
