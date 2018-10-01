#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int number_points = 0;
int number_points_circle = 0;

void* calculate_monte_carlo(void *args);
double rand_0_to_1(void);

int main(){

    double pi;

    pthread_t thread_id;

    pthread_create(&thread_id, NULL, calculate_monte_carlo, NULL);

    pthread_join(thread_id, NULL);

    pi = 4 * (double)number_points_circle/ number_points;

    printf("A aproximação de PI com o modelo monte carlos é %lf\n", pi);

    return 0;
}

void *calculate_monte_carlo(void *args){

    double x, y;

    for(int i = 0; i < 100000000; i++){

        x = rand_0_to_1();
        y = rand_0_to_1();

        if((x*x + y*y) <= 1){
            number_points_circle++;  
        }

        number_points++;
    }

    pthread_exit(0);

}

double rand_0_to_1(void)
{
    return rand() / ((double) RAND_MAX);
}