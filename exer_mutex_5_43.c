#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE_POINTS 1011

int number_points = 0;
int number_points_circle = 0;
pthread_mutex_t lock;

void* calculate_monte_carlo(void *args);
double rand_0_to_1(void);

int main(){

    if(pthread_mutex_init(&lock, NULL) != 0){
        fprintf(stderr,"Erro ao criar o mutex!");
        exit(EXIT_FAILURE);
    }

    double pi;

    pthread_t thread_id[SIZE_POINTS];

    for(int i = 0; i < SIZE_POINTS; i++)
        pthread_create(&thread_id[i], NULL, calculate_monte_carlo, NULL);

    for(int i = 0; i < SIZE_POINTS; i++)
        pthread_join(thread_id[i], NULL);

    pi = 4 * (double)number_points_circle/ number_points;

    printf("A aproximação de PI com o modelo monte carlos é %lf\n", pi);

    pthread_mutex_destroy(&lock);

    return 0;
}

void *calculate_monte_carlo(void *args){

    pthread_mutex_lock(&lock);

    double x, y;

    x = rand_0_to_1();
    y = rand_0_to_1();

    if((x*x + y*y) <= 1)
        number_points_circle++;  

    number_points++;

    pthread_mutex_unlock(&lock);

    pthread_exit(0);

}

double rand_0_to_1(void)
{
    return rand() / ((double) RAND_MAX);
}