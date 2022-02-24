#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int primes[1000];
double sines[1000];

void prime_table(int l)
{
    int i = 2 , j, p = 0, prime;
    while(p < l)
    {
        prime = 1;
        for( j = 2; j < i ; j++)
        {
            if( (i % j) == 0)
            {
                prime = 0;
                break;
            }
        }

        if(prime)
        {
            primes[p] = i;
            p++;
        }

        i++;
    }

}



void sine_table(int k)
{
    int m;
    for(m = 0; m < k; m++)
        sines[m] = sin(m*M_PI/180);
}


int main()
{
    int s, i, j;
    printf("\n Enter the size of sine and prime tables required : ");
    scanf("%d", &s);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            prime_table(s);
            printf("\n Prime Table : \n");
            for(i = 0; i < s; i++)
                printf("%d\t", primes[i]);
        }

        #pragma omp section
        {
            sine_table(s);
            printf("\n Sine Table : \n");
            for(j = 0; j < s; j++)
                printf("%lf\t",sines[j]);
        }
    }


    return 0;
}
