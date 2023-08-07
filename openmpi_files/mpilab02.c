#include "stdlib.h"
#include "stdio.h"
#include "mpi.h"

#define N 20

void iniciar_vector(int *v, int n);

void imprimir_vector(int *v, int n){
    for(int i=0; i<n; i++){
        printf("%i ",v[i]);
    }
    printf("\n");
}

int compara(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}


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

    int a[N];
    int *b;

    if (proceso == 0) {
        iniciar_vector(a,N);
        b = a + N/2;
        double inicio = MPI_Wtime();
        MPI_Send( b, N/2, MPI_INT, 1, 0, MPI_COMM_WORLD);
        qsort(a,N/2,sizeof(int),compara);
        MPI_Recv( b, N/2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double duracion = MPI_Wtime() - inicio;
        imprimir_vector(a,N);
        printf("Duracion: %lf segundos ",duracion);

    } else if (proceso == 1) {
        b = a + N/2;
        MPI_Recv( b, N/2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        qsort(b,N/2,sizeof(int),compara);
        MPI_Send( b, N/2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

void iniciar_vector(int *v, int n){
    double factor = 1.0/RAND_MAX;

    for(int i=0; i<n; i++){
        v[i] = (int) (1000.0 * rand()*factor);
    }
}

