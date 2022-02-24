#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define BS sizeof(int)*4

int main()
{
    int rank, i, j , k;
    int a[2][2] = {{1,2},{3,4}}
    int b[2][2] = {{1,0},{0,1}}
    int c[2][2] = {{0,0},{0,0}}

    MPI_Init(NULL,NULL);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0)
    {
        for(i = 0; i < 2; i++)
        {
            for(j = 0; j < 2; j++)
            {
                c[i][j] = 0;
                for(k=0; k < 2; k++)
                {
                    c[i][j] += a[i][k]*b[k][j]
                }
            }
        }

        MPI_Send(&c,BS,MPI_INT,1,0,MPI_COMM_WORLD);

    }
    
    else if(rank == 1)
    {
        MPI_Recv(c,BS,MP_INT,0,0,MPI_COMM_WORLD,&status);
        for(i = 0; i < 2; i++)
        {
            for(j = 0; j < 2 ; j++)
            {
                printf("%d\t", c[i][j]);
            }
            printf("\n");
        }

    }



    MPI_Finalize();
    return 0;
}
