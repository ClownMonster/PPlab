#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int arr[], int x1, int y1, int x2, int y2)
{
    int p= x1, q = x2, k = 0, i, j , temp[1000];

    while(p <= y1 && q <= y2)
    {
        if(arr[p] < arr[q])
            temp[k++] = arr[p++];
        
        else
            temp[k++] = arr[q++];
        
    }

    while(p <= y1)
     {
        temp[k++] = arr[p++];
    }

    while(q <= y2) 
    {
    temp[k++] = arr[q++];

    }

    for(i = x1, j = 0; i <= y2; i++, j++)
    {
        arr[i] = temp[j];
    }






}



void mergesort(int arr[], int p, int q)
{
    int mid = 0;

    if(p < q)
    {
        mid = (p+q)/2;

        #pragma omp parallel sections
        {
            
            #pragma omp section
            {
                printf("\nProcessor at left part : %d\n", omp_get_thread_num());
                mergesort(arr, p, mid);
            }

            #pragma omp section
            {
                printf("Processor at right part : %d\n", omp_get_thread_num());
                mergesort(arr, mid+1, q);
            }

        }

        merge(arr, p, mid, mid+1, q);


    }
}



int main()
{

    int n , i ;
    printf("Enter the number of elements : ");
    scanf("%d", & n);
    int arr[n];
    for(i= 0; i < n; i++)
        arr[i] = rand()%100;
    
    printf("\nUn sorted arry : \n");
    for(i = 0 ; i < n; i ++)
    {
        printf("%d\t",arr[i] );
    }

    mergesort(arr,0, n-1);

    printf("\n Sorted array : \n");
    for(i = 0; i < n ; i++)
    {
        printf("%d\t",arr[i] );
    }


    return 0;
}
