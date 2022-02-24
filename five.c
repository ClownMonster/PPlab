#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<float.h>
#include<time.h>
#include<math.h>

#define K 4

int num_threads;
long num_points, cluster_count[K];
long datapoints[100][2];

int cluster[K][2] = {{75,25},{25,25},{25,75},{75,75}};

void populate()
{
    int i ;

    #pragma omp parallel 
    for(i = 0; i < num_points; i++)
    {
        datapoints[i][0] = rand()%100;
        datapoints[i][1] = rand()%100;


    }

    for(i = 0; i < 4; i++)
    {
        cluster_count[i] = 0;
    }
}


double get_distance(int x1, int y1, int x2, int y2)
{
    int dx = x2-x1 , dy = y2-y1;
    return ((double)sqrt(dx*dx + dy*dy));

}


void classify()
{
    long i;
    int j, cluster_idx;
    double cur_dis = 0, min_dis = 999;

    #pragma omp parallel for private(cluster_idx, i, j, cur_dis, min_dis)
    for(i = 0; i < num_points; i++)
    {
        cluster_idx = -1;
        cur_dis = 0, min_dis = 999;

        for(j = 0; j < K; j++)
        {
            cur_dis = get_distance(datapoints[i][0], datapoints[i][1], cluster[j][0], cluster[j][1]);

            if(cur_dis < min_dis)
            {
                min_dis = cur_dis;
                cluster_idx = j;
            }

        }

        printf("\n%ld %ld belongs to %d %d\n",datapoints[i][0], datapoints[i][1],
         cluster[cluster_idx][0], cluster[cluster_idx][1]);

         cluster_count[cluster_idx]++;
    }




}

void main()
{
    printf("Maximum Number of threads :%d\n ", omp_get_max_threads());

    printf("\n Enter the number of points : ");
    scanf("%ld",&num_points);
    populate();

    double t1 = omp_get_wtime();

    classify();

    double t2 = omp_get_wtime();

    printf("\nTime Taken : %lf", t2-t1);

    int i = 0;
    printf("\nCounts : \n");
    while(i < 4)
    {
        printf("%d -> %ld \n", i, cluster_count[i++]);
    }



}
