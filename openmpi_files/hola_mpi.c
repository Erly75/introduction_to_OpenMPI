#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main ( int argc, char **argv ){
    int ierr;
    int yo;
    int todos;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &yo);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &todos);

    printf("Proceso -> %i de -> %i procesoS \n", yo, todos);

    for(int i=0; i<100000; i++){
        for(int j=0; j<10000; j++){
            pow(4000.0*i,i/5.5);
        }
    }   

    ierr = MPI_Finalize();
}
