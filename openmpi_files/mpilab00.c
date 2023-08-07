#include <stdio.h>
#include <mpi.h>

int main( int argc, char **argv){
  int ierr;
  int yo;
  int todos;

  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &yo);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &todos);
  
  printf("soy el proceso %i de %i procesos \n", yo, todos);

  ierr = MPI_Finalize();
}
