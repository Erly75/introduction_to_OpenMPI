#include "stdlib.h"
#include "stdio.h"
#include "mpi.h"

int main ( int argc, char **argv ){
    MPI_Init(NULL, NULL);

    int proceso, procesos, longitud;
    char equipo[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(equipo, &longitud);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso); 


    if (procesos < 2) {
        printf("Debo tener al menos 2 procesos\n");
        MPI_Abort(MPI_COMM_WORLD,1);
        return 0;
    }

    if (proceso == 0) {
        int mensaje = 1000;
        MPI_Send(&mensaje, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("envie el mensaje %i al proceso %i \n", mensaje, 1);
    } else if (proceso == 1) {
        int recibido = -1;
        MPI_Recv(&recibido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Recibi el mensaje %i desde el proceso %i \n", recibido, 0);
    } else{
        printf("soy el proceso %i de %i procesos \n", proceso, procesos);
    }

    MPI_Finalize();
}
