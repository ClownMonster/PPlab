#include<stdio.h>
#include<stdlib.h>
#include<omp.h>


void main()
{
    int r, c , v, i, j;
    printf("Enter row, col, vector size : ");
    scanf("%d%d%d", &r, &c, &v);
    int matrix[r][c], vector[v], result[v];
    if(r <= 0 || c <= 0 || v <= 0 || c!= v)
    {
        printf("\n Invalid");
        exit(0);
    }

    for(i = 0; i < r ; i++)
    {
        for(j = 0; j < c; j++ )
            {
                matrix[i][j] = rand()%100;
            }
    }

    for(i = 0; i < v; i++)
      {
          vector[i] = i*2;
          result[i] = 0;
      }  

   

    #pragma omp parallel for private(j)
    
        for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {

                result[i] = result[i] + matrix[i][j] * vector[j];

            }
        }

    

    printf("\n Result : \n");
    for(i = 0; i < v; i++)
        printf("%d\t",result[i]);


}
