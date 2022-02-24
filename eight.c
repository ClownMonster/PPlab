#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
    int rank, size, i , j;
    double mysum, allsum;
    double a[100], b[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0) 
    printf("Starting OMP dot product with tasks : %d", size);

    for(i = 0 ; i < 100; i++)
    {
        a[i] = 1.0;
        b[i] = a[i];
    }

    mysum = 0.0;

    for(i = 0; i < 100; i++)
    {
        mysum += a[i] * b[i];
    }

    printf("\n Task : %d partial sum is : %f", rank, mysum);

    MPI_Reduce(&mysum, &allsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0)
    {
        printf("\n Completed Process : Global Sum = %f", allsum);
    }

    MPI_Finalize();
}
