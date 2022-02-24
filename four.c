#include<stdio.h>
#include<stdlib.h>
#include<omp.h>


int main()
{
    int i, fact1= 1, fact2 = 1, a = 0 ;
    printf("\nEnter the element : ");
    scanf("%d", &a);

    #pragma omp parallel for firstprivate(a)
    for(i = 2; i <= a; i++) fact1 = fact1 * i;

    printf("\n When 1st private is not used : fact = %d", fact1);


    #pragma omp parallel for firstprivate(a, fact2)
    for(i = 2; i <= a; i++) fact2 = fact2 * i;

    printf("\n When 1st private is  used : fact = %d", fact2);

    return 0;
}
